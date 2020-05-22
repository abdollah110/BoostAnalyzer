#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "BoostTau/BoostAnalyzer/interface/BoostAnalyzer.h"
#include "BoostTau/BoostAnalyzer/interface/GenParticleParentage.h"
using namespace std;


Int_t            nMC_;
vector<int>      mcPID;
vector<float>    mcVtx;
vector<float>    mcVty;
vector<float>    mcVtz;
vector<float>    mcPt;
vector<float>    mcMass;
vector<float>    mcEta;
vector<float>    mcPhi;
vector<float>    mcE;
vector<float>    mcEt;
vector<int>      mcGMomPID;
vector<int>      mcMomPID;
vector<float>    mcMomPt;
vector<float>    mcMomMass;
vector<float>    mcMomEta;
vector<float>    mcMomPhi;
//vector<int>      mcIndex;
vector<UShort_t> mcStatusFlag;
vector<int>      mcParentage;
vector<int>      mcStatus;
vector<float>    mcCalIsoDR03;
vector<float>    mcTrkIsoDR03;
vector<float>    mcCalIsoDR04;
vector<float>    mcTrkIsoDR04;

//Tau visible daugthers
vector<float> taudaugPt ;
vector<float> taudaugEta;
vector<float> taudaugPhi;
vector<float> taudaugMass;
//vector<int> numGenTau;
Int_t            numGenTau;

//using namespace std;

std::vector<reco::Candidate::LorentzVector>  BoostAnalyzer::buildGenTaus(const edm::Event& e) {
    bool include_leptonic = false;
    std::vector< reco::Candidate::LorentzVector > genTauJets;


    edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
    e.getByToken(genParticlesCollection_, genParticlesHandle);

    if (!genParticlesHandle.isValid()) {
      edm::LogWarning("BoostAnalyzer") << "no reco::GenParticles in event";
//      return 0;
    }
        
    for (vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {

          size_t id = abs(ip->pdgId());
          if (id == 15) {
            bool prompt = ip->statusFlags().isPrompt();
            if (prompt) {
              if (ip->numberOfDaughters() > 0) {
                bool has_tau_daughter = false;
                bool has_lepton_daughter = false;
                for (unsigned j = 0; j < ip->numberOfDaughters(); ++j) {
                  if (abs(ip->daughterRef(j)->pdgId()) == 15) has_tau_daughter = true;
                  if (abs(ip->daughterRef(j)->pdgId()) == 11 || abs(ip->daughterRef(j)->pdgId()) == 13) has_lepton_daughter = true;
                }
                if (has_tau_daughter) {
                  //std::cout << "Has Tau Daughter" << std::endl;
                  continue;}
                if (has_lepton_daughter && !include_leptonic) {
                  //std::cout << "Has E/Mu Daughter" << std::endl;
                  continue;}

                reco::Candidate::LorentzVector genTau;
                for(size_t dau = 0; dau != ip->numberOfDaughters(); ++dau) {
                  size_t id_d = abs(ip->daughterRef( dau )->pdgId());
                  //if (id_d == 11 || id_d == 12 || id_d == 13 || id_d == 14 || id_d == 16) continue; //exclude neutrinos
                  if (id_d == 12 || id_d == 14 || id_d == 16) continue; //exclude neutrinos
                  genTau += ip->daughterRef( dau )->p4();
                  //std::cout << " ------- " << dau << ": " << genTau.Pt() << std::endl;
                } // daughers loop
                genTauJets.push_back( genTau );
              } // daughers > 0
            } // prompt
          } // tau ID
        } // gen Loop
    return genTauJets;
}


void BoostAnalyzer::branchesGenPart(TTree* tree) {

  tree->Branch("nMC",          &nMC_);
  tree->Branch("numGenTau",          &numGenTau);
  
  tree->Branch("mcPID",        &mcPID);
//  tree->Branch("mcVtx",        &mcVtx);
//  tree->Branch("mcVty",        &mcVty);
//  tree->Branch("mcVtz",        &mcVtz);
  tree->Branch("mcPt",         &mcPt);
  tree->Branch("mcMass",       &mcMass);
  tree->Branch("mcEta",        &mcEta);
  tree->Branch("mcPhi",        &mcPhi);
  tree->Branch("mcE",          &mcE);
  tree->Branch("mcEt",         &mcEt);
  tree->Branch("mcGMomPID",    &mcGMomPID);
  tree->Branch("mcMomPID",     &mcMomPID);
  tree->Branch("mcMomPt",      &mcMomPt);
  tree->Branch("mcMomMass",    &mcMomMass);
  tree->Branch("mcMomEta",     &mcMomEta);
  tree->Branch("mcMomPhi",     &mcMomPhi);
  //tree->Branch("mcIndex",      &mcIndex);
  tree->Branch("mcStatusFlag", &mcStatusFlag); //-999:non W or Z, 1:hardronic, 2:e, 3:mu, 4:tau
  tree->Branch("mcParentage",  &mcParentage);  // 16*lepton + 8*boson + 4*non-prompt + 2*qcd + exotics
  tree->Branch("mcStatus",     &mcStatus);     // status of the particle
//  tree->Branch("mcCalIsoDR03", &mcCalIsoDR03);
//  tree->Branch("mcTrkIsoDR03", &mcTrkIsoDR03);
//  tree->Branch("mcCalIsoDR04", &mcCalIsoDR04);
//  tree->Branch("mcTrkIsoDR04", &mcTrkIsoDR04);



    //Tau visible daugthers
    tree->Branch("taudaugPt" ,&taudaugPt   );
    tree->Branch("taudaugEta" ,&taudaugEta  );
    tree->Branch("taudaugPhi" ,&taudaugPhi );
    tree->Branch("taudaugMass" ,&taudaugMass  );
//    tree->Branch("numGenTau" ,&numGenTau  );
    
    
}


void BoostAnalyzer::fillGenPart(const edm::Event& e) {

  // Fills tree branches with generated particle info.

  // cleanup from previous execution
  mcPID       .clear();
  mcVtx       .clear();
  mcVty       .clear();
  mcVtz       .clear();
  mcPt        .clear();
  mcMass      .clear();
  mcEta       .clear();
  mcPhi       .clear();
  mcE         .clear();
  mcEt        .clear();
  mcGMomPID   .clear();
  mcMomPID    .clear();
  mcMomPt     .clear();
  mcMomMass   .clear();
  mcMomEta    .clear();
  mcMomPhi    .clear();
  //mcIndex     .clear();
  mcStatusFlag.clear();
  mcParentage .clear();
  mcStatus    .clear();
  mcCalIsoDR03.clear();
  mcTrkIsoDR03.clear();
  mcCalIsoDR04.clear();
  mcTrkIsoDR04.clear();
  
  taudaugPt.clear();
  taudaugEta.clear();
  taudaugPhi.clear();
  taudaugMass.clear();
//  numGenTau.clear();



  nMC_ = 0;

  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  e.getByToken(genParticlesCollection_, genParticlesHandle);

  if (!genParticlesHandle.isValid()) {
    edm::LogWarning("BoostAnalyzer") << "no reco::GenParticles in event";
    return;
  }
  
  
  numGenTau=0;
  
// Get rebuilt gen taus w/o neutrino energy
std::vector<reco::Candidate::LorentzVector> genTaus = buildGenTaus(e);
//numGenTau.push_back(genTaus.size());
    
for ( auto vec : genTaus ) {
  taudaugPt.push_back(vec.Pt());
  taudaugEta.push_back(vec.Eta());
  taudaugPhi.push_back(vec.Phi());
  taudaugMass.push_back(vec.mass());
  numGenTau++;
}
  
  
  

  int genIndex = 0;

  for (vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
    genIndex++;

    int status = ip->status();
    //bool stableFinalStateParticle = status == 1 && ip->pt() > 5.0;
    
    bool quarks = abs(ip->pdgId())<7;

    // keep non-FSR photons with pT > 5.0 and all leptons with pT > 3.0;
    bool photonOrLepton =
      (ip->pdgId() == 22 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && abs(ip->pdgId()) == 11 && (ip->isPromptFinalState() || ip->isLastCopy())) || 
      (status == 1 && abs(ip->pdgId()) == 13 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && (abs(ip->pdgId()) == 12 || abs(ip->pdgId()) == 14 || abs(ip->pdgId()) == 16)) ||
      (status == 1 && ( abs(ip->pdgId()) >= 11 && abs(ip->pdgId()) <= 16 ) && ip->pt() > 3.0)  ||
      (status < 10 && abs(ip->pdgId()) == 15 && ip->pt() > 3.0);
      
    // select also Z, W, H, top and b 
    bool heavyParticle =
      ((    ip->pdgId()  == 23 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) == 24 && ip->isHardProcess()) || 
       (    ip->pdgId()  == 25 && ip->isHardProcess()) ||
       (abs(ip->pdgId()) ==  6 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) ==  5 && ip->isHardProcess()));
    
    bool newParticle = false;
    for (size_t inp = 0; inp < newparticles_.size(); ++inp) {
      if (abs(ip->pdgId()) == newparticles_[inp]) newParticle = true;
    }
    
    if ( heavyParticle || photonOrLepton || quarks || newParticle ) {
      
      const reco::Candidate *p = (const reco::Candidate*)&(*ip);
      if (!runOnParticleGun_ && !p->mother()) continue;

      mcPID    .push_back(p->pdgId());
      mcVtx    .push_back(p->vx());
      mcVty    .push_back(p->vy());
      mcVtz    .push_back(p->vz());
      mcPt     .push_back(p->pt());
      mcMass   .push_back(p->mass());
      mcEta    .push_back(p->eta());
      mcPhi    .push_back(p->phi());
      mcE      .push_back(p->energy());
      mcEt     .push_back(p->et());
      mcStatus .push_back(p->status());
	
      UShort_t tmpStatusFlag = 0;
      if (ip->fromHardProcessFinalState()) setbit(tmpStatusFlag, 0);
      if (ip->isPromptFinalState())        setbit(tmpStatusFlag, 1);
      if (ip->isHardProcess())  setbit(tmpStatusFlag, 2);

      // if genParticle is W or Z, check its decay type
      if ( ip->pdgId() == 23 || abs(ip->pdgId()) == 24 ) {
        for (size_t k=0; k < p->numberOfDaughters(); ++k) {
          const reco::Candidate *dp = p->daughter(k);
          if (abs(dp->pdgId())<=6)                               setbit(tmpStatusFlag, 4);
          else if (abs(dp->pdgId())==11 || abs(dp->pdgId())==12) setbit(tmpStatusFlag, 5);
          else if (abs(dp->pdgId())==13 || abs(dp->pdgId())==14) setbit(tmpStatusFlag, 6);
          else if (abs(dp->pdgId())==15 || abs(dp->pdgId())==16) setbit(tmpStatusFlag, 7);
        }
      }
      if (ip->isLastCopy())  setbit(tmpStatusFlag, 8);
      
      
//      closest.statusFlags().isDirectPromptTauDecayProduct() ) return 4.0;

      if (ip->statusFlags().isPrompt())  setbit(tmpStatusFlag, 9);
      if (ip->statusFlags().isDirectPromptTauDecayProduct())  setbit(tmpStatusFlag, 10);
      
      
      
      mcStatusFlag.push_back(tmpStatusFlag);



      int mcGMomPID_ = -999;
      int mcMomPID_  = -999;
      float mcMomPt_    = -999.;
      float mcMomMass_  = -999.;
      float mcMomEta_   = -999.;
      float mcMomPhi_   = -999.;
      if (!runOnSherpa_) {
	
	      reco::GenParticleRef partRef = reco::GenParticleRef(genParticlesHandle, ip-genParticlesHandle->begin());
	      genpartparentage::GenParticleParentage particleHistory(partRef);
	      
	      mcParentage.push_back(particleHistory.hasLeptonParent()*16   +
	      		      particleHistory.hasBosonParent()*8     +
	      		      particleHistory.hasNonPromptParent()*4 +
	      		      particleHistory.hasQCDParent()*2       +
	      		      particleHistory.hasExoticParent());      
	      
	      if ( particleHistory.hasRealParent() ) {
	        reco::GenParticleRef momRef = particleHistory.parent();
	        if ( momRef.isNonnull() && momRef.isAvailable() ) {
	          mcMomPID_  = momRef->pdgId();
	          mcMomPt_   = momRef->pt();
	          mcMomMass_ = momRef->mass();
	          mcMomEta_  = momRef->eta();
	          mcMomPhi_  = momRef->phi();
	          
	          // get Granny
	          genpartparentage::GenParticleParentage motherParticle(momRef);
	          if ( motherParticle.hasRealParent() ) {
	            reco::GenParticleRef granny = motherParticle.parent();
	            mcGMomPID_ = granny->pdgId();
	          }
	        }
	      }
	      mcGMomPID.push_back(mcGMomPID_);
	      mcMomPID.push_back(mcMomPID_);
	      mcMomPt.push_back(mcMomPt_);
	      mcMomMass.push_back(mcMomMass_);
	      mcMomEta.push_back(mcMomEta_);
	      mcMomPhi.push_back(mcMomPhi_);
      }


      nMC_++;
    } // save info on particles of interest
  } // loop over gen-level particles

}
