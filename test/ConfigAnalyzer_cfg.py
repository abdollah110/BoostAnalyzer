import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#                                '/store/mc/RunIISummer16MiniAODv3/ZprimeToZhToZhadhtata_narrow_M-2000_13TeV-madgraph/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/20000/E8530115-67F1-E911-A75F-0242AC130002.root'
            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/BoostTau/BoostAnalyzer/test/ZprimeToZhToZhadhtata_narrow_M-2000_94X.root'
#            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/miniAOD-prod_PAT.root'
                        )
                )

                              
from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import *

########################################################################################
# A new boostedTau collection is made here and the overlap is removed
########################################################################################
cleanedBoostedTau = cms.EDProducer("PATBoostedTauCleaner",
   src = cms.InputTag('slimmedTausBoosted'),
   pfcands = cms.InputTag('packedPFCandidates'),
   vtxLabel= cms.InputTag('offlineSlimmedPrimaryVertices'),
   removeOverLap = cms.bool(True),
   ak8JetSrc = cms.InputTag('slimmedJetsAK8')
   )
setattr(process, "cleanedSlimmedTausBoosted", cleanedBoostedTau)

########################################################################################
# A new boostedTau tau Id is updated
########################################################################################
process.rerunDiscriminationByIsolationMVArun2v1rawNoOverLap = patDiscriminationByIsolationMVArun2v1raw.clone(
   PATTauProducer = cms.InputTag('cleanedSlimmedTausBoosted'),
   Prediscriminants = noPrediscriminants,
   loadMVAfromDB = cms.bool(True),
   mvaName = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2"), # name of the training you want to use
   mvaOpt = cms.string("DBoldDMwLTwGJ"), # option you want to use for your training (i.e., which variables are used to compute the BDT score)DBoldDMwLTwGJ
   requireDecayMode = cms.bool(True),
   verbosity = cms.int32(0),
   srcChargedIsoPtSum = cms.string('chargedIsoPtSumNoOverLap'),
   srcNeutralIsoPtSum = cms.string('neutralIsoPtSumNoOverLap'),
)

process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap = patDiscriminationByIsolationMVArun2v1VLoose.clone(
   PATTauProducer = cms.InputTag('cleanedSlimmedTausBoosted'),
   Prediscriminants = noPrediscriminants,
   toMultiplex = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1rawNoOverLap'),
   key = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1rawNoOverLap:category'),
   loadMVAfromDB = cms.bool(True),
#   mvaOutput_normalization = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_mvaOutput_normalization"), # normalization fo the
   mvaOutput_normalization = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_mvaOutput_normalization"), # normalization fo the training you want to use
   mapping = cms.VPSet(
      cms.PSet(
         category = cms.uint32(0),
         cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff90"), # this is the name of the working point you want to use
         variable = cms.string("pt"),
      )
   )
)

# here we produce all the other working points for the training
process.rerunDiscriminationByIsolationMVArun2v1LooseNoOverLap = process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap.clone()
process.rerunDiscriminationByIsolationMVArun2v1LooseNoOverLap.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff80")
process.rerunDiscriminationByIsolationMVArun2v1MediumNoOverLap = process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap.clone()
process.rerunDiscriminationByIsolationMVArun2v1MediumNoOverLap.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff70")
process.rerunDiscriminationByIsolationMVArun2v1TightNoOverLap = process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap.clone()
process.rerunDiscriminationByIsolationMVArun2v1TightNoOverLap.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff60")
process.rerunDiscriminationByIsolationMVArun2v1VTightNoOverLap = process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap.clone()
process.rerunDiscriminationByIsolationMVArun2v1VTightNoOverLap.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff50")
process.rerunDiscriminationByIsolationMVArun2v1VVTightNoOverLap = process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap.clone()
process.rerunDiscriminationByIsolationMVArun2v1VVTightNoOverLap.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff40")

# this sequence has to be included in your cms.Path() before your analyzer which accesses the new variables is called.
process.rerunMvaIsolation2SeqRun2 = cms.Sequence(
   process.rerunDiscriminationByIsolationMVArun2v1rawNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1LooseNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1MediumNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1TightNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1VTightNoOverLap
   *process.rerunDiscriminationByIsolationMVArun2v1VVTightNoOverLap
)

# embed new id's into new tau collection
embedBoostedTauIDNoOverLap = cms.EDProducer("PATBoostedTauIDEmbedder",
   src = cms.InputTag('cleanedSlimmedTausBoosted'),
   tauIDSources = cms.PSet(
      MybyIsolationMVArun2v1DBoldDMwLTrawNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1rawNoOverLap'),
      MybyVLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap'),
      MybyLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1LooseNoOverLap'),
      MybyMediumIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1MediumNoOverLap'),
      MybyTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1TightNoOverLap'),
      MybyVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTightNoOverLap'),
      MybyVVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTightNoOverLap'),
      ),
   )
setattr(process, "slimmedBoostedTausIDNoOverLap", embedBoostedTauIDNoOverLap)


########################################################################################
# A new Tau collection is made here
########################################################################################
#updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
#import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
#tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
#                    updatedTauName = updatedTauName,
#                    toKeep = [ "2017v2", "dR0p32017v2", "newDM2017v2", #classic MVAIso tau-Ids
#                               "deepTau2017v1", #deepTau Tau-Ids
#                               "DPFTau_2016_v0", #D[eep]PF[low] Tau-Id
#                               ])
#tauIdEmbedder.runTauID()
slimmedTausNewID="slimmedTaus" # tmp

########################################################################################
# Run ntuple Maker
########################################################################################

process.demo = cms.EDAnalyzer('BoostAnalyzer',
    boostedTauSrc             = cms.InputTag("slimmedTausBoosted"),
    tauSrc                    = cms.InputTag("slimmedTaus"),
    genParticleSrc            = cms.InputTag("prunedGenParticles"),
    tauSrcNew                 = cms.InputTag("slimmedTaus"),
    cleanedBoostedTauSrc    = cms.InputTag("cleanedSlimmedTausBoosted"),
    boostedTauIDNoOverLapSrc    = cms.InputTag("slimmedBoostedTausIDNoOverLap"),
    ak8JetSrc                 = cms.InputTag("slimmedJetsAK8"),
 )

########################################################################################
# Output name
########################################################################################
process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('ntuple.root')
                                   )
########################################################################################
# path
########################################################################################
#print process.dumpPython()
process.p = cms.Path(
     getattr(process, "cleanedSlimmedTausBoosted") *
     process.rerunMvaIsolation2SeqRun2 *
     getattr(process, "slimmedBoostedTausIDNoOverLap") *
#     process.rerunMvaIsolationSequence *
#     getattr(process,updatedTauName) *
     process.demo
)

