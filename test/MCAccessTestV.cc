#include "Analysis/TrackingVertexProducer/interface/TrackingVertexProducer.h"
#include "SimDataFormats/TrackingAnalysis/test/MCAccessTestV.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/EDProduct.h"
#include "SimDataFormats/Vertex/interface/EmbdSimVertexContainer.h"
#include "SimDataFormats/Track/interface/EmbdSimTrackContainer.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"

#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"
#include <exception>
//
// should probably go to simGeneral .... well, for the moment I put it here ...
// 

using namespace std;
///using namespace edm;


MCAccessTestV::MCAccessTestV(const edm::ParameterSet& conf){
  conf_ = conf;
  distanceCut_ = conf_.getParameter<double>("distanceCut");
  dataLabels_  = conf_.getParameter<vector<string> >("dataLabels");
}

void MCAccessTestV::analyze(const edm::Event& event, const edm::EventSetup& c){
  edm::Handle<edm::HepMCProduct>           hepMC;
  edm::Handle<edm::EmbdSimVertexContainer> G4VtxContainer;
  edm::Handle<edm::EmbdSimTrackContainer>  G4TrkContainer;
  CLHEP::HepLorentzVector                  position;

  auto_ptr<edm::TrackingVertexContainer> tVC( new edm::TrackingVertexContainer );  

  // Get information out of event record
  
  for (vector<string>::const_iterator source = dataLabels_.begin(); source !=
      dataLabels_.end(); ++source) {
    try {
      cout << "Trying to find source " << *source << endl;
      event.getByLabel(*source,hepMC);
      cout << "Found source " << *source << endl;
      break;
    } catch (std::exception &e) {
      cout << "Did not find a valid product named" << *source << endl;
    }    
  }
  
  event.getByType(G4VtxContainer);
  event.getByType(G4TrkContainer);
  const edm::HepMCProduct *mcp = hepMC.product();
  const edm::EmbdSimTrackContainer *etc = G4TrkContainer.product();

  if (mcp == 0) {
    cout << "No source found" << endl;
    return;
  }  
  
  
  // Find and loop over vertices from HepMC
  const HepMC::GenEvent *hme = mcp -> GetEvent();
  hme -> print();
  
  cout << "Distance cut set to "<<distanceCut_<<endl; 
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
    
  cout << "  V: EmbSimVertex #             PT: EmbSimVParticleParent" << endl 
       << "I/O: In/Out of tracker volume  PHM: HepMC# of parent "     << endl
       << "HPV: End HepMC Vertex            P: Vertex position"       << endl 
       << "CA:  Distance to nearest vertex                  " << endl << endl;
    
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
//    edm::Ref<edm::TrackingVertexContainer> closestRef;
    double closest = 9e99;
    int iTVC = 0;
    int cTVC = 0;
    for (edm::TrackingVertexContainer::const_iterator v =
        tVC -> begin();
        v != tVC ->end(); ++v) {
      math::XYZPoint vPosition = v->position();   
      double distance = sqrt(pow(vPosition.X()-mPosition.X(),2) +  
                             pow(vPosition.Y()-mPosition.Y(),2) + 
                             pow(vPosition.Z()-mPosition.Z(),2)); 
      if (distance < closest) {
        closest = distance;
        cTVC = iTVC;
        // flag which one so we can associate them
      }   
      ++iTVC;      
    }
    string NewV = " ";
    if (closest > distanceCut_) {
      TrackingVertex tV = TrackingVertex(mPosition);
//    tV.setG4Vertex(EmbdSimTrackRef( itVtx, 0 ) );
      NewV = "+";
      tVC -> push_back(tV);
      cTVC = tVC->size() - 1;
    }
    cout << "V " << setw(5) << index;
    cout << " PT " << setw(5) << vtxParent;             // Write parent track
    cout << " " << InOut << " ";
    cout << " PHM" <<    setw(5) << partHepMC;  
    cout << " HPV" << setw(5) << vb;    // ending vertex
    
    cout << " CA: " << setprecision(4) << setw(10) << closest*1000;
    cout << " CI: " << setw(5)  << cTVC<< NewV;
    cout << " P: " << position; // Write ESV position
    
    cout << endl;
    
    ++index;     
  }

  cout << tVC->size() << " unique vertices" << endl;
  
  cout << endl;
  cout << "  P: EmbSimParticle #           PT: EmbSimVertexParent"    << endl 
       << "  G: HepMC Particle #            T: PDG Particle Type "     << endl
       << "HPV: End HepMC Vertex            " << endl << endl;
  index = 0;
  for (edm::EmbdSimTrackContainer::const_iterator p = G4TrkContainer->begin(); 
       p != G4TrkContainer->end(); 
       ++p) {
         
    int partHepMC =    p -> genpartIndex();  
    HepMC::GenParticle *hmp = hme -> barcode_to_particle(partHepMC);
    
    cout <<  "P" << setw(5) << index;                // Position in EmbdSimTrackContainer
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
    ++index;  
    
  }

  cout << endl << "End of Event" << endl;
  
  // Put new info into event record  
  
//  event.put(tVC);

}
