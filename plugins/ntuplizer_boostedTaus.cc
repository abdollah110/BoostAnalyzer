// Updated by Abdollah Mohammadi (KSU)  [18 May 2015]
// abdollah.mohammadi@cern.ch

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"

using namespace std;

// (local) variables associated with tree branches
Int_t          nBoostedTau_;

// decay mode discriminators



//Tau Id & Isolation
vector<bool>   boostedTaupfTausDiscriminationByDecayModeFinding_;
vector<bool>   boostedTaupfTausDiscriminationByDecayModeFindingNewDMs_;

vector<bool>   boostedTauByMVA6LooseElectronRejection_;
vector<bool>   boostedTauByMVA6TightElectronRejection_;

vector<bool>   boostedTauByLooseMuonRejection3_;
vector<bool>   boostedTauByTightMuonRejection3_;

vector<bool>   boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits_;
vector<bool>   boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits_;
vector<float>  boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits_;

vector<float>  boostedTauByIsolationMVArun2v1DBnewDMwLTraw_;
vector<float>  boostedTauByIsolationMVArun2v1DBoldDMwLTraw_;
vector<bool>   boostedTauByTightIsolationMVArun2v1DBnewDMwLT_;
vector<bool>   boostedTauByTightIsolationMVArun2v1DBoldDMwLT_;
vector<bool>   boostedTauByLooseIsolationMVArun2v1DBnewDMwLT_;
vector<bool>   boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_;
//vector<bool>   MybyVVTightIsolationMVArun2v1DBoldDMwLTNew_;


//Tau Kinematics
vector<float> boostedTauEta_;
vector<float> boostedTauPhi_;
vector<float> boostedTauPt_;
vector<float> boostedTauEt_;
vector<float> boostedTauCharge_;
vector<int>   boostedTauDecayMode_;
vector<float> boostedTauP_;
vector<float> boostedTauPx_;
vector<float> boostedTauPy_;
vector<float> boostedTauPz_;
vector<float> boostedTauVz_;
vector<float> boostedTauEnergy_;
vector<float> boostedTauMass_;
vector<float> boostedTauDxy_;
vector<float> boostedTauZImpact_;

//Tau Ingredients
vector<float> boostedTauChargedIsoPtSum_;
vector<float> boostedTauNeutralIsoPtSum_;
vector<float> boostedTauPuCorrPtSum_;
vector<int>   boostedTauNumSignalPFChargedHadrCands_;
vector<int>   boostedTauNumSignalPFNeutrHadrCands_;
vector<int>   boostedTauNumSignalPFGammaCands_;
vector<int>   boostedTauNumSignalPFCands_;
vector<int>   boostedTauNumIsolationPFChargedHadrCands_;
vector<int>   boostedTauNumIsolationPFNeutrHadrCands_;
vector<int>   boostedTauNumIsolationPFGammaCands_;
vector<int>   boostedTauNumIsolationPFCands_;
vector<bool>  boostedTauLeadChargedHadronExists_;
vector<float> boostedTauLeadChargedHadronEta_;
vector<float> boostedTauLeadChargedHadronPhi_;
vector<float> boostedTauLeadChargedHadronPt_;
vector<float> boostedTauneutralIsoPtSumWeight_;
vector<float> boostedTaufootprintCorrection_;
vector<float> boostedTauphotonPtSumOutsideSignalCone_;
vector<float> boostedTaudz_;
vector<float> boostedTaudxy_;

vector<vector<float>> boostedTauSignalPFCands_;
vector<vector<float>> boostedTauSignalPFGammaCands_;
vector<vector<float>> boostedTauIsolationPFCands_;
vector<vector<float>> boostedTauIsolationPFGammaCands_;

//vector<vecto<float>>



void BoostAnalyzer::branchesBoostedTaus(TTree* tree)
{

    tree->Branch("nBoostedTau", &nBoostedTau_);
    
    //Tau Id & Isolation
    tree->Branch("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding_);
    tree->Branch("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs_);
    
    tree->Branch("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection_);
    tree->Branch("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection_);
    
    tree->Branch("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3_);
    tree->Branch("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3_);
    
    tree->Branch("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits_);
    tree->Branch("boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits_);
    tree->Branch("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits_);
    
    tree->Branch("boostedTauByIsolationMVArun2v1DBnewDMwLTraw", &boostedTauByIsolationMVArun2v1DBnewDMwLTraw_);
    tree->Branch("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw_);
    tree->Branch("boostedTauByTightIsolationMVArun2v1DBnewDMwLT", &boostedTauByTightIsolationMVArun2v1DBnewDMwLT_);
    tree->Branch("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT_);
    tree->Branch("boostedTauByLooseIsolationMVArun2v1DBnewDMwLT", &boostedTauByLooseIsolationMVArun2v1DBnewDMwLT_);
    tree->Branch("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("MybyVVTightIsolationMVArun2v1DBoldDMwLTNew", &MybyVVTightIsolationMVArun2v1DBoldDMwLTNew_);
    
    
    //Tau Kinematics
    tree->Branch("boostedTauEta"  ,&boostedTauEta_);
    tree->Branch("boostedTauPhi"  ,&boostedTauPhi_);
    tree->Branch("boostedTauPt"  ,&boostedTauPt_);
    tree->Branch("boostedTauEt"  ,&boostedTauEt_);
    tree->Branch("boostedTauCharge"  ,&boostedTauCharge_);
    tree->Branch("boostedTauP"  ,&boostedTauP_);
    tree->Branch("boostedTauPx"  ,&boostedTauPx_);
    tree->Branch("boostedTauPy"  ,&boostedTauPy_);
    tree->Branch("boostedTauPz"  ,&boostedTauPz_);
    tree->Branch("boostedTauVz"  ,&boostedTauVz_);
    tree->Branch("boostedTauEnergy"  ,&boostedTauEnergy_);
    tree->Branch("boostedTauMass"  ,&boostedTauMass_);
    tree->Branch("boostedTauDxy"  ,&boostedTauDxy_);
    tree->Branch("boostedTauZImpact"  ,&boostedTauZImpact_);
    
    // Tau Ingredients
    tree->Branch("boostedTauDecayMode"  ,&boostedTauDecayMode_);
    tree->Branch("boostedTauLeadChargedHadronExists"  ,&boostedTauLeadChargedHadronExists_);
    tree->Branch("boostedTauLeadChargedHadronEta"  ,&boostedTauLeadChargedHadronEta_);
    tree->Branch("boostedTauLeadChargedHadronPhi"  ,&boostedTauLeadChargedHadronPhi_);
    tree->Branch("boostedTauLeadChargedHadronPt"  ,&boostedTauLeadChargedHadronPt_);
    tree->Branch("boostedTauChargedIsoPtSum"  ,&boostedTauChargedIsoPtSum_);
    tree->Branch("boostedTauNeutralIsoPtSum"  ,&boostedTauNeutralIsoPtSum_);
    tree->Branch("boostedTauPuCorrPtSum"  ,&boostedTauPuCorrPtSum_);
    tree->Branch("boostedTauNumSignalPFChargedHadrCands"  ,&boostedTauNumSignalPFChargedHadrCands_);
    tree->Branch("boostedTauNumSignalPFNeutrHadrCands"  ,&boostedTauNumSignalPFNeutrHadrCands_);
    tree->Branch("boostedTauNumSignalPFGammaCands"  ,&boostedTauNumSignalPFGammaCands_);
    tree->Branch("boostedTauNumSignalPFCands"  ,&boostedTauNumSignalPFCands_);
    tree->Branch("boostedTauNumIsolationPFChargedHadrCands"  ,&boostedTauNumIsolationPFChargedHadrCands_);
    tree->Branch("boostedTauNumIsolationPFNeutrHadrCands"  ,&boostedTauNumIsolationPFNeutrHadrCands_);
    tree->Branch("boostedTauNumIsolationPFGammaCands"  ,&boostedTauNumIsolationPFGammaCands_);
    tree->Branch("boostedTauNumIsolationPFCands"  ,&boostedTauNumIsolationPFCands_);
    
    tree->Branch("boostedTaufootprintCorrection"  ,&boostedTaufootprintCorrection_);
    tree->Branch("boostedTauphotonPtSumOutsideSignalCone"  ,&boostedTauphotonPtSumOutsideSignalCone_);
    tree->Branch("boostedTaudz"  ,&boostedTaudz_);
    tree->Branch("boostedTaudxy"  ,&boostedTaudxy_);

    tree->Branch("boostedTauSignalPFCands"  ,&boostedTauSignalPFCands_);
    tree->Branch("boostedTauSignalPFGammaCands"  ,&boostedTauSignalPFGammaCands_);
    tree->Branch("boostedTauIsolationPFCands"  ,&boostedTauIsolationPFCands_);
    tree->Branch("boostedTauIsolationPFGammaCands"  ,&boostedTauIsolationPFGammaCands_);



}

void BoostAnalyzer::fillBoostedTaus(const edm::Event& e)
{
    
    // Tau Id & Isolation
    
    boostedTaupfTausDiscriminationByDecayModeFinding_.clear();
    boostedTaupfTausDiscriminationByDecayModeFindingNewDMs_.clear();
    
    boostedTauByMVA6LooseElectronRejection_.clear();
    boostedTauByMVA6TightElectronRejection_.clear();
    
    boostedTauByLooseMuonRejection3_.clear();
    boostedTauByTightMuonRejection3_.clear();

    boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits_.clear();
    boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits_.clear();
    boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits_.clear();
    
    boostedTauByIsolationMVArun2v1DBnewDMwLTraw_.clear();
    boostedTauByIsolationMVArun2v1DBoldDMwLTraw_.clear();
    boostedTauByTightIsolationMVArun2v1DBnewDMwLT_.clear();
    boostedTauByTightIsolationMVArun2v1DBoldDMwLT_.clear();
    boostedTauByLooseIsolationMVArun2v1DBnewDMwLT_.clear();
    boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_.clear();
//    MybyVVTightIsolationMVArun2v1DBoldDMwLTNew_.clear();

    
    //Tau Kinematics
    boostedTauEta_.clear();
    boostedTauPhi_.clear();
    boostedTauPt_.clear();
    boostedTauEt_.clear();
    boostedTauCharge_.clear();
    boostedTauP_.clear();
    boostedTauPx_.clear();
    boostedTauPy_.clear();
    boostedTauPz_.clear();
    boostedTauVz_.clear();
    boostedTauEnergy_.clear();
    boostedTauMass_.clear();
    boostedTauDxy_.clear();
    boostedTauZImpact_.clear();
    
    // Tau Ingredients
    boostedTauDecayMode_.clear();
    boostedTauLeadChargedHadronExists_.clear();
    boostedTauLeadChargedHadronEta_.clear();
    boostedTauLeadChargedHadronPhi_.clear();
    boostedTauLeadChargedHadronPt_.clear();
    boostedTauChargedIsoPtSum_.clear();
    boostedTauNeutralIsoPtSum_.clear();
    boostedTauPuCorrPtSum_.clear();
    boostedTauNumSignalPFChargedHadrCands_.clear();
    boostedTauNumSignalPFNeutrHadrCands_.clear();
    boostedTauNumSignalPFGammaCands_.clear();
    boostedTauNumSignalPFCands_.clear();
    boostedTauNumIsolationPFChargedHadrCands_.clear();
    boostedTauNumIsolationPFNeutrHadrCands_.clear();
    boostedTauNumIsolationPFGammaCands_.clear();
    boostedTauNumIsolationPFCands_.clear();
    
    boostedTauneutralIsoPtSumWeight_.clear();
    boostedTaufootprintCorrection_.clear();
    boostedTauphotonPtSumOutsideSignalCone_.clear();
    boostedTaudz_.clear();
    boostedTaudxy_.clear();
    
    boostedTauSignalPFCands_.clear();
    boostedTauSignalPFGammaCands_.clear();
    boostedTauIsolationPFCands_.clear();
    boostedTauIsolationPFGammaCands_.clear();

    
    
    nBoostedTau_ = 0;
    
    edm::Handle<vector<pat::Tau> > boostedTauHandle;
    e.getByToken(boostedTauCollection_, boostedTauHandle);
    
    if (!boostedTauHandle.isValid()) {
        edm::LogWarning("BoostAnalyzer") << "no pat::Tau in event";
        return;
    }
    
    edm::Handle<vector<pat::Tau> >  boostedTauHandleNew;
    e.getByToken(boostedTauCollectionNew_, boostedTauHandleNew);

    if (!boostedTauHandleNew.isValid()) {
        edm::LogWarning("BoostAnalyzer") << "no pat::Tau in event boostedTauHandleNew";
        return;
    }

    
    //startTaus Lvdp
    for(vector<pat::Tau>::const_iterator itau = boostedTauHandle->begin(); itau != boostedTauHandle->end(); ++itau) {
        
        // Tau Id & Isolation
        boostedTaupfTausDiscriminationByDecayModeFinding_.push_back(itau->tauID("decayModeFinding"));
        boostedTaupfTausDiscriminationByDecayModeFindingNewDMs_.push_back(itau->tauID("decayModeFindingNewDMs"));
        

        boostedTauByMVA6LooseElectronRejection_.push_back(itau->tauID("againstElectronLooseMVA6"));
        boostedTauByMVA6TightElectronRejection_.push_back(itau->tauID("againstElectronTightMVA6"));
        
        boostedTauByLooseMuonRejection3_.push_back(itau->tauID("againstMuonLoose3"));
        boostedTauByTightMuonRejection3_.push_back(itau->tauID("againstMuonTight3"));
        
        boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits_.push_back(itau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits"));
        boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits_.push_back(itau->tauID("byTightCombinedIsolationDeltaBetaCorr3Hits"));
        boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits_.push_back(itau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits"));
        
        boostedTauByIsolationMVArun2v1DBnewDMwLTraw_.push_back(itau->tauID("byIsolationMVArun2v1DBnewDMwLTraw"));
        boostedTauByIsolationMVArun2v1DBoldDMwLTraw_.push_back(itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw"));
        boostedTauByLooseIsolationMVArun2v1DBnewDMwLT_.push_back(itau->tauID("byLooseIsolationMVArun2v1DBnewDMwLT"));
        boostedTauByLooseIsolationMVArun2v1DBoldDMwLT_.push_back(itau->tauID("byLooseIsolationMVArun2v1DBoldDMwLT"));
        boostedTauByTightIsolationMVArun2v1DBnewDMwLT_.push_back(itau->tauID("byTightIsolationMVArun2v1DBnewDMwLT"));
        boostedTauByTightIsolationMVArun2v1DBoldDMwLT_.push_back(itau->tauID("byTightIsolationMVArun2v1DBoldDMwLT"));
//        MybyVVTightIsolationMVArun2v1DBoldDMwLTNew_.push_back(itau->tauID("MybyVVTightIsolationMVArun2v1DBoldDMwLTNew));
    
        
        //Tau Kinematics
        boostedTauEta_.push_back(itau->eta());
        boostedTauPhi_.push_back(itau->phi());
        boostedTauPt_.push_back(itau->pt());
        boostedTauEt_.push_back(itau->et());
        boostedTauCharge_.push_back(itau->charge());
        boostedTauP_.push_back(itau->p() );
        boostedTauPx_.push_back(itau->px() );
        boostedTauPy_.push_back(itau->py() );
        boostedTauPz_.push_back(itau->pz() );
        boostedTauVz_.push_back(itau->vz() );
        boostedTauEnergy_.push_back(itau->energy() );
        boostedTauMass_.push_back(itau->mass());
        boostedTauDxy_.push_back(itau->dxy() );
        boostedTauZImpact_.push_back(itau->vertex().z() + 130./tan(itau->theta()));
        
        
        // Tau Ingredients
        boostedTauDecayMode_.push_back(itau->decayMode());
        boostedTauChargedIsoPtSum_.push_back(itau->tauID("chargedIsoPtSum") );
        boostedTauNeutralIsoPtSum_.push_back(itau->tauID("neutralIsoPtSum")  );
        boostedTauPuCorrPtSum_.push_back(itau->tauID("puCorrPtSum")  );
        boostedTauneutralIsoPtSumWeight_.push_back(itau->tauID("neutralIsoPtSumWeight"));
        boostedTaufootprintCorrection_.push_back(itau->tauID("footprintCorrection"));
        boostedTauphotonPtSumOutsideSignalCone_.push_back(itau->tauID("photonPtSumOutsideSignalCone"));
        
        boostedTauNumSignalPFChargedHadrCands_.push_back(itau->signalChargedHadrCands().size());
        boostedTauNumSignalPFNeutrHadrCands_.push_back(itau->signalNeutrHadrCands().size());
        boostedTauNumSignalPFGammaCands_.push_back(itau->signalGammaCands().size());
        boostedTauNumSignalPFCands_.push_back(itau->signalCands().size());
        
        boostedTauNumIsolationPFChargedHadrCands_.push_back(itau->isolationChargedHadrCands().size());
        boostedTauNumIsolationPFNeutrHadrCands_.push_back(itau->isolationNeutrHadrCands().size());
        boostedTauNumIsolationPFGammaCands_.push_back(itau->isolationGammaCands().size());
        boostedTauNumIsolationPFCands_.push_back(itau->isolationCands().size());
        
        
        vector<float> sigCharged;
        sigCharged.clear();
        for (auto& cand : itau->signalChargedHadrCands()) {
        sigCharged.push_back(cand->pt());
        }
        boostedTauSignalPFCands_.push_back(sigCharged);

        vector<float> sigGamma;
        sigGamma.clear();
        for (auto& cand : itau->signalGammaCands()) {
        sigGamma.push_back(cand->pt());
        }
        boostedTauSignalPFGammaCands_.push_back(sigGamma);


        vector<float> isoCharged;
        isoCharged.clear();
        for (auto& cand : itau->isolationChargedHadrCands()) {
        isoCharged.push_back(cand->pt());
        }
        boostedTauIsolationPFCands_.push_back(isoCharged);

        vector<float> isoGamma;
        isoGamma.clear();
        for (auto& cand : itau->isolationGammaCands()) {
        isoGamma.push_back(cand->pt());
        }
        boostedTauIsolationPFGammaCands_.push_back(isoGamma);

        
        ++nBoostedTau_;
        
    } // loop over tau candidates
    
    for(vector<pat::Tau>::const_iterator ibtau_new = boostedTauHandleNew->begin(); ibtau_new != boostedTauHandleNew->end(); ++ibtau_new) {
        std::cout<<"itau->tauID('chargedIsoPtSum') " << ibtau_new->tauID("chargedIsoPtSum")<<"\n";
    }

    
    
}
