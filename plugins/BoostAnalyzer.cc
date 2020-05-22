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

// ------------ method called for each event  ------------
void
BoostAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


 using namespace std;
  edm::Handle<std::vector<pat::Tau> > boostedTauHandle;
    iEvent.getByToken(boostedTauCollection_, boostedTauHandle);
    for(vector<pat::Tau>::const_iterator itau = boostedTauHandle->begin(); itau != boostedTauHandle->end(); ++itau) {

std::cout<<" boostPt "<<itau->pt()<<"\n"; 
boostPt->Fill(itau->pt());
}

  //  Handle<TrackCollection> tracks;
// Handle<DeDxHitInfo> tracks;
//    iEvent.getByToken(tracksToken_, tracks);
//    for(TrackCollection::const_iterator itTrack = tracks->begin();
/*
for(DeDxHitInfo::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
      // int charge = itTrack->charge();
    }
*/
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
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

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostAnalyzer);
