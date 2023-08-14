#include "converter_to_opz.h"

s21::Converter::Converter() {}

void s21::Converter::ConvertToOpz(std::queue<s21::Element>& expression) {
  while (expression.size() > 0) {
    auto element = expression.front();
    if (element == Priority::kNumber) {
      opz_expression_.push(element);
    } else if (element == Priority::kBracket) {
      if (element == ElementType::kOpenBracket) {
        temp_.push(element);
      } else {
        MoveFromBrackets();
      }
    } else {
      if (temp_.size() == 0 || temp_.top() < element) {
        temp_.push(element);
      } else {
        PriorityMoveOperators(element);
      }
    }
    expression.pop();
  }
  while (temp_.size() > 0) {
    opz_expression_.push(temp_.top());
    temp_.pop();
  }
}

void s21::Converter::MoveFromBrackets() {
  auto stack_element = temp_.top();
  while (stack_element != ElementType::kOpenBracket) {
    opz_expression_.push(stack_element);
    temp_.pop();
    stack_element = temp_.top();
  }
  temp_.pop();
}

void s21::Converter::PriorityMoveOperators(const Element& element) {
  Element& stack_element = temp_.top();
  while (temp_.size() > 0 && stack_element >= element) {
    opz_expression_.push(stack_element);
    temp_.pop();
    if (temp_.size() > 0)
    stack_element = temp_.top();
  }
  temp_.push(element);
}

std::queue<s21::Element> s21::Converter::GetOpzExpression() {
  return opz_expression_;
}

void s21::Converter::Clean() {
  opz_expression_ = {};
  expression_ = {};
  temp_ = {};
}
