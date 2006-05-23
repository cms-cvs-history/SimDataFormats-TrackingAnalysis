#ifndef MCAccessTestV_h
#define MCAccessTestV_h
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <string>
#include <vector>

class MCAccessTestV  : public edm::EDAnalyzer {
 public:

  explicit MCAccessTestV(const edm::ParameterSet& conf);

  virtual ~MCAccessTestV(){}

  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);

 private:
  edm::ParameterSet conf_;
  double distanceCut_;
  std::vector<std::string> dataLabels_;
  
};

#endif
