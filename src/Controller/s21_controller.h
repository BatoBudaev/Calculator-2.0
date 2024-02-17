#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include <QObject>

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  explicit Controller(QObject *parent = nullptr);

 public slots:
  double onExpressionEntered(const QString &expression, double x);

 signals:
  void resultReady(double result);
  void errorOccurred(const QString &errorMessage);
};
}  // namespace s21
#endif  // S21_CONTROLLER_H
