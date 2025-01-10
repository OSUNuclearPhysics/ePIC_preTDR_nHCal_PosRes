/*
 * HistogramsRecoClusters.h
 *
 *  Created on: 23 mar 2023
 *      Author: Khaless
 */

#ifndef HISTOGRAMSRECOCLUSTERS_H_
#define HISTOGRAMSRECOCLUSTERS_H_

#include <TH1.h>
#include <TH1D.h>

#include <TH2.h>
#include <TH2D.h>

#include <TMath.h>

#include <TGraphErrors.h>

using namespace TMath;

void CreateHistogamsRecoClusters();


// HcalEndcapNClusters

TH1D *h_nHCal_cluster_Rec_E;

TH1D *h_nHCal_nclusters_Rec;

TH1D *h_nHCal_cluster_Rec_pos_x;
TH1D *h_nHCal_cluster_Rec_pos_y;
TH1D *h_nHCal_cluster_Rec_pos_z;
TH1D *h_nHCal_cluster_Rec_pos_R;	
TH2D *h_nHCal_cluster_Rec_pos_xy; //// used for Figure 8.173

TH2D *h_nHCal_cluster_Rec_pos_rE;

TH2D *h_nHCal_neutral_cluster_energytot_vs_nclusters;
TH2D *h_nHCal_charged_cluster_energytot_vs_nclusters;

TH2D *h_nHCal_neutralEMCvsReco;
TH2D *h_nHCal_chargedEMCvsReco;

TH2D *h_nHCal_neutralEreceffvsnClusters;
TH2D *h_nHCal_chargedEreceffvsnClusters;
TH2D *h_nHCal_neutralEreceffvschargedEreceff;

TH2D *h_nHCal_neutralErecfractionvschargedErecfraction;
TH2D *h_nHCal_neutralErecfractionvsEmcFraction;
TH2D *h_nHCal_chargedErecfractionvsEmcFraction;
TH2D *h_nHCal_neutralERecofractionvschargedERecofraction;
TH2D *h_nHCal_neutralEMCfractionvschargedEMCfraction;

TH2D *h_nHCal_neutralrecoEfracdeviation;
TH2D *h_nHCal_chargedrecoEfracdeviation;

TH2D *h_nHCal_f_neutral;
TH2D *h_nHCal_f_charged;
TH2D *h_nHCal_f_neutralvsf_charged;

TH1D *h_nHCal_lostEfrac;
// HcalEndcapNTruthClusters

TH1D *h_nHCal_cluster_MC_E;

TH1D *h_nHCal_nclusters_MC;

TH1D *h_nHCal_cluster_MC_pos_x;
TH1D *h_nHCal_cluster_MC_pos_y;
TH1D *h_nHCal_cluster_MC_pos_z;
TH1D *h_nHCal_cluster_MC_pos_R;
TH2D *h_nHCal_cluster_MC_pos_xy;

TH2D *h_nHCal_cluster_MC_pos_rE;

//TH2D *h_nHCal_clusters_MC_eta_deltaRxy;
//TH2D *h_nHCal_clusters_Reco_eta_deltaRxy;


// cluster distance
TH2D *h_nHCal_clusters_Reco_eta_deltaRxy;
TH2D *h_nHCal_clusters_MC_eta_deltaRxy;

TH2D *h_nHCal_sanitycheck;
TH2D *h_nHCal_EalterationperEMCthatenteredclustering;

TH2D *h_nHCal_neutralEClusfromchargedvsneutralEClus;
TH2D *h_nHCal_neutralEMCfromchargedvsneutralEMC;

TH2D *h_nHCal_neutralClustersvschargedClusterswnonzeroE;
TH2D *h_nHCal_neutralClusterEvschargedClusterEwoneone;

TH1D *h_nHCal_compareperformance; //// used for Figure 8.174
TH1D *h_nHCal_compareperformancewdiff;
TH1D *h_nHCal_compareperformanceweff;
TH1D *h_nHCal_compareperformancewpioneffneutroneff;

TH1D *h_nHCal_clusterdistance;

TH2D *h_nHCal_neutralEreceffvsneutralEMC;
TH2D *h_nHCal_chargedEreceffvschargedEMC;

TH2D *h_nHCal_neutralEfromchargedvsneutralEMC;

TH2D *h_nHCal_compareperformance2D; //// used for Figure 8.175

TH2D *h_nHCal_checkeffN;






void CreateHistogamsRecoClusters()
{   

	// HcalEndcapNClusters
	h_nHCal_cluster_Rec_E = new TH1D("h_nHCal_cluster_Rec_E", "nHCal Rec clusters energy ; E [GeV]; Entries", 100000, 0.0, 10.0);

	h_nHCal_nclusters_Rec = new TH1D("h_nHCal_nclusters_Rec", "No. of nHCal Rec clusters ; N_{clu}; Entries", 501, -0.5, 500.5);

	h_nHCal_cluster_Rec_pos_x = new TH1D("h_nHCal_cluster_Rec_pos_x", "nHCal Rec cluster position x; x [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_y = new TH1D("h_nHCal_cluster_Rec_pos_y", "nHCal Rec cluster position y; y [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_z = new TH1D("h_nHCal_cluster_Rec_pos_z", "nHCal Rec cluster position z; y [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_R = new TH1D("h_nHCal_cluster_Rec_pos_R", "nHCal Rec cluster position R; R [mm]; Entries", 1000, 0.0, 5000.0);
	h_nHCal_cluster_Rec_pos_xy = new TH2D("h_nHCal_cluster_Rec_pos_xy", "nHCal Rec cluster position xy; x [mm]; y [mm]; Entries", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_nHCal_cluster_Rec_pos_rE = new TH2D("h_nHCal_cluster_Rec_pos_rE", "nHCal Rec cluster energy vs. radial position; r [mm]; E [GeV]; Entries", 500, 0.0, 5000.0, 20000, 0.0, 20.0);

	h_nHCal_neutral_cluster_energytot_vs_nclusters = new TH2D("h_nHCal_neutral_cluster_energytot_vs_nclusters", "neutral cluster energy vs. nclusters; N_{clu}; E [GeV]; Entries", 11, -0.5, 10.5, 2000, 0.0, 20.0);
	h_nHCal_charged_cluster_energytot_vs_nclusters = new TH2D("h_nHCal_charged_cluster_energytot_vs_nclusters", "charged cluster energy vs. nclusters; N_{clu}; E [GeV]; Entries", 11, -0.5, 10.5, 2000, 0.0, 20.0);

	h_nHCal_neutralEMCvsReco = new TH2D("h_nHCal_neutralEMCvsReco", "neutral cluster energy MC vs. Reco; E_{MC} [GeV]; E_{Reco} [GeV]; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);
	h_nHCal_chargedEMCvsReco = new TH2D("h_nHCal_chargedEMCvsReco", "charged cluster energy MC vs. Reco; E_{MC} [GeV]; E_{Reco} [GeV]; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);

	h_nHCal_neutralEreceffvsnClusters = new TH2D("h_nHCal_neutralEreceffvsnClusters", "neutral cluster energy rec eff vs. nclusters; N_{clu}; E_{rec eff} [GeV]; Entries", 11, -0.5, 10.5, 10000, 0.0, 200.0);
	h_nHCal_chargedEreceffvsnClusters = new TH2D("h_nHCal_chargedEreceffvsnClusters", "charged cluster energy rec eff vs. nclusters; N_{clu}; E_{rec eff} [GeV]; Entries", 11, -0.5, 10.5, 10000, 0.0, 200.0);

	h_nHCal_neutralEreceffvschargedEreceff = new TH2D("h_nHCal_neutralEreceffvschargedEreceff", "neutral cluster energy rec eff vs. charged cluster energy rec eff; E_{rec charged}/E_{MC charged}; E_{rec neutral}/E_{MC neutral}; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);

	h_nHCal_neutralErecfractionvschargedErecfraction = new TH2D("h_nHCal_neutralErecfractionvschargedErecfraction", "neutral energy rec fraction vs. charged energy rec fraction; E_{rec charged}/E_{MC}; E_{rec neutral}/E_{MC}; Entries", 600, -1.0, 5.0, 600, -1.0, 5.0);

	h_nHCal_neutralErecfractionvsEmcFraction = new TH2D("h_nHCal_neutralErecfractionvsEmcFraction", "neutral energy rec fraction vs neutral energy MC fraction; E_{MC}/E_{MC Total}; E_{Rec}/E_{Rec Total}; Entries", 200, -0.5, 1.5, 2000, -0.5, 15);
	h_nHCal_chargedErecfractionvsEmcFraction = new TH2D("h_nHCal_chargedErecfractionvsEmcFraction", "charged energy rec fraction vs charged energy MC fraction; E_{MC}/E_{MC Total}; E_{Rec}/E_{Rec Total}; Entries", 200, -0.5, 1.5, 2000, -0.5, 15);

	h_nHCal_neutralERecofractionvschargedERecofraction = new TH2D("h_nHCal_neutralERecofractionvschargedERecofraction", "neutral energy rec fraction vs. charged energy rec fraction; E_{Rec charged}/E_{Rec}; E_{Rec neutral}/E_{Rec}; Entries", 600, -1.0, 5.0, 600, -1.0, 5.0);
	h_nHCal_neutralEMCfractionvschargedEMCfraction = new TH2D("h_nHCal_neutralEMCfractionvschargedEMCfraction", "neutral energy MC fraction vs. charged energy MC fraction; E_{MC charged}/E_{MC Total}; E_{MC neutral}/E_{MC Total}; Entries", 600, -1.0, 5.0, 600, -1.0, 5.0);



	h_nHCal_lostEfrac = new TH1D("h_nHCal_lostEfrac", "Lost energy fraction; E_{lost}/E_{MC}; Entries", 300, -1.0, 2.0);


	h_nHCal_neutralrecoEfracdeviation = new TH2D("h_nHCal_neutralrecoEfracdeviation", "neutral reco energy fraction deviation; E_{MC neutral}/E_{MC Total}; E_{Recfrac neutral} - E_{MCfrac neutral}; Entries", 120, -0.1, 1.1, 4000, -2., 20.0);
	h_nHCal_chargedrecoEfracdeviation = new TH2D("h_nHCal_chargedrecoEfracdeviation", "charged reco energy fraction deviation; E_{MC charged}/E_{MC Total}; E_{Recfrac charged} - E_{MCfrac charged}; Entries", 120, -0.1, 1.1, 4000, -2., 20.0);

	h_nHCal_f_neutral = new TH2D("h_nHCal_f_neutral", "neutral energy fraction deviation; E_{Rec neutral} [GeV]; f_{neutral}; Entries", 4000, -400.0, 400.0, 4000, -400.0, 400.0);
	h_nHCal_f_charged = new TH2D("h_nHCal_f_charged", "charged energy fraction deviation; E_{Rec charged} [GeV]; f_{charged}; Entries", 4000, -400.0, 400.0, 4000, -400.0, 400.0);

	h_nHCal_f_neutralvsf_charged = new TH2D("h_nHCal_f_neutralvsf_charged", "neutral energy fraction deviation vs. charged energy fraction deviation; f_{charged}; f_{neutral}; Entries", 4000, -400.0, 400.0, 4000, -400.0, 400.0);

	h_nHCal_sanitycheck = new TH2D("h_nHCal_sanitycheck", "Sanity check; #Delta E_{neutral} [GeV]; #Delta E_{charged} [GeV]; Entries", 4000, -400.0, 400.0, 4000, -400.0, 400.0);

	h_nHCal_EalterationperEMCthatenteredclustering = new TH2D("h_nHCal_EalterationperEMCthatenteredclustering", "Energy alteration per E_{MC particle} that entered clustering; #Delta E_{neutral}/(#epsilon_{global} E_{MC neutral}); #Delta E_{charged}/(#epsilon_{global} E_{MC charged}); Entries", 4000, -20.0, 200.0, 4000, -20.0, 200.0);

	h_nHCal_neutralEClusfromchargedvsneutralEClus = new TH2D("h_nHCal_neutralEClusfromchargedvsneutralEClus", "neutral clus energy from charged vs. neutral cluster energy; E_{Clus neutral} [GeV]; E_{Clu neutral from charged} [GeV]; Entries", 2000, 0.0, 20.0, 2000, -20.0, 20.0);
	h_nHCal_neutralEMCfromchargedvsneutralEMC = new TH2D("h_nHCal_neutralEMCfromchargedvsneutralEMC", "neutral EMC energy from charged vs. neutral EMC energy; E_{EMC neutral} [GeV]; E_{MC neutral from charged} [GeV]; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);

	h_nHCal_neutralEfromchargedvsneutralEMC = new TH2D("h_nHCal_neutralEfromchargedvsneutralEMC", "neutral cluster energy from charged vs. neutral EMC energy; E_{MC neutral} [GeV]; E_{neutral from charged} [GeV]; Entries", 2000, -10.0, 20.0, 2000, -10.0, 20.0);

	h_nHCal_neutralClustersvschargedClusterswnonzeroE = new TH2D("h_nHCal_neutralClustersvschargedClusterswnonzeroE", "No. of neutral clusters vs. charged clusters with non-zero energy; N_{neutral}; N_{charged}; Entries", 11, -0.5, 10.5, 11, -0.5, 10.5);
	h_nHCal_neutralClusterEvschargedClusterEwoneone = new TH2D("h_nHCal_neutralClusterEvschargedClusterEwoneone", "neutral cluster energy vs. charged cluster energy with one-one correspondence; E_{neutral} [GeV]; E_{charged} [GeV]; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);

	h_nHCal_compareperformance = new TH1D("h_nHCal_compareperformance", "Compare performance; E_{N after charged corr}/E_{N MC}; Entries", 5000, -20.0, 20.0);
	h_nHCal_compareperformancewdiff = new TH1D("h_nHCal_compareperformancewdiff", "Compare performance with difference; E_{N after charged corr} - E_{N MC}; Entries", 5000, -20.0, 20.0);
	h_nHCal_compareperformanceweff = new TH1D("h_nHCal_compareperformanceweff", "Compare performance with eff; E_{N after charged corr} - E_{N MC w/ eff}; Entries", 5000, -20.0, 20.0);
	h_nHCal_compareperformancewpioneffneutroneff = new TH1D("h_nHCal_compareperformancewpioneffneutroneff", "Compare performance with eff; E_{N after charged corr w/ eff} - E_{N MC w/ eff}; Entries", 5000, -20.0, 20.0);

	h_nHCal_compareperformance2D = new TH2D("h_nHCal_compareperformance2D", "Compare performance 2D; E_{MC neutral} [GeV]; E_{N after charged corr}/E_{N MC}; Entries", 1000, 0.0, 1.0, 5000, -20., 20.);

	h_nHCal_clusterdistance = new TH1D("h_nHCal_clusterdistance", "Cluster distance; #Delta R_{xy} [cm]; Entries", 5000, 0.0, 500.0);

	h_nHCal_neutralEreceffvsneutralEMC = new TH2D("h_nHCal_neutralEreceffvsneutralEMC", "neutral cluster energy rec eff vs. neutral cluster energy MC; E_{MC neutral} [GeV]; #epsilon_{neutral}; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);
	h_nHCal_chargedEreceffvschargedEMC = new TH2D("h_nHCal_chargedEreceffvschargedEMC", "charged cluster energy rec eff vs. charged cluster energy MC; E_{MC charged} [GeV]; #epsilon_{charged}; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);

	h_nHCal_checkeffN = new TH2D("h_nHCal_checkeffN", "Check efficiency; E_{neutral reco} [GeV]; E_{neutral MC w/ eff} [GeV]; Entries", 2000, 0.0, 20.0, 2000, 0.0, 20.0);




	// HcalEndcapNTruthClusters
	h_nHCal_cluster_MC_E = new TH1D("h_nHCal_cluster_MC_E", "nHCal MC clusters energy ; E [GeV]; Entries", 100000, 0.0, 10.0);

	h_nHCal_nclusters_MC = new TH1D("h_nHCal_nclusters_MC", "No. of nHCal MC clusters ; N_{clu}; Entries", 501, -0.5, 500.5);

	h_nHCal_cluster_MC_pos_x = new TH1D("h_nHCal_cluster_MC_pos_x", "nHCal MC cluster position x; x [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_y = new TH1D("h_nHCal_cluster_MC_pos_y", "nHCal MC cluster position y; y [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_z = new TH1D("h_nHCal_cluster_MC_pos_z", "nHCal MC cluster position z; y [mm]; Entries", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_R = new TH1D("h_nHCal_cluster_MC_pos_R", "nHCal MC cluster position R; R [mm]; Entries", 1000, 0.0, 5000.0);
	h_nHCal_cluster_MC_pos_xy = new TH2D("h_nHCal_cluster_MC_pos_xy", "nHCal MC cluster position xy; x [mm]; y [mm]; Entries", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_nHCal_cluster_MC_pos_rE = new TH2D("h_nHCal_cluster_MC_pos_rE", "nHCal MC cluster energy vs. radial position; r [mm]; E [GeV]; Entries", 500, 0.0, 5000.0, 20000, 0.0, 20.0);

	//h_nHCal_clusters_MC_eta_deltaRxy = new TH2D("h_nHCal_clusters_MC_eta_deltaRxy", "MC cluster pairs #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; Entries", 100, -10.0, 0.0, 100, 0.0, 500.0);
	//h_nHCal_clusters_Reco_eta_deltaRxy = new TH2D("h_nHCal_clusters_Reco_eta_deltaRxy", "Reco cluster pairs #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; Entries", 100, -10.0, 0.0, 100, 0.0, 500.0);



	// cluster distance
	h_nHCal_clusters_Reco_eta_deltaRxy = new TH2D("h_nHCal_clusters_Reco_eta_deltaRxy", "Reco clusters pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; Entries", 200, -10.0, 10.0, 5000, 0.0, 500.0);
	h_nHCal_clusters_MC_eta_deltaRxy = new TH2D("h_nHCal_clusters_MC_eta_deltaRxy", "Truth clusters pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; Entries", 200, -10.0, 10.0, 5000, 0.0, 500.0);


}


#endif /* HISTOGRAMSRECOCLUSTERS_H_ */
