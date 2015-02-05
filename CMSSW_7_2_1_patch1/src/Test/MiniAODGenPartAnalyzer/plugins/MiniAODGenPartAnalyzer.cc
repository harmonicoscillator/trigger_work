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
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TTree.h"
//
// class declaration
//

class MiniAODGenPartAnalyzer : public edm::EDAnalyzer {
public:
  explicit MiniAODGenPartAnalyzer(const edm::ParameterSet&);
  ~MiniAODGenPartAnalyzer();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
  TTree* onlyPhotons_;
  double pt,eta,phi;
  double vx,vy,vz;
  int pdgID;
};

MiniAODGenPartAnalyzer::MiniAODGenPartAnalyzer(const edm::ParameterSet& iConfig):
  packedGenToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed")))
{
  onlyPhotons_->Branch("PdgID",&pdgID,"PdgID/I");
  onlyPhotons_->Branch("Pt",&pt,"Pt/D");
  onlyPhotons_->Branch("Eta",&eta,"Eta/D");
  onlyPhotons_->Branch("Phi",&phi,"Phi/D");
  onlyPhotons_->Branch("Vx",&vx,"Vx/D");
  onlyPhotons_->Branch("Vy",&vy,"Vy/D");
  onlyPhotons_->Branch("Vz",&vz,"Vz/D");
}


MiniAODGenPartAnalyzer::~MiniAODGenPartAnalyzer()
{
}

//Check recursively if any ancestor of particle is the given one

//bool MiniAODGenPartAnalyzer::isAncestor(const reco::Candidate* ancestor, const reco::Candidate * particle)
//{
//  //particle is already the ancestor
//  if(ancestor == particle ) return true;
//
//  //otherwise loop on mothers, if any and return true if the ancestor is found
//  for(size_t i=0;i< particle->numberOfMothers();i++)
//    {
//      if(isAncestor(ancestor,particle->mother(i))) return true;
//    }
//  //if we did not return yet, then particle and ancestor are not relatives
//  return false;
//}

void 
MiniAODGenPartAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace reco;
  using namespace pat;
  std::cout<< "i started the analyzer." << std::endl;
  // Pruned particles are the one containing "important" stuff
  
  // Packed particles are all the status 1, so usable to remake jets
  // The navigation from status 1 to pruned is possible (the other direction should be made by hand)
  Handle<edm::View<pat::PackedGenParticle> > packed;
  iEvent.getByToken(packedGenToken_,packed);
  

  //trying to find all status 1 photons in the barrel, i.e. eta<=2
  for(size_t i=0; i<packed->size();i++)
    {
      if( (*packed)[i].pdgId() == 22 && (*packed)[i].status() == 1  && abs((*packed)[i].eta()) <= 2)
	{
	  
	  const Candidate * photon = &(*packed)[i];
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
MiniAODGenPartAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MiniAODGenPartAnalyzer::endJob() 
{
}

DEFINE_FWK_MODULE(MiniAODGenPartAnalyzer);






































































































































































 



