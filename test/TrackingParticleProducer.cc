#include "SimDataFormats/TrackingAnalysis/test/TrackingParticleProducer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
using namespace edm;
using namespace std;

TrackingParticleProducer::TrackingParticleProducer( const ParameterSet & ) {
  produces<TrackingParticleCollection>();
}

void TrackingParticleProducer::produce( Event & evt, const EventSetup & ) {
  Handle<HepMCProduct> h_mc;
  evt.getByType( h_mc );
  const HepMCProduct * mc = h_mc.product();

  auto_ptr<TrackingParticleCollection> tpc( new TrackingParticleCollection );  

  for ( HepMC::GenEvent::particle_const_iterator p = mc->GetEvent()->particles_begin(); 
	p != mc->GetEvent()->particles_end(); ++ p ) {
    cout << " HepMC Particle " << **p << endl;
    tpc->push_back( TrackingParticle( *p ) );
  }
  evt.put( tpc );
}
