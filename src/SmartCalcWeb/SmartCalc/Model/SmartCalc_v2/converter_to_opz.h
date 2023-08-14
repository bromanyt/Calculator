#ifndef SRC_MODEL_CONVERTER_TO_OPZ_H_
#define SRC_MODEL_CONVERTER_TO_OPZ_H_
#include <queue>
#include <stack>
#include "element.h"

namespace s21 {
class Converter {
 public:
  Converter();
  void ConvertToOpz(std::queue<Element>& expression);
  std::queue<Element> GetOpzExpression();
  void Clean();

 private:
  std::queue<Element> opz_expression_;
  std::queue<Element> expression_;
  std::stack<Element> temp_;

  void MoveFromBrackets();
  void PriorityMoveOperators(const Element& element);
};
}  // namespace s21
#endif  // SRC_MODEL_CONVERTER_TO_OPZ_H_
