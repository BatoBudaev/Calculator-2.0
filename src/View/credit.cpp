#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);

  QIntValidator *validator1 = new QIntValidator(0, 10000000.0);
  ui->creditSumLine->setValidator(validator1);
  QIntValidator *validator2 = new QIntValidator(0, 99);
  ui->creditTermLine->setValidator(validator2);
  QDoubleValidator *validator3 = new QDoubleValidator(0, 1000, 7);
  ui->percentLine->setValidator(validator3);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  ui->monthlyPaymentLabel->clear();
  ui->percentChargesLabel->clear();
  ui->debtAndPercentLabel->clear();

  if (ui->creditSumLine->text().isEmpty() ||
      ui->creditTermLine->text().isEmpty() ||
      ui->percentLine->text().isEmpty() ||
      ui->creditTermLine->text().toInt() == 0 ||
      ui->percentLine->text().toDouble() == 0) {
    if (ui->creditTermLine->text().toInt() == 0) {
      ui->creditTermLine->clear();
    }

    if (ui->percentLine->text().toDouble() == 0) {
      ui->percentLine->clear();
    }

    return;
  }

  if (ui->radioButton_1->isChecked()) {
    getAnnuity();
  } else if (ui->radioButton_2->isChecked()) {
    getDifferentiated();
  }
}

void Credit::getAnnuity() {
  double creditSum = ui->creditSumLine->text().toDouble();
  int months = ui->creditTermLine->text().toInt();

  if (!ui->comboBox->currentText().compare("Лет")) {
    months *= 12;
  }

  double percent = ui->percentLine->text().toDouble();

  double monthPayment, totalPayment, overpayment;
  monthPayment = bank.calculateAnnuity(creditSum, percent, months);

  totalPayment = monthPayment * months;
  overpayment = bank.calculateOverpayment(totalPayment, creditSum);

  char formattedOverpayment[20];
  sprintf(formattedOverpayment, "%.2lf", overpayment);

  char formattedTotalPayment[20];
  sprintf(formattedTotalPayment, "%.2lf", totalPayment);

  ui->monthlyPaymentLabel->setText(QString::number(monthPayment, 'g', 15));
  ui->percentChargesLabel->setText(formattedOverpayment);
  ui->debtAndPercentLabel->setText(formattedTotalPayment);
}

void Credit::getDifferentiated() {
  double creditSum = ui->creditSumLine->text().toDouble();
  int months = ui->creditTermLine->text().toInt();

  if (!ui->comboBox->currentText().compare("Лет")) {
    months *= 12;
  }

  double percent = ui->percentLine->text().toDouble();

  double totalPayment = 0, overpayment = 0;
  double payments[months];

  for (int month = 1; month <= months; month++) {
    payments[month - 1] =
        bank.calculateDifferentiated(creditSum, percent, months, month);
  }

  for (int i = 0; i < months; i++) {
    totalPayment += payments[i];
    overpayment += payments[i] - creditSum / months;
  }

  char formattedMonthlyPayment[40];
  sprintf(formattedMonthlyPayment, "%.2lf ... %.2lf", payments[0],
          payments[months - 1]);

  char formattedOverpayment[20];
  sprintf(formattedOverpayment, "%.2lf", overpayment);

  char formattedTotalPayment[20];
  sprintf(formattedTotalPayment, "%.2lf", totalPayment);

  ui->monthlyPaymentLabel->setText(formattedMonthlyPayment);
  ui->percentChargesLabel->setText(formattedOverpayment);
  ui->debtAndPercentLabel->setText(formattedTotalPayment);
}
