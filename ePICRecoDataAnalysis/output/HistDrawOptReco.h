/*
 * HistDrawOpt.h
 *
 *  Created on: 26 sie 2015
 *      Author: Khaless
 */

#include "TString.h"

#ifndef HISTDRAWOPTRECO_H_
#define HISTDRAWOPTRECO_H_

TString getHistDrawOpt(TObject *obj, Bool_t &logScale)
{
	TString drawOpt;

	TString name = obj->GetName();

	//cout<<name<<endl;

	if(!name.CompareTo("h_Events")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_nPion_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nPion_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nKaon_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nKaon_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nProton_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nProton_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nElectron_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nElectron_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_nNeutron")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_nGamma")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_nGen")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_nSec")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	if(!name.CompareTo("h_MCpart_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-5.0, 5.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_mom_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-10.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_mom_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-10.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_mom_z")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-10.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-8.0, 8.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_etaphi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_end_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_end_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_posEnd_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_posEnd_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_genStatus")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100000.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	// momentum
	if(!name.CompareTo("h_MCpart_Pion_p_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Pion_n_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Kaon_p_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Kaon_n_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Proton_p_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Proton_n_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Electron_p_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Electron_n_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_Neutron_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	if(!name.CompareTo("h_MCpart_Gamma_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	// energy

	if(!name.CompareTo("h_MCpart_Pion_p_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Pion_n_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Kaon_p_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Kaon_n_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Proton_p_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Proton_n_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Electron_p_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_Electron_n_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_Neutron_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_Gamma_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}



	// Generated MC particles
	if(!name.CompareTo("h_MCpart_gen_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_gen_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-5.0, 5.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_gen_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-8.0, 8.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_etaphi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_gen_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_end_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_gen_end_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_gen_posEnd_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_gen_posEnd_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	// Secondary MC particles
	if(!name.CompareTo("h_MCpart_sec_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_sec_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-5.0, 5.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_sec_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	if(!name.CompareTo("h_MCpart_sec_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-8.0, 8.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_etaphi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_sec_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_end_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_sec_end_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_sec_posEnd_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_sec_posEnd_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	// MC particles - 1st generation daughters
	if(!name.CompareTo("h_MCpart_1stgen_daughter_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_1stgen_daughter_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-5.0, 5.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_1stgen_daughter_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(-8.0, 8.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_etaphi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_1stgen_daughter_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_end_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_1stgen_daughter_end_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_MCpart_1stgen_daughter_posEnd_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_MCpart_1stgen_daughter_posEnd_zr")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	if(!name.CompareTo("h_nECal_hit_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nECal_hit_Esum")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nECal_nhits")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}


	if(!name.CompareTo("h_nHCal_hit_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_hit_Esum")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nCal_hit_delE_perevent")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_nhits")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_hit_pos_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_hit_pos_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_hit_pos_z")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_hit_pos_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetRangeUser(-3000.0, 3000.0);
		objH2->GetXaxis()->SetRangeUser(-3000.0, 3000.0);
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->RebinY(10);
		objH2->RebinX(10);
		//objH1->RebinX(16);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_hit_pos_rE")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->RebinX(16);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nCal_hits_Esum")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}






	// HcalEndcapNClusters

	if(!name.CompareTo("h_nHCal_cluster_Rec_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		objH1->RebinX(1000);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_nclusters_Rec")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_Rec_pos_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_cluster_Rec_pos_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_cluster_Rec_pos_z")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_Rec_pos_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetRangeUser(0.0, 3000.0);
		objH2->GetXaxis()->SetRangeUser(0.0, 3000.0);
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_Rec_pos_rE")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->RebinY(50);
		objH2->RebinX(6);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}



	// HcalEndcapNTruthClusters

	if(!name.CompareTo("h_nHCal_cluster_MC_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		objH1->RebinX(1000);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_nclusters_MC")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_MC_pos_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_cluster_MC_pos_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_nHCal_cluster_MC_pos_z")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 10.0);
		objH1->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_MC_pos_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->GetYaxis()->SetRangeUser(0.0, 3000.0);
		objH2->GetXaxis()->SetRangeUser(0.0, 3000.0);
		objH2->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_cluster_MC_pos_rE")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		objH2->RebinY(50);
		objH2->RebinX(6);
		objH2->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_clusters_Reco_eta_deltaRxy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_nHCal_clusters_MC_eta_deltaRxy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//drawOpt = "e";
		//logScale=kTRUE;
	}



	return drawOpt;
}



#endif /* HISTDRAWOPTRECO_H_ */
