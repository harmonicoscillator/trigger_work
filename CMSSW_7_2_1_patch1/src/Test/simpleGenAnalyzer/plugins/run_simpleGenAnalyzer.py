import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/i/ilaflott/public/test_files/AODSIM_TEST_FILE.root")    
    #fileNames = cms.untracked.vstring("/Neutrino_Pt-2to20_gun/Fall13dr-castor_tsg_PU1bx50_POSTLS162_V1-v1/AODSIM")    
    #fileNames = cms.untracked.vstring("root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/F6EDDC10-8DFC-E311-BC5D-0025905A60D6.root")
    
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("simpleGenAnalzyer_onlyPhotons.root")
    #closeFileFast = cms.untracked.bool(True)
)



process.demo = cms.EDAnalyzer('simpleGenAnalyzer',
    gen = cms.InputTag("genParticles")
)


process.p = cms.Path(process.demo)
