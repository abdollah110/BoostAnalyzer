
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "FWCore/Utilities/interface/transform.h"
#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"
#include <Math/VectorUtil.h>

class PATBoostedTauEmbedder : public edm::stream::EDProducer<>
{
public:
    
    explicit PATBoostedTauEmbedder(const edm::ParameterSet&);
    ~PATBoostedTauEmbedder(){};
    
    void produce(edm::Event&, const edm::EventSetup&);
    void setMySignalChargedHadrCands(const auto &ptrs);
    
    
private:
    
    
    
    //    pfCands    = cms.InputTag("packedPFCandidates"), //In .py config file
    //    ...
    //     pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
    //    ...
    //    edm::EDGetTokenT<pat::PackedCandidateCollection> pfToken_;
    //    ...
    //    edm::Handle<pat::PackedCandidateCollection> pfs;
    //    iEvent.getByToken(pfToken_, pfs);
    
    
    
    
    //--- configuration parameters
    edm::EDGetTokenT<pat::TauCollection> src_;
    //    edm::EDGetTokenT<edm::Association<pat::PackedCandidateCollection> > pf2pc_;
    edm::EDGetTokenT<pat::PackedCandidateCollection> pf2pc_;
//    typedef std::pair<std::string, edm::InputTag> NameTag;
//    std::vector<NameTag> tauIDSrcs_;
//    std::vector<edm::EDGetTokenT<pat::PATTauDiscriminator> > patTauIDTokens_;
    //    reco::CandidatePtrVector signalChargedHadrCandPtrs_;
    edm::EDGetTokenT<reco::VertexCollection> vtxLabel_;
    bool  removeOverLap_;
    
};

PATBoostedTauEmbedder::PATBoostedTauEmbedder(const edm::ParameterSet& cfg)
//pf2pc_(mayConsume<edm::Association<pat::PackedCandidateCollection> >(cfg.getParameter<edm::InputTag>("packedPFCandidates")))
{
    src_ = consumes<pat::TauCollection>(cfg.getParameter<edm::InputTag>("src"));
    pf2pc_ = consumes<pat::PackedCandidateCollection>(cfg.getParameter<edm::InputTag>("pfcands"));
    vtxLabel_ = consumes<reco::VertexCollection>(cfg.getParameter<edm::InputTag>("vtxLabel"));
    removeOverLap_ = cfg.getParameter<bool>( "removeOverLap" );
    
//    // read the different tau ID names
//    edm::ParameterSet idps = cfg.getParameter<edm::ParameterSet>("tauIDSources");
//    std::vector<std::string> names = idps.getParameterNamesForType<edm::InputTag>();
//    for (std::vector<std::string>::const_iterator it = names.begin(), ed = names.end(); it != ed; ++it) {
//        tauIDSrcs_.push_back(NameTag(*it, idps.getParameter<edm::InputTag>(*it)));
//    }
//    // but in any case at least once
//    if (tauIDSrcs_.empty()) throw cms::Exception("Configuration") <<
//        "PATTauProducer: id addTauID is true, you must specify:\n" <<
//        "\tPSet tauIDSources = { \n" <<
//        "\t\tInputTag <someName> = <someTag>   // as many as you want \n " <<
//        "\t}\n";
//    patTauIDTokens_ = edm::vector_transform(tauIDSrcs_, [this](NameTag const & tag){return mayConsume<pat::PATTauDiscriminator>(tag.second);});
    
    produces<std::vector<pat::Tau> >();
}


//void PATBoostedTauEmbedder::setMySignalChargedHadrCands(const auto &ptrs)
//        { signalChargedHadrCandPtrs_ = ptrs;}

void PATBoostedTauEmbedder::produce(edm::Event& evt, const edm::EventSetup& es)
{
    edm::Handle<pat::TauCollection> inputTaus;
    evt.getByToken(src_, inputTaus);
    
    edm::Handle<reco::VertexCollection> vertices;
    evt.getByToken(vtxLabel_, vertices);
    
    // This part is to add new Tau Id
    
    //  auto outputTaus = std::make_unique<std::vector<pat::Tau> >();
    //  outputTaus->reserve(inputTaus->size());
    
    //  int tau_idx = 0;
    //  for(pat::TauCollection::const_iterator inputTau = inputTaus->begin(); inputTau != inputTaus->end(); ++inputTau, ++tau_idx){
    //
    //    pat::Tau outputTau(*inputTau);
    //    pat::TauRef inputTauRef(inputTaus, tau_idx);
    //
    //    size_t nTauIds = inputTau->tauIDs().size();
    //    std::vector<pat::Tau::IdPair> tauIds(nTauIds+tauIDSrcs_.size());
    //
    //    for(size_t i = 0; i < nTauIds; ++i){
    //      tauIds[i] = inputTau->tauIDs().at(i);
    //    }
    //
    //    edm::Handle<pat::PATTauDiscriminator> tauDiscr;
    //    for(size_t i = 0; i < tauIDSrcs_.size(); ++i){
    //      evt.getByToken(patTauIDTokens_[i], tauDiscr);
    //      tauIds[nTauIds+i].first = tauIDSrcs_[i].first;
    //      tauIds[nTauIds+i].second = (*tauDiscr)[inputTauRef];
    //    }
    //
    //
    //
    //
    //    outputTau.setTauIDs(tauIds);
    //    outputTaus->push_back(outputTau);
    //  }
    
    //  edm::Handle<edm::Association<pat::PackedCandidateCollection>> pf2pc;
    //  evt.getByToken(pf2pc_, pf2pc);
    
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

        
        
        // clearing the pat isolation which is not used by taus
        //    tau.isolations_.clear();
        //    tau.isoDeposits_.clear();
                
        reco::CandidatePtrVector signalChHPtrs, signalNHPtrs, signalGammaPtrs, isolationChHPtrs, isolationNHPtrs,
        isolationGammaPtrs, signalPtrs, isolationPtrs;
        reco::CandidatePtrVector OverLappedIsoCand;
        
        
        
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
        
        // signalNeutr
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
         
         
        //############################################################################
        // leadChargedHadrCand
        //############################################################################
        // All Isolation
        for (const reco::CandidatePtr &p : tau.isolationCands()) {
            isolationPtrs.push_back(p);
        }
                
        if (removeOverLap_){
            
            for (const reco::CandidatePtr &p : tau.isolationCands()) {
                
                auto out2 = std::make_unique<std::vector<pat::Tau>>();
                out2->reserve(inputTaus->size());
                
                
                for (std::vector<pat::Tau>::const_iterator it2 = inputTaus->begin(), ed2 = inputTaus->end(); it2 != ed2; ++it2) {
                    
                    if (it2 == it) continue;
                    
                    out2->push_back(*it2);
                    pat::Tau &tau2 = out2->back();
                    
                    if (ROOT::Math::VectorUtil::DeltaR(tau2.p4(), tau.p4()) > 1.0) continue;
                    
                    
                    for (const reco::CandidatePtr &p2 : tau2.signalCands()) {
                        if (ROOT::Math::VectorUtil::DeltaR(p->p4(), p2->p4()) < 1e-4)
                            OverLappedIsoCand.push_back(p);
                    }
                }
            }// end of filling the new collection
            //############################################################################
            // looping over Iso Cand to see if ther overlap with sig cand of a close-by tau
            //############################################################################
            for (const reco::CandidatePtr &charged : tau.isolationChargedHadrCands()) {
                
                bool hasOverLap=false;
                for (const reco::CandidatePtr &q : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(charged->p4(), q->p4()) < 1e-4){
                        hasOverLap=true;
                    }
                }
                if (! hasOverLap){
                    isolationChHPtrs.push_back(charged);
                    
                    // here we want to make chargedPtIsoSum ,  neutralPtIsoSum03 , chargedPUPtIsoSum


                    //q-cuts
                    if (charged->pt() <= 0.5) continue;
//                    std::cout<<"tauVertexIdx = "<<tauVertexIdx<<"\n";
//                    if (std::abs(charged->dxy(*vertices[tauVertexIdx].position())) >= 0.03) continue;
                    const reco::Track *track = charged->bestTrack();
                    if (track == nullptr) continue;
//                      if (std::abs(track->dxy(*vertices[tauVertexIdx].position())) >= 0.03) continue;
//                    if (track->normChi2() >= 100) continue;
//                    if (track->numberOfHits() < 3) continue;
                    if (track->numberOfValidHits() < 3) continue; //????
                    
//                    double dz = std::abs(charged->dz(*vertices[tauVertexIdx].position()));
//                    double dz = std::abs(track->dz(*vertices[tauVertexIdx].position()));
                    double dz = 0.1;
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

            
            for (const reco::CandidatePtr &p : tau.isolationNeutrHadrCands()) {
                bool hasOverLap=false;
                for (const reco::CandidatePtr &q : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(p->p4(), q->p4()) < 1e-4){
                        hasOverLap=true;
                    }
                }
                if (! hasOverLap)
                    isolationNHPtrs.push_back(p);
            }
            tau.setIsolationNeutralHadrCands(isolationNHPtrs);
            
            
            //############################################################################
            // looping over Iso Cand to see if ther overlap with sig cand of a close-by tau
            //############################################################################
            
            for (const reco::CandidatePtr &gamma : tau.isolationGammaCands()) {
                bool hasOverLap=false;
                for (const reco::CandidatePtr &q : OverLappedIsoCand) {
                    if (ROOT::Math::VectorUtil::DeltaR(gamma->p4(), q->p4()) < 1e-4){
                        hasOverLap=true;
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
        
        // here we have to set Tau Id as well
        
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


    
//        edm::Handle<pat::PATTauDiscriminator> tauDiscr;
//        for(size_t i = 0; i < tauIDSrcs_.size(); ++i){
//          evt.getByToken(patTauIDTokens_[i], tauDiscr);
//          tauIds[nTauIds+i].first = tauIDSrcs_[i].first;
//          tauIds[nTauIds+i].second = (*tauDiscr)[inputTauRef];
//        }

        tau.setTauIDs(tauIds);
        
        
    }// iterate over tau is finished
    
    evt.put(std::move(out));
    
    //This is for Adding new tau Id
    //  evt.put(std::move(outputTaus));
}


//
//    boostedTauChargedIsoPtSum_.push_back(itau->tauID("chargedIsoPtSum") );
//    boostedTauNeutralIsoPtSum_.push_back(itau->tauID("neutralIsoPtSum")  );
//
//
//    0092 hpsPFTauDiscriminationByLooseIsolationDBSumPtCorr = hpsPFTauDiscriminationByLooseIsolation.clone(
//    0093     deltaBetaPUTrackPtCutOverride = cms.double(0.5),
//    0094     applyDeltaBetaCorrection = True,
//    0095     isoConeSizeForDeltaBeta = 0.8,
//    0096     deltaBetaFactor = "%0.4f"%(0.0123/0.1687),
//    0097     applyOccupancyCut = False,
//    0098     applySumPtCut = True,
//    0099 )
//
//
//     hpsPFTauDiscriminationByLooseIsolation = pfRecoTauDiscriminationByIsolation.clone(
//    0071     PFTauProducer = cms.InputTag("hpsPFTauProducer"),
//    0072     Prediscriminants = requireDecayMode.clone(),
//    0073     ApplyDiscriminationByTrackerIsolation = False,
//    0074     ApplyDiscriminationByECALIsolation = True,
//    0075     applyOccupancyCut = True
//    0076 )
//
//
//
//    0001 import FWCore.ParameterSet.Config as cms
//    0002
//    0003 from RecoTauTag.RecoTau.PFRecoTauQualityCuts_cfi import PFTauQualityCuts
//    0004 from RecoTauTag.RecoTau.TauDiscriminatorTools import requireLeadPion
//    0005 from RecoTauTag.RecoTau.PFRecoTauDiscriminationByIsolation_cfi import pfRecoTauDiscriminationByIsolation
//    0006
//    0007 # Cut on sum pt < 8GeV  isolation tracks.
//    0008
//    0009 pfRecoTauDiscriminationByIsolationChargedSumPt = pfRecoTauDiscriminationByIsolation.clone(
//    0010     PFTauProducer = cms.InputTag('pfRecoTauProducer'),
//    0011
//    0012     # Require leading pion ensures that: theee is at least one track above
//    0013     # threshold (0.5 GeV) in the signal cone a track in the signal cone has
//    0014     # pT > 5 GeV
//    0015     Prediscriminants = requireLeadPion,
//    0016
//    0017     # Select which collections to use for isolation.
//    0018     ApplyDiscriminationByECALIsolation = cms.bool(False),
//    0019     ApplyDiscriminationByTrackerIsolation = cms.bool(True),
//    0020
//    0021     applyOccupancyCut = cms.bool(False),
//    0022     maximumOccupancy = cms.uint32(1),
//    0023
//    0024     applySumPtCut = cms.bool(True),
//    0025     maximumSumPtCut = cms.double(8.0),
//    0026
//    0027     applyRelativeSumPtCut = cms.bool(False),
//    0028     relativeSumPtCut = cms.double(0.0),
//    0029
//    0030     # Set the standard quality cuts on the isolation candidates
//    0031     qualityCuts = PFTauQualityCuts,
//    0032     PVProducer = PFTauQualityCuts.primaryVertexSrc  # need for Q cuts
//    0033 )
//
//
//    021     isolationQualityCuts = cms.PSet(
//    0022         minTrackPt                   = cms.double(1.0),
//    0023         maxTrackChi2                 = cms.double(100.),
//    0024         maxTransverseImpactParameter = cms.double(0.03),
//    0025         maxDeltaZ                    = cms.double(0.2),
//    0026         minTrackVertexWeight         = cms.double(-1.),    # Tracks weight in vertex
//    0027         minTrackPixelHits            = cms.uint32(0),
//    0028         minTrackHits                 = cms.uint32(8),
//    0029         minGammaEt                   = cms.double(1.5),
//    0030         #useTracksInsteadOfPFHadrons  = cms.bool(False),
//    0031     ),
//
//
    
    //      }
    
    
    //    }
    //    if (dropPiZeroRefs_) {
    //      tau.pfSpecific_[0].signalPiZeroCandidates_.clear();
    //      tau.pfSpecific_[0].isolationPiZeroCandidates_.clear();
    //    }
    //    if (dropTauChargedHadronRefs_) {
    //      tau.pfSpecific_[0].signalTauChargedHadronCandidates_.clear();
    //      tau.pfSpecific_[0].isolationTauChargedHadronCandidates_.clear();
    //    }
    //  }
    
    //  }
    
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATBoostedTauEmbedder);
