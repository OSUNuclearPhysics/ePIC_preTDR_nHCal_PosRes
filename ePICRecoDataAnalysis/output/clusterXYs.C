#include <TFile.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TH1.h>
#include "style.C"

bool matchesPattern(const TString& str) {
    TRegexp pattern("Phi.*Theta.*");
    return str.Index(pattern) != -1;
}

float converttorad(float theta) {
    theta = theta * TMath::Pi() / 180;
    /////return -TMath::Log(TMath::Tan(theta/2));
    return theta;
}

TH2D* convertmmtocm(TH2D* histogram, TString name) {
    TString midname = histogram->GetName();
    TH2D* h2D = new TH2D("hPosition_HCal_Reco" + name, "Position in HCal", (histogram->GetNbinsX())*10, -500, 500, (histogram->GetNbinsY())*10, -500, 500);
    h2D->SetStats(0);
    h2D->SetTitle("");
    h2D->GetXaxis()->SetTitle("X [cm]");
    h2D->GetYaxis()->SetTitle("Y [cm]");
    h2D->GetYaxis()->SetTitleOffset(1.40);
    


    // Loop over the bins of the TH2D and fill the TH2D with bincontents
    for (int i = 1; i <= histogram->GetNbinsX(); i++) {
        for (int j = 1; j <= histogram->GetNbinsY(); j++) {
            double x = histogram->GetXaxis()->GetBinCenter(i);
            double y = histogram->GetYaxis()->GetBinCenter(j);
            h2D->Fill(x/10.0, y/10.0, histogram->GetBinContent(i, j));
        }
    }

    return h2D;


}

float converttoRcoord(float x, float y) {
    return sqrt(x*x + y*y);
}

TH1D* converttoR(TH2D* histogram, TString name) {
    TString midname = histogram->GetName();
    TH1D* h1D = new TH1D("hR_" + midname + name, "Radial Coordinate", (histogram->GetNbinsX())*10, 0, 10000);
    ////h1D->SetLineColor(kRed);
    h1D->SetMarkerStyle(20);
    h1D->SetMarkerSize(0.5);
    ////h1D->SetMarkerColor(kRed);

    // Loop over the bins of the TH2D and fill the TH1D with sqrt(x**2 + y**2)
    for (int i = 1; i <= histogram->GetNbinsX(); i++) {
        for (int j = 1; j <= histogram->GetNbinsY(); j++) {
            double x = histogram->GetXaxis()->GetBinCenter(i);
            double y = histogram->GetYaxis()->GetBinCenter(j);
            double r = sqrt(x*x + y*y)/10.0; // in cm
            h1D->Fill(r, histogram->GetBinContent(i, j));
        }
    }

    return h1D;
}

void clusterXYs(TString recohistname = "h_nHCal_cluster_Rec_pos_xy", TString recoNeutronhistname = "hPosition_HCal_RecoNeutron", TString recoPionhistname = "hPosition_HCal_RecoPion") {
    // Open the root file
    style();
  
    // Create a new root file to write the canvases
    TFile* outputFile = new TFile("output_filesReco_canvases.root", "RECREATE");
    if (!outputFile) {
        printf("Error creating the output root file!\n");
        return;
    }
    TCanvas* canvas = new TCanvas("canvas", "Reco Cluster XY position", 1600, 1600);
    
    /*canvas->SetRightMargin(0.15);
    canvas->SetLeftMargin(0.15);
    canvas->SetBottomMargin(0.15);
    canvas->SetTopMargin(0.15);
    canvas->SetGrid();
    canvas->SetTicks();
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameFillColor(0);
    canvas->SetFrameFillStyle(0);
    canvas->SetFrameLineColor(1);
    canvas->SetFrameLineStyle(0);
    canvas->SetFrameLineWidth(1);*/
    canvas->Divide(3, 2);
    
    // Loop over the TDirectories with name Phi*Theta*
    /*TList* keys = file->GetListOfKeys();
    TIter next(keys);
    TKey* key;*/
    
    for (int icanvas = 1; icanvas <= 6; icanvas++) {
        canvas->cd(icanvas);
        //set logz for all canvases
        gPad->SetLogz();
        TFile* file = TFile::Open(Form("output_filesReco_%d.root", (155+(3*(icanvas-1)))), "READ");
            // Get the TH1F objects
            TH2D* hReco = (TH2D*)file->Get(recohistname);
            TH2D* hRecocm = convertmmtocm(hReco, Form("hist_%d", (155+(3*(icanvas-1)))));
            hRecocm->SetStats(0);
            hRecocm->SetTitle("");
            hRecocm->GetXaxis()->SetRangeUser(-400.0, 400.0);
            hRecocm->GetYaxis()->SetRangeUser(-400.0, 400.0);
            hRecocm->Draw("colz");

            TString PhiName = "45";
            TString ThetaName = Form("%d", (155+(3*(icanvas-1))));
            /////float etapi = converttoeta(ThetaName.Atof());
            /////float etan = converttoeta(155.0);
            TString EtaNamepi = Form("%.0f", ThetaName.Atof());
            TString EtaNamen = Form("%.0f", 155.0);

            TPaveText* text = new TPaveText(0.1618289,0.6798787,0.3900944,0.9205525,"brNDC");
            text->SetTextSize(0.045);
            text->AddText("#phi_{(MC)} =  45#circ");
            text->AddText("#theta_{n(MC)} = " + EtaNamen + " #circ");
            text->AddText("#theta_{#pi(MC)} = " + EtaNamepi + " #circ");
            text->Draw();

            // Draw a circle of radius 400
            TEllipse* circleout = new TEllipse(0, 0, -410.75*TMath::Tan((145.838*TMath::Pi())/180.0));
            circleout->SetFillStyle(0);
            circleout->SetLineColor(kBlack);
            circleout->SetLineWidth(2);
            circleout->Draw();

            TEllipse* circlein = new TEllipse(0, 0, -410.75*TMath::Tan((178.176*TMath::Pi())/180.0));

            circlein->SetFillStyle(0);
            circlein->SetLineColor(kBlack);
            circlein->SetLineWidth(2);
            circlein->Draw();
    }

    canvas->SaveAs("clustersXY.png");
    outputFile->Write();
}