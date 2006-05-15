#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "SimDataFormats/TrackingAnalysis/test/MCAccessTest.h"
#include "SimDataFormats/TrackingAnalysis/test/TrackingParticleProducer.h"

DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE( MCAccessTest );
DEFINE_ANOTHER_FWK_MODULE( TrackingParticleProducer );
