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
                              
from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import *

process.rerunDiscriminationByIsolationMVArun2v1raw = patDiscriminationByIsolationMVArun2v1raw.clone(
   PATTauProducer = cms.InputTag('slimmedTaus'),
   Prediscriminants = noPrediscriminants,
   loadMVAfromDB = cms.bool(True),
   mvaName = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1"), # name of the training you want to use
   mvaOpt = cms.string("DBoldDMwLT"), # option you want to use for your training (i.e., which variables are used to compute the BDT score)
   requireDecayMode = cms.bool(True),
   verbosity = cms.int32(0)
)

process.rerunDiscriminationByIsolationMVArun2v1VLoose = patDiscriminationByIsolationMVArun2v1VLoose.clone(
   PATTauProducer = cms.InputTag('slimmedTaus'),
   Prediscriminants = noPrediscriminants,
   toMultiplex = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
   key = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw:category'),
   loadMVAfromDB = cms.bool(True),
   mvaOutput_normalization = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_mvaOutput_normalization"), # normalization fo the training you want to use
   mapping = cms.VPSet(
      cms.PSet(
         category = cms.uint32(0),
         cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff90"), # this is the name of the working point you want to use
         variable = cms.string("pt"),
      )
   )
)

# here we produce all the other working points for the training
process.rerunDiscriminationByIsolationMVArun2v1Loose = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
process.rerunDiscriminationByIsolationMVArun2v1Loose.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff80")
process.rerunDiscriminationByIsolationMVArun2v1Medium = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
process.rerunDiscriminationByIsolationMVArun2v1Medium.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff70")
process.rerunDiscriminationByIsolationMVArun2v1Tight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
process.rerunDiscriminationByIsolationMVArun2v1Tight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff60")
process.rerunDiscriminationByIsolationMVArun2v1VTight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
process.rerunDiscriminationByIsolationMVArun2v1VTight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff50")
process.rerunDiscriminationByIsolationMVArun2v1VVTight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
process.rerunDiscriminationByIsolationMVArun2v1VVTight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff40")

# this sequence has to be included in your cms.Path() before your analyzer which accesses the new variables is called.
process.rerunMvaIsolation2SeqRun2 = cms.Sequence(
   process.rerunDiscriminationByIsolationMVArun2v1raw
   *process.rerunDiscriminationByIsolationMVArun2v1VLoose
   *process.rerunDiscriminationByIsolationMVArun2v1Loose
   *process.rerunDiscriminationByIsolationMVArun2v1Medium
   *process.rerunDiscriminationByIsolationMVArun2v1Tight
   *process.rerunDiscriminationByIsolationMVArun2v1VTight
   *process.rerunDiscriminationByIsolationMVArun2v1VVTight
)


# embed new id's into new tau collection
embedID = cms.EDProducer("PATTauIDEmbedder",
   src = cms.InputTag('slimmedTaus'),
   tauIDSources = cms.PSet(
      MybyIsolationMVArun2v1DBoldDMwLTrawNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
      MybyVLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLoose'),
      MybyLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Loose'),
      MybyMediumIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Medium'),
      MybyTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Tight'),
      MybyVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTight'),
      MybyVVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTight'),
#      . . . (other discriminators like anti-electron),
      ),
   )
setattr(process, "NewTauIDsEmbedded", embedID)






#
#
#
#
#from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
#process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
#from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import *
#from RecoTauTag.RecoTau.PATTauDiscriminationAgainstElectronMVA6_cfi import *
#
#process.rerunDiscriminationByIsolationMVArun2v1raw = patDiscriminationByIsolationMVArun2v1raw.clone(
#  PATTauProducer = cms.InputTag('slimmedTaus'),
#  Prediscriminants = noPrediscriminants,
#  loadMVAfromDB = cms.bool(True),
#  # run with old MVA training
#  #mvaName = cms.string("RecoTauTag_tauIdMVADBoldDMwLTv1"),
#  # run with new MVA training
#  mvaName = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1"),
#  mvaOpt = cms.string("DBoldDMwLT"),
#  requireDecayMode = cms.bool(True),
#  verbosity = cms.int32(0)
#)
#
## embed new id's into tau
#embedID = cms.EDProducer("PATTauIDEmbedder",
#   src = cms.InputTag('slimmedTaus'),
#   tauIDSources = cms.PSet(
#      byIsolationMVArun2v1DBoldDMwLTrawNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
##      byVLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLoose'),
##      byLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Loose'),
##      byMediumIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Medium'),
##      byTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Tight'),
##      byVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTight'),
##      byVVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTight'),
##      againstElectronMVA6RawNew = cms.InputTag('rerunDiscriminationAgainstElectronMVA6')
#   ),
#)
#setattr(process, "newTauIDsEmbedded", embedID)
#
##from BoostTau.BoostAnalyzer.runTauIdMVA import *
##na = TauIDEmbedder(process, cms, # pass tour process object
##    debug=True,
##    toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
##)
##na.runTauID()



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
#     process.rerunDiscriminationByIsolationMVArun2v1raw *
#     process.newTauIDsEmbedded *#     process.boostedTauSeeds *
    process.rerunMvaIsolation2SeqRun2 *
     getattr(process, "NewTauIDsEmbedded") *
#    process.rerunMvaIsolationSequence
#    * process.NewTauIDsEmbedded # *getattr(process, "NewTauIDsEmbedded")
     process.rerunMvaIsolationSequence *
     getattr(process,updatedTauName)
    * process.demo
)

