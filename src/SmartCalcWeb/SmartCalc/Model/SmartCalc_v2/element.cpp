#include "element.h"

s21::Element::Element(s21::ElementType::Type elem_type) :
                      priority_(Prioritize(elem_type)),
                      type_(elem_type),
                      value_(0.0),
                      isXvariable_(false) { }

s21::Element::Element(double value, bool isXvariable) :
                      priority_(s21::Priority::kNumber),
                      type_(s21::ElementType::kDigital),
                      value_(value),
                      isXvariable_(isXvariable) { }

s21::Element::~Element() { }

s21::Priority::Group s21::Element::Prioritize(s21::ElementType::Type elem_type) {
  s21::Priority::Group result = s21::Priority::kFunction;
  switch (elem_type) {
    case s21::ElementType::kDigital :
      result = s21::Priority::kNumber;
      break;
    case s21::ElementType::kOpenBracket :
    case s21::ElementType::kCloseBracket :
      result = s21::Priority::kBracket;
      break;
    case s21::ElementType::kMinus :
    case s21::ElementType::kPlus :
      result = s21::Priority::kPlusMinus;
      break;
    case s21::ElementType::kMultiply :
    case s21::ElementType::kDivision :
    case s21::ElementType::kMod :
      result = s21::Priority::kOperator;
    default :
      break;
  }
  return result;
}

double s21::Element::GetValue() const {
  return value_;
}

bool s21::Element::IsXvariable() const {
  return isXvariable_;
}

s21::ElementType::Type s21::Element::operator*() const {
  return type_;
}

bool s21::Element::operator==(const Element& other) const {
  return priority_ == other.priority_;
}

bool s21::Element::operator!=(const Element& other) const {
  return priority_ != other.priority_;
}

bool s21::Element::operator>(const Element& other) const {
  return priority_ > other.priority_;
}

bool s21::Element::operator<(const Element& other) const {
  return priority_ < other.priority_;
}

bool s21::Element::operator>=(const Element& other) const {
  return priority_ >= other.priority_;
}

bool s21::Element::operator<=(const Element& other) const {
  return priority_ <= other.priority_;
}

bool s21::Element::operator==(const s21::ElementType::Type type) const {
  return type_ == type;
}

bool s21::Element::operator!=(const s21::ElementType::Type type) const {
  return type_ != type;
}

bool s21::Element::operator==(const s21::Priority::Group priority) const {
  return priority_ == priority;
}

bool s21::Element::operator!=(const s21::Priority::Group priority) const {
  return priority_ != priority;
}
