#include "validator.h"
#include <regex>

s21::Validator::Validator() : isCorrect(true) {
}

s21::Validator::Validator(const std::string& expression) :
                          expression_(expression),
                          isCorrect(true) {
}

void s21::Validator::SetExpression(const std::string& expression) {
  expression_ = expression;
}

bool s21::Validator::Validate() {
  if (expression_.length() == 0) {
    isCorrect = false;
  }
  if (isCorrect) {
    OperatorsChecker();
  }
  if (isCorrect) {
    BracketChecker();
  }
  return isCorrect;
}

void s21::Validator::OperatorsChecker() {
  static const std::regex reg(
    "[^0-9x)]+[*][(0-9x]+|"
    "[^0-9x)]+[*][^0-9x]+|"
    "[^0-9x)]+[\\^][(0-9x]+|"
    "[^0-9x)]+[\\^][^0-9x]+|"
    "[0-9]+[.]{2,}|"
    "[^0-9]+[.]+|"
    "([0-9]+[.]+[0-9x]+[.])|"
    "[0-9]+[.][^0-9x]|"
    "[^0-9]+[.]|"
    "(\\(\\))|[0-9x][(]|^E|E$|"
    "[^0-9x)]+[\\/]|[+][)]|"
    "^[*\\/^]|[^0-9][E]|[E][^-+0-9]|"
    "[-*\\/+]$|^[.]|[(][^(0-9x][)]|"
    "[^0-9x()+-E][-+]|[^0-9x)][*/^]|"
    "[^)0-9x](mod)|(mod)[^0-9x(]|"
    "^(mod)|(mod)$|[0-9E.]{15,}|"
    "[x]{2,}|[0-9)][x]|[x][(0-9]|"
    "E[+-]{2,}[0-9]|"
    "^[)]|[(]$|[^a-wyz(*\\/+-^][(]|[)][^)\\^*\\/+-]");
  isCorrect = !regex_search(expression_, reg);
}

void s21::Validator::BracketChecker() {
  int open_br = 0;
  int len = expression_.size();
  for (int i = 0; i < len && isCorrect; i++) {
    char ch = expression_[i];
    if (ch == '(') {
      open_br++;
    } else if (ch == ')') {
      open_br--;
      if (open_br < 0) {
        isCorrect = false;
      }
    }
  }
  if (open_br > 0) {
    isCorrect = false;
  }
}

bool s21::Validator::IsValid() {
  return isCorrect;
}
