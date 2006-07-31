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
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/EncodedEventId/interface/EncodedEventId.h"

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
//  edm::Handle<edm::HepMCProduct> hepMC;
//  e.getByType(hepMC);
//  cout <<" Got HepMC "<<endl;
//  const edm::HepMCProduct * mcp = hepMC.product();

  // print the event
  //
  //  std::cout<<" Event: "<<*(mcp->GetEvent())<<endl;

  //
  // loop over it
  //

//  for ( HepMC::GenEvent::particle_const_iterator p = mcp->GetEvent()->particles_begin(); p != mcp->GetEvent()->particles_end(); ++p ) {
//    cout <<" HepMC Particle "<<*((*p))<<endl;
//  }
  //
  // SimTracks
  //
  edm::Handle<edm::SimTrackContainer> G4TrkContainer;
  e.getByLabel("SimG4Object", G4TrkContainer);

  edm::Handle<edm::PSimHitContainer> TIBHitsLowTof;
  edm::Handle<edm::PSimHitContainer> TIBHitsHighTof;
  edm::Handle<edm::PSimHitContainer> TIDHitsLowTof;
  edm::Handle<edm::PSimHitContainer> TIDHitsHighTof;
  edm::Handle<edm::PSimHitContainer> TOBHitsLowTof;
  edm::Handle<edm::PSimHitContainer> TOBHitsHighTof;
  edm::Handle<edm::PSimHitContainer> TECHitsLowTof;
  edm::Handle<edm::PSimHitContainer> TECHitsHighTof;
//  edm::Handle<edm::PSimHitContainer> PixelBarrelHitsHighTof;
//  edm::Handle<edm::PSimHitContainer> PixelBarrelHitsLowTof;
//  edm::Handle<edm::PSimHitContainer> PixelEndcapHitsHighTof;
//  edm::Handle<edm::PSimHitContainer> PixelEndcapHitsLowTof;

  e.getByLabel("SimG4Object","TrackerHitsTIBLowTof", TIBHitsLowTof);
  e.getByLabel("SimG4Object","TrackerHitsTIBHighTof", TIBHitsHighTof);
  e.getByLabel("SimG4Object","TrackerHitsTIDLowTof", TIDHitsLowTof);
  e.getByLabel("SimG4Object","TrackerHitsTIDHighTof", TIDHitsHighTof);
  e.getByLabel("SimG4Object","TrackerHitsTOBLowTof", TOBHitsLowTof);
  e.getByLabel("SimG4Object","TrackerHitsTOBHighTof", TOBHitsHighTof);
  e.getByLabel("SimG4Object","TrackerHitsTECLowTof", TECHitsLowTof);
  e.getByLabel("SimG4Object","TrackerHitsTECHighTof", TECHitsHighTof);
//  e.getByLabel("SimG4Object","PixelBarrelHitsHighTof", PixelBarrelHitsHighTof);
//  e.getByLabel("SimG4Object","PixelBarrelHitsLowTof", PixelBarrelHitsLowTof);  
//  e.getByLabel("SimG4Object","PixelEndcapHitsHighTof", PixelEndcapHitsHighTof);  
//  e.getByLabel("SimG4Object","PixelEndcapHitsLowTof", PixelEndcapHitsLowTof);
   
//  vector<PSimHit> AlltheHits;
   vector<edm::Handle<edm::PSimHitContainer> > AlltheConteiners;
   
  AlltheConteiners.push_back(TIBHitsLowTof);
  AlltheConteiners.push_back(TIBHitsHighTof);
  AlltheConteiners.push_back(TIDHitsLowTof);
  AlltheConteiners.push_back(TIDHitsHighTof);
  AlltheConteiners.push_back(TOBHitsLowTof);
  AlltheConteiners.push_back(TOBHitsHighTof);
  AlltheConteiners.push_back(TECHitsLowTof);
  AlltheConteiners.push_back(TECHitsHighTof);
//  AlltheConteiners.push_back(PixelBarrelHitsHighTof);
//  AlltheConteiners.push_back(PixelBarrelHitsLowTof);
//  AlltheConteiners.push_back(PixelEndcapHitsHighTof);
//  AlltheConteiners.push_back(PixelEndcapHitsLowTof);
//    
//  AlltheHits.insert(AlltheHits.end(),TIBHitsLowTof->begin(), TIBHitsLowTof->end());
//  AlltheHits.insert(AlltheHits.end(),TIBHitsHighTof->begin(), TIBHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),TIDHitsLowTof->begin(), TIDHitsLowTof->end());
//  AlltheHits.insert(AlltheHits.end(),TIDHitsHighTof->begin(), TIDHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),TOBHitsLowTof->begin(), TOBHitsLowTof->end());
//  AlltheHits.insert(AlltheHits.end(),TOBHitsHighTof->begin(), TOBHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),TECHitsLowTof->begin(), TECHitsLowTof->end());
//  AlltheHits.insert(AlltheHits.end(),TECHitsHighTof->begin(), TECHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),PixelBarrelHitsHighTof->begin(), PixelBarrelHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),PixelBarrelHitsLowTof->begin(), PixelBarrelHitsLowTof->end());
//  AlltheHits.insert(AlltheHits.end(),PixelEndcapHitsHighTof->begin(), PixelEndcapHitsHighTof->end());
//  AlltheHits.insert(AlltheHits.end(),PixelEndcapHitsLowTof->begin(), PixelEndcapHitsLowTof->end());
  
//
// loop over it
//
typedef edm::RefVector<edm::PSimHitContainer>		       TrackPSimHitRefVector;
typedef edm::Ref<edm::PSimHitContainer> 		       TrackPSimHitRef;


  TrackPSimHitRefVector newVec;

  edm::SimTrackContainer::const_iterator itTrk;
  int simtrackId = 0;
//  vector<PSimHit> sametrackId;
//  map<int, vector<PSimHit> > trackIdSimHitMap;
  for (itTrk = G4TrkContainer->begin(); itTrk != G4TrkContainer->end(); ++itTrk) {
    simtrackId = itTrk->trackId();
    EncodedEventId trackEventId = itTrk->eventId();
  
    cout <<" SimTrack TrackId "<< simtrackId << " Event Id " << trackEventId.event() <<endl;
//    typedef vector<PSimHit>::const_iterator hit_iter;
//    for ( hit_iter itHits = AlltheHits.begin(); itHits != AlltheHits.end(); ++itHits ){
//	   if( simtrackId == itHits->trackId() && trackEventId == itHits->eventId() ) {
//	    //sametrackId.push_back(*itHits);
//	    trackIdSimHitMap[simtrackId].push_back(*itHits);
//	    cout << " Got a match!" << endl;
//	    }
//    }  
    typedef vector<edm::Handle<edm::PSimHitContainer> >::const_iterator cont_iter;
    int  index = 0;
    for( cont_iter allCont = AlltheConteiners.begin(); allCont != AlltheConteiners.end(); ++allCont ){
      for (edm::PSimHitContainer::const_iterator hit = (*allCont)->begin(); hit != (*allCont)->end(); ++hit,  ++index) {
	if( simtrackId == hit->trackId() && trackEventId == hit->eventId() ){
	
	  newVec.push_back(TrackPSimHitRef(*allCont, index)); 
	  cout << " Containers TrackId " << hit->trackId() << endl;
	}
      }
    }
  }
  
  //
  // SimVertices
  //
//  edm::Handle<edm::SimVertexContainer> G4VtxContainer;
//  e.getByLabel("VtxSmeared",G4VtxContainer);
  
  //
  // loop over it
  //
//  edm::SimVertexContainer::const_iterator itVtx;
//  for (itVtx = G4VtxContainer->begin(); itVtx != G4VtxContainer->end(); 
//       ++itVtx) {
//    cout <<" SimVertex Particle "<<*itVtx<<endl;
//  }
 // SimHits
//    edm::Handle<edm::PSimHitContainer> TIBHitsLowTof;
//    e.getByLabel("SimG4Object", "TrackerHitsTIBLowTof", TIBHitsLowTof);
//    
//    edm::PSimHitContainer::const_iterator itSimHit; 
//    
//    for (itSimHit = TIBHitsLowTof->begin(); itSimHit != TIBHitsLowTof->end(); ++itSimHit){
//	 cout << "PsimHit TrackId " << itSimHit->trackId() << endl;
//    }

}
