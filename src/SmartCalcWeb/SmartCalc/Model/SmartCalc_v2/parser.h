#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_
#include <string>
#include <queue>
#include "element.h"

namespace s21 {
class Parser {
 public:
  Parser();
  std::queue<Element> ParseInputString(const std::string& input_string);
  int SkipNumbers(const std::string& input_string, int current_index);
  int AddNumber(const std::string& input_string, int current_index);
  void AddSingleCharOperator(char ch);
  int AddOperator(const std::string& input_string, int current_index);
  std::string ResetUnary(const std::string& expression);
  void setSign();
  void Clean();

 private:
  ElementType::Type previous_element;
  ElementType::Type current_element;
  std::queue<Element> elements_;
  std::string input_string_;
};
}  // namespace s21
#endif  // SRC_MODEL_PARSER_H_
