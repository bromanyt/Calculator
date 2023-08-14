#include "gtest/gtest.h"
#include "element.h"
#include "opz_calculator.h"
#include "converter_to_opz.h"
#include "parser.h"
#include "validator.h"
#include "model.h"
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <cmath>

constexpr double epsilon = 1e-7;
s21::Model sc;

TEST(Calculator, validator_incorrect) {
  s21::Validator validator;
  std::string negative[] = {
    "2+mod1",
    "2-mod1",
    "2*mod1",
    "2/mod1",
    "2modmod1",
    "(mod2)",
    "(*mod3)",
    "mod4",
    "(2mod)",
    "(mod2mod3)",
    "(mod)",
    "(^)",
    "(*2)",
    "()",
    "(*/)",
    "(-+*/^)",
    "(.)",
    "sin()",
    "3+4()+cos",
    "2+/1",
    "2+*1",
    "2-*1",
    "2-/1",
    "2--/1",
    "2++**1",
    "2+*-1",
    "2*/1",
    "2/*1",
    "2**1",
    "2//1",
    "(*1+3)*2",
    ".2+3",
    "2..3+1",
    "23.39.94+1",
    "56.78.3455.23",
    "2.3.4+1",
    "...345+3",
    "2.+3",
    "(1+)*2",
    "*+",
    "(1+(1+))*3",
    "sin(2**3)",
    "(1+)*2",
    "(*1+3)*2",
    ".2+3",
    "2.+3",
    "2..3+1",
    "(23+(34-",
    "))24+4((",
    ")10-2(",
    "(23-4(24)(",
    "58*",
    "23+45-",
    "857*(32-45)*",
    "7*",
    "*8",
    "**8",
    "35*sin23)",
    "11-cos34+5)",
    "23(4+1)",
    "4+2(41-3)",
    "E23+4",
    "34-23E",
    "8+.E34-1",
    "73E.*12",
    "23E-E3+14",
    "87EE5*3",
    "8E6E32-11"
    };

  for (int i = 0; i < 67; ++i) {
    validator.SetExpression(negative[i]);
    EXPECT_FALSE(validator.Validate()) << negative[i];
  }
}

TEST(Calculator, simpleOperations) {
  sc.Calculator("99+101");
  EXPECT_TRUE((99+101 - sc.GetResult()) < epsilon);
  sc.Calculator("0.345-0.301");
  EXPECT_TRUE((0.345-0.301 - sc.GetResult()) < epsilon);
  sc.Calculator("1.1234567*320");
  EXPECT_TRUE((1.1234567*320 - sc.GetResult()) < epsilon);
  sc.Calculator("734552/2");
  EXPECT_TRUE((734552/2 - sc.GetResult()) < epsilon);
  sc.Calculator("4^3");
  EXPECT_TRUE((pow(4, 3) - sc.GetResult()) < epsilon);
  sc.Calculator("7*2^2");
  EXPECT_TRUE((7*pow(2, 2) - sc.GetResult()) < epsilon);
  sc.Calculator("7mod3");
  EXPECT_TRUE((7%3 - sc.GetResult()) < epsilon);
  sc.Calculator("sqrt(724)");
  EXPECT_TRUE((sqrt(724) - sc.GetResult()) < epsilon);
  sc.Calculator("log(34)");
  EXPECT_TRUE((log10f(34) - sc.GetResult()) < epsilon);
  sc.Calculator("ln(34)");
  EXPECT_TRUE((log(34) - sc.GetResult()) < epsilon);
  sc.Calculator("0.000004+0.000006");
  EXPECT_TRUE((0.000004+0.000006 - sc.GetResult()) < epsilon);
}

TEST(Calculator, numberWithE) {
  sc.Calculator("2.3E5*2");
  EXPECT_TRUE((2.3E5*2 - sc.GetResult()) < epsilon);
  sc.Calculator("2345E4/100");
  EXPECT_TRUE((2345E4/100 - sc.GetResult()) < epsilon);
  sc.Calculator("7302E-4*1000");
  EXPECT_TRUE((7302E-4*1000 - sc.GetResult()) < epsilon);
  sc.Calculator("0.00009E7*23");
  EXPECT_TRUE((0.00009E7*23 - sc.GetResult()) < epsilon);
  sc.Calculator("5000000E-7/2");
  EXPECT_TRUE((5000000E-7/2 - sc.GetResult()) < epsilon);
  sc.Calculator("sin(500E-2)+2344");
  EXPECT_TRUE((sin(500E-2)+2344 - sc.GetResult()) < epsilon);
}

TEST(Calculator, simpleTtigonometric) {
  sc.Calculator("sin(240)");
  EXPECT_TRUE((sin(240) - sc.GetResult()) < epsilon);
  sc.Calculator("cos(43456)");
  EXPECT_TRUE((cos(43456) - sc.GetResult()) < epsilon);
  sc.Calculator("tan(999)");
  EXPECT_TRUE((tan(999) - sc.GetResult()) < epsilon);
  sc.Calculator("asin(0.5)");
  EXPECT_TRUE((fabs(asin(0.5) - sc.GetResult())) < epsilon);
  sc.Calculator("acos(0.5)");
  EXPECT_TRUE((fabs(acos(0.5) - sc.GetResult())) < epsilon);
  sc.Calculator("atan(162)");
  EXPECT_TRUE((atan(162) - sc.GetResult()) < epsilon);
}

TEST(Calculator, brackets) {
  sc.Calculator("(0.456*3)+0.59");
  EXPECT_TRUE(((0.456*3)+0.59 - sc.GetResult()) < epsilon);
  sc.Calculator("(794+(93/2)-45)");
  EXPECT_TRUE(((794+(93/2)-45) - sc.GetResult()) < epsilon);
  sc.Calculator("(934-(76*3)+23^3*2)");
  EXPECT_TRUE(((934-(76*3)+pow(23, 3)*2) - sc.GetResult()) < epsilon);
  sc.Calculator("(3+((45+3)-7))*3");
  EXPECT_TRUE(((3+((45+3)-7))*3 - sc.GetResult()) < epsilon);
  sc.Calculator("(sin(30))-(84-23*2)");
  EXPECT_TRUE(((sin(30))-(84-23*2) - sc.GetResult()) < epsilon);
}

TEST(Calculator, combination) {
  sc.Calculator("tan(sin(45)-cos(90))");
  EXPECT_TRUE((tan(sin(45)-cos(90)) - sc.GetResult()) < epsilon);
  sc.Calculator("845-(34+98-4^2)*(3857-3855)-(0.34/3.1)+(sin(60))");
  EXPECT_TRUE((845-(34+98-pow(4, 2))*(3857-3855)-(0.34/3.1)+(sin(60)) - sc.GetResult()) < epsilon);
  sc.Calculator("((394-sin(345))+(345/0.23)/2-12mod5)*7");
  EXPECT_TRUE(((((394-sin(345))+(345/0.23)/2-12%5)*7) - sc.GetResult()) < epsilon);
  sc.Calculator("8456*3-(atan(90)+12^2-839.35*(-34))");
  EXPECT_TRUE(((8456*3-(atan(90)+pow(12, 2)-839.35*(-34))) - sc.GetResult()) < epsilon);
}

TEST(Calculator, negative) {
  sc.Calculator("-34+20");
  EXPECT_TRUE(((-34+20) - sc.GetResult()) < epsilon);
  sc.Calculator("(-0.23+2)*71");
  EXPECT_TRUE((((-0.23+2)*71) - sc.GetResult()) < epsilon);
  sc.Calculator("-+34+20");
  EXPECT_TRUE(((-34+20) - sc.GetResult()) < epsilon);
  sc.Calculator("25/(-cos(3))");
  EXPECT_TRUE(((25/-cos(3)) - sc.GetResult()) < epsilon);
  sc.Calculator("730+--+29");
  EXPECT_TRUE(((730+29) - sc.GetResult()) < epsilon);
  sc.Calculator("00.98+00000.02");
  EXPECT_TRUE(((00.98+00000.02) - sc.GetResult()) < epsilon);
  sc.Calculator("-cos(20)+-sin(34)");
  EXPECT_TRUE(((-cos(20)+-sin(34)) - sc.GetResult()) < epsilon);
  sc.Calculator("42^(-2)");
  EXPECT_TRUE(((42^(-2))- sc.GetResult()) < epsilon);
}

TEST(Calculator, yCoordinates) {
  double total_x = fabs(-10) + fabs(10);
  double step_x = total_x / 1000;

  sc.CalculateYvalues("sin(x)", -10, step_x);
  auto list = sc.GetYcoorinates();
  double num = -10 - step_x;
  for (auto d : list) {
    EXPECT_TRUE((sin(num + step_x) - d) < epsilon);
    num += step_x;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
