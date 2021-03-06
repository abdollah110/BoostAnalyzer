from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import patDiscriminationByIsolationMVArun2v1raw, patDiscriminationByIsolationMVArun2v1VLoose
import os
import re

class BoostedTauIDEmbedder(object):
    """class to rerun the tau seq and acces trainings from the database"""

    def __init__(self, process, cms, debug = False,
        updatedTauName = "slimmedTausBoostedNewID",
        PATTauProducer = "cleanedSlimmedTausBoosted",
        srcChargedIsoPtSum = "chargedIsoPtSumNoOverLap",
        srcNeutralIsoPtSum = "neutralIsoPtSumNoOverLap",
        toKeep = ["2016v1","2017v2","deepTau2017v1","DPFTau_2016_v0","againstEle2018"],
        tauIdDiscrMVA_trainings_run2_2017 = {
            'tauIdMVAIsoDBoldDMwLT2017' : "tauIdMVAIsoDBoldDMwLT2017",
        },
        tauIdDiscrMVA_WPs_run2_2017 = {
            'tauIdMVAIsoDBoldDMwLT2017' : {
                'Eff95' : "DBoldDMwLTEff95",
                'Eff90' : "DBoldDMwLTEff90",
                'Eff80' : "DBoldDMwLTEff80",
                'Eff70' : "DBoldDMwLTEff70",
                'Eff60' : "DBoldDMwLTEff60",
                'Eff50' : "DBoldDMwLTEff50",
                'Eff40' : "DBoldDMwLTEff40"
            }
        },
        tauIdDiscrMVA_2017_version = "v1",
        conditionDB = "" # preparational DB: 'frontier://FrontierPrep/CMS_CONDITIONS'
        ):
        super(BoostedTauIDEmbedder, self).__init__()
        self.process = process
        self.cms = cms
        self.debug = debug
        self.updatedTauName = updatedTauName
        self.process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
        if len(conditionDB) != 0:
            self.process.CondDBTauConnection.connect = cms.string(conditionDB)
            self.process.loadRecoTauTagMVAsFromPrepDB.connect = cms.string(conditionDB)
            # if debug:
            # 	print self.process.CondDBTauConnection.connect
            # 	print dir(self.process.loadRecoTauTagMVAsFromPrepDB)
            # 	print self.process.loadRecoTauTagMVAsFromPrepDB.parameterNames_

        self.tauIdDiscrMVA_trainings_run2_2017 = tauIdDiscrMVA_trainings_run2_2017
        self.tauIdDiscrMVA_WPs_run2_2017 = tauIdDiscrMVA_WPs_run2_2017
        self.tauIdDiscrMVA_2017_version = tauIdDiscrMVA_2017_version
        self.toKeep = toKeep
        self.PATTauProducer = PATTauProducer
        self.srcChargedIsoPtSum=srcChargedIsoPtSum
        self.srcNeutralIsoPtSum=srcNeutralIsoPtSum


    @staticmethod
    def get_cmssw_version(debug = False):
        """returns 'CMSSW_X_Y_Z'"""
        cmssw_version = os.environ["CMSSW_VERSION"]
        if debug: print "get_cmssw_version:", cmssw_version
        return cmssw_version

    @classmethod
    def get_cmssw_version_number(klass, debug = False):
        """returns '(release, subversion, patch)' (without 'CMSSW_')"""
        v = klass.get_cmssw_version().split("CMSSW_")[1].split("_")[0:3]
        if debug: print "get_cmssw_version_number:", v
        if v[2] == "X":
            patch = -1
        else:
            patch = int(v[2])
        return int(v[0]), int(v[1]), patch

    @staticmethod
    def versionToInt(release=9, subversion=4, patch=0, debug = False):
        version = release * 10000 + subversion * 100 + patch + 1 # shifted by one to account for pre-releases.
        if debug: print "versionToInt:", version
        return version


    @classmethod
    def is_above_cmssw_version(klass, release=9, subversion=4, patch=0, debug = False):
        split_cmssw_version = klass.get_cmssw_version_number()
        if klass.versionToInt(release, subversion, patch) > klass.versionToInt(split_cmssw_version[0], split_cmssw_version[1], split_cmssw_version[2]):
            if debug: print "is_above_cmssw_version:", False
            return False
        else:
            if debug: print "is_above_cmssw_version:", True
            return True

    def loadMVA_WPs_run2_2017(self):
        if self.debug: print "loadMVA_WPs_run2_2017: performed"
        global cms
        for training, gbrForestName in self.tauIdDiscrMVA_trainings_run2_2017.items():

            self.process.loadRecoTauTagMVAsFromPrepDB.toGet.append(
                self.cms.PSet(
                    record = self.cms.string('GBRWrapperRcd'),
                    tag = self.cms.string("RecoTauTag_%s%s" % (gbrForestName, self.tauIdDiscrMVA_2017_version)),
                    label = self.cms.untracked.string("RecoTauTag_%s%s" % (gbrForestName, self.tauIdDiscrMVA_2017_version))
                )
            )

            for WP in self.tauIdDiscrMVA_WPs_run2_2017[training].keys():
                self.process.loadRecoTauTagMVAsFromPrepDB.toGet.append(
                    self.cms.PSet(
                        record = self.cms.string('PhysicsTGraphPayloadRcd'),
                        tag = self.cms.string("RecoTauTag_%s%s_WP%s" % (gbrForestName, self.tauIdDiscrMVA_2017_version, WP)),
                        label = self.cms.untracked.string("RecoTauTag_%s%s_WP%s" % (gbrForestName, self.tauIdDiscrMVA_2017_version, WP))
                    )
                )

            self.process.loadRecoTauTagMVAsFromPrepDB.toGet.append(
                self.cms.PSet(
                    record = self.cms.string('PhysicsTFormulaPayloadRcd'),
                    tag = self.cms.string("RecoTauTag_%s%s_mvaOutput_normalization" % (gbrForestName, self.tauIdDiscrMVA_2017_version)),
                    label = self.cms.untracked.string("RecoTauTag_%s%s_mvaOutput_normalization" % (gbrForestName, self.tauIdDiscrMVA_2017_version))
                )
            )

    def runTauID(self):
        self.process.rerunMvaIsolationBoostTask = self.cms.Task()
        self.process.rerunMvaIsolationBoostSequence = self.cms.Sequence()
        tauIDSources = self.cms.PSet()

        #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if "2017v2" in self.toKeep:
            self.tauIdDiscrMVA_2017_version = "v2"
            self.tauIdDiscrMVA_trainings_run2_2017 = {
                'tauIdMVAIsoDBoldDMwLT2017' : "tauIdMVAIsoDBoldDMwLT2017",
            }
            self.tauIdDiscrMVA_WPs_run2_2017 = {
                'tauIdMVAIsoDBoldDMwLT2017' : {
                    'Eff95' : "DBoldDMwLTEff95",
                    'Eff90' : "DBoldDMwLTEff90",
                    'Eff80' : "DBoldDMwLTEff80",
                    'Eff70' : "DBoldDMwLTEff70",
                    'Eff60' : "DBoldDMwLTEff60",
                    'Eff50' : "DBoldDMwLTEff50",
                    'Eff40' : "DBoldDMwLTEff40"
                }
            }

            if not self.is_above_cmssw_version(9, 4, 5, self.debug):
                if self.debug: print "runTauID: not is_above_cmssw_version(9, 4, 5). Will update the list of available in DB samples to access 2017v2"
                self.loadMVA_WPs_run2_2017()

            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2raw = patDiscriminationByIsolationMVArun2v1raw.clone(
#                PATTauProducer = self.PATTauProducer,
                PATTauProducer = self.PATTauProducer,
                srcChargedIsoPtSum = self.srcChargedIsoPtSum,
                srcNeutralIsoPtSum = self.srcNeutralIsoPtSum,
                Prediscriminants = noPrediscriminants,
                loadMVAfromDB = self.cms.bool(True),
                mvaName = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2"),#RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1 writeTauIdDiscrMVAs
                mvaOpt = self.cms.string("DBoldDMwLTwGJ"),
                requireDecayMode = self.cms.bool(True),
                verbosity = self.cms.int32(0)
            )

            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose = patDiscriminationByIsolationMVArun2v1VLoose.clone(
                PATTauProducer = self.PATTauProducer,
                srcChargedIsoPtSum = self.srcChargedIsoPtSum,
                srcNeutralIsoPtSum = self.srcNeutralIsoPtSum,
                Prediscriminants = noPrediscriminants,
                toMultiplex = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2raw'),
                key = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2raw:category'),#?
                loadMVAfromDB = self.cms.bool(True),
                mvaOutput_normalization = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_mvaOutput_normalization"), #writeTauIdDiscrMVAoutputNormalizations
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff90"), #writeTauIdDiscrWPs
                        variable = self.cms.string("pt"),
                    )
                ),
                verbosity = self.cms.int32(0)
            )

            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVLoose = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVLoose.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff95")
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Loose = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Loose.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff80")
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Medium = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Medium.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff70")
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Tight = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Tight.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff60")
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VTight = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VTight.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff50")
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVTight = self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose.clone()
            self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVTight.mapping[0].cut = self.cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff40")

            self.rerunIsolationOldDMMVArun2017v2Task = self.cms.Task(
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2raw,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVLoose,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Loose,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Medium,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2Tight,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VTight,
                self.process.rerunDiscriminationByIsolationOldDMMVArun2017v2VVTight
            )
            self.process.rerunMvaIsolationBoostTask.add(self.rerunIsolationOldDMMVArun2017v2Task)
            self.process.rerunMvaIsolationBoostSequence += self.cms.Sequence(self.rerunIsolationOldDMMVArun2017v2Task)

            tauIDSources.byIsolationMVArun2017v2DBoldDMwLTraw2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2raw')
            tauIDSources.byVVLooseIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2VVLoose')
            tauIDSources.byVLooseIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2VLoose')
            tauIDSources.byLooseIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2Loose')
            tauIDSources.byMediumIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2Medium')
            tauIDSources.byTightIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2Tight')
            tauIDSources.byVTightIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2VTight')
            tauIDSources.byVVTightIsolationMVArun2017v2DBoldDMwLT2017 = self.cms.InputTag('rerunDiscriminationByIsolationOldDMMVArun2017v2VVTight')

        #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if "deepTau2017v1" in self.toKeep:
            print "Adding DeepTau IDs"

            workingPoints_ = {
                "e": {
                    "VVVLoose" : 0.96424,
                    "VVLoose" : 0.98992,
                    "VLoose" : 0.99574,
                    "Loose": 0.99831,
                    "Medium": 0.99868,
                    "Tight": 0.99898,
                    "VTight": 0.99911,
                    "VVTight": 0.99918
                },
                "mu": {
                    "VVVLoose" : 0.959619,
                    "VVLoose" : 0.997687,
                    "VLoose" : 0.999392,
                    "Loose": 0.999755,
                    "Medium": 0.999854,
                    "Tight": 0.999886,
                    "VTight": 0.999944,
                    "VVTight": 0.9999971
                },

                "jet": {
                    "VVVLoose" : 0.5329,
                    "VVLoose" : 0.7645,
                    "VLoose" : 0.8623,
                    "Loose": 0.9140,
                    "Medium": 0.9464,
                    "Tight": 0.9635,
                    "VTight": 0.9760,
                    "VVTight": 0.9859
                }
            }
            file_name = 'RecoTauTag/TrainingFiles/data/DeepTauId/deepTau_2017v1_20L1024N_quantized.pb'
            self.process.deepTau2017v1 = self.cms.EDProducer("DeepBoostedTauId",
                electrons              = self.cms.InputTag('slimmedElectrons'),
                muons                  = self.cms.InputTag('slimmedMuons'),
                taus                   = self.PATTauProducer,
                graph_file             = self.cms.string(file_name),
                mem_mapped             = self.cms.bool(False)
            )

            self.processDeepProducer('deepTau2017v1', tauIDSources, workingPoints_)

            self.process.rerunMvaIsolationBoostTask.add(self.process.deepTau2017v1)
            self.process.rerunMvaIsolationBoostSequence += self.process.deepTau2017v1

        #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if "againstEle2018" in self.toKeep:
            print "starting {}".format(self.toKeep)
#            antiElectronDiscrMVA6_version = "MVA6v1"
            antiElectronDiscrMVA6_version = "MVA6v3_noeveto"
            ### Define new anti-e discriminants
            ## Raw
            from RecoTauTag.RecoTau.PATTauDiscriminationAgainstElectronMVA6_cfi import patTauDiscriminationAgainstElectronMVA6
            self.process.patTauDiscriminationByElectronRejectionMVA62018Raw = patTauDiscriminationAgainstElectronMVA6.clone(
                PATTauProducer = self.PATTauProducer,
                Prediscriminants = noPrediscriminants,
                #Prediscriminants = requireLeadTrack,
                loadMVAfromDB = True,
                returnMVA = True,
                method = "BDTG",
                mvaName_NoEleMatch_wGwoGSF_BL = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL',
                mvaName_NoEleMatch_wGwoGSF_EC = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC',
                mvaName_NoEleMatch_woGwoGSF_BL = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL',
                mvaName_NoEleMatch_woGwoGSF_EC = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC',
                mvaName_wGwGSF_BL = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL',
                mvaName_wGwGSF_EC = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC',
                mvaName_woGwGSF_BL = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL',
                mvaName_woGwGSF_EC = 'RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC',
                minMVANoEleMatchWOgWOgsfBL = 0,
                minMVANoEleMatchWgWOgsfBL  = 0,
                minMVAWOgWgsfBL            = 0,
                minMVAWgWgsfBL             = 0,
                minMVANoEleMatchWOgWOgsfEC = 0,
                minMVANoEleMatchWgWOgsfEC  = 0,
                minMVAWOgWgsfEC            = 0,
                minMVAWgWgsfEC             = 0,
                srcElectrons = 'slimmedElectrons',
                usePhiAtEcalEntranceExtrapolation = True,
            )
            ## WPs
            from RecoTauTag.RecoTau.PATTauDiscriminantCutMultiplexer_cfi import patTauDiscriminantCutMultiplexer
            
            # VLoose
            self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018 = patTauDiscriminantCutMultiplexer.clone(
                PATTauProducer = self.PATTauProducer,
                Prediscriminants = self.process.patTauDiscriminationByElectronRejectionMVA62018Raw.Prediscriminants,
                toMultiplex = self.cms.InputTag("patTauDiscriminationByElectronRejectionMVA62018Raw"),
                key = self.cms.InputTag("patTauDiscriminationByElectronRejectionMVA62018Raw","category"),
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(2),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(5),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(7),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(8),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(10),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(13),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC_WPeff98'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(15),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC_WPeff98'),
                        variable = self.cms.string('pt')
                    )
                )
            )

            # Loose
            self.process.patTauDiscriminationByLooseElectronRejectionMVA62018 = self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018.clone(
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(2),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(5),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(7),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(8),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(10),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(13),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC_WPeff90'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(15),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC_WPeff90'),
                        variable = self.cms.string('pt')
                    )
                )
            )
            # Medium
            self.process.patTauDiscriminationByMediumElectronRejectionMVA62018 = self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018.clone(
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL_WPeff80'),
                        variable = self.cms.string('pt')
                     ),
                    self.cms.PSet(
                        category = self.cms.uint32(2),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(5),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(7),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(8),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(10),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(13),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC_WPeff80'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(15),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC_WPeff80'),
                        variable = self.cms.string('pt')
                    )
                )
            )
            # Tight
            self.process.patTauDiscriminationByTightElectronRejectionMVA62018 = self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018.clone(
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(2),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(5),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(7),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(8),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(10),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(13),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC_WPeff70'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(15),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC_WPeff70'),
                        variable = self.cms.string('pt')
                    )
                )
            )
            # VTight
            self.process.patTauDiscriminationByVTightElectronRejectionMVA62018 = self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018.clone(
                mapping = self.cms.VPSet(
                    self.cms.PSet(
                        category = self.cms.uint32(0),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_BL_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(2),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_BL_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(5),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_BL_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(7),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_BL_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(8),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_woGwoGSF_EC_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(10),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_NoEleMatch_wGwoGSF_EC_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(13),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_woGwGSF_EC_WPeff60'),
                        variable = self.cms.string('pt')
                    ),
                    self.cms.PSet(
                        category = self.cms.uint32(15),
                        cut = self.cms.string('RecoTauTag_antiElectron'+antiElectronDiscrMVA6_version+'_gbr_wGwGSF_EC_WPeff60'),
                        variable = self.cms.string('pt')
                    )
                )
            )
            ### Put all new anti-e discrminats to a sequence
            self.process.patTauDiscriminationByElectronRejectionMVA62018Task = self.cms.Task(
                self.process.patTauDiscriminationByElectronRejectionMVA62018Raw,
                self.process.patTauDiscriminationByVLooseElectronRejectionMVA62018,
                self.process.patTauDiscriminationByLooseElectronRejectionMVA62018,
                self.process.patTauDiscriminationByMediumElectronRejectionMVA62018,
                self.process.patTauDiscriminationByTightElectronRejectionMVA62018,
                self.process.patTauDiscriminationByVTightElectronRejectionMVA62018
            )
            self.process.patTauDiscriminationByElectronRejectionMVA62018Seq = self.cms.Sequence(self.process.patTauDiscriminationByElectronRejectionMVA62018Task)
            self.process.rerunMvaIsolationBoostTask.add(self.process.patTauDiscriminationByElectronRejectionMVA62018Task)
            self.process.rerunMvaIsolationBoostSequence += self.process.patTauDiscriminationByElectronRejectionMVA62018Seq

            _againstElectronTauIDSources = self.cms.PSet(
                againstElectronMVA6Raw2018 = self.cms.InputTag("patTauDiscriminationByElectronRejectionMVA62018Raw"),
                againstElectronMVA6category2018 = self.cms.InputTag("patTauDiscriminationByElectronRejectionMVA62018Raw","category"),
                againstElectronVLooseMVA62018 = self.cms.InputTag("patTauDiscriminationByVLooseElectronRejectionMVA62018"),
                againstElectronLooseMVA62018 = self.cms.InputTag("patTauDiscriminationByLooseElectronRejectionMVA62018"),
                againstElectronMediumMVA62018 = self.cms.InputTag("patTauDiscriminationByMediumElectronRejectionMVA62018"),
                againstElectronTightMVA62018 = self.cms.InputTag("patTauDiscriminationByTightElectronRejectionMVA62018"),
                againstElectronVTightMVA62018 = self.cms.InputTag("patTauDiscriminationByVTightElectronRejectionMVA62018")
            )
            _tauIDSourcesWithAgainistEle = self.cms.PSet(
                tauIDSources.clone(),
                _againstElectronTauIDSources
            )
            tauIDSources =_tauIDSourcesWithAgainistEle.clone()
            

        ##
        print('Embedding new TauIDs into \"'+self.updatedTauName+'\"')
        embedID = self.cms.EDProducer("PATTauIDEmbedder",
            src = self.PATTauProducer,
            tauIDSources = tauIDSources
        )
        setattr(self.process, self.updatedTauName, embedID)

    def processDeepProducer(self, producer_name, tauIDSources, workingPoints_):
        for target,points in workingPoints_.iteritems():
            cuts = self.cms.PSet()
            setattr(tauIDSources, 'by{}VS{}raw'.format(producer_name[0].upper()+producer_name[1:], target),
                        self.cms.InputTag(producer_name, 'VS{}'.format(target)))
            for point,cut in points.iteritems():
                setattr(cuts, point, self.cms.string(str(cut)))

                setattr(tauIDSources, 'by{}{}VS{}'.format(point, producer_name[0].upper()+producer_name[1:], target),
                        self.cms.InputTag(producer_name, 'VS{}{}'.format(target, point)))

            setattr(getattr(self.process, producer_name), 'VS{}WP'.format(target), cuts)


    def getDpfTauVersion(self, file_name):
        """returns the DNN version. File name should contain a version label with data takig year (2011-2, 2015-8) and \
           version number (vX), e.g. 2017v0, in general the following format: {year}v{version}"""
        version_search = re.search('201[125678]v([0-9]+)[\._]', file_name)
        if not version_search:
            raise RuntimeError('File "{}" has an invalid name pattern, should be in the format "{year}v{version}". \
                                Unable to extract version number.'.format(file_name))
        version = version_search.group(1)
        return int(version)
