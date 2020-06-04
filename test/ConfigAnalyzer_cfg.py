import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
            'file:ZprimeToZhToZhadhtata_narrow_M-2000_94X.root'
                )
                            )

process.demo = cms.EDAnalyzer('BoostAnalyzer',
                             boostedTauSrc    = cms.InputTag("slimmedTausBoosted"),
                             tauSrc                    = cms.InputTag("slimmedTaus"),
                             genParticleSrc       = cms.InputTag("prunedGenParticles"),
                             tauSrcNew                    = cms.InputTag("NewTauIDsEmbedded"),
                              )

from BoostTau.BoostAnalyzer.runTauIdMVA import *
na = TauIDEmbedder(process, cms, # pass tour process object
    debug=True,
    toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
)
na.runTauID()



process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histodemo.root')
                                   )
process.p = cms.Path(
    process.rerunMvaIsolationSequence
    * process.NewTauIDsEmbedded # *getattr(process, "NewTauIDsEmbedded")
    * process.demo
)

