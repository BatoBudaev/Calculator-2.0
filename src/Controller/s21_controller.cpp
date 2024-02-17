#include "s21_controller.h"

#include "../Model/s21_model.h"

namespace s21 {
Controller::Controller(QObject *parent) : QObject(parent) {}

double Controller::onExpressionEntered(const QString &expression, double x) {
  Model model;
  model.processExpression(expression.toStdString().c_str(), x);

  if (model.isNoError()) {
    emit resultReady(model.getResult());
  } else {
    emit errorOccurred("ERROR");
  }

  return model.getResult();
}
}  // namespace s21
