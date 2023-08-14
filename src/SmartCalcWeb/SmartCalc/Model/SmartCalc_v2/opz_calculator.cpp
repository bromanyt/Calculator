#include <cmath>
#include "opz_calculator.h"

s21::Opz_calculator::Opz_calculator() : calculation_result_(0.0), x_variable_(0.0) {
}

void s21::Opz_calculator::CalculateExpression(std::queue<Element>& expression) {
  while (expression.size() > 0) {
    auto &current_element = expression.front();
    if (current_element == Priority::kNumber) {
      numbers_stack_.push(current_element);
    } else {
      auto result = Element(CalculateOperation(current_element));
      numbers_stack_.push(result);
    }
    expression.pop();
  }
  calculation_result_ = numbers_stack_.top().GetValue();
}

double s21::Opz_calculator::CalculateOperation(const Element& operation) {
  double result = 0.0;
  if (*operation >= s21::ElementType::kSin) {
    result = UnaryOperation(operation);
  } else {
    result = BinaryOperation(operation);
  }
return result;
}

double s21::Opz_calculator::UnaryOperation(const Element& operation) {
  double result = 0.0;
  auto& element = numbers_stack_.top();
  auto number = element.IsXvariable() ? x_variable_ : element.GetValue();
  numbers_stack_.pop();
  switch (*operation) {
    case (s21::ElementType::kSin) :
      result = sin(number);
      break;
    case (s21::ElementType::kCos) :
      result = cos(number);
      break;
    case (s21::ElementType::kTan) :
      result = tan(number);
      break;
    case (s21::ElementType::kAsin) :
      result = asin(number);
      break;
    case (s21::ElementType::kAcos) :
      result = acos(number);
      break;
    case (s21::ElementType::kAtan) :
      result = atan(number);
      break;
    case (s21::ElementType::kLog) :
      result = log10f(number);
      break;
    case (s21::ElementType::kLn) :
      result = log(number);
      break;
    case (s21::ElementType::kSqrt) :
      result = sqrt(number);
      break;
    default :
      break;
  }
return result;
}

double s21::Opz_calculator::BinaryOperation(const Element& operation) {
  double result = 0.0;
  auto& element = numbers_stack_.top();
  auto second_number = element.IsXvariable() ? x_variable_ : element.GetValue();
  numbers_stack_.pop();
  auto& element2 = numbers_stack_.top();
  auto first_number = element2.IsXvariable() ? x_variable_ : element2.GetValue();
  numbers_stack_.pop();

switch (*operation) {
  case s21::ElementType::kMinus :
    result = first_number - second_number;
    break;
  case s21::ElementType::kPlus :
    result = first_number + second_number;
    break;
  case s21::ElementType::kMultiply :
    result = first_number * second_number;
    break;
  case s21::ElementType::kDivision :
    result = first_number / second_number;
    break;
  case s21::ElementType::kMod :
    result = fmod(first_number, second_number);
    break;
  case s21::ElementType::kExponent :
    result = pow(first_number, second_number);
    break;
  default :
    break;
}
return result;
}

void s21::Opz_calculator::AddX(std::string x) {
  x_variable_ = std::stod(x);
}

double s21::Opz_calculator::GetCalculatedResult() {
  return calculation_result_;
}

void s21::Opz_calculator::Clean() {
  numbers_stack_ = { };
}

void s21::Opz_calculator::CalculateYforGrath(const std::queue<Element>& expression,
                                            double x_min, double step_x) {
  std::queue<Element> temp {expression};
  double x = x_min;
  for (int s = 0; s < 1000; s++, x += step_x) {
    if (s == 0 && x_min >= 0) x_variable_ = 0;
    else 
    x_variable_ = x;
    CalculateExpression(temp);
    temp = expression;
    y_coordinates_[s] = calculation_result_;
  }
}

std::array<double, 1000> s21::Opz_calculator::GetYdata() {
  return y_coordinates_;
}
