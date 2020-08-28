
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "FWCore/Utilities/interface/transform.h"
#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"


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
	typedef std::pair<std::string, edm::InputTag> NameTag;
	std::vector<NameTag> tauIDSrcs_;
	std::vector<edm::EDGetTokenT<pat::PATTauDiscriminator> > patTauIDTokens_;
//    reco::CandidatePtrVector signalChargedHadrCandPtrs_;
    
};

PATBoostedTauEmbedder::PATBoostedTauEmbedder(const edm::ParameterSet& cfg)
//pf2pc_(mayConsume<edm::Association<pat::PackedCandidateCollection> >(cfg.getParameter<edm::InputTag>("packedPFCandidates")))
{
  src_ = consumes<pat::TauCollection>(cfg.getParameter<edm::InputTag>("src"));
//  pf2pc_ = mayConsume<edm::Association<pat::PackedCandidateCollection> >(cfg.getParameter<edm::InputTag>("pfcands"));
  pf2pc_ = consumes<pat::PackedCandidateCollection>(cfg.getParameter<edm::InputTag>("pfcands"));
  
//  embedIsolationPFCands_ = cfg.getParameter<bool>( "embedIsolationPFCands" );
//  embedIsolationPFChargedHadrCands_ = cfg.getParameter<bool>( "embedIsolationPFChargedHadrCands" );
//  embedIsolationPFNeutralHadrCands_ = cfg.getParameter<bool>( "embedIsolationPFNeutralHadrCands" );
//  embedIsolationPFGammaCands_ = cfg.getParameter<bool>( "embedIsolationPFGammaCands" );
  
  // read the different tau ID names
  edm::ParameterSet idps = cfg.getParameter<edm::ParameterSet>("tauIDSources");
  std::vector<std::string> names = idps.getParameterNamesForType<edm::InputTag>();
  for (std::vector<std::string>::const_iterator it = names.begin(), ed = names.end(); it != ed; ++it) {
    tauIDSrcs_.push_back(NameTag(*it, idps.getParameter<edm::InputTag>(*it)));
  }
  // but in any case at least once
  if (tauIDSrcs_.empty()) throw cms::Exception("Configuration") <<
    "PATTauProducer: id addTauID is true, you must specify:\n" <<
    "\tPSet tauIDSources = { \n" <<
    "\t\tInputTag <someName> = <someTag>   // as many as you want \n " <<
    "\t}\n";
  patTauIDTokens_ = edm::vector_transform(tauIDSrcs_, [this](NameTag const & tag){return mayConsume<pat::PATTauDiscriminator>(tag.second);});
  
  produces<std::vector<pat::Tau> >();
}


//void PATBoostedTauEmbedder::setMySignalChargedHadrCands(const auto &ptrs)
//        { signalChargedHadrCandPtrs_ = ptrs;}

void PATBoostedTauEmbedder::produce(edm::Event& evt, const edm::EventSetup& es)
{
  edm::Handle<pat::TauCollection> inputTaus;
  evt.getByToken(src_, inputTaus);
  
  
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


    // clearing the pat isolation which is not used by taus
//    tau.isolations_.clear();
//    tau.isoDeposits_.clear();
    

//   if (linkToPackedPF_) {
      reco::CandidatePtrVector signalChHPtrs, signalNHPtrs, signalGammaPtrs, isolationChHPtrs, isolationNHPtrs,
          isolationGammaPtrs;
          
        reco::CandidatePtrVector signalPtrs;
        
          int nSig=0;
          int nIso=0;



        std::cout<<" \t  tau.signalCands() " << tau.signalCands().size()<< "\n";
        
      for (const reco::CandidatePtr &p : tau.signalCands()) {
        std::cout<<" \t ###==> entering tau.signalCands()  \n";
//        signalPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
        signalPtrs.push_back(p);
      }
//      tau.setMySignalChargedHadrCands(signalPtrs);
      
   /*

      for (const reco::PFCandidatePtr &p : tau.signalPFChargedHadrCands()) {
//    for (const reco::PFCandidatePtr &p : tau.signalChargedHadrCands()) {
      std::cout<<" \t ==> entering tau.signalPFChargedHadrCands \n";
      if (nSig < 2){
        nSig++;
        signalChHPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
        }
      }
      tau.setSignalChargedHadrCands(signalChHPtrs);
      std::cout<<"\t\t signalChHPtrs = "<<signalChHPtrs.size()<<"\n\n";
      
      for (const reco::PFCandidatePtr &p : tau.signalPFNeutrHadrCands()) {
        std::cout<<" \t ==> entering tau.signalPFNeutrHadrCands \n";
        signalNHPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
      }
      tau.setSignalNeutralHadrCands(signalNHPtrs);

      for (const reco::PFCandidatePtr &p : tau.signalPFGammaCands()) {
        std::cout<<" \t ==> entering tau.signalPFGammaCands \n";
        signalGammaPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
      }
      tau.setSignalGammaCands(signalGammaPtrs);

      for (const reco::PFCandidatePtr &p : tau.isolationPFChargedHadrCands()) {
      if (nIso < 2){
        nIso++;
        isolationChHPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
        }
      }
      tau.setIsolationChargedHadrCands(isolationChHPtrs);

      for (const reco::PFCandidatePtr &p : tau.isolationPFNeutrHadrCands()) {
        std::cout<<" \t ==> entering tau.isolationPFNeutrHadrCands \n"   ;
        isolationNHPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
      }
      tau.setIsolationNeutralHadrCands(isolationNHPtrs);

      for (const reco::PFCandidatePtr &p : tau.isolationPFGammaCands()) {
        isolationGammaPtrs.push_back(edm::refToPtr((*pf2pc)[p]));
      }
      tau.setIsolationGammaCands(isolationGammaPtrs);
      std::cout<<"\t\t isolationGammaPtrs = "<<isolationGammaPtrs.size()<<"\n\n";
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
  */
  }
  
evt.put(std::move(out));
  
  //This is for Adding new tau Id
//  evt.put(std::move(outputTaus));
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATBoostedTauEmbedder);
