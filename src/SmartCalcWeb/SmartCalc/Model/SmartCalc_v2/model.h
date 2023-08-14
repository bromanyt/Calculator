#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_
#include <string>
#include "converter_to_opz.h"
#include "element.h"
#include "opz_calculator.h"
#include "parser.h"
#include "validator.h"
namespace s21 {
class Model {
 public:
  Model();
  virtual ~Model() { }
  void Calculator(std::string expression);
  void CalculatorWithX(const std::string& expression, std::string x_variable);
  void CalculateYvalues(std::string expression, double x_min, double step_x);
  std::array<double, 1000> GetYcoorinates();
  bool IsExpressionValid();
  double GetResult();

 private:
  Parser parser_;
  Converter converter_;
  Opz_calculator opz_calculator_;
  s21::Validator validator_;
  void Clean();
};
}  // namespace s21
#endif  // SRC_MODEL_MODEL_H_
