#ifndef TrackingAnalysis_TrackingParticleProducer_h
#define TrackingAnalysis_TrackingParticleProducer_h
#include "FWCore/Framework/interface/EDProducer.h"

class TrackingParticleProducer : public edm::EDProducer {
public:
  explicit TrackingParticleProducer( const edm::ParameterSet & );
private:
  void produce( edm::Event &, const edm::EventSetup & );
};

#endif
