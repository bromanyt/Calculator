#ifndef SRC_MODEL_ELEMENT_H_
#define SRC_MODEL_ELEMENT_H_

#include <string>
namespace s21 {
namespace ElementType {
enum Type {
  kDigital,
  kOpenBracket,
  kCloseBracket,
  kMinus,
  kPlus,
  kMultiply,
  kDivision,
  kMod,
  kExponent,
  kSin,
  kCos,
  kTan,
  kAsin,
  kAcos,
  kAtan,
  kLog,
  kLn,
  kSqrt,
  kNone
};
}  // namespace ElementType

namespace Priority {
enum Group {
  kNumber,
  kBracket,
  kPlusMinus,
  kOperator,
  kFunction
};
}  // namespace Priority

class Element {
 public:
  explicit Element(ElementType::Type type);
  explicit Element(double value, bool isXvariable = false);
  virtual ~Element();
  Priority::Group Prioritize(ElementType::Type elem_type);
  double GetValue() const;
  bool IsXvariable() const;

  bool operator==(const Element& other) const;
  bool operator!=(const Element& other) const;
  bool operator>(const Element& other) const;
  bool operator<(const Element& other) const;
  bool operator>=(const Element& other) const;
  bool operator<=(const Element& other) const;

  bool operator==(const ElementType::Type type) const;
  bool operator!=(const ElementType::Type type) const;

  bool operator==(const Priority::Group priority) const;
  bool operator!=(const Priority::Group priority) const;

  ElementType::Type operator*() const;

 private:
  Priority::Group priority_;
  ElementType::Type type_;
  double value_;
  bool isXvariable_;
};
}  // namespace s21
#endif  // SRC_MODEL_ELEMENT_H_
