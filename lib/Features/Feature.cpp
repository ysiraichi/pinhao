/*-------------------------- PINHAO project --------------------------*/

/**
 * @file Feature.cpp
 */

#include "pinhao/Features/Feature.h"

using namespace pinhao;

Feature::Feature(FeatureInfo* InfoPtr, FeatureKind FKind) : 
  Info(std::shared_ptr<FeatureInfo>(InfoPtr)), Kind(FKind) { 
    Processed = false; 
  }

std::string Feature::getName() const { 
  return Info->getName(); 
}

std::string Feature::getDescription() const { 
  return Info->getDescription(); 
}

bool Feature::hasSubFeature(std::string SubFeatureName) const {
  if (!isComposite()) return false;
  CompositeFeatureInfo *CompInfo = static_cast<CompositeFeatureInfo*>(Info.get());
  return CompInfo->hasSubFeature(SubFeatureName); 
}

std::string Feature::getSubFeatureDescription(std::string SubFeatureName) {
  assert(hasSubFeature(SubFeatureName) && "This feature does not have the sub-feature desired.");
  CompositeFeatureInfo *CompInfo = static_cast<CompositeFeatureInfo*>(Info.get());
  return CompInfo->getSubFeatureDescription(SubFeatureName); 
}

bool Feature::isComposite() const { 
  return Info->isComposite();
}

bool Feature::isProcessed() const { 
  return Processed;
}

bool Feature::isLinear() const { 
  return Kind == LinearKind;
}

bool Feature::isMapped() const { 
  return Kind == MappedKind;
}

bool Feature::isStaticFeature() const { 
  return Info->isStaticFeature();
}

bool Feature::isDynamicFeature() const { 
  return Info->isDynamicFeature();
}

Feature::iterator Feature::begin() const {
  assert(isComposite() && "This feature is not a composite type feature.");
  CompositeFeatureInfo *CompInfo = static_cast<CompositeFeatureInfo*>(Info.get());
  return CompInfo->begin();
}

Feature::iterator Feature::end() const {
  assert(isComposite() && "This feature is not a composite type feature.");
  CompositeFeatureInfo *CompInfo = static_cast<CompositeFeatureInfo*>(Info.get());
  return CompInfo->end();
}

void Feature::print(std::ostream &Out) {
  YAML::Emitter Emitter(Out);
  append(Emitter);
  Out << std::endl;
}
