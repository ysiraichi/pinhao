/*-------------------------- PINHAO project --------------------------*/

/**
 * @file FeatureRegistry.h
 * @brief This file defines a class that has all the registered features.
 */

#ifndef PINHAO_FEATURE_REGISTRY_H
#define PINHAO_FEATURE_REGISTRY_H

#include <memory>
#include <cassert>
#include <map>

namespace pinhao {
  class Feature;

  /**
   * @brief This class contains all registered features as well as its
   * manipulation methods.
   *
   * @details 
   * When a RegisterFeature variable is created it calls a static method
   * of this class in order to insert the new feature in the registry.
   * It is the container of all registered features.
   */
  class FeatureRegistry {
    private:
      /**
       * @brief Stores unique pointers to all registered features.
       *
       * @details
       * In order to use a registered feature, one should clone the
       * desired feature. It maps the name to the feature.
       */
      static std::map<std::string, std::unique_ptr<const Feature>> RegisteredFeatures;

      /**
       * @brief Checks whether a feature (or sub-feature) is already
       * registered.
       *
       * @details
       * It iterates each element in the @a RegisteredFeatures, checking also
       * the sub-feature names. 
       *
       * @param Name The name of the feature or sub-feature.
       *
       * @return True if there already is a feature (or sub-feature) registered
       * with the same name.
       */
      static bool isNameRegistered(std::string Name);

    public:
      /// @brief Register a feature in order to become available.
      static void registerFeature(Feature *F);
  
      /**
       * @brief Clones a feature with name @a FeatureName and returns it.
       *
       * @details
       * Search the @a RegisteredFeatures for a feature with name @a FeatureName.
       * If it finds the feature, then it return the feature's clone. Else, it
       * will return a unique_ptr to nullptr.
       *
       * @param FeatureName The name of the feature.
       * @return A unique pointer with a clone of the feature (if found).
       */
      static std::unique_ptr<Feature> get(std::string FeatureName);
  };

}

#endif