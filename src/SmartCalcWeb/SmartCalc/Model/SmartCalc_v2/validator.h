#ifndef SRC_MODEL_VALIDATOR_H_
#define SRC_MODEL_VALIDATOR_H_
#include <string>

namespace s21 {
class Validator {
 public:
  Validator();
  explicit Validator(const std::string& expression);
  bool Validate();
  void SetExpression(const std::string& expression);
  bool IsValid();
 private:
  std::string expression_;
  bool isCorrect;
  void OperatorsChecker();
  void BracketChecker();
};
}  // namespace s21
#endif  // SRC_MODEL_VALIDATOR_H_
