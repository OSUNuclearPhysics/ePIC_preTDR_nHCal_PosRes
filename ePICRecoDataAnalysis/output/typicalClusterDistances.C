//includes
#include "TObject.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TChain.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom3.h"
#include <iostream>


int ican = 0;
void makeCanvas()  {
    TCanvas * can = new TCanvas( TString::Format( "can%d", ican++ ), "", 900, 600);
    can->SetTopMargin(0.1);
    can->SetRightMargin(0.1);
}

void typicalClusterDistances()
{
    TFile * reco_output = new TFile("/Users/Nick/eic/epic/ePICRecoDataAnalysis/output/hcal_full.root");
    TH2D * typical_distances = (TH2D*)reco_output->Get("h_nHCal_clusters_MC_eta_deltaRxy");
    TH2D * typical_distances_reco = (TH2D*)reco_output->Get("h_nHCal_clusters_Reco_eta_deltaRxy");


    makeCanvas();
    typical_distances->Draw();

    makeCanvas();
    TH1D *projy41 = typical_distances->ProjectionY("py41", typical_distances->GetXaxis()->FindBin(-4), typical_distances->GetXaxis()->FindBin(-1));
    TH1D *projy32 = typical_distances->ProjectionY("py32", typical_distances->GetXaxis()->FindBin(-3), typical_distances->GetXaxis()->FindBin(-2));
    TH1D *projy43 = typical_distances->ProjectionY("py43", typical_distances->GetXaxis()->FindBin(-4), typical_distances->GetXaxis()->FindBin(-3) );
    TH1D * projy21 = typical_distances->ProjectionY("py21", typical_distances->GetXaxis()->FindBin(-2), typical_distances->GetXaxis()->FindBin(-1));
    TH1D * projy54 = typical_distances->ProjectionY("py54", typical_distances->GetXaxis()->FindBin(-5), typical_distances->GetXaxis()->FindBin(-4));
    TH1D * projy65 = typical_distances->ProjectionY("py65", typical_distances->GetXaxis()->FindBin(-6), typical_distances->GetXaxis()->FindBin(-5));



    projy41->Rebin(25);
    projy32->Rebin(25);
    projy43->Rebin(25);
    projy21->Rebin(25);
    projy65->Rebin(25);
    projy54->Rebin(25);
    
    projy41->SetLineColor(kBlack);
    projy41->SetMarkerColor(kBlack);
    projy41->SetMarkerSize(0.7);
    projy41->SetMarkerStyle(kFullDotLarge);
    //projy41->Scale(1/projy41->Integral());
    //projy41->Rebin(2);    

    projy41->GetXaxis()->SetLimits(0,100);
    //projy41->GetYaxis()->SetRangeUser(0,0.08);
    projy41->SetStats(false);
    projy41->Draw("P");
    

    projy32->SetLineColor(kRed);
    projy32->SetMarkerColor(kRed);
    projy32->SetMarkerSize(0.7);
    projy32->SetMarkerStyle(kFullTriangleDown);
    //projy32->Scale(1/projy32->Integral());
    //projy32->Rebin(2);
    projy32->Draw("P;same");

    projy43->SetLineColor(kGreen);
    projy43->SetMarkerColor(kGreen);
    projy43->SetMarkerSize(0.7);
    projy43->SetMarkerStyle(kFullDiamond);
    //projy43->Scale(1/projy43->Integral());
    //projy43->Rebin(2);
    projy43->Draw("P;same");

    projy21->SetLineColor(kBlue);
    projy21->SetMarkerColor(kBlue);
    projy21->SetMarkerSize(0.7);
    projy21->SetMarkerStyle(kFullSquare);
    //projy21->Scale(1/projy21->Integral());
    //projy21->Rebin(2);
    projy21->Draw("P;same");


    projy54->SetLineColor(kPink);
    projy54->SetMarkerColor(kPink);
    projy54->SetMarkerSize(0.7);
    projy54->SetMarkerStyle(kFullSquare);
    //projy54->Scale(1/projy54->Integral());
    //projy54->Rebin(2);
    projy54->Draw("P;same");


    projy65->SetLineColor(kBlue);
    projy65->SetMarkerColor(kBlue);
    projy65->SetMarkerSize(0.7);
    projy65->SetMarkerStyle(kFullTriangleUp);
    //projy65->Scale(1/projy65->Integral());
    //projy65->Rebin(2);
    projy65->Draw("P;same");

    auto legend = new TLegend(0.7,0.6,1,0.9);
    legend->SetHeader("Legend","C"); // option "C" allows to center the header
    legend->AddEntry(projy41,"-4 < #eta < -1");
    legend->AddEntry(projy21, "-2 < #eta < -1");
    legend->AddEntry(projy32, "-3 < #eta < -2");
    legend->AddEntry(projy43, "-4 < #eta < -3");
    legend->AddEntry(projy54, "-5 < #eta < -4");
    legend->AddEntry(projy65, "-6 < #eta < -5");
    legend->SetTextSize(.055);
    legend->Draw("same");
    
    gPad->Print("plot_mc_clusters_distances.png");



    makeCanvas();
    typical_distances_reco->Draw("colz");
    gPad->Print("plot_eta_distance.png");

    makeCanvas();
    TH1D *projy41reco = typical_distances_reco->ProjectionY("py41reco", typical_distances_reco->GetXaxis()->FindBin(-4), typical_distances_reco->GetXaxis()->FindBin(-1));
    TH1D *projy32reco = typical_distances_reco->ProjectionY("py32reco", typical_distances_reco->GetXaxis()->FindBin(-3), typical_distances_reco->GetXaxis()->FindBin(-2));
    TH1D *projy43reco = typical_distances_reco->ProjectionY("py43reco", typical_distances_reco->GetXaxis()->FindBin(-4), typical_distances_reco->GetXaxis()->FindBin(-3) );
    TH1D * projy21reco = typical_distances_reco->ProjectionY("py21reco", typical_distances_reco->GetXaxis()->FindBin(-2), typical_distances_reco->GetXaxis()->FindBin(-1));
    TH1D * projy54reco = typical_distances->ProjectionY("py54reco", typical_distances_reco->GetXaxis()->FindBin(-5), typical_distances->GetXaxis()->FindBin(-4));
    TH1D * projy65reco = typical_distances->ProjectionY("py65rexo", typical_distances_reco->GetXaxis()->FindBin(-6), typical_distances->GetXaxis()->FindBin(-5));

    projy41reco->Rebin(25);
    projy32reco->Rebin(25);
    projy43reco->Rebin(25);
    projy21reco->Rebin(25);
    projy54reco->Rebin(25);
    projy65reco->Rebin(25);
    
    projy41reco->SetLineColor(kBlack);
    projy41reco->SetMarkerColor(kBlack);
    projy41reco->SetMarkerSize(0.7);
    projy41reco->SetMarkerStyle(kFullDotLarge);
    //projy41reco->Scale(1/projy41reco->Integral());
    //projy41reco->Rebin(2);    

    projy41reco->GetXaxis()->SetLimits(0,100);
    //projy41reco->GetYaxis()->SetRangeUser(0,0.03);
    projy41reco->SetStats(false);
    projy41reco->Draw("P");
    

    projy32reco->SetLineColor(kRed);
    projy32reco->SetMarkerColor(kRed);
    projy32reco->SetMarkerSize(0.7);
    projy32reco->SetMarkerStyle(kFullTriangleDown);
    //projy32reco->Scale(1/projy32reco->Integral());
    //projy32reco->Rebin(2);
    projy32reco->Draw("P;same");

    projy43reco->SetLineColor(kGreen);
    projy43reco->SetMarkerColor(kGreen);
    projy43reco->SetMarkerSize(0.7);
    projy43reco->SetMarkerStyle(kFullDiamond);
    //projy43reco->Scale(1/projy43reco->Integral());
    //projy43reco->Rebin(2);
    projy43reco->Draw("P;same");

    projy21reco->SetLineColor(kBlue);
    projy21reco->SetMarkerColor(kBlue);
    projy21reco->SetMarkerSize(0.7);
    projy21reco->SetMarkerStyle(kFullSquare);
    //projy21reco->Scale(1/projy21reco->Integral());
    //projy21reco->Rebin(2);
    projy21reco->Draw("P;same");

    projy54reco->SetLineColor(kPink);
    projy54reco->SetMarkerColor(kPink);
    projy54reco->SetMarkerSize(0.7);
    projy54reco->SetMarkerStyle(kFullSquare);
    //projy54reco->Scale(1/projy54reco->Integral());
    //projy54reco->Rebin(2);
    projy54reco->Draw("P;same");


    projy65reco->SetLineColor(kBlue);
    projy65reco->SetMarkerColor(kBlue);
    projy65reco->SetMarkerSize(0.7);
    projy65reco->SetMarkerStyle(kFullTriangleUp);
    //projy65reco->Scale(1/projy65reco->Integral());
    //projy65reco->Rebin(2);
    projy65reco->Draw("P;same");

    auto legendreco = new TLegend(0.7,0.6,1,0.9);
    legendreco->SetHeader("Legend","C"); // option "C" allows to center the header
    legendreco->AddEntry(projy41reco,"-4 < #eta < -1");
    legendreco->AddEntry(projy21reco, "-2 < #eta < -1");
    legendreco->AddEntry(projy32reco, "-3 < #eta < -2");
    legendreco->AddEntry(projy43reco, "-4 < #eta < -3");
    legendreco->AddEntry(projy54reco, "-5 < #eta < -4");
    legendreco->AddEntry(projy65reco, "-6 < #eta < -5");
    legendreco->SetTextSize(.055);
    legendreco->Draw("same");

    gPad->Print("plot_reco_clusters_distances.png");


    


}