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

Double_t fitpol0(Double_t *x, Double_t *par) {
    return par[0];
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

float converttoRcoord(float theta) {
    double z = 4107.5;
    double r = z * TMath::Tan(converttorad(180 - theta));  
    return r;
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

void neutronReco_from_chargedHadroncorrection(TString recohistname = "h_nHCal_neutralEfromchargedvsneutralEMC", TString recoPerformancehistname = "h_nHCal_compareperformance", TString recoPerformancehistname2D = "h_nHCal_compareperformance2D") {
    style();
  
    

    TCanvas* canvas = new TCanvas("canvas2D_performance", "canvas", 800, 800);
    canvas->Divide(4, 2);

    TCanvas* canvaswosf = new TCanvas("canvas2D_performancewosf", "canvas", 800, 800);
    canvaswosf->Divide(4, 2);

    TCanvas* canvaswE = new TCanvas("canvas2D_performancewE", "canvas", 800, 800);
    canvaswE->Divide(4, 2);

    TCanvas* canvaswE_hist = new TCanvas("canvas2D_performancewE_hist", "canvas", 800, 800);
    canvaswE_hist->Divide(4, 2);


    

    TCanvas* canvas1 = new TCanvas("canvas1D_performance", "canvas", 800, 800);

    TLegend* legend = new TLegend(0.1967419,0.4529032,0.6478697,0.8529032,NULL,"brNDC");

    TLine* line = new TLine(0, 0, 12, 12);
        line->SetLineColor(kBlack);
        line->SetLineWidth(2);
        line->SetLineStyle(7);

        Int_t fileIndex[10] = {155, 156, 157, 158, 159, 160, 161, 164, 167, 170};
    
    for (int i = 1; i <= 8; i++) {
        ///if (i > 1) continue;
        if (fileIndex[i-1] > 164)  {
            continue;
        }
      TFile* file = TFile::Open(Form("output_filesReco_%d.root", fileIndex[i-1]), "READ");
      if (!file) {
        printf("Error opening the root file!\n");
        ///return;
        continue;
      }

      

      // Get the histogram from the root file
      TH2D* recohist = (TH2D*)file->Get(recohistname);
      
       if (!recohist) {
            printf("Error getting the histogram!\n");
            return;
            }

        TH2D *recohistwithoutsf = new TH2D("recohistwithoutsf", "Reconstructed Energy without Scale Factor", recohist->GetNbinsX(), 0, 100, recohist->GetNbinsY(), 0, 100);
        // Modify the x and y coordinates of the histogram by multiplying with 0.0095
        for (int i = 1; i <= recohist->GetNbinsX(); i++) {
            for (int j = 1; j <= recohist->GetNbinsY(); j++) {
                double x = recohist->GetXaxis()->GetBinCenter(i) * 0.0095 *1000;
                double y = recohist->GetYaxis()->GetBinCenter(j) * 0.0095 *1000;
                double content = recohist->GetBinContent(i, j);
                ///recohist->SetBinContent(i, j, 0); // Clear the bin content
                recohistwithoutsf->Fill(x, y, content); // Fill with new coordinates
            }
        }

        recohist->Rebin2D(10, 10);

        TH2D* recoPerformancehist2D = (TH2D*)file->Get(recoPerformancehistname2D);
        if (!recoPerformancehist2D) {
            printf("Error getting the histogram!\n");
            return;
        }
        
        TH2D* modifiedRecoPerformancehist2D = new TH2D("modifiedRecoPerformancehist2D", "Modified Performance", recoPerformancehist2D->GetNbinsX(), 0, 100, recoPerformancehist2D->GetNbinsY(), -20., 20.);
        for (int i = 1; i <= recoPerformancehist2D->GetNbinsX(); i++) {
            for (int j = 1; j <= recoPerformancehist2D->GetNbinsY(); j++) {
                double x = recoPerformancehist2D->GetXaxis()->GetBinCenter(i) * 1000;
                double y = recoPerformancehist2D->GetYaxis()->GetBinCenter(j);
                double content = recoPerformancehist2D->GetBinContent(i, j);
                modifiedRecoPerformancehist2D->Fill(x, y, content);
            }
        }

        modifiedRecoPerformancehist2D->Rebin2D(10, 10);

        TProfile* profile = modifiedRecoPerformancehist2D->ProfileX();

        TFile* filereverse = TFile::Open(Form("output_filesReco_%d.root", fileIndex[8-i]), "READ");
        if (!filereverse) {
            printf("Error opening the root file!\n");
            ///return;
            continue;
        }
        TH1D* recoPerformancehist = (TH1D*)filereverse->Get(recoPerformancehistname);
        if (!recoPerformancehist) {
            printf("Error getting the histogram!\n");
            return;
        }
        recoPerformancehist->Rebin(4);

        
        



        /*TH2D *recoPerformancehist2D_wos = new TH2D("recoPerformancehist2D_wos", "Performance without Scale Factor", recoPerformancehist2D->GetNbinsX()*100, 0, 100, recoPerformancehist2D->GetNbinsY()*100, 0, 100);
        // Modify the x and y coordinates of the histogram by multiplying with 0.0095
        for (int i = 1; i <= recoPerformancehist2D->GetNbinsX(); i++) {
            for (int j = 1; j <= recoPerformancehist2D->GetNbinsY(); j++) {
                double x = recoPerformancehist2D->GetXaxis()->GetBinCenter(i)*1000;
                double y = recoPerformancehist2D->GetYaxis()->GetBinCenter(j)*1000;
                double content = recoPerformancehist2D->GetBinContent(i, j);
                ///recohist->SetBinContent(i, j, 0); // Clear the bin content
                recoPerformancehist2D_wos->Fill(x, y, content); // Fill with new coordinates
            }
        }*/

        // Create a new canvas
        
        recohist->SetStats(0);
        recohist->SetTitle("");
        recohist->GetXaxis()->SetTitle("E_{neutral}^{MC} [GeV]");
        recohist->GetYaxis()->SetTitle("E_{neutral}^{Reco} [GeV]");
        recohist->GetYaxis()->SetTitleSize(0.06);
        recohist->GetXaxis()->SetTitleSize(0.06);
        recohist->GetYaxis()->SetLabelSize(0.06);
        recohist->GetXaxis()->SetLabelSize(0.06);
        recohist->GetXaxis()->SetRangeUser(0, 13.);
        recohist->GetYaxis()->SetRangeUser(0, 13.);
        ///
         
        
    

        

        //draw a line y = x
        
        canvas->cd(i);
        gPad->SetLogz();
        recohist->Draw("colz");

        line = new TLine(0, 0, 12, 12);
        line->SetLineColor(kBlack);
        line->SetLineWidth(2);
        line->SetLineStyle(7);
        line->Draw("same");
        
        TLegend *legend1 = new TLegend(0.2158198,0.9325565,0.3022525,0.9766949,NULL,"brNDC");
        TLegendEntry *entry=legend1->AddEntry(recohist, Form("R_{Gen Neutron} - R_{Gen Pion} = %.1f cm", (converttoRcoord(155) - converttoRcoord(fileIndex[i-1]))/10.0), "");
        legend1->SetTextFont(62);
        legend1->SetTextSize(0.04413842);
        legend1->SetLineColor(1);
        legend1->SetLineStyle(1);
        legend1->SetLineWidth(2);
        legend1->SetFillColor(0);
        legend1->SetFillStyle(1001);
        entry->SetLineColor(1);
        entry->SetLineStyle(1);
        entry->SetLineWidth(1);
        entry->SetMarkerColor(1);
        entry->SetMarkerStyle(21);
        entry->SetMarkerSize(1);
        entry->SetTextFont(62);
        legend1->Draw("same");
        ////legend1->Delete();

        recohistwithoutsf->Rebin2D(10, 10);
        recohistwithoutsf->SetStats(0);
        recohistwithoutsf->SetTitle("");
        recohistwithoutsf->GetXaxis()->SetTitle("E_{neutral}^{MC}*f [MeV]");
        recohistwithoutsf->GetYaxis()->SetTitle("E_{neutral}^{Reco}*f [MeV]");

        canvaswosf->cd(i);
        gPad->SetLogz();
        recohistwithoutsf->Draw("colz");

        //chaange the range of line to 0.1
        line = new TLine(0, 0, 80, 80);
        line->SetLineColor(kBlack);
        line->SetLineWidth(2);
        line->SetLineStyle(7);
        line->Draw("same");
        legend1->Draw("same");
        ////legend1->Delete();


        canvaswE->cd(i);
        gPad->SetLogz();

        ////modifiedRecoPerformancehist2D->Draw("colz");
        
        profile->SetTitle("");
        profile->GetXaxis()->SetTitle("E^{MC}_{neutral}*f [MeV]");
        profile->GetYaxis()->SetTitle("E^{Reco}_{neutral}/E^{MC}_{neutral}");

        profile->GetYaxis()->SetRangeUser(-0.1, 1.1);
        profile->GetXaxis()->SetRangeUser(0, 50);
        /////profile->GetYaxis()->SetTitleOffset(1.60);
        ////profile->GetXaxis()->SetTitleOffset(1.30);
        profile->SetMarkerStyle(22);
        profile->SetStats(0);
        profile->Draw("");
        legend1->Draw("same");

        //chaange the range of line to 0.1

        canvaswE_hist->cd(i);
        gPad->SetLogz();
        modifiedRecoPerformancehist2D->SetStats(0);
        modifiedRecoPerformancehist2D->SetTitle("");
        modifiedRecoPerformancehist2D->GetXaxis()->SetTitle("E^{MC}_{neutral}*f [MeV]");
        modifiedRecoPerformancehist2D->GetYaxis()->SetTitle("E^{Reco}_{neutral}/E^{MC}_{neutral}");

        modifiedRecoPerformancehist2D->GetYaxis()->SetRangeUser(-0.1, 1.1);
        modifiedRecoPerformancehist2D->GetXaxis()->SetRangeUser(0, 50);
        /*modifiedRecoPerformancehist2D->GetYaxis()->SetTitleOffset(1.60);
        modifiedRecoPerformancehist2D->GetXaxis()->SetTitleOffset(1.30);
        modifiedRecoPerformancehist2D->SetMarkerStyle(22);*/
        modifiedRecoPerformancehist2D->Draw("colz");
        legend1->Draw("same");

        



        
        

        

        // Create a new canvas
        canvas1->cd();
        ///if (i == 6) continue;
        recoPerformancehist->SetStats(0);
        recoPerformancehist->SetTitle("");

        recoPerformancehist->Scale(1.0/recoPerformancehist->GetEntries());
    
        recoPerformancehist->GetXaxis()->SetTitle("E^{Reco}_{neutral}/E^{MC}_{neutral}");
        recoPerformancehist->GetXaxis()->SetRangeUser(0.035, 1.05);
        recoPerformancehist->GetYaxis()->SetRangeUser(0, 0.1);
        recoPerformancehist->GetYaxis()->SetTitle("Probability");
        recoPerformancehist->GetYaxis()->SetTitleOffset(1.60);
        recoPerformancehist->GetXaxis()->SetTitleOffset(1.30);
        recoPerformancehist->SetMarkerStyle(22);
        recoPerformancehist->SetMarkerColor(9-i);
        recoPerformancehist->SetLineColor(9-i);
        
        recoPerformancehist->Draw("same");

        //build the legend
        double x = (converttoRcoord(155) - converttoRcoord(fileIndex[8-i]))/10.0;
        legend->AddEntry(recoPerformancehist, Form("R_{Gen Neutron} - R_{Gen Pion} = %.1f cm", x), "lp");
        legend->SetTextSize(0.025);
        /* Create a new root file to write the canvases
       TFile* outputFile = new TFile("output_filesReco_canvases.root", "RECREATE");
        if (!outputFile) {
        printf("Error creating the output root file!\n");
        return;
       }
       canvas1->Write("recoPerformancehist"); */
    }

    canvas1->cd();
    legend->Draw();

}