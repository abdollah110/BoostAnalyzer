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
using reco::DeDxHitInfo;

class BoostAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit BoostAnalyzer(const edm::ParameterSet&);
      ~BoostAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      void fillBoostedTaus(const edm::Event&);
      void branchesBoostedTaus(TTree*)

      // ----------member data ---------------------------
     // edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
//	edm::EDGetTokenT<DeDxHitInfo> tracksToken_;  //used to select what tracks to read from configuration file

  edm::EDGetTokenT<std::vector<pat::Tau> >              boostedTauCollection_;
TH1F * boostPt;
TTree * tree_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
BoostAnalyzer::BoostAnalyzer(const edm::ParameterSet& iConfig)
 :
 boostedTauCollection_(consumes<std::vector<pat::Tau> >             (iConfig.getParameter<edm::InputTag>("boostedTauSrc")))
//  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
//tracksToken_(consumes<DeDxHitInfo>(iConfig.getUntrackedParameter<edm::InputTag>("isolatedTracks")))
 // boostedTauCollection_(consumes<std::vector<pat::Tau>(iConfig.getUntrackedParameter<edm::InputTag>("slimmedTausBoosted")))  
{
   //now do what ever initialization is needed
 // boostedTauCollection_      = consumes<std::vector<pat::Tau> >             (iConfig.getParameter<edm::InputTag>("boostedTauSrc"));
   edm::Service<TFileService> fs; 
  boostPt = fs->make<TH1F>("pt" , "pt" , 100 , 0 , 1000 );
  tree_    = fs->make<TTree>("EventTree", "Event data");
  branchesBoostedTaus(tree_);

}


BoostAnalyzer::~BoostAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

