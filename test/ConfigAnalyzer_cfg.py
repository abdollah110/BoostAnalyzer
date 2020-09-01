import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
#                                '/store/mc/RunIISummer16MiniAODv3/ZprimeToZhToZhadhtata_narrow_M-2000_13TeV-madgraph/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/20000/E8530115-67F1-E911-A75F-0242AC130002.root'
            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/BoostTau/BoostAnalyzer/test/ZprimeToZhToZhadhtata_narrow_M-2000_94X.root'
#            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/miniAOD-prod_PAT.root'
                )
                            )

process.demo = cms.EDAnalyzer('BoostAnalyzer',
                             boostedTauSrc             = cms.InputTag("slimmedTausBoosted"),
                             tauSrc                    = cms.InputTag("slimmedTaus"),
                             genParticleSrc            = cms.InputTag("prunedGenParticles"),
                             tauSrcNew                 = cms.InputTag("slimmedTausNewID"),
                             boostedTauNoOverLapSrc    = cms.InputTag("slimmedTausBoostedNoOverLap"),
                             boostedTauNoOverLapIDUpdatedSrc    = cms.InputTag("slimmedTausBoostedNoOverLapIDUpdated"),
                             
                              )
                              
from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import *

########################################################################################
# A new boostedTau collection is made here and the overlap is removed
########################################################################################
embedBoostedTau = cms.EDProducer("PATBoostedTauEmbedder",
   src = cms.InputTag('slimmedTausBoosted'),
   pfcands = cms.InputTag('packedPFCandidates'),
   removeOverLap = cms.bool(True),
   )
setattr(process, "slimmedTausBoostedNoOverLap", embedBoostedTau)


########################################################################################
# A new boostedTau collection is made here and the Id is updated
########################################################################################
process.rerunDiscriminationByIsolationMVArun2v1raw = patDiscriminationByIsolationMVArun2v1raw.clone(
   PATTauProducer = cms.InputTag('slimmedTausBoostedNoOverLap'),
   Prediscriminants = noPrediscriminants,
   loadMVAfromDB = cms.bool(True),
   mvaName = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1"), # name of the training you want to use
   mvaOpt = cms.string("DBoldDMwLT"), # option you want to use for your training (i.e., which variables are used to compute the BDT score)
   requireDecayMode = cms.bool(True),
   verbosity = cms.int32(0)
)

process.rerunDiscriminationByIsolationMVArun2v1VLoose = patDiscriminationByIsolationMVArun2v1VLoose.clone(
   PATTauProducer = cms.InputTag('slimmedTausBoostedNoOverLap'),
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
embedBoostedTauID = cms.EDProducer("PATBoostedTauIDEmbedder",
   src = cms.InputTag('slimmedTausBoostedNoOverLap'),
   tauIDSources = cms.PSet(
      MybyIsolationMVArun2v1DBoldDMwLTrawNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
      MybyVLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLoose'),
      MybyLooseIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Loose'),
      MybyMediumIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Medium'),
      MybyTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1Tight'),
      MybyVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTight'),
      MybyVVTightIsolationMVArun2v1DBoldDMwLTNew = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTight'),
      ),
   )
setattr(process, "slimmedTausBoostedNoOverLapIDUpdated", embedBoostedTauID)


########################################################################################
# A new Tau collection is made here
########################################################################################
updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = [ "2017v2", "dR0p32017v2", "newDM2017v2", #classic MVAIso tau-Ids
                               "deepTau2017v1", #deepTau Tau-Ids
                               "DPFTau_2016_v0", #D[eep]PF[low] Tau-Id
                               ])
tauIdEmbedder.runTauID()


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
     getattr(process, "slimmedTausBoostedNoOverLap") *
     process.rerunMvaIsolation2SeqRun2 *
     getattr(process, "slimmedTausBoostedNoOverLapIDUpdated") *
     process.rerunMvaIsolationSequence *
     getattr(process,updatedTauName) *
     process.demo
)

