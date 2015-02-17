// -*- C++ -*-
//
// Package:    Test/MiniAnalyzer
// Class:      MiniAnalyzer
// 
/* class MiniAnalyzer MiniAnalyzer.cc Test/MiniAnalyzer/plugins/MiniAnalyzer.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
*/
// Original Author:  Andrea RIZZI
// Edited By: Ian Laflotte
//         Created:  Mon, 07 Jul 2014 07:56:38 GMT

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

//#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
//
// class declaration
//

class simpleGenAnalyzer : public edm::EDAnalyzer {
public:
  explicit simpleGenAnalyzer(const edm::ParameterSet&);
  ~simpleGenAnalyzer();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  edm::EDGetTokenT<std::vector<reco::GenParticle> > genToken_;
  TTree* onlyPhotons_;
  double pt,eta,phi;
  double vx,vy,vz;
  int pdgID;
};

simpleGenAnalyzer::simpleGenAnalyzer(const edm::ParameterSet& iConfig):
  genToken_(consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("gen")))
{
}

simpleGenAnalyzer::~simpleGenAnalyzer()
{
}

void 
simpleGenAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace reco;
  //using namespace pat;

  //std::cout<< "i started the analyzer." << std::endl;

  Handle<std::vector<reco::GenParticle> > gen;
  iEvent.getByToken(genToken_,gen);

  //trying to find all status 1 photons in the barrel, i.e. eta<=2
  for(size_t i=0; i<gen->size();i++)
    {
      std::cout<< "i started the loop, i =" << i << std::endl;
      if( (*gen)[i].pdgId() == 22 && (*gen)[i].status() == 1  && abs((*gen)[i].eta()) <= 2)
	{
	  
	  const Candidate * photon = &(*gen)[i];
	  vx      = photon->vx()   ;
	  vy      = photon->vy()   ;
	  vz      = photon->vz()   ;
	  eta     = photon->eta()  ;
	  phi     = photon->phi()  ;
	  pt      = photon->pt()   ;
	  pdgID   = photon->pdgId();
	  
	  std::cout << "PdgID: " << pdgID << " pt: " << pt << " eta: " << eta << " phi: " << phi << std::endl;
	  
	  onlyPhotons_->Fill();
	}
      
    }
  
}
// ------------ method called once each job just before starting event loop  ------------
void 
simpleGenAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  onlyPhotons_= fs->make<TTree>("PhotonTree","GenBarrelPhotonsOnly");
  
  onlyPhotons_->Branch("pdgID",&pdgID,"pdgID/I");   
  onlyPhotons_->Branch("pt",&pt,"pt/D");	   
  onlyPhotons_->Branch("eta",&eta,"eta/D");	   
  onlyPhotons_->Branch("phi",&phi,"phi/D");	   
  onlyPhotons_->Branch("vx",&vx,"vx/D");	   
  onlyPhotons_->Branch("vy",&vy,"vy/D");	   
  onlyPhotons_->Branch("vz",&vz,"vz/D");           
}

// ------------ method called once each job just after ending the event loop  ------------
void 
simpleGenAnalyzer::endJob() 
{
}

DEFINE_FWK_MODULE(simpleGenAnalyzer);
