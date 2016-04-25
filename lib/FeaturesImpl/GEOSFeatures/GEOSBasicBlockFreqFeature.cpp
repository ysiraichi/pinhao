/*-------------------------- PINHAO project --------------------------*/

/**
 * @file GEOSBasicBlockFreqFeature.cpp
 */

#include "pinhao/Initialization.h"
#include "pinhao/Features/MapFeature.h"
#include "pinhao/PerformanceAnalyser/GEOSWrapper.h"

#include "geos/ProfileModule/ProfileModule.h"

using namespace pinhao;

static std::shared_ptr<ProfileModule> PModule;

namespace {

  class GEOSBasicBlockFreqFeature : public MapFeature<void*, uint64_t> {
    public:
      GEOSBasicBlockFreqFeature(FeatureInfo *Info) : 
        MapFeature<void*, uint64_t>(Info) {}

      std::unique_ptr<Feature> clone() const override;

      void processModule(llvm::Module &Module) override;
  };

}

void GEOSBasicBlockFreqFeature::processModule(llvm::Module &Module) {
  std::shared_ptr<ProfileModule> PM(PModule);

  if (&Module != PModule->getLLVMModule()) {
    PM.reset(PModule->getCopy(false));
    PM->setLLVMModule(&Module);
    PM->repairProfiling();
  }

  for (auto &Function : Module)
    for (auto &BasicBlock : Function) {
      uint64_t Frequency = PM->getBasicBlockFrequency(BasicBlock);
      setValueOfKey(this->getName(), Frequency, (void*)&BasicBlock); 
    }

}

std::unique_ptr<Feature> GEOSBasicBlockFreqFeature::clone() const {
  GEOSBasicBlockFreqFeature *Clone = new GEOSBasicBlockFreqFeature(*this);
  Clone->Yaml.reset(new Yamlfy<MapFeature<void*, uint64_t>>(Clone));
  return std::unique_ptr<Feature>(Clone);
}

void pinhao::initializeGEOSBasicBlockFreqFeature(llvm::Module &Module) {
  PModule.reset(new ProfileModule(&Module));
  GEOSWrapper::getFrequencies(PModule);
}

static RegisterFeature<GEOSBasicBlockFreqFeature> 
X(new FeatureInfo("geos-bbfreq", "BasicBlock frequency calculated by GEOS.", 
      ValueType::Int, FeatureInfo::Dynamic));
