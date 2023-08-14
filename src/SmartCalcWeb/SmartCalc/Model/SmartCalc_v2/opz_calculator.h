#ifndef SRC_MODEL_OPZ_CALCULATOR_H_
#define SRC_MODEL_OPZ_CALCULATOR_H_
#include <queue>
#include <stack>
#include <array>
#include "element.h"

namespace s21 {
class Opz_calculator {

 public:
  static const int kSize = 1000;
  Opz_calculator();
  void AddX(std::string x);
  void CalculateExpression(std::queue<Element>& expression);
  void CalculateYforGrath(const std::queue<Element>& expression, double x_min, double step_x);
  double GetCalculatedResult();
  std::array<double, kSize> GetYdata();
  double GetLastResult();
  void Clean();

 private:
  double calculation_result_;
  std::stack<Element> numbers_stack_;
  double x_variable_;
  std::array<double, 1000> y_coordinates_;

  double CalculateOperation(const Element& operation);
  double UnaryOperation(const Element& operation);
  double BinaryOperation(const Element& operation);
};
}  // namespace s21
#endif  // SRC_MODEL_OPZ_CALCULATOR_H_
