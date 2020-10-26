
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "FWCore/Utilities/interface/transform.h"
#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"
#include "DataFormats/PatCandidates/interface/TauPFSpecific.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include <Math/VectorUtil.h>

using namespace std;

class PATBoostedTauCleaner : public edm::stream::EDProducer<>
{
public:
    
    explicit PATBoostedTauCleaner(const edm::ParameterSet&);
    ~PATBoostedTauCleaner(){};
    
    void produce(edm::Event&, const edm::EventSetup&);
    void setMySignalChargedHadrCands(const auto &ptrs);
    
    
private:
    
    
    //--- configuration parameters
    edm::EDGetTokenT<pat::TauCollection> src_;
    edm::EDGetTokenT<pat::PackedCandidateCollection> pf2pc_;
    edm::EDGetTokenT<reco::VertexCollection> vtxLabel_;
    bool  removeOverLap_;
    edm::EDGetTokenT<pat::JetCollection> jetsAK8Label_;
    
};

PATBoostedTauCleaner::PATBoostedTauCleaner(const edm::ParameterSet& cfg)
{
    src_ = consumes<pat::TauCollection>(cfg.getParameter<edm::InputTag>("src"));
    pf2pc_ = consumes<pat::PackedCandidateCollection>(cfg.getParameter<edm::InputTag>("pfcands"));
    vtxLabel_ = consumes<reco::VertexCollection>(cfg.getParameter<edm::InputTag>("vtxLabel"));
    removeOverLap_ = cfg.getParameter<bool>( "removeOverLap" );
    jetsAK8Label_= consumes<pat::JetCollection>(cfg.getParameter<edm::InputTag>("ak8JetSrc"));
    produces<std::vector<pat::Tau> >();
}


void PATBoostedTauCleaner::produce(edm::Event& evt, const edm::EventSetup& es)
{
    edm::Handle<pat::TauCollection> inputTaus;
    evt.getByToken(src_, inputTaus);
    
    edm::Handle<reco::VertexCollection> vertices;
    evt.getByToken(vtxLabel_, vertices);
    
    edm::Handle<pat::PackedCandidateCollection> pf2pc;
    evt.getByToken(pf2pc_, pf2pc);
    
    auto out = std::make_unique<std::vector<pat::Tau>>();
    out->reserve(inputTaus->size());
        
    for (std::vector<pat::Tau>::const_iterator it = inputTaus->begin(), ed = inputTaus->end(); it != ed; ++it) {
        out->push_back(*it);
        pat::Tau &tau = out->back();
        
        
        float  chargedPtIsoSum = 0;
        float  chargedPtIsoSum03 = 0;
        float  neutralPtIsoSum = 0;
        float  neutralPtIsoSum03  = 0;
        float  chargedPUPtIsoSum = 0;
        
        reco::CandidatePtrVector signalChHPtrs, signalNHPtrs, signalGammaPtrs, isolationChHPtrs, isolationNHPtrs,
        isolationGammaPtrs, signalPtrs, isolationPtrs;

        //############################################################################
        // Store all of the signal Candidates
        //############################################################################
        // All signal
        for (const reco::CandidatePtr &p : tau.signalCands()) {
            signalPtrs.push_back(p);
        }
        
        // signalCharged
        for (const reco::CandidatePtr &p : tau.signalChargedHadrCands()) {
            signalChHPtrs.push_back(p);
        }
        tau.setSignalChargedHadrCands(signalChHPtrs);
        
        // signalNeutral
        for (const reco::CandidatePtr &p : tau.signalNeutrHadrCands()) {
            signalNHPtrs.push_back(p);
        }
        tau.setSignalNeutralHadrCands(signalNHPtrs);
        
        // signalGamma
        for (const reco::CandidatePtr &p : tau.signalGammaCands()) {
            signalGammaPtrs.push_back(p);
        }
        tau.setSignalGammaCands(signalGammaPtrs);
        
        
        //############################################################################
        // leadChargedHadrCand
        //############################################################################
        
        const pat::PackedCandidate* packedLeadChCand = dynamic_cast<const pat::PackedCandidate*>(tau.leadChargedHadrCand().get());
        
        float minDz = 99;
        int tauVertexIdx = 0;
        int idx = 0;
        for (const auto& vertex : *vertices) {//vertices is handle to vertices
            float dz = std::abs(packedLeadChCand->dz(vertex.position()));
            if (dz < minDz) {
                minDz = dz;
                tauVertexIdx = idx;
            }
            idx++;
        }
        
        if (removeOverLap_){
            
            //############################################################################
            // filling a collection of IsoCandidates which overlapped with either other signal candidates or other Jet contitients
            //############################################################################
            reco::CandidatePtrVector OverLappedIsoCand;
            OverLappedIsoCand.clear();
            
            for (const reco::CandidatePtr &isoCand1 : tau.isolationCands()) {
                
                // Check iso candidate does not overlap with other signal candidates
                auto out2 = std::make_unique<std::vector<pat::Tau>>();
                out2->reserve(inputTaus->size());
                for (std::vector<pat::Tau>::const_iterator it2 = inputTaus->begin(), ed2 = inputTaus->end(); it2 != ed2; ++it2) {
                    
                    if (it2 == it) continue;
                    
                    out2->push_back(*it2);
                    pat::Tau &tau2 = out2->back();
                    
                    if (ROOT::Math::VectorUtil::DeltaR(tau2.p4(), tau.p4()) > 1.0) continue;
                    
                    for (const reco::CandidatePtr &sigCand2 : tau2.signalCands()) {
                        if (ROOT::Math::VectorUtil::DeltaR(isoCand1->p4(), sigCand2->p4()) < 1e-4)
                            OverLappedIsoCand.push_back(isoCand1);
                    }
                }
                
                // Check iso candidate does not overlap with other subjet constituents
                edm::Handle<vector<pat::Jet> > jetHandle;
                evt.getByToken(jetsAK8Label_, jetHandle);
                
                for (vector<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {
                    
                    if (iJet->pt() < 170) continue;
                    
                    if (ROOT::Math::VectorUtil::DeltaR(iJet->p4(), tau.p4()) > 2.0) continue;
                    
                    //        auto const & sdSubjets = iJet->subjets("SoftDrop");
                    auto const & sdSubjets = iJet->subjets("SoftDropPuppi");
                    
                    // Find the subjet that seeds taus : closest subjet to tau
                    float dRClosest=1000;
                    TLorentzVector TauSeedSubJet;
                    for ( auto const & SDSJ : sdSubjets ) {
                    if (ROOT::Math::VectorUtil::DeltaR(SDSJ->p4(), tau.p4()) < dRClosest){
                            dRClosest= ROOT::Math::VectorUtil::DeltaR(SDSJ->p4(), tau.p4());
                            TauSeedSubJet.SetPtEtaPhiE(SDSJ->pt(),SDSJ->eta(),SDSJ->phi(),SDSJ->E());
                        }
                    }
                    
                    for ( auto const & SDSJ : sdSubjets ) {
                        
                        if (ROOT::Math::VectorUtil::DeltaR(SDSJ->p4(), tau.p4()) > 2.0) continue;
                        if (ROOT::Math::VectorUtil::DeltaR(SDSJ->p4(), TauSeedSubJet.p4()) < 0.0001) continue;
//                        if (ROOT::Math::VectorUtil::DeltaR(SDSJ->p4(), tau.p4()) < 0.05) continue;
                                                
                        for (unsigned id = 0; id < SDSJ->getJetConstituents().size(); id++) {
                            const edm::Ptr<reco::Candidate> daughter = SDSJ->getJetConstituents().at(id);
                            if (ROOT::Math::VectorUtil::DeltaR(isoCand1->p4(), daughter->p4()) < 1e-4)
                                OverLappedIsoCand.push_back(isoCand1);
                        }
                    }
                }
            }// end of filling the OverLappedIsoCand collection

            //############################################################################
            // looping over Iso Cand to see if ther overlap with sig cand of a close-by tau
            //############################################################################
            for (const reco::CandidatePtr &charged : tau.isolationChargedHadrCands()) {
                
                bool hasOverLap=false;
                for (const reco::CandidatePtr &overLapCand : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(charged->p4(), overLapCand->p4()) < 1e-4){
                        hasOverLap=true;
                        break;
                    }
                }
                if (! hasOverLap){
                    isolationChHPtrs.push_back(charged);
                    
                    
                    //q-cuts
                    if (charged->pt() <= 0.5) continue;
                    //                    if (std::abs(tau.dxy((*vertices)[tauVertexIdx].position())) >= 0.03) continue;
                    const reco::Track *track = charged->bestTrack();
                    if (track == nullptr) continue;
                    if (std::abs(track->dxy((*vertices)[tauVertexIdx].position())) >= 0.03) continue;
                    if (track->normalizedChi2() >= 100) continue;
                    //                    if (track->numberOfHits() < 3) continue;
                    if (track->numberOfValidHits() < 3) continue; //????
                    //                    double dz = std::abs(tau.dz((*vertices)[tauVertexIdx].position()));
                    double dz = std::abs(track->dz((*vertices)[tauVertexIdx].position()));
                    double dR = deltaR(charged->p4(), tau.p4());
                    if (dz < 0.2) {//from tau vertex
                        //iso cone
                        if (dR < 0.5)
                            chargedPtIsoSum += charged->pt();
                        if (dR < 0.3)
                            chargedPtIsoSum03 += charged->pt();
                    } else {//not from tau vertex
                        //iso cone
                        if (dR < 0.8)
                            chargedPUPtIsoSum += charged->pt();
                    }
                }
            }
            tau.setIsolationChargedHadrCands(isolationChHPtrs);
            //############################################################################
            // looping over Iso Cand to see if ther overlap with sig cand of a close-by tau
            //############################################################################
                        
            for (const reco::CandidatePtr &neutral : tau.isolationNeutrHadrCands()) {
                bool hasOverLap=false;
                for (const reco::CandidatePtr &overLapCand : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(neutral->p4(), overLapCand->p4()) < 1e-4){
                        hasOverLap=true;
                        break;
                    }
                }
                if (! hasOverLap)
                    isolationNHPtrs.push_back(neutral);
            }
            tau.setIsolationNeutralHadrCands(isolationNHPtrs);
                        
            //############################################################################
            // looping over Iso Cand to see if ther overlap with sig cand of a close-by tau
            //############################################################################
            
            for (const reco::CandidatePtr &gamma : tau.isolationGammaCands()) {
                bool hasOverLap=false;
                for (const reco::CandidatePtr &overLapCand : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(gamma->p4(), overLapCand->p4()) < 1e-4){
                        hasOverLap=true;
                        break;
                    }
                }
                if (! hasOverLap){
                    isolationGammaPtrs.push_back(gamma);
                    
                    // Fill neutralPtIsoSum03 and neutralPtIsoSum
                    //q-cuts
                    if (gamma->pt() <= 1.) continue;
                    //iso cone
                    double dR = deltaR(gamma->p4(), tau.p4());
                    if (dR < 0.5)
                        neutralPtIsoSum += gamma->pt();
                    if (dR < 0.3)
                        neutralPtIsoSum03 += gamma->pt();
                }
            }
            tau.setIsolationGammaCands(isolationGammaPtrs);
            
            //############################################################################
        }// check if overLap removal is needed
                
        size_t nTauIds = tau.tauIDs().size();
        std::vector<pat::Tau::IdPair> tauIds(nTauIds+5);
        
        
        for(size_t q = 0; q < nTauIds; ++q){
            tauIds[q] = tau.tauIDs().at(q);
        }
        size_t q = nTauIds;
        tauIds[q].first="chargedIsoPtSumNoOverLap";
        tauIds[q].second= chargedPtIsoSum;
        q=q+1;
        
        tauIds[q].first="chargedIsoPtSum03NoOverLap";
        tauIds[q].second= chargedPtIsoSum03;
        q=q+1;
        
        tauIds[q].first="neutralIsoPtSumNoOverLap";
        tauIds[q].second= neutralPtIsoSum;
        q=q+1;
        
        tauIds[q].first="neutralIsoPtSum03NoOverLap";
        tauIds[q].second= neutralPtIsoSum03;
        q=q+1;
        
        tauIds[q].first="chargedPUIsoPtSumNoOverLap";
        tauIds[q].second= chargedPUPtIsoSum;
        q=q+1;
        
        tau.setTauIDs(tauIds);
        
        
    }// iterate over tau is finished
    
    //This is for Adding new tau Id
    evt.put(std::move(out));
}

DEFINE_FWK_MODULE(PATBoostedTauCleaner);
