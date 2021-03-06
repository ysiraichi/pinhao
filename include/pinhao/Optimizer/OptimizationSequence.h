/*-------------------------- PINHAO project --------------------------*/

/**
 * @file OptimizationSequence.h
 */

#ifndef PINHAO_OPTIMIZATION_SEQUENCE_H
#define PINHAO_OPTIMIZATION_SEQUENCE_H

#include "pinhao/Optimizer/Optimizations.h"
#include "pinhao/Optimizer/OptimizationInfo.h"

#include "llvm/IR/LegacyPassManager.h"

#include <vector>
#include <iostream>

namespace pinhao {
  class OptimizationSet;

  enum class OptLevel {
    None = 0, O1, O2, O3, Os, Oz 
  };

  /**
   * @brief Contains a sequence for a specific @a OptimizationSet.
   */
  class OptimizationSequence : public std::vector<OptimizationInfo> {
    public:
      OptimizationSequence(OptLevel OLevel = OptLevel::None) : OLevel(OLevel) {}

      OptLevel OLevel;

      /// @brief This function should be used when @a OLevel is set. It is called by
      /// @a populateDefaultPasses.
      void populateWithOLevel(llvm::legacy::PassManager &PM, llvm::legacy::FunctionPassManager &FPM);

      /// @brief Generates a @a OptimizationSequence from a specified @a OptimizationSet.
      static std::unique_ptr<OptimizationSequence> generate(OptimizationSet &Set, int Size = -1);

      /// @brief Encapsulates a vector of @a Optimizations into a @a OptimizationSequence.
      static std::unique_ptr<OptimizationSequence> generate(std::vector<Optimization> Sequence);

      /// @brief Generates a random sequence.
      static std::unique_ptr<OptimizationSequence> randomize(uint64_t Size);

      /// @brief Gets the @a OptimizationInfo of the @a Nth element of the sequence.
      OptimizationInfo getOptimization(uint64_t N);

      /// @brief Prints to @a Out the information of this @a OptimizationSequence.
      void print(std::ostream &Out = std::cout);

      /// @brief Populates the @a llvm::legacy::PassManager and the @a llvm::legacy::FunctionPassManager
      /// with the default passes. Should be used always, before any other populate.
      void addDefaultPasses(llvm::Module &Module, llvm::legacy::PassManager &PM,
          llvm::legacy::FunctionPassManager &FPM);

      /// @brief Populates a @a llvm::legacy::PassManager with the current @a Sequence.
      void populatePassManager(llvm::legacy::PassManager &PM);

      /// @brief Populates a @a llvm::legacy::FunctionPassManager with the current @a Sequence.
      /// @details Note that all the optimizations must be for functions (PassKind < 4).
      void populateFunctionPassManager(llvm::legacy::FunctionPassManager &FPM);

  };

}

#endif


