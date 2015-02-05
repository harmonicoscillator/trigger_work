import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/i/ilaflott/test_files/AODSIM_TEST_FILE.root")
)

process.demo = cms.EDAnalyzer('MiniAODGenPartAnalyzer',
packed = cms.InputTag("packedGenParticles")

)


process.p = cms.Path(process.demo)
