#include "SimDataFormats/TrackingAnalysis/test/TrackingParticleProducer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/EmbdSimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/EmbdSimVertexContainer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include <CLHEP/HepMC/GenParticle.h>
#include <CLHEP/HepMC/GenVertex.h>
#include <iostream>
using namespace edm;
using namespace std;

TrackingParticleProducer::TrackingParticleProducer( const ParameterSet & ) {
  produces<TrackingParticleCollection>();
}

void TrackingParticleProducer::produce( Event & event, const EventSetup & ) {
  Handle<HepMCProduct> h_genEvent;
  event.getByType( h_genEvent );
  const HepMC::GenEvent& genEvent = h_genEvent->getHepMCData();
  
  edm::Handle<EmbdSimTrackContainer> g4Tracks;
  event.getByType( g4Tracks );
  edm::Handle<EmbdSimVertexContainer> g4Vertices;
  event.getByType( g4Vertices );

  auto_ptr<TrackingParticleCollection> tpc( new TrackingParticleCollection );  

  int index = 0;
  for ( EmbdSimTrackContainer::const_iterator t = g4Tracks->begin(); 
	t != g4Tracks->end(); ++ t, ++ index ) {
    const HepLorentzVector & l = t->momentum();
    TrackingParticle::LorentzVector p( l.x(), l.y(), l.z(), l.t() );
    TrackingParticle::Point v( 0, 0, 0 );
    int i_gp = t->genpartIndex(), i_gv = t->vertIndex();
    const HepMC::GenParticle * gp = 0;
    TrackingParticle::Charge q = 0;
    int id = 0;
    if ( i_gp >= 0 ) {
      gp = genEvent.barcode_to_particle( i_gp );
      // the following crashes...
      //      q = char( gp->particledata().charge() );
      id = gp->pdg_id();
    }
    if ( i_gv >= 0 ) {
      const EmbdSimVertex & gv = ( * g4Vertices )[ i_gv ];
      const HepLorentzVector & d = gv.position();
      v = TrackingParticle::Point( d.x(), d.y(), d.z() );
    }
    cout << "create tracking particle" << endl;
    
    TrackingParticle tp( q, p, v, id );
    tp.setG4Track( EmbdSimTrackRef( g4Tracks, index ) );
    if ( gp != 0 ) tp.setGenParticle( gp );
    tpc->push_back( tp );
  }
  event.put( tpc );
}
