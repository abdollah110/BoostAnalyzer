#ifndef BoostAnalyzer_h
#define BoostAnalyzer_h

// -*- C++ -*-
//
// Package:    BoostTau/BoostAnalyzer
// Class:      BoostAnalyzer
//
/**\class BoostAnalyzer BoostAnalyzer.cc BoostTau/BoostAnalyzer/plugins/BoostAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Abdollah Mohammadi
//         Created:  Thu, 21 May 2020 17:33:45 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"
 #include "DataFormats/TrackReco/interface/DeDxHitInfo.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


//using reco::TrackCollection;
void setbit(UShort_t& x, UShort_t bit);

class BoostAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit BoostAnalyzer(const edm::ParameterSet&);
//      ~BoostAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      void fillBoostedTaus(const edm::Event&);
      void fillTaus(const edm::Event&);
      void fillGenPart(const edm::Event&);
      
      void branchesBoostedTaus(TTree*);
      void branchesTaus(TTree*);
      void branchesGenPart(TTree*);
      std::vector<reco::Candidate::LorentzVector>  buildGenTaus (const edm::Event&);


      // ----------member data ---------------------------

  edm::EDGetTokenT<std::vector<pat::Tau> >              boostedTauCollection_;
  edm::EDGetTokenT<std::vector<pat::Tau> >              tauCollection_;
  edm::EDGetTokenT<std::vector<reco::GenParticle>>              genParticlesCollection_;
  edm::EDGetTokenT<std::vector<pat::Tau> >              NewtauCollection_;
  edm::EDGetTokenT<std::vector<pat::Tau> >              NewtauCollectionTest_;
  edm::EDGetTokenT<std::vector<pat::Tau> >              boostedTauCollectionNoOverLap_;
  
  


  
TH1F * boostPt;
TTree * tree_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//




//BoostAnalyzer::~BoostAnalyzer()
//{
//
//   // do anything here that needs to be done at desctruction time
//   // (e.g. close files, deallocate resources etc.)
//
//}


//
// member functions
//

#endif
