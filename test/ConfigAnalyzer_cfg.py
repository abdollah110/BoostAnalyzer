import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
##process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
#process.load('Configuration.Geometry.GeometryIdeal_cff')
##process.load('Configuration.Geometry.GeometryRecoDB_cff')
##process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
##process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

## Geometry and Detector Conditions (needed for a few tau reco steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.load("Configuration.StandardSequences.MagneticField_cff")

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')


process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#                                '/store/mc/RunIISummer16MiniAODv3/ZprimeToZhToZhadhtata_narrow_M-2000_13TeV-madgraph/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/20000/E8530115-67F1-E911-A75F-0242AC130002.root'
#            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/BoostTau/BoostAnalyzer/test/ZprimeToZhToZhadhtata_narrow_M-2000_94X.root'
#            'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_16/src/miniAOD-prod_PAT.root'

#    'file:/uscms_data/d3/abdollah/Analysis/ValidationBoostedTau/CMSSW_9_4_15/src/BoostTau/BoostAnalyzer/test/ZprimeToZhToZhadhtata_narrow_M-2000_94X_MiniAODSIM_Orig.root'
                    
                    'file:miniAOD-prod_PAT_1.root',
                    'file:miniAOD-prod_PAT_2.root',
                    'file:miniAOD-prod_PAT_3.root',
                    'file:miniAOD-prod_PAT_4.root',
                    'file:miniAOD-prod_PAT_5.root'
                        )
                )

                              
from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import *
#anti-electron
from RecoTauTag.RecoTau.PATTauDiscriminationAgainstElectronMVA6_cfi import *

from RecoTauTag.Configuration.boostedHPSPFTaus_cff import ca8PFJetsCHSprunedForBoostedTaus
process.ca8PFJetsCHSprunedForBoostedTausPAT = ca8PFJetsCHSprunedForBoostedTaus.clone(
                        src=cms.InputTag("packedPFCandidates"),
                        jetCollInstanceName = cms.string('subJetsForSeedingBoostedTausPAT')
                )


########################################################################################
# A new boostedTau collection is made here and the overlap is removed
########################################################################################
cleanedBoostedTau = cms.EDProducer("PATBoostedTauCleaner",
   src = cms.InputTag('slimmedTausBoosted'),
   pfcands = cms.InputTag('packedPFCandidates'),
   vtxLabel= cms.InputTag('offlineSlimmedPrimaryVertices'),
#   removeOverLap = cms.bool(True),
   removeOverLap = cms.bool(False),
   ak8JetSrc = cms.InputTag('slimmedJetsAK8'),
   ca8JetSrc = cms.InputTag('ca8PFJetsCHSprunedForBoostedTausPAT','subJetsForSeedingBoostedTausPAT')
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

#
#process.rerunDiscriminationAgainstElectronMVA6 = patTauDiscriminationAgainstElectronMVA6.clone(
#    PATTauProducer = cms.InputTag('cleanedSlimmedTausBoosted'),
#    Prediscriminants = noPrediscriminants,
#    #Prediscriminants = requireLeadTrack,
#    loadMVAfromDB = cms.bool(True),
#    returnMVA = cms.bool(True),
#    method = cms.string("BDTG"),
#    mvaName_NoEleMatch_woGwoGSF_BL = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL"),
#    mvaName_NoEleMatch_wGwoGSF_BL = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL"),
#    mvaName_woGwGSF_BL = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL"),
#    mvaName_wGwGSF_BL = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL"),
#    mvaName_NoEleMatch_woGwoGSF_EC = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC"),
#    mvaName_NoEleMatch_wGwoGSF_EC = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC"),
#    mvaName_woGwGSF_EC = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC"),
#    mvaName_wGwGSF_EC = cms.string("RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC"),
#    minMVANoEleMatchWOgWOgsfBL = cms.double(0.0),
#    minMVANoEleMatchWgWOgsfBL  = cms.double(0.0),
#    minMVAWOgWgsfBL            = cms.double(0.0),
#    minMVAWgWgsfBL             = cms.double(0.0),
#    minMVANoEleMatchWOgWOgsfEC = cms.double(0.0),
#    minMVANoEleMatchWgWOgsfEC  = cms.double(0.0),
#    minMVAWOgWgsfEC            = cms.double(0.0),
#    minMVAWgWgsfEC             = cms.double(0.0),
#    srcElectrons = cms.InputTag('slimmedElectrons'),
#    usePhiAtEcalEntranceExtrapolation = cms.bool(True)
#)


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
      byIsolationMVArun2v1DBoldDMwLTrawNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1rawNoOverLap'),
      byVLooseIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VLooseNoOverLap'),
      byLooseIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1LooseNoOverLap'),
      byMediumIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1MediumNoOverLap'),
      byTightIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1TightNoOverLap'),
      byVTightIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VTightNoOverLap'),
      byVVTightIsolationMVArun2v1DBoldDMwLTNoOverLap = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1VVTightNoOverLap'),
#      againstElectronMVA6RawNew = cms.InputTag('rerunDiscriminationAgainstElectronMVA6')

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
#slimmedTausNewID="slimmedTaus" # tmp




########################################################################################
# Anti electron
########################################################################################
updatedTauName = "slimmedBoostedTausNewID" #name of pat::Tau collection with new tau-Ids
#import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
import BoostTau.BoostAnalyzer.runCleanedBoostedTauIdMVA as tauIdConfig
boostedTauIdEmbedder = tauIdConfig.BoostedTauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
#                    PATTauProducer = cms.InputTag('cleanedSlimmedTausBoosted'),
#                    srcChargedIsoPtSum = cms.string('chargedIsoPtSumNoOverLap'),
#                    srcNeutralIsoPtSum = cms.string('neutralIsoPtSumNoOverLap'),
                    PATTauProducer = cms.InputTag('slimmedTausBoosted'),
                    srcChargedIsoPtSum = cms.string('chargedIsoPtSum'),
                    srcNeutralIsoPtSum = cms.string('neutralIsoPtSum'),

                    toKeep = [
#                                "2017v2", "dR0p32017v2", "newDM2017v2", #classic MVAIso tau-Ids
#                               "deepTau2017v1", #deepTau Tau-Ids
#                               "DPFTau_2016_v0", #D[eep]PF[low] Tau-Id
                                "2017v2","deepBoostedTau2017v1","againstEle2018"
                               ])
boostedTauIdEmbedder.runTauID()


########################################################################################
# Run ntuple Maker
########################################################################################

process.demo = cms.EDAnalyzer('BoostAnalyzer',
    boostedTauSrc             = cms.InputTag("slimmedTausBoosted"),
    tauSrc                    = cms.InputTag("slimmedTaus"),
    genParticleSrc            = cms.InputTag("prunedGenParticles"),
    tauSrcNew                 = cms.InputTag("slimmedTaus"),
    cleanedBoostedTauSrc    = cms.InputTag("slimmedBoostedTausNewID"),
    boostedTauIDNoOverLapSrc    = cms.InputTag("slimmedBoostedTausIDNoOverLap"),
#    boostedTauIDNoOverLapSrc    = cms.InputTag("slimmedBoostedTausNewIDCleaned"),
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
    process.ca8PFJetsCHSprunedForBoostedTausPAT *
     getattr(process, "cleanedSlimmedTausBoosted") *
     process.rerunMvaIsolationSequence *
     getattr(process,updatedTauName) *
#     process.rerunDiscriminationAgainstElectronMVA6 *
     process.rerunMvaIsolation2SeqRun2 *
     getattr(process, "slimmedBoostedTausIDNoOverLap") *
#     process.rerunMvaIsolationSequence *
     
     process.demo
)

