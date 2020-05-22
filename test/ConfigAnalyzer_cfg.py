import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
            'file:/uscms/home/abdollah/tau/RunIIAutumn18MiniAOD.root'
                )
                            )

process.demo = cms.EDAnalyzer('BoostAnalyzer',
                             boostedTauSrc    = cms.InputTag("slimmedTausBoosted"),
                              )

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histodemo.root')
                                   )
process.p = cms.Path(process.demo)

