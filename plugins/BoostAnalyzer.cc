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



#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"


using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}


//
// constructors and destructor
//
BoostAnalyzer::BoostAnalyzer(const edm::ParameterSet& iConfig)
 :
 boostedTauCollection_(consumes<std::vector<pat::Tau> >                   (iConfig.getParameter<edm::InputTag>("boostedTauSrc"))),
 tauCollection_(consumes<std::vector<pat::Tau> >                          (iConfig.getParameter<edm::InputTag>("tauSrc"))),
 genParticlesCollection_(consumes<vector<reco::GenParticle> >             (iConfig.getParameter<edm::InputTag>("genParticleSrc"))),
 NewtauCollection_(consumes<std::vector<pat::Tau> >                          (iConfig.getParameter<edm::InputTag>("tauSrcNew"))),
 boostedTauCollectionNoOverLap_(consumes<std::vector<pat::Tau> >                          (iConfig.getParameter<edm::InputTag>("boostedTauNoOverLapSrc"))),
boostedTauCollectionNoOverLapIDUpdated_(consumes<std::vector<pat::Tau> >                          (iConfig.getParameter<edm::InputTag>("boostedTauNoOverLapIDUpdatedSrc"))),
jetsAK8Label_(consumes<std::vector<pat::Jet> >               (iConfig.getParameter<edm::InputTag>("ak8JetSrc"))),
{
  edm::Service<TFileService> fs;
  boostPt = fs->make<TH1F>("pt" , "pt" , 100 , 0 , 1000 );
  tree_    = fs->make<TTree>("EventTree", "Event data");
  branchesBoostedTaus(tree_);
  branchesTaus(tree_);
  branchesGenPart(tree_);

}




// ------------ method called for each event  ------------
void
BoostAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    fillBoostedTaus(iEvent);
    fillTaus(iEvent);
    fillGenPart(iEvent);

    tree_->Fill();
    
    
}


// ------------ method called once each job just before starting event loop  ------------
void
BoostAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
BoostAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BoostAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostAnalyzer);
