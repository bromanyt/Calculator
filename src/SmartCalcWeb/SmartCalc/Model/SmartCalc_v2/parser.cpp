#include <stdlib.h>
#include <sstream>
#include "parser.h"

s21::Parser::Parser() {
  previous_element = s21::ElementType::kNone;
  current_element = s21::ElementType::kNone;
}

std::queue<s21::Element> s21::Parser::ParseInputString(const std::string& input_string) {
  std::string single_char_operator = "-+/*^()";
  std::string expression = ResetUnary(input_string);
  int length = expression.length();
  for (int i = 0; i < length; i++) {
    previous_element = current_element;
    char current_char = expression[i];
    if (std::isdigit(current_char) || current_char == '.' || current_char == 'x') {
      i = AddNumber(expression, i);
    } else if (single_char_operator.find(current_char) != std::string::npos) {
      AddSingleCharOperator(current_char);
    } else {
      i = AddOperator(expression, i);
      if (i == -1) {
        elements_ = {};
        i = length;
      }
    }
  }
  return elements_;
}


int s21::Parser::AddNumber(const std::string& input_string, int current_index) {
  int index = current_index;
  if (input_string[current_index] == 'x') {
    elements_.push(Element(0.0, true));
    current_element = s21::ElementType::kDigital;
  } else {
    double number = std::stod(&input_string[current_index]);
    elements_.push(Element(number));
    current_element = s21::ElementType::kDigital;
    index = SkipNumbers(input_string, current_index);
  }
  return index;
}

int s21::Parser::SkipNumbers(const std::string& input_string, int current_index) {
  int index = current_index;
  while (std::isdigit(
    input_string[index]) || input_string[index] == '.' || input_string[index] == 'E') {
    if (input_string[index] == 'E'
      && (input_string[index + 1] == '-' || input_string[index + 1] == '+')) {
      index++;
    }
    index++;
  }
  return index - 1;
}

void s21::Parser::AddSingleCharOperator(char ch) {
  switch (ch) {
    case '-' :
      setSign();
      elements_.push(Element(s21::ElementType::kMinus));
      current_element = s21::ElementType::kMinus;
      break;
    case '+' :
      setSign();
      elements_.push(Element(s21::ElementType::kPlus));
      current_element = s21::ElementType::kPlus;
      break;
    case '/' :
      elements_.push(Element(s21::ElementType::kDivision));
      current_element = s21::ElementType::kDivision;
      break;
    case '*' :
      elements_.push(Element(s21::ElementType::kMultiply));
      current_element = s21::ElementType::kMultiply;
      break;
    case '^' :
      elements_.push(Element(s21::ElementType::kExponent));
      current_element = s21::ElementType::kExponent;
      break;
    case '(' :
      elements_.push(Element(s21::ElementType::kOpenBracket));
      current_element = s21::ElementType::kOpenBracket;
      break;
    case ')' :
      elements_.push(Element(s21::ElementType::kCloseBracket));
      current_element = s21::ElementType::kCloseBracket;
  }
}

void s21::Parser::setSign() {
  if (previous_element == s21::ElementType::kOpenBracket || previous_element == s21::ElementType::kNone ||
      current_element == s21::ElementType::kMinus || current_element == s21::ElementType::kPlus) {
      elements_.push(Element(0.0));
  }
}

int s21::Parser::AddOperator(const std::string& input_string, int current_index) {
  long unsigned int index = current_index;
  if (input_string.find("cos") == index) {
    elements_.push(Element(s21::ElementType::kCos));
    current_element = s21::ElementType::kCos;
    index += 2;
  } else if (input_string.find("sin") == index) {
    elements_.push(Element(s21::ElementType::kSin));
    current_element = s21::ElementType::kSin;
    index += 2;
  } else if (input_string.find("mod") == index) {
    elements_.push(Element(s21::ElementType::kMod));
    current_element = s21::ElementType::kMod;
    index += 2;
  } else if (input_string.find("tan") == index) {
    elements_.push(Element(s21::ElementType::kTan));
    current_element = s21::ElementType::kTan;
    index += 2;
  } else if (input_string.find("log") == index) {
    elements_.push(Element(s21::ElementType::kLog));
    current_element = s21::ElementType::kLog;
    index += 2;
  } else if (input_string.find("ln") == index) {
    elements_.push(Element(s21::ElementType::kLn));
    current_element = s21::ElementType::kLn;
    ++index;
  } else if (input_string.find("sqrt") == index) {
    elements_.push(Element(s21::ElementType::kSqrt));
    current_element = s21::ElementType::kSqrt;
    index += 3;
  } else if (input_string.find("asin") == index) {
    elements_.push(Element(s21::ElementType::kAsin));
    current_element = s21::ElementType::kAsin;
    index += 3;
  } else if (input_string.find("acos") == index) {
    elements_.push(Element(s21::ElementType::kAcos));
    current_element = s21::ElementType::kAcos;
    index += 3;
  } else if (input_string.find("atan") == index) {
    elements_.push(Element(s21::ElementType::kAtan));
    current_element = s21::ElementType::kAtan;
    index += 3;
  } else {
    index = -1;
  }
return index;
}

std::string s21::Parser::ResetUnary(const std::string& expression) {
    std::stringstream result;
    char previous = '\0';
    for (int i = 0; i < expression.length(); ++i) {
        char current = expression[i];
        if ((current == '-' || current == '+') && (previous == '-' || previous == '+')) {
            if ((current == '-' && previous == '+') || (current == '+' && previous == '-')) {
                result.seekp(-1, std::ios::end);
                result << '-';
                previous = '-';
            }
            else if ((current == '-' && previous == '-') || (current == '+' && previous == '+')) {
                result.seekp(-1, std::ios::end);
                result << '+';
                previous = '+';
            }
        } else {
            previous = current;
            result << current;
        }
    }
    return result.str();
}


void s21::Parser::Clean() {
  elements_ = {};
  previous_element = s21::ElementType::kNone;
  current_element = s21::ElementType::kNone;
}

