#include "Analysis/TrackingVertexProducer/interface/TrackingVertexProducer.h"
#include "SimDataFormats/TrackingAnalysis/test/MCAccessTest.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Common/interface/EDProduct.h"
#include "SimDataFormats/Vertex/interface/EmbdSimVertexContainer.h"
#include "SimDataFormats/Track/interface/EmbdSimTrackContainer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"

#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"

//
// should probably go to simGeneral .... well, for the moment I put it here ...
// 

using namespace std;
///using namespace edm;


MCAccessTest::MCAccessTest(const edm::ParameterSet& conf){
  conf_ = conf;
}

void MCAccessTest::analyze(const edm::Event& event, const edm::EventSetup& c){
  edm::Handle<edm::HepMCProduct>           hepMC;
  edm::Handle<edm::EmbdSimVertexContainer> G4VtxContainer;
  edm::Handle<edm::EmbdSimTrackContainer>  G4TrkContainer;
  CLHEP::HepLorentzVector                  position;

  auto_ptr<edm::TrackingVertexContainer> tVC( new edm::TrackingVertexContainer );  

  // Get information out of event record
  
  event.getByLabel("VtxSmeared",hepMC);
  event.getByType(G4VtxContainer);
  event.getByType(G4TrkContainer);
  const edm::HepMCProduct *mcp = hepMC.product();
  const edm::EmbdSimTrackContainer *etc = G4TrkContainer.product();

  // Find and loop over vertices from HepMC
  const HepMC::GenEvent *hme = mcp -> GetEvent();
  hme -> print();

  /*
  for (HepMC::GenEvent::vertex_const_iterator v = hme->vertices_begin(); 
       v != hme->vertices_end(); 
       ++v) {

    position = (*v) -> position();
    math::XYZPoint mPosition = math::XYZPoint(position.x(),position.y(),position.z());
    if (position != HepLorentzVector(0,0,0,0)) {
      cout << "HepMC " << position << endl;
    }
    tVC -> push_back(TrackingVertex(mPosition));
  }
*/
  // Find and loop over EmbdSimVertex vertices
  int index = 0;
  for (edm::EmbdSimVertexContainer::const_iterator itVtx = G4VtxContainer->begin(); 
       itVtx != G4VtxContainer->end(); 
       ++itVtx) {
         
    position = itVtx -> position();  // Get position of ESV
    math::XYZPoint mPosition = math::XYZPoint(position.x(),position.y(),position.z());
    int vtxParent = itVtx -> parentIndex(); // Get incoming track (EST)
    
    string InOut;
    int partHepMC = -1;
    int vb = 0;
    
    if (position.perp() < 1200 && abs(position.z()) < 3000) { // In or out of Tracker
      InOut = "I";
    } else {
      InOut = "O";
    }
    if (vtxParent >= 0) {                     // If there is parent track, figure out HEPMC Vertex 
      EmbdSimTrack est = etc->at(vtxParent);  // Pull track out from vector
      partHepMC =     est.genpartIndex(); // Get HepMC particle barcode
      HepMC::GenParticle *hmp = hme -> barcode_to_particle(partHepMC); // Convert barcode
      if (hmp != 0) {
       HepMC::GenVertex *hmpv = hmp -> production_vertex(); 
       if (hmpv != 0) {
         vb = hmpv  -> barcode();
       }  
      }  
    }  
    cout << "V " << setw(5) << index;
    cout << " PT " << setw(5) << vtxParent;             // Write parent track
    cout << " " << InOut << " ";
    cout << " PHM" <<    setw(5) << partHepMC;  
    cout << " HPV" << setw(5) << vb;    // ending vertex
    
    cout << " P: " << position; // Write ESV position
    TrackingVertex tV = TrackingVertex(mPosition);
//    tV.setG4Vertex(EmbdSimTrackRef( itVtx, 0 ) );
    
    tVC -> push_back(tV);
    ++index;     
    cout << endl;
  }

  cout << endl;
  index = 0;
  for (edm::EmbdSimTrackContainer::const_iterator p = G4TrkContainer->begin(); 
       p != G4TrkContainer->end(); 
       ++p) {
         
    ++index;  
    
    int partHepMC =    p -> genpartIndex();  
    HepMC::GenParticle *hmp = hme -> barcode_to_particle(partHepMC);
    
    cout << "P" << setw(5) << index;                // Position in EmbdSimTrackContainer
    cout << " V" << setw(5) << p -> vertIndex();    // EmbdSimVertex
    cout << " G" << setw(5) << partHepMC; // HepMC particle number
    cout << " T" << setw(10) << p -> type();        // HepMC/PDG particle type 
    if (hmp != 0) {
       HepMC::GenVertex *hmpv = hmp -> production_vertex(); 
       if (hmpv != 0) {
         int vb = hmpv  -> barcode();
         cout << " HPV" << setw(5) << vb;    // production vertex
       }  
    }  
    
    cout << endl;
  }

  cout << endl << "End of Event" << endl;
  
  // Put new info into event record  
  
//  event.put(tVC);

}
