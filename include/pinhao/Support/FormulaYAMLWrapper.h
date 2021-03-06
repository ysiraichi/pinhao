/*-------------------------- PINHAO project --------------------------*/

/**
 * @file FormulaYAMLWrapper.h
 */

#ifndef PINHAO_FORMULA_YAML_WRAPPER_H
#define PINHAO_FORMULA_YAML_WRAPPER_H

#include "pinhao/Support/YAMLWrapper.h"
#include "pinhao/Support/YamlOptions.h"
#include "pinhao/Support/Types.h"

#include "pinhao/MachineLearning/GrammarEvolution/Formulas.h"

using namespace pinhao;

/*
 * -----------------------------------
 *  Overloading for: Formula<T>
 */
template <class T>
void YAMLWrapper::fill(Formula<T> &Value, ConstNode &Node) {
  switch (Value.getKind()) {
    case FormulaKind::Literal:
      YAMLWrapper::fill(static_cast<LitFormula<T>&>(Value), Node);
      break;
    case FormulaKind::BoolBinOp:
      {
        FormulaBase &FormulaCast = static_cast<FormulaBase&>(Value);
        switch (Value.getOperandsType()) {
          case ValueType::Int: 
            YAMLWrapper::fill(static_cast<BoolBinOpFormula<int>&>(FormulaCast), Node);
            break;
          case ValueType::Float: 
            YAMLWrapper::fill(static_cast<BoolBinOpFormula<double>&>(FormulaCast), Node);
            break;
          case ValueType::String: 
            YAMLWrapper::fill(static_cast<BoolBinOpFormula<std::string>&>(FormulaCast), Node);
            break;
          case ValueType::Bool: 
            YAMLWrapper::fill(static_cast<BoolBinOpFormula<bool>&>(FormulaCast), Node);
            break;
        }
      }
    case FormulaKind::ArithBinOp:
      YAMLWrapper::fill(static_cast<ArithBinOpFormula<T>&>(Value), Node);
      break;
    case FormulaKind::If:
      YAMLWrapper::fill(static_cast<IfFormula<T>&>(Value), Node);
      break;
    case FormulaKind::Feature:
      YAMLWrapper::fill(static_cast<FeatureFormula<T>&>(Value), Node);
      break;
  }
}

template <class T>
void YAMLWrapper::append(const Formula<T> &Value, Emitter &E) {
  switch (Value.getKind()) {
    case FormulaKind::Literal:
      YAMLWrapper::append(static_cast<const LitFormula<T>&>(Value), E);
      break;
    case FormulaKind::BoolBinOp:
      {
        const FormulaBase &FormulaCast = static_cast<const FormulaBase&>(Value);
        switch (Value.getOperandsType()) {
          case ValueType::Int:
            YAMLWrapper::append(static_cast<const BoolBinOpFormula<int>&>(FormulaCast), E);
            break;
          case ValueType::Float:
            YAMLWrapper::append(static_cast<const BoolBinOpFormula<double>&>(FormulaCast), E);
            break;
          case ValueType::String:
            YAMLWrapper::append(static_cast<const BoolBinOpFormula<std::string>&>(FormulaCast), E);
            break;
          case ValueType::Bool:
            YAMLWrapper::append(static_cast<const BoolBinOpFormula<bool>&>(FormulaCast), E);
            break;
        }
        break;
      }
    case FormulaKind::ArithBinOp:
      YAMLWrapper::append(static_cast<const ArithBinOpFormula<T>&>(Value), E);
      break;
    case FormulaKind::If:
      YAMLWrapper::append(static_cast<const IfFormula<T>&>(Value), E);
      break;
    case FormulaKind::Feature:
      YAMLWrapper::append(static_cast<const FeatureFormula<T>&>(Value), E);
      break;
  }
}

/*
 * -----------------------------------
 *  Overloading for: ArithBinOpFormula
 */
template <class T>
void YAMLWrapper::fill(ArithBinOpFormula<T> &Value, ConstNode &Node) {
  Value.Lhs.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["lhs"]).release()));
  Value.Rhs.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["rhs"]).release()));
  Value.setOperator(getOperatorKind(Node["op"].as<std::string>()));
}

template <class T>
void YAMLWrapper::append(const ArithBinOpFormula<T> &Value, Emitter &E) {
  E << YAML::BeginMap;
  E << YAML::Key << "type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getType()), E);
  E << YAML::Key << "kind" << YAML::Value;
  YAMLWrapper::append(getFormulaKindString(Value.getKind()), E);
  E << YAML::Key << "op" << YAML::Value;
  YAMLWrapper::append(getOperatorKindString(Value.getOperator()), E);
  E << YAML::Key << "lhs" << YAML::Value;
  YAMLWrapper::append(*Value.Lhs, E);
  E << YAML::Key << "rhs" << YAML::Value;
  YAMLWrapper::append(*Value.Rhs, E);
  E << YAML::EndMap;
}

/*
 * -----------------------------------
 *  Overloading for: BoolBinOpFormula
 */
template <class T>
void YAMLWrapper::fill(BoolBinOpFormula<T> &Value, ConstNode &Node) {
  Value.Lhs.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["lhs"]).release()));
  Value.Rhs.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["rhs"]).release()));
  Value.setOperator(getOperatorKind(Node["op"].as<std::string>()));
}

template <class T>
void YAMLWrapper::append(const BoolBinOpFormula<T> &Value, Emitter &E) {
  E << YAML::BeginMap;
  E << YAML::Key << "type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getType()), E);
  E << YAML::Key << "kind" << YAML::Value;
  YAMLWrapper::append(getFormulaKindString(Value.getKind()), E);
  E << YAML::Key << "op-type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getOperandsType()), E);
  E << YAML::Key << "op" << YAML::Value;
  YAMLWrapper::append(getOperatorKindString(Value.getOperator()), E);
  E << YAML::Key << "lhs" << YAML::Value;
  YAMLWrapper::append(*Value.Lhs, E);
  E << YAML::Key << "rhs" << YAML::Value;
  YAMLWrapper::append(*Value.Rhs, E);
  E << YAML::EndMap;
}

/*
 * -----------------------------------
 *  Overloading for: IfFormula
 */
template <class T>
void YAMLWrapper::fill(IfFormula<T> &Value, ConstNode &Node) {
  Value.Condition.reset(static_cast<Formula<bool>*>(YAMLWrapper::get<FormulaBase>(Node["cond"]).release()));
  Value.ThenBody.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["then"]).release()));
  Value.ElseBody.reset(static_cast<Formula<T>*>(YAMLWrapper::get<FormulaBase>(Node["else"]).release()));
}

template <class T>
void YAMLWrapper::append(const IfFormula<T> &Value, Emitter &E) {
  E << YAML::BeginMap;
  E << YAML::Key << "type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getType()), E);
  E << YAML::Key << "kind" << YAML::Value;
  YAMLWrapper::append(getFormulaKindString(Value.getKind()), E);
  E << YAML::Key << "cond" << YAML::Value;
  YAMLWrapper::append(*Value.Condition, E); 
  E << YAML::Key << "then" << YAML::Value;
  YAMLWrapper::append(*Value.ThenBody, E); 
  E << YAML::Key << "else" << YAML::Value;
  YAMLWrapper::append(*Value.ElseBody, E); 
  E << YAML::EndMap;
}

/*
 * -----------------------------------
 *  Overloading for: LitFormula
 */
template <class T>
void YAMLWrapper::fill(LitFormula<T> &Value, ConstNode &Node) {
  Value.setValue(Node["value"].as<T>());
}

template <class T>
void YAMLWrapper::append(const LitFormula<T> &Value, Emitter &E) {
  E << YAML::BeginMap;
  E << YAML::Key << "type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getType()), E);
  E << YAML::Key << "kind" << YAML::Value;
  YAMLWrapper::append(getFormulaKindString(Value.getKind()), E);
  E << YAML::Key << "value" << YAML::Value;
  YAMLWrapper::append(Value.getValue(), E);
  E << YAML::EndMap;
}

/*
 * -----------------------------------
 *  Overloading for: FeatureFormula<T>
 */
template <class T>
void YAMLWrapper::fill(FeatureFormula<T> &Value, ConstNode &Node) {
  std::pair<std::string, std::string> Pair;
  Pair.first = Node["feature"].as<std::string>();
  if (Node["sub"])
    Pair.second = Node["sub"].as<std::string>();
  Value.FeaturePair = Pair;
}

template <class T>
void YAMLWrapper::append(const FeatureFormula<T> &Value, Emitter &E) {
  E << YAML::BeginMap;
  E << YAML::Key << "type" << YAML::Value;
  YAMLWrapper::append(static_cast<int>(Value.getType()), E);
  E << YAML::Key << "kind" << YAML::Value;
  YAMLWrapper::append(getFormulaKindString(Value.getKind()), E);
  E << YAML::Key << "feature" << YAML::Value;
  YAMLWrapper::append(Value.FeaturePair.first, E);
  if (Value.FeaturePair.second != "") {
    E << YAML::Key << "sub" << YAML::Value;
    YAMLWrapper::append(Value.FeaturePair.second, E);
  }
  E << YAML::EndMap;
}

#endif
