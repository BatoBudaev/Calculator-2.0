#ifndef CREDIT_H
#define CREDIT_H

#include <../Model/s21_bank.h>

#include <QDialog>

namespace Ui {
class Credit;
}

using namespace s21;

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();
  void getAnnuity();
  void getDifferentiated();

 private:
  Ui::Credit *ui;
  BankModel bank;
};

#endif  // CREDIT_H
