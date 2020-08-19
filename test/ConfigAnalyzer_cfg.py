import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
#            'file:ZprimeToZhToZhadhtata_narrow_M-2000_94X.root'
            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/miniAOD-prod_PAT.root'
                )
                            )

process.demo = cms.EDAnalyzer('BoostAnalyzer',
                             boostedTauSrc    = cms.InputTag("slimmedTausBoosted"),
                             tauSrc                    = cms.InputTag("slimmedTaus"),
                             genParticleSrc       = cms.InputTag("prunedGenParticles"),
#                             tauSrcNew                    = cms.InputTag("NewTauIDsEmbedded"),
                             tauSrcNew                    = cms.InputTag("slimmedTausNewID"),
                              )
                              
process.newTau= cms.EDProducer('PATTauIDEmbedder',
            src=cms.InputTag("slimmedTaus"),
            tauIDSources=ParameterSet("tauIDSources")
            )

# embed new id's into tau
embedID = cms.EDProducer("PATTauIDEmbedder",
   src = cms.InputTag('slimmedTaus'),
   tauIDSources = cms.PSet(
      byIsolationMVArun2v1DBoldDMwLTrawNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
      byVLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLoose'),
      byLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Loose'),
      byMediumIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Medium'),
      byTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Tight'),
      byVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTight'),
      byVVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTight'),
      againstElectronMVA6RawNew = cms.InputTag('rerunDiscriminationAgainstElectronMVA6')
   ),
)
setattr(process, "newTauIDsEmbeddedBBB", embedID)

#from BoostTau.BoostAnalyzer.runTauIdMVA import *
#na = TauIDEmbedder(process, cms, # pass tour process object
#    debug=True,
#    toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
#)
#na.runTauID()



process.load("RecoTauTag.Configuration.boostedHPSPFTaus_cff")
process.ca8PFJetsCHSprunedForBoostedTaus.jetPtMin = cms.double(100.0)
#process.ca8PFJetsCHSprunedForBoostedTaus.jetCollInstanceName=cms.string("MyNewJetCollection_subJetsForSeedingBoostedTaus")
process.boostedTauSeeds.verbosity =1


updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = [ "2017v2", "dR0p32017v2", "newDM2017v2", #classic MVAIso tau-Ids
                               "deepTau2017v1", #deepTau Tau-Ids
                               "DPFTau_2016_v0", #D[eep]PF[low] Tau-Id
                               ])
tauIdEmbedder.runTauID()


process.load("PhysicsTools.PatAlgos.patSequences_cff")


process.load("RecoTauTag.Configuration.updateHPSPFTaus_cff")

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histodemo_new.root')
                                   )
#print process.dumpPython()
process.p = cms.Path(
#    updateHPSPFTaus
#     process.patDefaultSequence *
     process.newTauIDsEmbedded *#     process.boostedTauSeeds *
#    process.rerunMvaIsolationSequence
#    * process.NewTauIDsEmbedded # *getattr(process, "NewTauIDsEmbedded")
     process.rerunMvaIsolationSequence *
     getattr(process,updatedTauName)
    * process.demo
)

