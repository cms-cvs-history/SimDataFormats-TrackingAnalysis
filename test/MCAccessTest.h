#ifndef MCAccessTest_h
#define MCAccessTest_h
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class MCAccessTest  : public edm::EDAnalyzer {
 public:

  explicit MCAccessTest(const edm::ParameterSet& conf);

  virtual ~MCAccessTest(){}

  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);

 private:
  edm::ParameterSet conf_;

};

#endif
