//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat May 23 18:37:38 2020 by ROOT version 6.16/00
// from TTree EventTree/Event data
// found on file: histodemo.root
//////////////////////////////////////////////////////////

#ifndef SkimerBoost_h
#define SkimerBoost_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class SkimerBoost {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nBoostedTau;
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFinding;
   vector<bool>    *boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;
   vector<bool>    *boostedTauByMVA6LooseElectronRejection;
   vector<bool>    *boostedTauByMVA6TightElectronRejection;
   vector<bool>    *boostedTauByLooseMuonRejection3;
   vector<bool>    *boostedTauByTightMuonRejection3;
   vector<bool>    *boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;
   vector<float>   *boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *boostedTauByIsolationMVArun2v1DBnewDMwLTraw;
   vector<float>   *boostedTauByIsolationMVArun2v1DBoldDMwLTraw;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;
   vector<float>   *boostedTauEta;
   vector<float>   *boostedTauPhi;
   vector<float>   *boostedTauPt;
   vector<float>   *boostedTauEt;
   vector<float>   *boostedTauCharge;
   vector<float>   *boostedTauP;
   vector<float>   *boostedTauPx;
   vector<float>   *boostedTauPy;
   vector<float>   *boostedTauPz;
   vector<float>   *boostedTauVz;
   vector<float>   *boostedTauEnergy;
   vector<float>   *boostedTauMass;
   vector<float>   *boostedTauDxy;
   vector<float>   *boostedTauZImpact;
   vector<int>     *boostedTauDecayMode;
   vector<bool>    *boostedTauLeadChargedHadronExists;
   vector<float>   *boostedTauLeadChargedHadronEta;
   vector<float>   *boostedTauLeadChargedHadronPhi;
   vector<float>   *boostedTauLeadChargedHadronPt;
   vector<float>   *boostedTauChargedIsoPtSum;
   vector<float>   *boostedTauNeutralIsoPtSum;
   vector<float>   *boostedTauPuCorrPtSum;
   vector<int>     *boostedTauNumSignalPFChargedHadrCands;
   vector<int>     *boostedTauNumSignalPFNeutrHadrCands;
   vector<int>     *boostedTauNumSignalPFGammaCands;
   vector<int>     *boostedTauNumSignalPFCands;
   vector<int>     *boostedTauNumIsolationPFChargedHadrCands;
   vector<int>     *boostedTauNumIsolationPFNeutrHadrCands;
   vector<int>     *boostedTauNumIsolationPFGammaCands;
   vector<int>     *boostedTauNumIsolationPFCands;
   vector<float>   *boostedTaufootprintCorrection;
   vector<float>   *boostedTauphotonPtSumOutsideSignalCone;
   vector<float>   *boostedTaudz;
   vector<float>   *boostedTaudxy;
   vector<vector<float> > *boostedTauSignalPFCands;
   vector<vector<float> > *boostedTauSignalPFGammaCands;
   vector<vector<float> > *boostedTauIsolationPFCands;
   vector<vector<float> > *boostedTauIsolationPFGammaCands;
   Int_t           nTau;
   vector<bool>    *taupfTausDiscriminationByDecayModeFinding;
   vector<bool>    *taupfTausDiscriminationByDecayModeFindingNewDMs;
   vector<bool>    *tauByMVA6LooseElectronRejection;
   vector<bool>    *tauByMVA6TightElectronRejection;
   vector<bool>    *tauByLooseMuonRejection3;
   vector<bool>    *tauByTightMuonRejection3;
   vector<bool>    *tauByLooseCombinedIsolationDeltaBetaCorr3Hits;
   vector<bool>    *tauByTightCombinedIsolationDeltaBetaCorr3Hits;
   vector<float>   *tauCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *tauByIsolationMVArun2v1DBnewDMwLTraw;
   vector<float>   *tauByIsolationMVArun2v1DBoldDMwLTraw;
   vector<bool>    *tauByTightIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByTightIsolationMVArun2v1DBoldDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1DBnewDMwLT;
   vector<bool>    *tauByLooseIsolationMVArun2v1DBoldDMwLT;
   vector<float>   *tauEta;
   vector<float>   *tauPhi;
   vector<float>   *tauPt;
   vector<float>   *tauEt;
   vector<float>   *tauCharge;
   vector<float>   *tauP;
   vector<float>   *tauPx;
   vector<float>   *tauPy;
   vector<float>   *tauPz;
   vector<float>   *tauVz;
   vector<float>   *tauEnergy;
   vector<float>   *tauMass;
   vector<float>   *tauDxy;
   vector<float>   *tauZImpact;
   vector<int>     *tauDecayMode;
   vector<bool>    *tauLeadChargedHadronExists;
   vector<float>   *tauLeadChargedHadronEta;
   vector<float>   *tauLeadChargedHadronPhi;
   vector<float>   *tauLeadChargedHadronPt;
   vector<float>   *tauChargedIsoPtSum;
   vector<float>   *tauNeutralIsoPtSum;
   vector<float>   *tauPuCorrPtSum;
   vector<int>     *tauNumSignalPFChargedHadrCands;
   vector<int>     *tauNumSignalPFNeutrHadrCands;
   vector<int>     *tauNumSignalPFGammaCands;
   vector<int>     *tauNumSignalPFCands;
   vector<int>     *tauNumIsolationPFChargedHadrCands;
   vector<int>     *tauNumIsolationPFNeutrHadrCands;
   vector<int>     *tauNumIsolationPFGammaCands;
   vector<int>     *tauNumIsolationPFCands;
   vector<float>   *taufootprintCorrection;
   vector<float>   *tauphotonPtSumOutsideSignalCone;
   vector<float>   *taudz;
   vector<float>   *taudxy;
   Int_t           nMC;
   Int_t           numGenTau;
   vector<int>     *mcPID;
   vector<float>   *mcPt;
   vector<float>   *mcMass;
   vector<float>   *mcEta;
   vector<float>   *mcPhi;
   vector<float>   *mcE;
   vector<float>   *mcEt;
   vector<int>     *mcGMomPID;
   vector<int>     *mcMomPID;
   vector<float>   *mcMomPt;
   vector<float>   *mcMomMass;
   vector<float>   *mcMomEta;
   vector<float>   *mcMomPhi;
   vector<unsigned short> *mcStatusFlag;
   vector<int>     *mcParentage;
   vector<int>     *mcStatus;
   vector<float>   *taudaugPt;
   vector<float>   *taudaugEta;
   vector<float>   *taudaugPhi;
   vector<float>   *taudaugMass;

   // List of branches
   TBranch        *b_nBoostedTau;   //!
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFinding;   //!
   TBranch        *b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs;   //!
   TBranch        *b_boostedTauByMVA6LooseElectronRejection;   //!
   TBranch        *b_boostedTauByMVA6TightElectronRejection;   //!
   TBranch        *b_boostedTauByLooseMuonRejection3;   //!
   TBranch        *b_boostedTauByTightMuonRejection3;   //!
   TBranch        *b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBnewDMwLTraw;   //!
   TBranch        *b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_boostedTauEta;   //!
   TBranch        *b_boostedTauPhi;   //!
   TBranch        *b_boostedTauPt;   //!
   TBranch        *b_boostedTauEt;   //!
   TBranch        *b_boostedTauCharge;   //!
   TBranch        *b_boostedTauP;   //!
   TBranch        *b_boostedTauPx;   //!
   TBranch        *b_boostedTauPy;   //!
   TBranch        *b_boostedTauPz;   //!
   TBranch        *b_boostedTauVz;   //!
   TBranch        *b_boostedTauEnergy;   //!
   TBranch        *b_boostedTauMass;   //!
   TBranch        *b_boostedTauDxy;   //!
   TBranch        *b_boostedTauZImpact;   //!
   TBranch        *b_boostedTauDecayMode;   //!
   TBranch        *b_boostedTauLeadChargedHadronExists;   //!
   TBranch        *b_boostedTauLeadChargedHadronEta;   //!
   TBranch        *b_boostedTauLeadChargedHadronPhi;   //!
   TBranch        *b_boostedTauLeadChargedHadronPt;   //!
   TBranch        *b_boostedTauChargedIsoPtSum;   //!
   TBranch        *b_boostedTauNeutralIsoPtSum;   //!
   TBranch        *b_boostedTauPuCorrPtSum;   //!
   TBranch        *b_boostedTauNumSignalPFChargedHadrCands;   //!
   TBranch        *b_boostedTauNumSignalPFNeutrHadrCands;   //!
   TBranch        *b_boostedTauNumSignalPFGammaCands;   //!
   TBranch        *b_boostedTauNumSignalPFCands;   //!
   TBranch        *b_boostedTauNumIsolationPFChargedHadrCands;   //!
   TBranch        *b_boostedTauNumIsolationPFNeutrHadrCands;   //!
   TBranch        *b_boostedTauNumIsolationPFGammaCands;   //!
   TBranch        *b_boostedTauNumIsolationPFCands;   //!
   TBranch        *b_boostedTaufootprintCorrection;   //!
   TBranch        *b_boostedTauphotonPtSumOutsideSignalCone;   //!
   TBranch        *b_boostedTaudz;   //!
   TBranch        *b_boostedTaudxy;   //!
   TBranch        *b_boostedTauSignalPFCands;   //!
   TBranch        *b_boostedTauSignalPFGammaCands;   //!
   TBranch        *b_boostedTauIsolationPFCands;   //!
   TBranch        *b_boostedTauIsolationPFGammaCands;   //!
   TBranch        *b_nTau;   //!
   TBranch        *b_taupfTausDiscriminationByDecayModeFinding;   //!
   TBranch        *b_taupfTausDiscriminationByDecayModeFindingNewDMs;   //!
   TBranch        *b_tauByMVA6LooseElectronRejection;   //!
   TBranch        *b_tauByMVA6TightElectronRejection;   //!
   TBranch        *b_tauByLooseMuonRejection3;   //!
   TBranch        *b_tauByTightMuonRejection3;   //!
   TBranch        *b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_tauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_tauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_tauByIsolationMVArun2v1DBnewDMwLTraw;   //!
   TBranch        *b_tauByIsolationMVArun2v1DBoldDMwLTraw;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByTightIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1DBnewDMwLT;   //!
   TBranch        *b_tauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
   TBranch        *b_tauEta;   //!
   TBranch        *b_tauPhi;   //!
   TBranch        *b_tauPt;   //!
   TBranch        *b_tauEt;   //!
   TBranch        *b_tauCharge;   //!
   TBranch        *b_tauP;   //!
   TBranch        *b_tauPx;   //!
   TBranch        *b_tauPy;   //!
   TBranch        *b_tauPz;   //!
   TBranch        *b_tauVz;   //!
   TBranch        *b_tauEnergy;   //!
   TBranch        *b_tauMass;   //!
   TBranch        *b_tauDxy;   //!
   TBranch        *b_tauZImpact;   //!
   TBranch        *b_tauDecayMode;   //!
   TBranch        *b_tauLeadChargedHadronExists;   //!
   TBranch        *b_tauLeadChargedHadronEta;   //!
   TBranch        *b_tauLeadChargedHadronPhi;   //!
   TBranch        *b_tauLeadChargedHadronPt;   //!
   TBranch        *b_tauChargedIsoPtSum;   //!
   TBranch        *b_tauNeutralIsoPtSum;   //!
   TBranch        *b_tauPuCorrPtSum;   //!
   TBranch        *b_tauNumSignalPFChargedHadrCands;   //!
   TBranch        *b_tauNumSignalPFNeutrHadrCands;   //!
   TBranch        *b_tauNumSignalPFGammaCands;   //!
   TBranch        *b_tauNumSignalPFCands;   //!
   TBranch        *b_tauNumIsolationPFChargedHadrCands;   //!
   TBranch        *b_tauNumIsolationPFNeutrHadrCands;   //!
   TBranch        *b_tauNumIsolationPFGammaCands;   //!
   TBranch        *b_tauNumIsolationPFCands;   //!
   TBranch        *b_taufootprintCorrection;   //!
   TBranch        *b_tauphotonPtSumOutsideSignalCone;   //!
   TBranch        *b_taudz;   //!
   TBranch        *b_taudxy;   //!
   TBranch        *b_nMC;   //!
   TBranch        *b_numGenTau;   //!
   TBranch        *b_mcPID;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcMass;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_mcE;   //!
   TBranch        *b_mcEt;   //!
   TBranch        *b_mcGMomPID;   //!
   TBranch        *b_mcMomPID;   //!
   TBranch        *b_mcMomPt;   //!
   TBranch        *b_mcMomMass;   //!
   TBranch        *b_mcMomEta;   //!
   TBranch        *b_mcMomPhi;   //!
   TBranch        *b_mcStatusFlag;   //!
   TBranch        *b_mcParentage;   //!
   TBranch        *b_mcStatus;   //!
   TBranch        *b_taudaugPt;   //!
   TBranch        *b_taudaugEta;   //!
   TBranch        *b_taudaugPhi;   //!
   TBranch        *b_taudaugMass;   //!

   SkimerBoost(TString fileNamem);
    virtual ~SkimerBoost();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(TString outputFile);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SkimerBoost_cxx
SkimerBoost::SkimerBoost(TTree *tree) : fChain(0)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    TFile* file = TFile::Open(fileName);
    //    file->cd(fileName + ":/ggNtuplizer");
    //    lllll
//    TTree* tree = (TTree*)gDirectory->Get("EventTree");
    TTree* tree = (TTree*)gDirectory->Get("demo/EventTree");
    Init(tree);
}

SkimerBoost::~SkimerBoost()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SkimerBoost::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SkimerBoost::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SkimerBoost::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   boostedTaupfTausDiscriminationByDecayModeFinding = 0;
   boostedTaupfTausDiscriminationByDecayModeFindingNewDMs = 0;
   boostedTauByMVA6LooseElectronRejection = 0;
   boostedTauByMVA6TightElectronRejection = 0;
   boostedTauByLooseMuonRejection3 = 0;
   boostedTauByTightMuonRejection3 = 0;
   boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
   boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits = 0;
   boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   boostedTauByIsolationMVArun2v1DBnewDMwLTraw = 0;
   boostedTauByIsolationMVArun2v1DBoldDMwLTraw = 0;
   boostedTauByTightIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByTightIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1DBnewDMwLT = 0;
   boostedTauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
   boostedTauEta = 0;
   boostedTauPhi = 0;
   boostedTauPt = 0;
   boostedTauEt = 0;
   boostedTauCharge = 0;
   boostedTauP = 0;
   boostedTauPx = 0;
   boostedTauPy = 0;
   boostedTauPz = 0;
   boostedTauVz = 0;
   boostedTauEnergy = 0;
   boostedTauMass = 0;
   boostedTauDxy = 0;
   boostedTauZImpact = 0;
   boostedTauDecayMode = 0;
   boostedTauLeadChargedHadronExists = 0;
   boostedTauLeadChargedHadronEta = 0;
   boostedTauLeadChargedHadronPhi = 0;
   boostedTauLeadChargedHadronPt = 0;
   boostedTauChargedIsoPtSum = 0;
   boostedTauNeutralIsoPtSum = 0;
   boostedTauPuCorrPtSum = 0;
   boostedTauNumSignalPFChargedHadrCands = 0;
   boostedTauNumSignalPFNeutrHadrCands = 0;
   boostedTauNumSignalPFGammaCands = 0;
   boostedTauNumSignalPFCands = 0;
   boostedTauNumIsolationPFChargedHadrCands = 0;
   boostedTauNumIsolationPFNeutrHadrCands = 0;
   boostedTauNumIsolationPFGammaCands = 0;
   boostedTauNumIsolationPFCands = 0;
   boostedTaufootprintCorrection = 0;
   boostedTauphotonPtSumOutsideSignalCone = 0;
   boostedTaudz = 0;
   boostedTaudxy = 0;
   boostedTauSignalPFCands = 0;
   boostedTauSignalPFGammaCands = 0;
   boostedTauIsolationPFCands = 0;
   boostedTauIsolationPFGammaCands = 0;
   taupfTausDiscriminationByDecayModeFinding = 0;
   taupfTausDiscriminationByDecayModeFindingNewDMs = 0;
   tauByMVA6LooseElectronRejection = 0;
   tauByMVA6TightElectronRejection = 0;
   tauByLooseMuonRejection3 = 0;
   tauByTightMuonRejection3 = 0;
   tauByLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
   tauByTightCombinedIsolationDeltaBetaCorr3Hits = 0;
   tauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   tauByIsolationMVArun2v1DBnewDMwLTraw = 0;
   tauByIsolationMVArun2v1DBoldDMwLTraw = 0;
   tauByTightIsolationMVArun2v1DBnewDMwLT = 0;
   tauByTightIsolationMVArun2v1DBoldDMwLT = 0;
   tauByLooseIsolationMVArun2v1DBnewDMwLT = 0;
   tauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
   tauEta = 0;
   tauPhi = 0;
   tauPt = 0;
   tauEt = 0;
   tauCharge = 0;
   tauP = 0;
   tauPx = 0;
   tauPy = 0;
   tauPz = 0;
   tauVz = 0;
   tauEnergy = 0;
   tauMass = 0;
   tauDxy = 0;
   tauZImpact = 0;
   tauDecayMode = 0;
   tauLeadChargedHadronExists = 0;
   tauLeadChargedHadronEta = 0;
   tauLeadChargedHadronPhi = 0;
   tauLeadChargedHadronPt = 0;
   tauChargedIsoPtSum = 0;
   tauNeutralIsoPtSum = 0;
   tauPuCorrPtSum = 0;
   tauNumSignalPFChargedHadrCands = 0;
   tauNumSignalPFNeutrHadrCands = 0;
   tauNumSignalPFGammaCands = 0;
   tauNumSignalPFCands = 0;
   tauNumIsolationPFChargedHadrCands = 0;
   tauNumIsolationPFNeutrHadrCands = 0;
   tauNumIsolationPFGammaCands = 0;
   tauNumIsolationPFCands = 0;
   taufootprintCorrection = 0;
   tauphotonPtSumOutsideSignalCone = 0;
   taudz = 0;
   taudxy = 0;
   mcPID = 0;
   mcPt = 0;
   mcMass = 0;
   mcEta = 0;
   mcPhi = 0;
   mcE = 0;
   mcEt = 0;
   mcGMomPID = 0;
   mcMomPID = 0;
   mcMomPt = 0;
   mcMomMass = 0;
   mcMomEta = 0;
   mcMomPhi = 0;
   mcStatusFlag = 0;
   mcParentage = 0;
   mcStatus = 0;
   taudaugPt = 0;
   taudaugEta = 0;
   taudaugPhi = 0;
   taudaugMass = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nBoostedTau", &nBoostedTau, &b_nBoostedTau);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFinding", &boostedTaupfTausDiscriminationByDecayModeFinding, &b_boostedTaupfTausDiscriminationByDecayModeFinding);
   fChain->SetBranchAddress("boostedTaupfTausDiscriminationByDecayModeFindingNewDMs", &boostedTaupfTausDiscriminationByDecayModeFindingNewDMs, &b_boostedTaupfTausDiscriminationByDecayModeFindingNewDMs);
   fChain->SetBranchAddress("boostedTauByMVA6LooseElectronRejection", &boostedTauByMVA6LooseElectronRejection, &b_boostedTauByMVA6LooseElectronRejection);
   fChain->SetBranchAddress("boostedTauByMVA6TightElectronRejection", &boostedTauByMVA6TightElectronRejection, &b_boostedTauByMVA6TightElectronRejection);
   fChain->SetBranchAddress("boostedTauByLooseMuonRejection3", &boostedTauByLooseMuonRejection3, &b_boostedTauByLooseMuonRejection3);
   fChain->SetBranchAddress("boostedTauByTightMuonRejection3", &boostedTauByTightMuonRejection3, &b_boostedTauByTightMuonRejection3);
   fChain->SetBranchAddress("boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits", &boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_boostedTauByTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits", &boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_boostedTauCombinedIsolationDeltaBetaCorrRaw3Hits);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBnewDMwLTraw", &boostedTauByIsolationMVArun2v1DBnewDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBnewDMwLTraw);
   fChain->SetBranchAddress("boostedTauByIsolationMVArun2v1DBoldDMwLTraw", &boostedTauByIsolationMVArun2v1DBoldDMwLTraw, &b_boostedTauByIsolationMVArun2v1DBoldDMwLTraw);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBnewDMwLT", &boostedTauByTightIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByTightIsolationMVArun2v1DBoldDMwLT", &boostedTauByTightIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBnewDMwLT", &boostedTauByLooseIsolationMVArun2v1DBnewDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("boostedTauByLooseIsolationMVArun2v1DBoldDMwLT", &boostedTauByLooseIsolationMVArun2v1DBoldDMwLT, &b_boostedTauByLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("boostedTauEta", &boostedTauEta, &b_boostedTauEta);
   fChain->SetBranchAddress("boostedTauPhi", &boostedTauPhi, &b_boostedTauPhi);
   fChain->SetBranchAddress("boostedTauPt", &boostedTauPt, &b_boostedTauPt);
   fChain->SetBranchAddress("boostedTauEt", &boostedTauEt, &b_boostedTauEt);
   fChain->SetBranchAddress("boostedTauCharge", &boostedTauCharge, &b_boostedTauCharge);
   fChain->SetBranchAddress("boostedTauP", &boostedTauP, &b_boostedTauP);
   fChain->SetBranchAddress("boostedTauPx", &boostedTauPx, &b_boostedTauPx);
   fChain->SetBranchAddress("boostedTauPy", &boostedTauPy, &b_boostedTauPy);
   fChain->SetBranchAddress("boostedTauPz", &boostedTauPz, &b_boostedTauPz);
   fChain->SetBranchAddress("boostedTauVz", &boostedTauVz, &b_boostedTauVz);
   fChain->SetBranchAddress("boostedTauEnergy", &boostedTauEnergy, &b_boostedTauEnergy);
   fChain->SetBranchAddress("boostedTauMass", &boostedTauMass, &b_boostedTauMass);
   fChain->SetBranchAddress("boostedTauDxy", &boostedTauDxy, &b_boostedTauDxy);
   fChain->SetBranchAddress("boostedTauZImpact", &boostedTauZImpact, &b_boostedTauZImpact);
   fChain->SetBranchAddress("boostedTauDecayMode", &boostedTauDecayMode, &b_boostedTauDecayMode);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronExists", &boostedTauLeadChargedHadronExists, &b_boostedTauLeadChargedHadronExists);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronEta", &boostedTauLeadChargedHadronEta, &b_boostedTauLeadChargedHadronEta);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronPhi", &boostedTauLeadChargedHadronPhi, &b_boostedTauLeadChargedHadronPhi);
   fChain->SetBranchAddress("boostedTauLeadChargedHadronPt", &boostedTauLeadChargedHadronPt, &b_boostedTauLeadChargedHadronPt);
   fChain->SetBranchAddress("boostedTauChargedIsoPtSum", &boostedTauChargedIsoPtSum, &b_boostedTauChargedIsoPtSum);
   fChain->SetBranchAddress("boostedTauNeutralIsoPtSum", &boostedTauNeutralIsoPtSum, &b_boostedTauNeutralIsoPtSum);
   fChain->SetBranchAddress("boostedTauPuCorrPtSum", &boostedTauPuCorrPtSum, &b_boostedTauPuCorrPtSum);
   fChain->SetBranchAddress("boostedTauNumSignalPFChargedHadrCands", &boostedTauNumSignalPFChargedHadrCands, &b_boostedTauNumSignalPFChargedHadrCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFNeutrHadrCands", &boostedTauNumSignalPFNeutrHadrCands, &b_boostedTauNumSignalPFNeutrHadrCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFGammaCands", &boostedTauNumSignalPFGammaCands, &b_boostedTauNumSignalPFGammaCands);
   fChain->SetBranchAddress("boostedTauNumSignalPFCands", &boostedTauNumSignalPFCands, &b_boostedTauNumSignalPFCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFChargedHadrCands", &boostedTauNumIsolationPFChargedHadrCands, &b_boostedTauNumIsolationPFChargedHadrCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFNeutrHadrCands", &boostedTauNumIsolationPFNeutrHadrCands, &b_boostedTauNumIsolationPFNeutrHadrCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFGammaCands", &boostedTauNumIsolationPFGammaCands, &b_boostedTauNumIsolationPFGammaCands);
   fChain->SetBranchAddress("boostedTauNumIsolationPFCands", &boostedTauNumIsolationPFCands, &b_boostedTauNumIsolationPFCands);
   fChain->SetBranchAddress("boostedTaufootprintCorrection", &boostedTaufootprintCorrection, &b_boostedTaufootprintCorrection);
   fChain->SetBranchAddress("boostedTauphotonPtSumOutsideSignalCone", &boostedTauphotonPtSumOutsideSignalCone, &b_boostedTauphotonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("boostedTaudz", &boostedTaudz, &b_boostedTaudz);
   fChain->SetBranchAddress("boostedTaudxy", &boostedTaudxy, &b_boostedTaudxy);
   fChain->SetBranchAddress("boostedTauSignalPFCands", &boostedTauSignalPFCands, &b_boostedTauSignalPFCands);
   fChain->SetBranchAddress("boostedTauSignalPFGammaCands", &boostedTauSignalPFGammaCands, &b_boostedTauSignalPFGammaCands);
   fChain->SetBranchAddress("boostedTauIsolationPFCands", &boostedTauIsolationPFCands, &b_boostedTauIsolationPFCands);
   fChain->SetBranchAddress("boostedTauIsolationPFGammaCands", &boostedTauIsolationPFGammaCands, &b_boostedTauIsolationPFGammaCands);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFinding", &taupfTausDiscriminationByDecayModeFinding, &b_taupfTausDiscriminationByDecayModeFinding);
   fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFindingNewDMs", &taupfTausDiscriminationByDecayModeFindingNewDMs, &b_taupfTausDiscriminationByDecayModeFindingNewDMs);
   fChain->SetBranchAddress("tauByMVA6LooseElectronRejection", &tauByMVA6LooseElectronRejection, &b_tauByMVA6LooseElectronRejection);
   fChain->SetBranchAddress("tauByMVA6TightElectronRejection", &tauByMVA6TightElectronRejection, &b_tauByMVA6TightElectronRejection);
   fChain->SetBranchAddress("tauByLooseMuonRejection3", &tauByLooseMuonRejection3, &b_tauByLooseMuonRejection3);
   fChain->SetBranchAddress("tauByTightMuonRejection3", &tauByTightMuonRejection3, &b_tauByTightMuonRejection3);
   fChain->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits", &tauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("tauByTightCombinedIsolationDeltaBetaCorr3Hits", &tauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_tauByTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("tauCombinedIsolationDeltaBetaCorrRaw3Hits", &tauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_tauCombinedIsolationDeltaBetaCorrRaw3Hits);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1DBnewDMwLTraw", &tauByIsolationMVArun2v1DBnewDMwLTraw, &b_tauByIsolationMVArun2v1DBnewDMwLTraw);
   fChain->SetBranchAddress("tauByIsolationMVArun2v1DBoldDMwLTraw", &tauByIsolationMVArun2v1DBoldDMwLTraw, &b_tauByIsolationMVArun2v1DBoldDMwLTraw);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBnewDMwLT", &tauByTightIsolationMVArun2v1DBnewDMwLT, &b_tauByTightIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBoldDMwLT", &tauByTightIsolationMVArun2v1DBoldDMwLT, &b_tauByTightIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBnewDMwLT", &tauByLooseIsolationMVArun2v1DBnewDMwLT, &b_tauByLooseIsolationMVArun2v1DBnewDMwLT);
   fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBoldDMwLT", &tauByLooseIsolationMVArun2v1DBoldDMwLT, &b_tauByLooseIsolationMVArun2v1DBoldDMwLT);
   fChain->SetBranchAddress("tauEta", &tauEta, &b_tauEta);
   fChain->SetBranchAddress("tauPhi", &tauPhi, &b_tauPhi);
   fChain->SetBranchAddress("tauPt", &tauPt, &b_tauPt);
   fChain->SetBranchAddress("tauEt", &tauEt, &b_tauEt);
   fChain->SetBranchAddress("tauCharge", &tauCharge, &b_tauCharge);
   fChain->SetBranchAddress("tauP", &tauP, &b_tauP);
   fChain->SetBranchAddress("tauPx", &tauPx, &b_tauPx);
   fChain->SetBranchAddress("tauPy", &tauPy, &b_tauPy);
   fChain->SetBranchAddress("tauPz", &tauPz, &b_tauPz);
   fChain->SetBranchAddress("tauVz", &tauVz, &b_tauVz);
   fChain->SetBranchAddress("tauEnergy", &tauEnergy, &b_tauEnergy);
   fChain->SetBranchAddress("tauMass", &tauMass, &b_tauMass);
   fChain->SetBranchAddress("tauDxy", &tauDxy, &b_tauDxy);
   fChain->SetBranchAddress("tauZImpact", &tauZImpact, &b_tauZImpact);
   fChain->SetBranchAddress("tauDecayMode", &tauDecayMode, &b_tauDecayMode);
   fChain->SetBranchAddress("tauLeadChargedHadronExists", &tauLeadChargedHadronExists, &b_tauLeadChargedHadronExists);
   fChain->SetBranchAddress("tauLeadChargedHadronEta", &tauLeadChargedHadronEta, &b_tauLeadChargedHadronEta);
   fChain->SetBranchAddress("tauLeadChargedHadronPhi", &tauLeadChargedHadronPhi, &b_tauLeadChargedHadronPhi);
   fChain->SetBranchAddress("tauLeadChargedHadronPt", &tauLeadChargedHadronPt, &b_tauLeadChargedHadronPt);
   fChain->SetBranchAddress("tauChargedIsoPtSum", &tauChargedIsoPtSum, &b_tauChargedIsoPtSum);
   fChain->SetBranchAddress("tauNeutralIsoPtSum", &tauNeutralIsoPtSum, &b_tauNeutralIsoPtSum);
   fChain->SetBranchAddress("tauPuCorrPtSum", &tauPuCorrPtSum, &b_tauPuCorrPtSum);
   fChain->SetBranchAddress("tauNumSignalPFChargedHadrCands", &tauNumSignalPFChargedHadrCands, &b_tauNumSignalPFChargedHadrCands);
   fChain->SetBranchAddress("tauNumSignalPFNeutrHadrCands", &tauNumSignalPFNeutrHadrCands, &b_tauNumSignalPFNeutrHadrCands);
   fChain->SetBranchAddress("tauNumSignalPFGammaCands", &tauNumSignalPFGammaCands, &b_tauNumSignalPFGammaCands);
   fChain->SetBranchAddress("tauNumSignalPFCands", &tauNumSignalPFCands, &b_tauNumSignalPFCands);
   fChain->SetBranchAddress("tauNumIsolationPFChargedHadrCands", &tauNumIsolationPFChargedHadrCands, &b_tauNumIsolationPFChargedHadrCands);
   fChain->SetBranchAddress("tauNumIsolationPFNeutrHadrCands", &tauNumIsolationPFNeutrHadrCands, &b_tauNumIsolationPFNeutrHadrCands);
   fChain->SetBranchAddress("tauNumIsolationPFGammaCands", &tauNumIsolationPFGammaCands, &b_tauNumIsolationPFGammaCands);
   fChain->SetBranchAddress("tauNumIsolationPFCands", &tauNumIsolationPFCands, &b_tauNumIsolationPFCands);
   fChain->SetBranchAddress("taufootprintCorrection", &taufootprintCorrection, &b_taufootprintCorrection);
   fChain->SetBranchAddress("tauphotonPtSumOutsideSignalCone", &tauphotonPtSumOutsideSignalCone, &b_tauphotonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("taudz", &taudz, &b_taudz);
   fChain->SetBranchAddress("taudxy", &taudxy, &b_taudxy);
   fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
   fChain->SetBranchAddress("numGenTau", &numGenTau, &b_numGenTau);
   fChain->SetBranchAddress("mcPID", &mcPID, &b_mcPID);
   fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
   fChain->SetBranchAddress("mcMass", &mcMass, &b_mcMass);
   fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
   fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
   fChain->SetBranchAddress("mcE", &mcE, &b_mcE);
   fChain->SetBranchAddress("mcEt", &mcEt, &b_mcEt);
   fChain->SetBranchAddress("mcGMomPID", &mcGMomPID, &b_mcGMomPID);
   fChain->SetBranchAddress("mcMomPID", &mcMomPID, &b_mcMomPID);
   fChain->SetBranchAddress("mcMomPt", &mcMomPt, &b_mcMomPt);
   fChain->SetBranchAddress("mcMomMass", &mcMomMass, &b_mcMomMass);
   fChain->SetBranchAddress("mcMomEta", &mcMomEta, &b_mcMomEta);
   fChain->SetBranchAddress("mcMomPhi", &mcMomPhi, &b_mcMomPhi);
   fChain->SetBranchAddress("mcStatusFlag", &mcStatusFlag, &b_mcStatusFlag);
   fChain->SetBranchAddress("mcParentage", &mcParentage, &b_mcParentage);
   fChain->SetBranchAddress("mcStatus", &mcStatus, &b_mcStatus);
   fChain->SetBranchAddress("taudaugPt", &taudaugPt, &b_taudaugPt);
   fChain->SetBranchAddress("taudaugEta", &taudaugEta, &b_taudaugEta);
   fChain->SetBranchAddress("taudaugPhi", &taudaugPhi, &b_taudaugPhi);
   fChain->SetBranchAddress("taudaugMass", &taudaugMass, &b_taudaugMass);
   Notify();
}

Bool_t SkimerBoost::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SkimerBoost::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SkimerBoost::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SkimerBoost_cxx
