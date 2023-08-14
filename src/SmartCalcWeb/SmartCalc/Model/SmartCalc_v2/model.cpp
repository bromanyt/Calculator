#include "model.h"

void s21::Model::Calculator(std::string expression) {
  validator_.SetExpression(expression);
  if (validator_.Validate()) {
    auto elements_list = parser_.ParseInputString(expression);
    converter_.ConvertToOpz(elements_list);
    auto result = converter_.GetOpzExpression();
    opz_calculator_.CalculateExpression(result);
    Clean();
  }
}

void s21::Model::Clean() {
  opz_calculator_.Clean();
  converter_.Clean();
  parser_.Clean();
}

void s21::Model::CalculatorWithX(const std::string& expression, std::string x) {
  validator_.SetExpression(x);
  if (validator_.Validate()) {
    opz_calculator_.AddX(x);
    Calculator(expression);
  }
}

void s21::Model::CalculateYvalues(std::string expression, double x_min, double step_x) {
  validator_.SetExpression(expression);
  if (validator_.Validate()) {
    auto elements_list = parser_.ParseInputString(expression);
    converter_.ConvertToOpz(elements_list);
    auto result = converter_.GetOpzExpression();
    opz_calculator_.CalculateYforGrath(result, x_min, step_x);
    Clean();
  }
}

s21::Model::Model() {
}

std::array<double, 1000> s21::Model::GetYcoorinates() {
  return opz_calculator_.GetYdata();
}

double s21::Model::GetResult() {
  return opz_calculator_.GetCalculatedResult();
}

bool s21::Model::IsExpressionValid() {
  return validator_.IsValid();
}
