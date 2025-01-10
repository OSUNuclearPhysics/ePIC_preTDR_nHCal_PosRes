#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fmt/core.h"

#include "ROOT/RDataFrame.hxx"
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TVector3.h>

#include "TROOT.h"
#include "TRandom.h"
#include "TH3.h"


#include "DD4hep/Detector.h"
#include "DDRec/CellIDPositionConverter.h"

#include <podio/Frame.h>
#include <podio/CollectionBase.h>
#include "podio/ROOTReader.h"
#include "podio/CollectionIDTable.h"
#include "podio/ObjectID.h"


#include "edm4hep/utils/kinematics.h"

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/MCParticleCollectionData.h"
#include "edm4hep/MCParticle.h"
#include "edm4hep/MCParticleData.h"

#include "edm4hep/SimCalorimeterHitCollectionData.h"
#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/SimCalorimeterHitData.h"
#include "edm4hep/SimCalorimeterHit.h"

#include "edm4hep/CaloHitContributionCollectionData.h"
#include "edm4hep/CaloHitContributionCollection.h"
#include "edm4hep/CaloHitContributionData.h"
#include "edm4hep/CaloHitContribution.h"

#include "edm4hep/RawCalorimeterHitData.h"
#include "edm4hep/CalorimeterHitData.h"

#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitCollectionData.h"
#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitData.h"
#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitObj.h"

//dd4hep::sim::Geant4Calorimeter::Hit

#include "edm4eic/ReconstructedParticleCollection.h"
#include "edm4eic/MCRecoParticleAssociationCollection.h"
#include "edm4eic/MCRecoClusterParticleAssociationCollectionData.h"
#include "edm4eic/MCRecoClusterParticleAssociationCollection.h"
#include "edm4eic/MCRecoClusterParticleAssociationData.h"
#include "edm4eic/MCRecoClusterParticleAssociation.h"


#include "edm4eic/ClusterCollection.h"
#include "edm4eic/Cluster.h"
#include "edm4eic/ClusterData.h"

#include "edm4eic/CalorimeterHitCollectionData.h"
#include "edm4eic/CalorimeterHitCollection.h"
#include "edm4eic/CalorimeterHitData.h"
#include "edm4eic/CalorimeterHit.h"
#include "edm4eic/CalorimeterHitObj.h"


#include <edm4eic/vector_utils_legacy.h>
#include <edm4hep/Vector3f.h>

///#include "eicd/Vector3f.h"

///#include "eicd/VectorXYZ.h"
//#include "eicd/Cluster.h"
//#include "eicd/ClusterData.h"
//#include "edm4hep/Vector3f.h"
//#include "Vector3D.h"
//include "eic/Vector3D.h"
//#include <eic/vector_utils.h>
//#include "dd4pod/CalorimeterHitData.h"

#include "FileList.h"
#include "HistogramsReco.h"
#include "HistogramsRecoClusters.h"
#include "BasicUtil.h"
#include "EICutil.h"

/*
#pragma link C++ class vector<edm4hep::MCParticleData>+;
#pragma link C++ class vector<eicd::ClusterData>+;
#pragma link C++ class vector<podio::ObjectID>+;
#pragma link C++ class vector<edm4hep::SimCalorimeterHitData>+;
#pragma link C++ class vector<edm4hep::RawCalorimeterHitData>+;


#pragma link C++ class vector<edm4eic::CalorimeterHitData>+;
#pragma link C++ class vector<edm4eic::ClusterData>+;
#pragma link C++ class vector<podio::ObjectID>+;
#pragma link C++ class vector<edm4hep::CaloHitContributionData>+;
#pragma link C++ class vector<edm4eic::MCRecoClusterParticleAssociationData>+;
*/

//edm4hep::MCParticleCollectionData *MCParticles_data = 0;
vector<edm4hep::MCParticleData> *MCParticles_data = 0;
vector<podio::ObjectID> *MCparents_data = 0;
vector<podio::ObjectID> *MCdaughters_data = 0;

vector<edm4eic::CalorimeterHitData> *nHCal_data = 0;

vector<edm4eic::ClusterData> *nHCal_Cluster_Rec_data_vec = 0;
vector<podio::ObjectID> *nHCal_Cluster_Rec_assoc_vec = 0;

vector<edm4eic::ClusterData> *nHCal_Cluster_MC_data_vec = 0;
vector<podio::ObjectID> *nHCal_Cluster_MC_assoc_vec = 0;

using namespace std;
using namespace ROOT;
using namespace TMath;
//using namespace eicd;
using namespace edm4eic;
//using namespace edm4hep;

void SafeFill(TH1* hist, double value) {
    if (!std::isnan(value) && !std::isinf(value)) {
        hist->Fill(value);  // Only fill the histogram if the value is valid
    }
}

void SafeFill(TH2* hist, double x, double y) {
	if (!std::isnan(x) && !std::isinf(x) && !std::isnan(y) && !std::isinf(y)) {
		hist->Fill(x, y);  // Only fill the histogram if the value is valid
	}
}

Double_t neutronrecoeff(Double_t x) {
	Double_t f = 9.40835e-01*(1.0 - exp(-2.83540e+00*x));
	return f;
}

///loops at line 770 and 946 are relevant for the preTDR plots


int getPDGofPrimary(edm4hep::MCParticle mcpart)
{
	bool parentIsPrimary = false;

			//podio::RelationRange<edm4hep::MCParticle> MCparents = mcpart.getParents();

			//vector<edm4hep::MCParticleData> *parents_data = new vector<edm4hep::MCParticleData>;
			//vector<edm4hep::MCParticleData> *daughters_data = new vector<edm4hep::MCParticleData>;

			std::vector<edm4hep::MCParticle> parents_data(mcpart.getParents().begin(), mcpart.getParents().end());
			while (!parentIsPrimary && !parents_data.empty()) {
				for (auto parent : parents_data) {
					if (parent.getGeneratorStatus() == 1) {
						parentIsPrimary = true;
						return parent.getPDG();
					}
				}
				std::vector<edm4hep::MCParticle> nextGenParents;
				// Move to the next generation of parents
				for (auto parent : parents_data) {
					auto nextGen = parent.getParents();
					nextGenParents.insert(nextGenParents.end(), nextGen.begin(), nextGen.end());
				}
				parents_data = nextGenParents;
			}
			return 0; // Return 0 if no primary parent is found
			

} 

int readFrameRootReco(TString list = "data/filesReco_164.list", TString ofname = "output/output_filesReco_164.root", long nevents = -1);
int MakeEvent(podio::ROOTReader *reader, unsigned ev);


bool printEvNum = true;
bool debug = false;

int main(int argc, char **argv)
{
	readFrameRootReco();

	return 1;
}

int readFrameRootReco(TString list, TString ofname, long nevents)
{

	// open file w/ frame reader
	podio::ROOTReader *reader = new podio::ROOTReader();

	std::vector<std::string> filenames = openList(list);
	if(filenames.size() != 0) reader->openFiles(filenames);
	else {
		cout<<"Can't open file list! Exiting."<<endl;
		return 0;
	}

	std::vector<std::string_view> categories = reader->getAvailableCategories();

	cout<<"Available categories:"<<endl;
	PrintStringVector(categories);
	cout<<endl;


	unsigned nEvents = reader->getEntries(podio::Category::Event);
	cout<<"Number of events = "<<nEvents<<endl;

	if(nevents>0) nEvents = nevents;
	

	// Delete existing root file
	if (std::remove(ofname.Data()) != 0) {
		std::cout << "Error deleting file: " << ofname << std::endl;
	} else {
		std::cout << "Existing file deleted: " << ofname << std::endl;
	}
	TFile *output = new TFile(ofname, "recreate");
	output->cd();

	CreateHistogamsReco();
	CreateHistogamsRecoClusters();


	if(nevents>0) nEvents = nevents;
    //////TGraphErrors *g_nHCal_neutralEfromchargedvsneutralEMC = new TGraphErrors();
	for(unsigned ev=0; ev<nEvents; ++ev) {

		if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

		MakeEvent(reader, ev); // execute for each event

		if(debug) std::cout<<"End of event"<<std::endl;

	} // event loop

	////g_nHCal_neutralEfromchargedvsneutralEMC->Draw("AP");

	std::cout<<"Writing output"<<std::endl;
    /////g_nHCal_neutralEfromchargedvsneutralEMC->Write();
	output->Write();
	

	//DeleteHistogamsReco();
	//DeleteHistogamsRecoClusters();

	output->Close();

	std::cout<<"Finished!"<<std::endl;

	delete output;

	return 1;

}



int MakeEvent(podio::ROOTReader *reader, unsigned ev)
{

	// Get frame
    auto frame = podio::Frame(reader->readNextEntry(podio::Category::Event));

    /*std::vector<std::string> collections_names = frame.getAvailableCollections();

	if (ev==0) PrintStringVector(collections_names);*/

	//reader->goToEvent(ev);
	//reader->readEvent();
	//////if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

	//store->endOfEvent();


	// Get collections
	auto& MCParticles_coll  = frame.get<edm4hep::MCParticleCollection>("MCParticles");
	auto& nHCal_simhitscoll = frame.get<edm4hep::SimCalorimeterHitCollection>("HcalEndcapNHits");
	auto& nHCal_rechitscoll = frame.get<edm4eic::CalorimeterHitCollection>("HcalEndcapNRecHits");
	/////auto& nHCal_mergedhitscoll = frame.get<edm4eic::CalorimeterHitCollection>("HcalEndcapNMergedHits");
	auto& nHCal_Cluster_Rec_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
	auto& nHCal_Cluster_MC_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNTruthClusters");
	auto& nHCal_Hitcontributions_coll = frame.get<edm4hep::CaloHitContributionCollection>("HcalEndcapNHitsContributions");
	auto& nHCal_recoClusterMCparticleAssociation_coll = frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("HcalEndcapNClusterAssociations");


	int nPion_p = 0;
	int nPion_n = 0;
	int nKaon_p = 0;
	int nKaon_n = 0;
	int nProton_p = 0;
	int nProton_n = 0;
	int nElectron_p = 0;
	int nElectron_n = 0;

	int nNeutron = 0;
	int nGamma = 0;

	int nMCpart = 0;
	int nMCpart_gen = 0;
	int nMCpart_sec = 0;


	h_Events->Fill(1.0);

	// MC particle loop

	if(!MCParticles_coll.isValid())
		cout<<"MCParticleCollection does not exist!"<<endl;

	if(debug) cout<<"MCParticles size = "<<MCParticles_coll.size()<<endl;


	for (unsigned mc_iter = 0; mc_iter < MCParticles_coll.size(); ++mc_iter) {

		edm4hep::MCParticle mcpart =  MCParticles_coll.at(mc_iter);


		if(debug)
		{
			cout<<endl;

			cout<<"MCParticle generator status = "<<mcpart.getGeneratorStatus()<<endl;
			cout<<"MCParticle simulator status = "<<mcpart.getSimulatorStatus()<<endl;
			cout<<"MCParticle isCreatedInSimulation = "<<mcpart.isCreatedInSimulation()<<endl;
		}

		TVector3 mcMom(mcpart.getMomentum().x, mcpart.getMomentum().y, mcpart.getMomentum().z);
		TVector3 mcMomEnd(mcpart.getMomentumAtEndpoint ().x, mcpart.getMomentumAtEndpoint ().y, mcpart.getMomentumAtEndpoint ().z);
		TVector3 mcStart(mcpart.getVertex().x, mcpart.getVertex().y, mcpart.getVertex().z);
		TVector3 mcEnd(mcpart.getEndpoint().x, mcpart.getEndpoint().y, mcpart.getEndpoint().z);

		//vector<edm4hep::MCParticleData> *parents_check = new vector<edm4hep::MCParticleData>;
		//GetMCParentsData(mcpart_data, MCParticles_data, MCparents_data, parents_check);

		auto parents_check = mcpart.getParents();

		if(debug)
		{
			cout<<"MCParticle parents size = "<<parents_check.size()<<endl;
		}

		//if(mcpart.isCreatedInSimulation()) continue; // select primaries, reject secondaries
		//if(!mcpart.isCreatedInSimulation()) continue; // select secondaries, reject primaries
		//if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()==1) continue; // select secondaries, reject primaries

		//	Correct!
		if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()!=0) continue; // select secondaries, reject primaries
		//if(mcMom.Eta()<-4.0 ||  mcMom.Eta()>-1.0)	continue;
		if(mcMom.Eta()<-4.14 ||  mcMom.Eta()>-1.18)	continue;
		//if(mcEnd.z()>-3250)	continue;

		nMCpart++;

		if(debug)
		{
			cout<<"MCParticle px = "<<mcMom.x()<<endl;
			cout<<"MCParticle py = "<<mcMom.y()<<endl;
			cout<<"MCParticle pz = "<<mcMom.z()<<endl;
		}

		h_MCpart_mass->Fill(mcpart.getMass());
		h_MCpart_charge->Fill(mcpart.getCharge());
		h_MCpart_E->Fill(mcpart.getEnergy());
		h_MCpart_p->Fill(mcMom.Mag());
		h_MCpart_pT->Fill(mcMom.Pt());

		h_MCpart_mom_x->Fill(mcMom.x());
		h_MCpart_mom_y->Fill(mcMom.y());
		h_MCpart_mom_z->Fill(mcMom.z());

		h_MCpart_eta->Fill(mcMom.Eta());
		h_MCpart_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

		h_MCpart_xy->Fill(mcStart.x(), mcStart.y());
		h_MCpart_zr->Fill(mcStart.z(), mcStart.Pt());

		h_MCpart_end_p->Fill(mcMomEnd.Mag());
		h_MCpart_end_pT->Fill(mcMomEnd.Pt());

		h_MCpart_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
		h_MCpart_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

		h_MCpart_genStatus->Fill(mcpart.getGeneratorStatus());

		if(mcpart.getPDG() == 211) nPion_p++;
		if(mcpart.getPDG() == -211) nPion_n++;
		if(mcpart.getPDG() == 321) nKaon_p++;
		if(mcpart.getPDG() == -321) nKaon_n++;
		if(mcpart.getPDG() == 2212) nProton_p++;
		if(mcpart.getPDG() == -2212) nProton_n++;
		if(mcpart.getPDG() == -11) nElectron_p++;
		if(mcpart.getPDG() == 11) nElectron_n++;

		if(mcpart.getPDG() == 2112) nNeutron++;
		if(mcpart.getPDG() == 22) nGamma++;


		// momentum
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_p->Fill(mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_p->Fill(mcMom.Mag());

		// energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_E->Fill(mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_E->Fill(mcpart.getEnergy());


		// eta, momentum
		if(mcpart.getPDG() == 211) h_MCpart_pion_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_pion_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_proton_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_proton_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		// eta, energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());


		// Generated MC particles
		if(mcpart.getGeneratorStatus()==1)
		{
			h_MCpart_gen_mass->Fill(mcpart.getMass());
			h_MCpart_gen_charge->Fill(mcpart.getCharge());
			h_MCpart_gen_E->Fill(mcpart.getEnergy());
			h_MCpart_gen_p->Fill(mcMom.Mag());
			h_MCpart_gen_pT->Fill(mcMom.Pt());

			h_MCpart_gen_eta->Fill(mcMom.Eta());
			h_MCpart_gen_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_gen_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_gen_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_gen_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_gen_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_gen_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_gen_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_gen++;
		}


		// Secondary MC particles
		if(mcpart.getGeneratorStatus()==0)
		{
			h_MCpart_sec_mass->Fill(mcpart.getMass());
			h_MCpart_sec_charge->Fill(mcpart.getCharge());
			h_MCpart_sec_E->Fill(mcpart.getEnergy());
			h_MCpart_sec_p->Fill(mcMom.Mag());
			h_MCpart_sec_pT->Fill(mcMom.Pt());

			h_MCpart_sec_eta->Fill(mcMom.Eta());
			h_MCpart_sec_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_sec_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_sec_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_sec_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_sec_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_sec_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_sec_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_sec++;

			bool parentIsPrimary = false;

			auto parents_data = mcpart.getParents();
			/////auto daughters_data = mcpart.getDaughters();

			for (size_t parentIter = 0; parentIter < parents_data.size(); ++parentIter) {

				edm4hep::MCParticle mcpart_parent = parents_data.at(parentIter);

				if(mcpart_parent.getGeneratorStatus()==1)	parentIsPrimary = true;
			}

			//for (int parentIter = 0; parentIter < MCparents.size(); ++parentIter) {
/*			for (int parentIter = mcpart_data.parents_begin; parentIter < mcpart_data.parents_end; ++parentIter) {

				//if(!MCParticles_data->at(parentIter).isCreatedInSimulation)	parentIsPrimary = true;

	        	unsigned parentID = MCparents_data->at(parentIter).index;

				edm4hep::MCParticleData mcpart_data_parent = MCParticles_data->at(parentID);
				edm4hep::MCParticle mcpart_parent(mcpart_data_parent.PDG, mcpart_data_parent.generatorStatus, mcpart_data_parent.simulatorStatus, mcpart_data_parent.charge, mcpart_data_parent.time, mcpart_data_parent.mass, mcpart_data_parent.vertex, mcpart_data_parent.endpoint, mcpart_data_parent.momentum, mcpart_data_parent.momentumAtEndpoint, mcpart_data_parent.spin, mcpart_data_parent.colorFlow);

				if(!mcpart_parent.isCreatedInSimulation())	parentIsPrimary = true;
			}*/

			// MC particles - 1st generation daughters
			if(parentIsPrimary)
			{
				h_MCpart_1stgen_daughter_mass->Fill(mcpart.getMass());
				h_MCpart_1stgen_daughter_charge->Fill(mcpart.getCharge());
				h_MCpart_1stgen_daughter_E->Fill(mcpart.getEnergy());
				h_MCpart_1stgen_daughter_p->Fill(mcMom.Mag());
				h_MCpart_1stgen_daughter_pT->Fill(mcMom.Pt());

				h_MCpart_1stgen_daughter_eta->Fill(mcMom.Eta());
				h_MCpart_1stgen_daughter_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

				h_MCpart_1stgen_daughter_xy->Fill(mcStart.x(), mcStart.y());
				h_MCpart_1stgen_daughter_zr->Fill(mcStart.z(), mcStart.Pt());

				h_MCpart_1stgen_daughter_end_p->Fill(mcMomEnd.Mag());
				h_MCpart_1stgen_daughter_end_pT->Fill(mcMomEnd.Pt());

				h_MCpart_1stgen_daughter_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
				h_MCpart_1stgen_daughter_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());
			}

		}	// Secondary MC particles

	} // MCParticles loop

	//h_MCpart->Fill(MCParticles_frame.size());
	//h_MCpart->Fill(MCParticles_data->size());
	h_MCpart->Fill(nMCpart);

	h_MCpart_nPion_p->Fill(nPion_p);
	h_MCpart_nPion_n->Fill(nPion_n);
	h_MCpart_nKaon_p->Fill(nKaon_p);
	h_MCpart_nKaon_n->Fill(nKaon_n);
	h_MCpart_nProton_p->Fill(nProton_p);
	h_MCpart_nProton_n->Fill(nProton_n);
	h_MCpart_nElectron_p->Fill(nElectron_p);
	h_MCpart_nElectron_n->Fill(nElectron_n);

	h_MCpart_nNeutron->Fill(nNeutron);
	h_MCpart_nGamma->Fill(nGamma);

	h_MCpart_nGen->Fill(nMCpart_gen);
	h_MCpart_nSec->Fill(nMCpart_sec);


	if(!nHCal_rechitscoll.isValid())
		cout<<"HcalEndcapNRecHits collection does not exist!"<<endl;

	if(debug) cout<<"HcalEndcapNRecHits collection size = "<<nHCal_rechitscoll.size()<<endl;

	h_nHCal_nrechits->Fill(nHCal_rechitscoll.size());

	            

        double rechitEtotal = 0;
		for (unsigned hit_iter = 0; hit_iter < nHCal_rechitscoll.size(); ++hit_iter) {

			edm4eic::CalorimeterHit rechit_nHCal = nHCal_rechitscoll.at(hit_iter);
			const uint64_t recCellID = rechit_nHCal.getCellID();
            
			double highestcontrienergy = 0;
			int highestcontriPDG;
			double contribETotal = 0;

			double neutralEdep = 0;
			double chargedEdep = 0;

			/*double neutralE = 1.37215;
			double chargedE = 1.00969;*/

			

			if(!rechit_nHCal.isAvailable())
				cout<<"CalorimeterHit does not exist! index = "<<rechit_nHCal<<endl;

            rechitEtotal += rechit_nHCal.getEnergy();
			h_nHCal_rechit_E->Fill(rechit_nHCal.getEnergy());

			h_nHCal_rechit_pos_x->Fill(rechit_nHCal.getPosition().x);
			h_nHCal_rechit_pos_y->Fill(rechit_nHCal.getPosition().y);
			h_nHCal_rechit_pos_z->Fill(rechit_nHCal.getPosition().z);
			h_nHCal_rechit_pos_R->Fill(sqrt(pow(rechit_nHCal.getPosition().x, 2) + pow(rechit_nHCal.getPosition().y, 2)));
			h_nHCal_rechit_pos_xy->Fill(rechit_nHCal.getPosition().x, rechit_nHCal.getPosition().y); 

			cout << rechit_nHCal.getRawHit().getAmplitude() << endl;

			for (unsigned hit_itersim = 0; hit_itersim < nHCal_simhitscoll.size(); ++hit_itersim) {
				edm4hep::SimCalorimeterHit simhit_nHCal = nHCal_simhitscoll.at(hit_itersim);
				const uint64_t simCellID  = simhit_nHCal.getCellID();
                const bool     isSameCell = (recCellID == simCellID);
                if (!isSameCell) continue;
				/////if (simhit_nHCal.getEnergy() < 0.1875e-3) continue;*/
				

				
				for (size_t iContrib = 0; edm4hep::CaloHitContribution contrib : simhit_nHCal.getContributions()) {
					//////auto contrib = nHCal_Hitcontributions_coll.at(iContrib);
					auto particle = contrib.getParticle();
					/////if (contrib.getTime() > 100) continue;
                    contribETotal += contrib.getEnergy();
					if (particle.getGeneratorStatus() == 1)  {
					  if (particle.getPDG() == 2112) {
						neutralEdep += contrib.getEnergy();
					  }
					   if (particle.getPDG() == -211) {
						chargedEdep += contrib.getEnergy();
					  }
					}

					if (particle.getGeneratorStatus() != 1)  {
					  if (getPDGofPrimary(particle) == 2112) {
						neutralEdep += contrib.getEnergy();
						////neutralE = particle.getEnergy();
					  }
					   if (getPDGofPrimary(particle) == -211) {	
						chargedEdep += contrib.getEnergy();
						/////chargedE = particle.getEnergy();
					  }
					}

					if (contrib.getEnergy() > highestcontrienergy) {
						highestcontrienergy = contrib.getEnergy();
						highestcontriPDG = particle.getPDG();
					}

					std::cout << "        [Contrib #" << iContrib << "] (reco hit, sim hit, contrib, particle) ID = ("
                      << rechit_nHCal.getObjectID().index      << ", "
                      << simhit_nHCal.getObjectID().index      << ", "
                      << contrib.getObjectID().index  << ", "
                      << particle.getObjectID().index << ")"
                      << std::endl;

					std::cout 
                      << "          Rec Hit:  energy = " << rechit_nHCal.getEnergy() << ", time = " << rechit_nHCal.getTime() << "\n"
                      << "          Sim Hit:  energy = " << simhit_nHCal.getEnergy() << "\n"
                      << "          Contrib:  energy = " << contrib.getEnergy() << ", time = " << contrib.getTime() << "\n"
                      << "          Particle: energy = " << particle.getEnergy() << ", pdg = " << particle.getPDG() << ", gen status = " << particle.getGeneratorStatus()
                      << std::endl;
					  ++iContrib;
				}
                /////;
				
				/////h_nHCal_neutralEdepchargedEdep_recHits->Fill(((neutralEdep + chargedEdep)/(neutralE + chargedE)), (chargedEdep/chargedE));
				//////h_nHCal_neutralEdepchargedEdep_recHits->Fill(neutralEdep, chargedEdep);


			}

			std::cout << "Highest energy contribution:  " << highestcontrienergy << std::endl;
					  std::cout << "corresponding PDG:  " << highestcontriPDG << std::endl;

			if (highestcontriPDG == 211) h_nHCal_rechit_Piplus_pos_R->Fill(sqrt(pow(rechit_nHCal.getPosition().x, 2) + pow(rechit_nHCal.getPosition().y, 2)));
			if (highestcontriPDG == -211) h_nHCal_rechit_Piminus_pos_R->Fill(sqrt(pow(rechit_nHCal.getPosition().x, 2) + pow(rechit_nHCal.getPosition().y, 2)));
			if (highestcontriPDG == 2112) h_nHCal_rechit_Neutron_pos_R->Fill(sqrt(pow(rechit_nHCal.getPosition().x, 2) + pow(rechit_nHCal.getPosition().y, 2)));

			if (((100.0*neutralEdep)/(0.0095*rechit_nHCal.getEnergy())) > 100.0 || ((100.0*chargedEdep)/(0.0095*rechit_nHCal.getEnergy())) > 100.0) {
				std::cout << "Energy deposition percentage is greater than 100% for rechit " << hit_iter << std::endl;
				std::cout << "neutral particle energy deposition percentage:  " << ((100.0*neutralEdep)/(0.0095*rechit_nHCal.getEnergy())) << std::endl;
				std::cout << "charged particle energy deposition percentage:  " << ((100.0*chargedEdep)/(0.0095*rechit_nHCal.getEnergy())) << std::endl;
			}
            
			
			/////h_nHCal_neutralEdepchargedEdep_recHits->Fill(((100.0*neutralEdep)/(0.0095*rechit_nHCal.getEnergy())), ((100.0*chargedEdep)/(0.0095*rechit_nHCal.getEnergy())));
	        SafeFill(h_nHCal_NeutronEdeppionEdep_recHits, ((100.0*neutralEdep)/(0.0095*rechit_nHCal.getEnergy())), ((100.0*chargedEdep)/(0.0095*rechit_nHCal.getEnergy())));

			




		} // HcalEndcapNRecHits loop 

		h_nHCal_rechit_Esum->Fill(rechitEtotal);

		if(!nHCal_simhitscoll.isValid())
		cout<<"HcalEndcapNHits collection does not exist!"<<endl;

	if(debug) cout<<"HcalEndcapNHits collection size = "<<nHCal_simhitscoll.size()<<endl;

	h_nHCal_nsimhits->Fill(nHCal_simhitscoll.size());

	Double_t simhitEtotal = 0;


		for (unsigned hit_iter = 0; hit_iter < nHCal_simhitscoll.size(); ++hit_iter) {

			edm4hep::SimCalorimeterHit simhit_nHCal = nHCal_simhitscoll.at(hit_iter);

			if(!simhit_nHCal.isAvailable())
				cout<<"CalorimeterHit does not exist! index = "<<simhit_nHCal<<endl;

			simhitEtotal += simhit_nHCal.getEnergy();
			h_nHCal_simhit_E->Fill(simhit_nHCal.getEnergy());

			h_nHCal_simhit_pos_x->Fill(simhit_nHCal.getPosition().x);
			h_nHCal_simhit_pos_y->Fill(simhit_nHCal.getPosition().y);
			h_nHCal_simhit_pos_z->Fill(simhit_nHCal.getPosition().z);
			h_nHCal_simhit_pos_R->Fill(sqrt(pow(simhit_nHCal.getPosition().x, 2) + pow(simhit_nHCal.getPosition().y, 2)));
			h_nHCal_simhit_pos_xy->Fill(simhit_nHCal.getPosition().x, simhit_nHCal.getPosition().y);

		} // HcalEndcapNHits loop

		h_nHCal_simhit_Esum->Fill(simhitEtotal);



		if(!nHCal_Cluster_Rec_coll.isValid())
				cout<<"HcalEndcapNClusters collection does not exist!"<<endl;

		if(debug) cout<<"HcalEndcapNClusters collection size = "<<nHCal_Cluster_Rec_coll.size()<<endl;

		h_nHCal_nclusters_Rec->Fill(nHCal_Cluster_Rec_coll.size());

		
        Double_t clusterEtotal = 0;
		Double_t chargedClusterE = 0;
		Int_t charged_nclusters = 0;
		Int_t neutral_nclusters = 0;
		Double_t neutralClusterE = 0;
		


		for (unsigned clu_iter = 0; clu_iter < nHCal_Cluster_Rec_coll.size(); ++clu_iter) {

			edm4eic::Cluster cluster_nHCal_Rec = nHCal_Cluster_Rec_coll.at(clu_iter);

           

			h_nHCal_cluster_Rec_E->Fill(cluster_nHCal_Rec.getEnergy());

			h_nHCal_cluster_Rec_pos_x->Fill(cluster_nHCal_Rec.getPosition().x);
			h_nHCal_cluster_Rec_pos_y->Fill(cluster_nHCal_Rec.getPosition().y);
			h_nHCal_cluster_Rec_pos_z->Fill(cluster_nHCal_Rec.getPosition().z);
			h_nHCal_cluster_Rec_pos_R->Fill(sqrt(pow(cluster_nHCal_Rec.getPosition().x, 2) + pow(cluster_nHCal_Rec.getPosition().y, 2)));
			h_nHCal_cluster_Rec_pos_xy->Fill(cluster_nHCal_Rec.getPosition().x, cluster_nHCal_Rec.getPosition().y);

	        /*for (unsigned clu_iter2 = 0; clu_iter2 < nHCal_Cluster_Rec_coll.size(); ++clu_iter2) {

				edm4eic::Cluster cluster2_nHCal_Rec =  nHCal_Cluster_Rec_coll.at(clu_iter2);

	            if(clu_iter==clu_iter2)	continue;
	            /*double z1 = cluster_nHCal_Rec.getPosition().z;
	            double z2 = cluster2_nHCal_Rec.getPosition().z;
	            //if(abs(z2-z1) <=10){
	            //TVector3 mcProjPos2 = projTrackZ(mcMom2.Eta(), mcMom2.Phi(), projLayerZ, mcStart2);
	            double diffx2 = pow(cluster_nHCal_Rec.getPosition().x - cluster2_nHCal_Rec.getPosition().x, 2);
	            double diffy2 = pow(cluster_nHCal_Rec.getPosition().y - cluster2_nHCal_Rec.getPosition().y, 2);
	            double diffxy = sqrt(diffx2 + diffy2)/10.0; //convert to cm
	            //TVector3 diffVect = mcProjPos-mcProjPos2;
				//diffVect.SetMag(diffVect.Mag()/10.0); // convert [mm]->[cm]
	            double eta = - log(tan(cluster_nHCal_Rec.getIntrinsicTheta()/2));
	            h_nHCal_clusters_Reco_eta_deltaRxy->Fill(eta, diffxy);
	            //}

	        }*/

		   for (unsigned cluasso_iter = 0; cluasso_iter < nHCal_recoClusterMCparticleAssociation_coll.size(); ++cluasso_iter)
      {
		edm4eic::MCRecoClusterParticleAssociation assoc = nHCal_recoClusterMCparticleAssociation_coll.at(cluasso_iter);
		if (assoc.getRec() == cluster_nHCal_Rec) {
				if (assoc.getSim().getGeneratorStatus() == 1) {
				   if (assoc.getSim().getPDG() == -211) {
					chargedClusterE += cluster_nHCal_Rec.getEnergy();
					charged_nclusters++;
				  }
				  if (assoc.getSim().getPDG() == 2112) {
					neutralClusterE += cluster_nHCal_Rec.getEnergy();
					neutral_nclusters++;
				  }
				}
				if (assoc.getSim().getGeneratorStatus() != 1) {
					if (getPDGofPrimary(assoc.getSim()) == -211) {
					chargedClusterE += cluster_nHCal_Rec.getEnergy();
					charged_nclusters++;
					}
					if (getPDGofPrimary(assoc.getSim()) == 2112) {
					neutralClusterE += cluster_nHCal_Rec.getEnergy();
					neutral_nclusters++;
					}
				}
	        }
	  }

	 	clusterEtotal += cluster_nHCal_Rec.getEnergy();

		} // HcalEndcapNClusters loop all inclusive (with split clusters too)
  
		/*Double_t neutralEclusfromcharged = clusterEtotal - 0.8215*1.00969;
		Double_t neutralEclusfromchargederr = 0.1897*1.00969;*/

		Double_t neutralEMCfromcharged = (clusterEtotal - 0.8215*1.00969)/0.5092;

		Double_t neutralEfromcharged = clusterEtotal - chargedClusterE; //charged cluster is the cluster matched with a track
        Double_t neutralEfromchargedweff = neutralEfromcharged;
		Double_t fEICrecon = 0.0095; // sampling fraction mentioned in EICrecon
		Double_t fp1 = 0.00801105; //sampling fraction for 1 GeV pions
		Double_t sigmafp1 = 0.00467597/1.00969; //sigma of sampling fraction [note: it would be different for electrons (but these widths for these two are approx same at low momentum)]
		///Double_t sigmachargedClusterE = (fEICrecon*chargedClusterE*sigmafp1)/(pow(fp1, 2));
		Double_t sigmachargedClusterE = (chargedClusterE*sigmafp1)/fEICrecon;

		Double_t chargedp = 1.0;


		Double_t chicluster = (chargedClusterE - chargedp)/sigmachargedClusterE; //no need to pluggin clustering efficiency here as we can't know exactly how much energy will be deposited by the particle there in that event. So, can't get the efficiency for that energy deposition.

		if (abs(chicluster) > 3.0)
		{
			neutralEfromcharged = clusterEtotal - chargedp; //no need to pluggin clustering efficiency here as we can't know exactly how much energy will be deposited by the particle there in that event. So, can't get the efficiency for that energy deposition.
            neutralEfromchargedweff = clusterEtotal - neutronrecoeff(chargedp)*chargedp;
		}
        
		//remember that nHCal is a compensating calorimeter.

		/*Float_t neutralClusterE = 0;
		
		Float_t chargedClusterE = 0;
		

		 

		for (unsigned cluasso_iter = 0; cluasso_iter < nHCal_recoClusterMCparticleAssociation_coll.size(); ++cluasso_iter)
      {
		edm4eic::MCRecoClusterParticleAssociation assoc = nHCal_recoClusterMCparticleAssociation_coll.at(cluasso_iter);
	   if (assoc.getSim().getGeneratorStatus() == 1) {
		  if (assoc.getSim().getPDG() == 2112) {
			neutralClusterE += assoc.getRec().getEnergy();
			neutral_nclusters++;
		  }
		  if (assoc.getSim().getPDG() == -211) {
			chargedClusterE += assoc.getRec().getEnergy();
			charged_nclusters++;
		  }
		}

		if (assoc.getSim().getGeneratorStatus() != 1) {
			if (getPDGofPrimary(assoc.getSim()) == 2112) {
			  neutralClusterE += assoc.getRec().getEnergy();
			  neutral_nclusters++;
			}
			if (getPDGofPrimary(assoc.getSim()) == -211) {
			  chargedClusterE += assoc.getRec().getEnergy();
			  charged_nclusters++;
			}
		  }
	  }  //////RecoClusterMCparticleAssociation loop */

	  h_nHCal_neutral_cluster_energytot_vs_nclusters->Fill(neutral_nclusters, neutralClusterE);
	  h_nHCal_charged_cluster_energytot_vs_nclusters->Fill(charged_nclusters, chargedClusterE);

	  float neutralEdepMC = 0;
	  float chargedEdepMC = 0;

      for (unsigned hitcontri_iter = 0; hitcontri_iter < nHCal_Hitcontributions_coll.size(); ++hitcontri_iter) {

			edm4hep::CaloHitContribution contrib = nHCal_Hitcontributions_coll.at(hitcontri_iter);

			/*if(!contrib.isAvailable())
				cout<<"CaloHitContribution does not exist! index = "<<hitcontri_nHCal<<endl;*/

			auto particle = contrib.getParticle();

			if (particle.getGeneratorStatus() == 1)  {
					  if (particle.getPDG() == 2112) {
						neutralEdepMC += contrib.getEnergy();
					  }
					   if (particle.getPDG() == -211) {
						chargedEdepMC += contrib.getEnergy();
					  }
					}

			if (particle.getGeneratorStatus() != 1)  {
					  if (getPDGofPrimary(particle) == 2112) {
						neutralEdepMC += contrib.getEnergy();
						////neutralE = particle.getEnergy();
					  }
					   if (getPDGofPrimary(particle) == -211) {	
						chargedEdepMC += contrib.getEnergy();
						/////chargedE = particle.getEnergy();
					  }
					}

	  } //////Hitcontributions loop

	  h_nHCal_neutralEMCvsReco->Fill(neutralEdepMC/0.0095, neutralClusterE);
	  h_nHCal_chargedEMCvsReco->Fill(chargedEdepMC/0.0095, chargedClusterE);

	  /*g_nHCal_neutralEfromchargedvsneutralEMC->SetPoint(ev+1 , neutralEdepMC/0.0095, neutralEclusfromcharged);   
	  g_nHCal_neutralEfromchargedvsneutralEMC->SetPointError(ev+1 , 0, neutralEclusfromchargederr);    */
      
	  if ((chargedClusterE > 0) && (neutralClusterE > 0)) {
	  //////h_nHCal_neutralEClusfromchargedvsneutralEClus->Fill(neutralClusterE, neutralEclusfromcharged);
	  h_nHCal_neutralEMCfromchargedvsneutralEMC->Fill((neutralEdepMC/0.0095), neutralEMCfromcharged);
	  h_nHCal_neutralClustersvschargedClusterswnonzeroE->Fill(charged_nclusters, neutral_nclusters);
	  }
      
	  double neutralreceff = neutralClusterE/(neutralEdepMC/0.0095);
	  double chargedreceff = chargedClusterE/(chargedEdepMC/0.0095);

	  if (charged_nclusters <= 1) {
		Double_t neutralclusterR;
		Double_t chargedclusterR;
		h_nHCal_neutralClusterEvschargedClusterEwoneone->Fill(chargedClusterE, neutralClusterE);
		for (unsigned clu_iter = 0; clu_iter < nHCal_Cluster_Rec_coll.size(); ++clu_iter) {

			edm4eic::Cluster cluster_nHCal_Rec = nHCal_Cluster_Rec_coll.at(clu_iter);
			for (unsigned cluasso_iter = 0; cluasso_iter < nHCal_recoClusterMCparticleAssociation_coll.size(); ++cluasso_iter)
      {
		edm4eic::MCRecoClusterParticleAssociation assoc = nHCal_recoClusterMCparticleAssociation_coll.at(cluasso_iter);
		if (assoc.getRec() == cluster_nHCal_Rec) {
				if (assoc.getSim().getGeneratorStatus() == 1) {
				   if (assoc.getSim().getPDG() == -211) {
					chargedclusterR = sqrt(pow(cluster_nHCal_Rec.getPosition().x, 2) + pow(cluster_nHCal_Rec.getPosition().y, 2));
				  }
				  if (assoc.getSim().getPDG() == 2112) {
					neutralclusterR = sqrt(pow(cluster_nHCal_Rec.getPosition().x, 2) + pow(cluster_nHCal_Rec.getPosition().y, 2));
				  }
				}
				if (assoc.getSim().getGeneratorStatus() != 1) {
					if (getPDGofPrimary(assoc.getSim()) == -211) {
					 chargedclusterR = sqrt(pow(cluster_nHCal_Rec.getPosition().x, 2) + pow(cluster_nHCal_Rec.getPosition().y, 2));
					}
					if (getPDGofPrimary(assoc.getSim()) == 2112) {
					 neutralclusterR = sqrt(pow(cluster_nHCal_Rec.getPosition().x, 2) + pow(cluster_nHCal_Rec.getPosition().y, 2));
					}
				}
	        }
	  }


	  /*if (abs(neutralclusterR - chargedclusterR) >= 50) {
		neutralEfromcharged = clusterEtotal - chargedClusterE;
	  }*/

	  h_nHCal_clusterdistance->Fill(abs(neutralclusterR - chargedclusterR));

	  } //// cluster loop

	  h_nHCal_neutralEClusfromchargedvsneutralEClus->Fill(neutralClusterE, neutralEfromcharged);
	  h_nHCal_neutralEfromchargedvsneutralEMC->Fill((neutralEdepMC/0.0095), neutralEfromcharged);
      
	  Double_t neutronEMCwEff = neutronrecoeff((neutralEdepMC/0.0095))*(neutralEdepMC/0.0095);
	  h_nHCal_checkeffN->Fill(neutralClusterE, neutronEMCwEff);
    
	  if ((neutralEfromcharged - neutronEMCwEff) > 0.0) {
	   cout << "(neutralEdepMC/0.0095) = " << (neutralEdepMC/0.0095) << "   neutralEfromcharged =  " << neutralEfromcharged << "---------------------------------------------------------------------------------------------------------------------- check here" << endl;
	   cout << "neutralClusterE = " << neutralClusterE << "   neutronEMCwEff =  " << neutronEMCwEff << "---------------------------------------------------------------------------------------------------------------------- check here" << endl;
	   cout << "totalClusterE = " << clusterEtotal << "   chargedClusterE =  " << chargedClusterE << "---------------------------------------------------------------------------------------------------------------------- check here" << endl;
	  }

	  h_nHCal_compareperformanceweff->Fill(neutralEfromcharged - neutronEMCwEff);
	  h_nHCal_compareperformancewdiff->Fill(neutralEfromcharged - (neutralEdepMC/0.0095));
	  h_nHCal_compareperformancewpioneffneutroneff->Fill(neutralEfromchargedweff - neutronEMCwEff);
	  SafeFill(h_nHCal_compareperformance, neutralEfromcharged/(neutralEdepMC/0.0095));
	  SafeFill(h_nHCal_compareperformance2D, neutralEdepMC, neutralEfromcharged/(neutralEdepMC/0.0095));

	  } //// if (charged_nclusters <= 1)
	 
	  /*h_nHCal_neutralEreceffvsnClusters->Fill(neutral_nclusters, neutralreceff);
	  h_nHCal_chargedEreceffvsnClusters->Fill(charged_nclusters, chargedreceff);*/
	  SafeFill(h_nHCal_neutralEreceffvsnClusters, neutral_nclusters, neutralreceff);
	  SafeFill(h_nHCal_chargedEreceffvsnClusters, charged_nclusters, chargedreceff);

	  SafeFill(h_nHCal_neutralEreceffvschargedEreceff, chargedreceff, neutralreceff);

	  SafeFill(h_nHCal_neutralEreceffvsneutralEMC, (neutralEdepMC/0.0095), neutralreceff);
	  SafeFill(h_nHCal_chargedEreceffvschargedEMC, (chargedEdepMC/0.0095), chargedreceff);

	  double totalEdepMC = neutralEdepMC + chargedEdepMC;
	  

	  double chargedRecofractionofMC = chargedClusterE/(totalEdepMC/0.0095);
	  double neutralRecofractionofMC = neutralClusterE/(totalEdepMC/0.0095);

	  SafeFill(h_nHCal_neutralErecfractionvschargedErecfraction, chargedRecofractionofMC, neutralRecofractionofMC);
      
	  double neutralEmcFraction = neutralEdepMC/totalEdepMC;
	  double chargedEmcFraction = chargedEdepMC/totalEdepMC;
	  double neutralRecoFraction = neutralClusterE/clusterEtotal;
	  double chargedRecoFraction = chargedClusterE/clusterEtotal;

	  /*h_nHCal_neutralErecfractionvsEmcFraction->Fill(neutralEmcFraction, neutralRecoFraction);
	  h_nHCal_chargedErecfractionvsEmcFraction->Fill(chargedEmcFraction, chargedRecoFraction);

	  h_nHCal_lostEfrac->Fill(((totalEdepMC/0.0095) - clusterEtotal)/(totalEdepMC/0.0095));
      
	  h_nHCal_neutralrecoEfracdeviation->Fill(neutralEmcFraction, ((neutralRecoFraction - neutralEmcFraction)));
	  h_nHCal_chargedrecoEfracdeviation->Fill(chargedEmcFraction, ((chargedRecoFraction - chargedEmcFraction)));*/

	  SafeFill(h_nHCal_neutralErecfractionvsEmcFraction, neutralEmcFraction, neutralRecoFraction);
	  SafeFill(h_nHCal_chargedErecfractionvsEmcFraction, chargedEmcFraction, chargedRecoFraction);

	  SafeFill(h_nHCal_neutralERecofractionvschargedERecofraction, chargedRecoFraction, neutralRecoFraction);
	  SafeFill(h_nHCal_neutralEMCfractionvschargedEMCfraction, chargedEmcFraction, neutralEmcFraction);
	  
	  SafeFill(h_nHCal_lostEfrac, ((totalEdepMC/0.0095) - clusterEtotal)/(totalEdepMC/0.0095));
	  SafeFill(h_nHCal_neutralrecoEfracdeviation, neutralEmcFraction, ((neutralRecoFraction - neutralEmcFraction)));
	  SafeFill(h_nHCal_chargedrecoEfracdeviation, chargedEmcFraction, ((chargedRecoFraction - chargedEmcFraction)));

	  Double_t clusteringEfficiency = (clusterEtotal/(totalEdepMC/0.0095));
	  

	  /*Double_t fractionofneutralEaltered = ((clusteringEfficiency*(neutralEdepMC/0.0095))/neutralClusterE) - 1;
	  Double_t fractionofchargedEaltered = ((clusteringEfficiency*(chargedEdepMC/0.0095))/chargedClusterE) - 1;

	  

	  h_nHCal_f_neutral->Fill(neutralClusterE, fractionofneutralEaltered);
	  h_nHCal_f_charged->Fill(chargedClusterE, fractionofchargedEaltered);*/

	  h_nHCal_sanitycheck->Fill((neutralClusterE - (clusteringEfficiency*(neutralEdepMC/0.0095))),(chargedClusterE - (clusteringEfficiency*(chargedEdepMC/0.0095))));
	  
	  ///////SafeFill(h_nHCal_sanitycheck, fractionofneutralEaltered*neutralClusterE, fractionofchargedEaltered*chargedClusterE);

	  Double_t Ealteredneutral = (neutralClusterE - (clusteringEfficiency*(neutralEdepMC/0.0095)));
	  Double_t Ealteredcharged = (chargedClusterE - (clusteringEfficiency*(chargedEdepMC/0.0095)));

	  Double_t f_neutral = (-1*Ealteredneutral)/neutralClusterE;
	  Double_t f_charged = (-1*Ealteredcharged)/chargedClusterE;

	  SafeFill(h_nHCal_f_neutral, neutralClusterE, f_neutral);
	  SafeFill(h_nHCal_f_charged, chargedClusterE, f_charged);

	  SafeFill(h_nHCal_f_neutralvsf_charged, f_charged, f_neutral);

	  Double_t EalterationperEMCthatenteredclusteringneutral = Ealteredneutral/(clusteringEfficiency*(neutralEdepMC/0.0095));
	  Double_t EalterationperEMCthatenteredclusteringcharged = Ealteredcharged/(clusteringEfficiency*(chargedEdepMC/0.0095));

	  /////h_nHCal_EalterationperEMCthatenteredclustering->Fill(EalterationperEMCthatenteredclusteringneutral, EalterationperEMCthatenteredclusteringcharged);
	  SafeFill(h_nHCal_EalterationperEMCthatenteredclustering, EalterationperEMCthatenteredclusteringneutral, EalterationperEMCthatenteredclusteringcharged);



		if(!nHCal_Cluster_MC_coll.isValid())
				cout<<"HcalEndcapNTruthClusters collection does not exist!"<<endl;

		if(debug) cout<<"HcalEndcapNTruthClusters collection size = "<<nHCal_Cluster_MC_coll.size()<<endl;

		h_nHCal_nclusters_MC->Fill(nHCal_Cluster_MC_coll.size());


		for (unsigned clu_iter = 0; clu_iter < nHCal_Cluster_MC_coll.size(); ++clu_iter) {

			edm4eic::Cluster cluster_nHCal_MC = nHCal_Cluster_MC_coll.at(clu_iter);


			h_nHCal_cluster_MC_E->Fill(cluster_nHCal_MC.getEnergy());

			h_nHCal_cluster_MC_pos_x->Fill(cluster_nHCal_MC.getPosition().x);
			h_nHCal_cluster_MC_pos_y->Fill(cluster_nHCal_MC.getPosition().y);
			h_nHCal_cluster_MC_pos_z->Fill(cluster_nHCal_MC.getPosition().z);
			h_nHCal_cluster_MC_pos_R->Fill(sqrt(pow(cluster_nHCal_MC.getPosition().x, 2) + pow(cluster_nHCal_MC.getPosition().y, 2)));
			h_nHCal_cluster_MC_pos_xy->Fill(cluster_nHCal_MC.getPosition().x, cluster_nHCal_MC.getPosition().y);

	        for (unsigned clu_iter2 = 0; clu_iter2 < nHCal_Cluster_MC_coll.size(); ++clu_iter2) {

				edm4eic::Cluster cluster2_nHCal_MC =  nHCal_Cluster_MC_coll.at(clu_iter2);

	            if(clu_iter==clu_iter2)	continue;
	            /*double z1 = cluster_nHCal_MC.getPosition().z;
	            double z2 = cluster2_nHCal_MC.getPosition().z;*/
	            //if(abs(z2-z1) <=10){
	            //TVector3 mcProjPos2 = projTrackZ(mcMom2.Eta(), mcMom2.Phi(), projLayerZ, mcStart2);
	            double diffx2 = pow(cluster_nHCal_MC.getPosition().x - cluster2_nHCal_MC.getPosition().x, 2);
	            double diffy2 = pow(cluster_nHCal_MC.getPosition().y - cluster2_nHCal_MC.getPosition().y, 2);
	            double diffxy = sqrt(diffx2 + diffy2)/10.0; //convert to cm
	            //TVector3 diffVect = mcProjPos-mcProjPos2;
				//diffVect.SetMag(diffVect.Mag()/10.0); // convert [mm]->[cm]
	            double eta = - log(tan(cluster_nHCal_MC.getIntrinsicTheta()/2));
	            h_nHCal_clusters_MC_eta_deltaRxy->Fill(eta, diffxy);
	            //}

	        }

	     //loop over all other clusters, fill histograms with distances between typical clusters (do same for reco)
	     //eventually loop at distances of clusters from neutrals, with all other clusters
	     //look into associations objects in the tree

		} // HcalEndcapNTruthClusters loop

	    //loop over one cluster, and inner loop with all other clusters nad check distances

	return 1;

}

