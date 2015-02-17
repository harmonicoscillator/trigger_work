// -*- C++ -*-
// Original Author:  Ian Laflotte
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
  //const unsigned int MAXSIZE=1000;
  TTree* onlyPhotons_;
  double pt[1000],eta[1000],phi[1000];
  double vx[1000],vy[1000],vz[1000];
  int pdgID[1000];
  int event, run;
  int nPhotons;
  double lumi;

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
  nPhotons = 0;

  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().luminosityBlock();

  //trying to find all status 1 photons in the barrel, i.e. eta<=2
  for(size_t i=0; i<gen->size();i++)
    {
      int flag = 0;      
      
      //std::cout<< "i started the loop, i =" << i << std::endl;
      if( (*gen)[i].pdgId() == 22 && (*gen)[i].status() == 1  && abs((*gen)[i].eta()) <= 2)
	{
	  flag = 1;


	  const Candidate * photon = &(*gen)[i];
	  vx[nPhotons]      = photon->vx()   ;
	  vy[nPhotons]      = photon->vy()   ;
	  vz[nPhotons]      = photon->vz()   ;
	  eta[nPhotons]     = photon->eta()  ;
	  phi[nPhotons]     = photon->phi()  ;
	  pt[nPhotons]      = photon->pt()   ;
	  pdgID[nPhotons]   = photon->pdgId();
	  
	  std::cout << "PdgID: " << pdgID << " pt: " << pt << " eta: " << eta << " phi: " << phi << std::endl;
	  
	  nPhotons++;
	}

      if (flag == 1) std::cout << "I found a photon(s)!" << std::endl;
      
    }
  
  onlyPhotons_->Fill();
  
}
// ------------ method called once each job just before starting event loop  ------------
void 
simpleGenAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  onlyPhotons_= fs->make<TTree>("PhotonTree","GenBarrelPhotonsOnly");

  onlyPhotons_->Branch("event",&event,"event/I");
  onlyPhotons_->Branch("run", &run, "run/I");
  onlyPhotons_->Branch("lumi", &lumi, "lumi/I");

  //const unsigned int MAXSIZE=1000;

  //pdgID = new int[MAXSIZE];
  //pt = new double[MAXSIZE];
  //eta = new double[MAXSIZE];
  //phi = new double[MAXSIZE];
  //vx = new double[MAXSIZE];
  //vy = new double[MAXSIZE];
  //vz = new double[MAXSIZE];

  onlyPhotons_->Branch("nPhotons", &nPhotons, "nPhotons/I");

  onlyPhotons_->Branch("pdgID",pdgID,"pdgID[nPhotons]/I");   
  onlyPhotons_->Branch("pt",pt,"pt[nPhotons]/D");	   
  onlyPhotons_->Branch("eta",eta,"eta[nPhotons]/D");	   
  onlyPhotons_->Branch("phi",phi,"phi[nPhotons]/D");	   
  onlyPhotons_->Branch("vx",vx,"vx[nPhotons]/D");	   
  onlyPhotons_->Branch("vy",vy,"vy[nPhotons]/D");	   
  onlyPhotons_->Branch("vz",vz,"vz[nPhotons]/D");           
}

// ------------ method called once each job just after ending the event loop  ------------
void 
simpleGenAnalyzer::endJob() 
{
}

DEFINE_FWK_MODULE(simpleGenAnalyzer);
