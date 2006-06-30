#include "SimDataFormats/TrackingAnalysis/test/MCAccessTest.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Common/interface/EDProduct.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"

#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"

//
// should probably go to simGeneral .... well, for the moment I put it here ...
// 

MCAccessTest::MCAccessTest(const edm::ParameterSet& conf){
  conf_ = conf;
}

void MCAccessTest::analyze(const edm::Event& e, const edm::EventSetup& c){
  using namespace std;
  //
  // access hepmc product
  //
  edm::Handle<edm::HepMCProduct> hepMC;
  e.getByType(hepMC);
  cout <<" Got HepMC "<<endl;
  const edm::HepMCProduct * mcp = hepMC.product();

  // print the event
  //
  //  std::cout<<" Event: "<<*(mcp->GetEvent())<<endl;

  //
  // loop over it
  //

  for ( HepMC::GenEvent::particle_const_iterator p = mcp->GetEvent()->particles_begin(); p != mcp->GetEvent()->particles_end(); ++p ) {
    cout <<" HepMC Particle "<<*((*p))<<endl;
  }
  //
  // SimTracks
  //
  edm::Handle<edm::SimTrackContainer> G4TrkContainer;
  e.getByType(G4TrkContainer);
  
  //
  // loop over it
  //
  edm::SimTrackContainer::const_iterator itTrk;
  for (itTrk = G4TrkContainer->begin(); itTrk != G4TrkContainer->end(); 
       ++itTrk) {
    cout <<" SimTrack Particle "<<*itTrk<<endl;
  }
  //
  // SimVertices
  //
  edm::Handle<edm::SimVertexContainer> G4VtxContainer;
  e.getByType(G4VtxContainer);
  
  //
  // loop over it
  //
  edm::SimVertexContainer::const_iterator itVtx;
  for (itVtx = G4VtxContainer->begin(); itVtx != G4VtxContainer->end(); 
       ++itVtx) {
    cout <<" SimVertex Particle "<<*itVtx<<endl;
  }

}
