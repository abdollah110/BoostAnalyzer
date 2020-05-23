from CRABClient.UserUtilities import config
# getUsernameFromSiteDB
#from WMCore.Configuration import Configuration
#config = Configuration()
config=config()
config.section_('General')
config.General.transferOutputs = True
config.General.workArea = 'MC_BG'
config.section_('JobType')
config.JobType.psetName = 'miniAODAutumn18_PAT.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['RunIIAutumn18MiniAOD.root']
config.JobType.numCores = 1
#config.JobType.inputFiles = ['Fall17_17Nov2017BCDEF_V6_DATA.db','Fall17_17Nov2017_V6_MC.db']
config.JobType.maxMemoryMB = 2500
config.JobType.sendExternalFolder = True
config.JobType.allowUndistributedCMSSW = True
config.section_('Data')
config.Data.unitsPerJob = 5
config.Data.totalUnits = 100
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.outLFNDirBase = '/store/user/abdollah/TauPOG/10_2_3/DYJets_M50/'
config.Data.allowNonValidInputDataset = True
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T3_US_FNALLPC'


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'MC_Boost'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################


Samples=[
    ['DYJetsToLL_M-50_AOD','/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18DRPremix-102X_upgrade2018_realistic_v15_ext2-v1/AODSIM']
]


for sam in Samples:
    
    config.General.requestName = sam[0]
    config.Data.inputDataset=sam[1]
    submit(config)
