#define SkimerBoost_cxx
#include "SkimerBoost.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <TMath.h>
#include <string>
#include <sstream>
using namespace std;


void SkimerBoost::Loop(TString OutputFile)
{
    
//    TH1F* hEvents = (TH1F*)gDirectory->Get("ggNtuplizer/hEvents");
//    TH1F* hPU     = (TH1F*)gDirectory->Get("ggNtuplizer/hPU");
//    TH1F* hPUTrue = (TH1F*)gDirectory->Get("ggNtuplizer/hPUTrue");
    
    TFile* file = TFile::Open(OutputFile, "RECREATE");
    TTree* BoostTree = fChain->CloneTree(0);
    
    fChain->SetBranchStatus("*",0);
    fChain->SetBranchStatus("vt*",1);
//    fChain->SetBranchStatus("EventTag",1);
//    fChain->SetBranchStatus("run",1);
//    fChain->SetBranchStatus("event",1);
//    fChain->SetBranchStatus("lumis",1);
//    fChain->SetBranchStatus("isData",1);
//    fChain->SetBranchStatus("HLT*",1);
//    fChain->SetBranchStatus("gen*",1);
//    fChain->SetBranchStatus("pdf*",1);
//    fChain->SetBranchStatus("pthat",1);
//    fChain->SetBranchStatus("processID",1);
//    fChain->SetBranchStatus("rho*",1);
//    fChain->SetBranchStatus("pu*",1);
//    fChain->SetBranchStatus("mc*",1);
//    fChain->SetBranchStatus("pfMET*",1);
    fChain->SetBranchStatus("n*",1);
//    fChain->SetBranchStatus("jet*",1);
//    fChain->SetBranchStatus("AK8*",1);
//    fChain->SetBranchStatus("ele*",1);
//    fChain->SetBranchStatus("mu*",1);
    fChain->SetBranchStatus("tau*",1);
    fChain->SetBranchStatus("m*",1);
    fChain->SetBranchStatus("b*",1);
    
    TH1F* hcount = new TH1F("hcount", "", 10, 0, 10);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    float MuMass= 0.10565837;
    float eleMass= 0.000511;
    
//    float  met_px = 0;
//    float  met_py = 0;
//    float  met = 0;
//    float  metphi = 0;
//    float pfCovMatrix00 = 0;
//    float pfCovMatrix01 = 0;
//    float pfCovMatrix10 = 0;
//    float pfCovMatrix11 = 0;
    
    float  m_1 = 0;
    float  px_1 = 0;
    float  py_1 = 0;
    float  pz_1 = 0;
    float  e_1 = 0;
    float  pt_1 = 0;
    float  phi_1 = 0;
    float  eta_1 = 0;
    
    float  m_2 = 0;
    float  px_2 = 0;
    float  py_2 = 0;
    float  pz_2 = 0;
    float  e_2 = 0;
    float  pt_2 = 0;
    float  phi_2 = 0;
    float  eta_2 = 0;
    
    int era = 0;
    int decayMode1 = -1;
    int decayMode2 = -1;
    int leadtauIndex = -1;
    int subtauIndex= -1;
    int NumPair=0;
    float dR_=-1.0;
    
    
//    BoostTree->Branch("era", &era);
    BoostTree->Branch("NumPair", &NumPair);
//
//    BoostTree->Branch("met_px", &met_px);
//    BoostTree->Branch("met_py", &met_py);
//    BoostTree->Branch("met", &met);
//    BoostTree->Branch("metphi", &metphi);
//    BoostTree->Branch("metcov00", &pfCovMatrix00);
//    BoostTree->Branch("metcov01", &pfCovMatrix01);
//    BoostTree->Branch("metcov10", &pfCovMatrix10);
//    BoostTree->Branch("metcov11", &pfCovMatrix11);
    
    BoostTree->Branch("m_1", &m_1);
    BoostTree->Branch("px_1", &px_1);
    BoostTree->Branch("py_1", &py_1);
    BoostTree->Branch("pz_1", &pz_1);
    BoostTree->Branch("e_1", &e_1);
    BoostTree->Branch("pt_1", &pt_1);
    BoostTree->Branch("phi_1", &phi_1);
    BoostTree->Branch("eta_1", &eta_1);
    BoostTree->Branch("decayMode1", &decayMode1);
    
    BoostTree->Branch("m_2", &m_2);
    BoostTree->Branch("px_2", &px_2);
    BoostTree->Branch("py_2", &py_2);
    BoostTree->Branch("pz_2", &pz_2);
    BoostTree->Branch("e_2", &e_2);
    BoostTree->Branch("pt_2", &pt_2);
    BoostTree->Branch("phi_2", &phi_2);
    BoostTree->Branch("eta_2", &eta_2);
    BoostTree->Branch("decayMode2", &decayMode2);
    
    BoostTree->Branch("leadtauIndex", &leadtauIndex);
    BoostTree->Branch("subtauIndex", &subtauIndex);
    BoostTree->Branch("dR_", &dR_);
    
    for (int jentry=0; jentry<nentries;jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        if(jentry % 10000 == 0) cout << "Processed " << jentry << " events out of " <<nentries<<endl;
        
        hcount->Fill(1);
//        if (!isData)
//            hcount->Fill(2,genWeight);
        
//        if (pfMET < 50) continue;
//        hcount->Fill(3);
        
        TLorentzVector BoostSubTau4Mom, BoostLeadTau4Mom,BoostSubTau4Momtmp, BoostLeadTau4Momtmp;
        auto numTauTau(0);
        auto dR(-1.0);
        bool foundApair= false;
        

//            if (nBoostedTau > 0) cout<<"  numBoostedTau "<<nBoostedTau <<"\n";
            
            for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){

//            cout<<"test 3\n";
            
                if (boostedTauPt->at(ibtau) < 40 || fabs(boostedTauEta->at(ibtau)) > 2.3 ) continue;
//                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(ibtau) < 0.5 ) continue;
                if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(ibtau) < 0.5 ) continue;
                
//                if (boostedTauByMVA6VLooseElectronRejection->at(ibtau) < 0.5) continue;
                if (boostedTauByLooseMuonRejection3->at(ibtau) < 0.5) continue;
//                if (boostedTauByIsolationMVArun2v1DBnewDMwLTraw->at(ibtau) < 0) continue;
                
                BoostLeadTau4Momtmp.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
//                cout<<"test 4\n";
                
                
                for (int jbtau = ibtau+1; jbtau < nBoostedTau; ++jbtau){
                    
//                    cout<<"test 5\n";
                    
                    if (boostedTauPt->at(jbtau) < 40 || fabs(boostedTauEta->at(jbtau)) > 2.3 ) continue;
    //                if (boostedTaupfTausDiscriminationByDecayModeFinding->at(jbtau) < 0.5 ) continue;
                    if (boostedTaupfTausDiscriminationByDecayModeFindingNewDMs->at(jbtau) < 0.5 ) continue;
                    
//                    if (boostedTauByMVA6VLooseElectronRejection->at(jbtau) < 0.5) continue;
                    if (boostedTauByLooseMuonRejection3->at(jbtau) < 0.5) continue;
//                    if (boostedTauByIsolationMVArun2v1DBnewDMwLTraw->at(jbtau) < 0) continue;
                    
                    BoostSubTau4Momtmp.SetPtEtaPhiM(boostedTauPt->at(jbtau),boostedTauEta->at(jbtau),boostedTauPhi->at(jbtau),boostedTauMass->at(jbtau));
                                

//                if(BoostSubTau4Momtmp.DeltaR(BoostLeadTau4Momtmp) > 1.5 || BoostSubTau4Momtmp.DeltaR(BoostLeadTau4Momtmp) < 0.1) continue;
                decayMode1 = boostedTauDecayMode->at(ibtau);
                decayMode2 = boostedTauDecayMode->at(jbtau);
                numTauTau++;
                if (!foundApair){
                leadtauIndex=ibtau;
                subtauIndex=jbtau;
                dR=BoostSubTau4Momtmp.DeltaR(BoostLeadTau4Momtmp);
                }
                foundApair=true;
//                break;
            }
        }
        
        
        if(numTauTau < 1) continue;
        hcount->Fill(4);
        
    BoostLeadTau4Mom.SetPtEtaPhiM(boostedTauPt->at(leadtauIndex),boostedTauEta->at(leadtauIndex),boostedTauPhi->at(leadtauIndex),boostedTauMass->at(leadtauIndex));
    BoostSubTau4Mom.SetPtEtaPhiM(boostedTauPt->at(subtauIndex),boostedTauEta->at(subtauIndex),boostedTauPhi->at(subtauIndex),boostedTauMass->at(subtauIndex));
    
//        met_px = pfMET*sin(pfMETPhi);
//        met_py = pfMET*cos(pfMETPhi);
//        met = pfMET;
//        metphi = pfMETPhi;
        
        m_1 = BoostLeadTau4Mom.M();
        px_1 = BoostLeadTau4Mom.Px();
        py_1 = BoostLeadTau4Mom.Py();
        pz_1 = BoostLeadTau4Mom.Pz();
        e_1 = BoostLeadTau4Mom.E();
        pt_1 = BoostLeadTau4Mom.Pt();
        phi_1 = BoostLeadTau4Mom.Phi();
        eta_1 = BoostLeadTau4Mom.Eta();
        
        m_2 = BoostSubTau4Mom.M();
        px_2 = BoostSubTau4Mom.Px();
        py_2 = BoostSubTau4Mom.Py();
        pz_2 = BoostSubTau4Mom.Pz();
        e_2 = BoostSubTau4Mom.E();
        pt_2 = BoostSubTau4Mom.Pt();
        phi_2 = BoostSubTau4Mom.Phi();
        eta_2 = BoostSubTau4Mom.Eta();
        
//        pfCovMatrix00 = metcov00;
//        pfCovMatrix01 = metcov01;
//        pfCovMatrix10 = metcov10;
//        pfCovMatrix11 = metcov11;
//        era = 2017;
        NumPair=numTauTau;
        dR_=dR;
        
        
        BoostTree->Fill();
    }
    
    
    BoostTree->SetName("tautau_tree");
    BoostTree->AutoSave();
//    hEvents->Write();
    hcount->Write();
//    if (hPU) hPU->Write();
//    if (hPUTrue) hPUTrue->Write();
    file->Close();
}

int main(int argc, char* argv[]){
    
    string InputFile=argv[1];
    string OutputFile=argv[2];
    
    cout<< "\n===\n input is "<<InputFile  <<"  and output is "<<OutputFile<<"\n===\n";
    
    SkimerBoost t(InputFile);
    t.Loop(OutputFile);    
    return 0;
}



