#include "model.h"
#include <cstring>

extern "C" s21::Model* CreateCalculator() {
    s21::Model* calc = new s21::Model();
    return calc;
}

extern "C" void Calculate(s21::Model* model, char* expression) {
  if (model != nullptr)
    model->Calculator(std::string(expression));
}

extern "C" void CalculateWithX(s21::Model* model, char* expression, char* x) {
  if (model != nullptr)
    model->CalculatorWithX(expression, x);
}

extern "C" bool IsExpressionCorrect(s21::Model* model) {
  if (model == nullptr) return false;
  return model->IsExpressionValid();
}

extern "C" double GetAnswer(s21::Model* model) {
  if (model == nullptr) return 0;
  return model->GetResult();
}

extern "C" void FreeCalculator(s21::Model* model) {
  if (model != nullptr) {
    delete model;
    model = nullptr;
  }
}

extern "C" void CalculateCoordinates(s21::Model* model, char* expression, double x_min, double step_x) {
  if (model != nullptr)
    model->CalculateYvalues(expression, x_min, step_x);
}

extern "C" void GetArrayOfCoordinateY(s21::Model* model, long* len, double **data)
{
  auto coordinates = model->GetYcoorinates();
  *len = coordinates.size();
  auto size = (*len)*sizeof(double);
  *data = static_cast<double*>(malloc(size));
  memcpy(*data, coordinates.data(), size);
}
