#ifndef __PFClusterEnergyCorrectorBase_H__
#define __PFClusterEnergyCorrectorBase_H__

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"

#include <string>

namespace edm {
  class EventSetup;
}

class PFClusterEnergyCorrectorBase {
  typedef PFClusterEnergyCorrectorBase Corrector;
 public:
  PFClusterEnergyCorrectorBase(const edm::ParameterSet& conf) :
    _algoName(conf.getParameter<std::string>("algoName")) { }
  ~PFClusterEnergyCorrectorBase() { }
  //get rid of things we should never use
  PFClusterEnergyCorrectorBase(const Corrector&) = delete;
  Corrector& operator=(const Corrector&) = delete;

  virtual void update(const edm::EventSetup&) { }

  // here we transform one PFCluster to use the new position calculation
  virtual void correctEnergy(reco::PFCluster&) = 0;
  // here you call a loop inside to transform the whole vector
  virtual void correctEnergies(reco::PFClusterCollection&) = 0;

  const std::string& name() const { return _algoName; }
 
 private:  
  const std::string _algoName;

};

#endif
