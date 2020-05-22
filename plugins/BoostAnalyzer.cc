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
        fillBoostedTaus(iEvent);
        
        tree_->Fill();
        
        
    }
    
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
