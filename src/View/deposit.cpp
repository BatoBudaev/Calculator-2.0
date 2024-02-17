#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QDialog(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  ui->dateEdit->setDisplayFormat("dd.MM.yyyy");
  ui->dateEdit->setDate(QDate::currentDate());

  QCalendarWidget *calendar = new QCalendarWidget;
  calendar->setFirstDayOfWeek(Qt::Monday);

  ui->dateEdit->setCalendarWidget(calendar);
  ui->depositLine->setVisible(false);
  ui->withdrawalsLine->setVisible(false);

  QIntValidator *validator1 = new QIntValidator(0, 100000000.0);
  ui->depositSumLine->setValidator(validator1);
  QIntValidator *validator2 = new QIntValidator(0, 99);
  ui->depositTermLine->setValidator(validator2);
  QDoubleValidator *validator3 = new QDoubleValidator(0.0, 1000.0, 2, this);
  ui->percentLine->setValidator(validator3);
  QDoubleValidator *validator4 = new QDoubleValidator(0.0, 100.0, 2, this);
  ui->taxLine->setValidator(validator4);
  QDoubleValidator *validator5 = new QDoubleValidator(0, 10000000, 2);
  ui->depositLine->setValidator(validator5);
  ui->withdrawalsLine->setValidator(validator5);
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_radioButton_1_clicked() {
  ui->periodComboBox->removeItem(3);
  ui->periodComboBox->setCurrentIndex(0);
}

void Deposit::on_radioButton_2_clicked() {
  if (ui->periodComboBox->count() == 3) {
    ui->periodComboBox->addItem("В конце срока");
  }

  ui->periodComboBox->setCurrentIndex(3);
}

void Deposit::on_depositComboBox_currentIndexChanged(int index) {
  if (index == 0) {
    ui->depositLine->setVisible(false);
    ui->depositLine->setText("0");
  } else {
    ui->depositLine->setVisible(true);
    ui->depositLine->setText("10000");
  }
}

void Deposit::on_withdrawalsComboBox_currentIndexChanged(int index) {
  if (index == 0) {
    ui->withdrawalsLine->setVisible(false);
    ui->withdrawalsLine->setText("0");
  } else {
    ui->withdrawalsLine->setVisible(true);
    ui->withdrawalsLine->setText("10000");
  }
}

void Deposit::on_pushButton_clicked() {
  ui->percentChargesLabel->clear();
  ui->depositLabel->clear();
  ui->withdrawalsLabel->clear();
  ui->taxLabel->clear();
  ui->incomeLabel->clear();
  ui->balanceLabel->clear();
  ui->tableView->clearSpans();

  getDeposit();
}

void Deposit::getDeposit() {
  double initialDeposit = ui->depositSumLine->text().toDouble();
  int months = ui->depositTermLine->text().toInt();
  long double balance = 0;
  double interestRate = ui->percentLine->text().toDouble();
  double taxRate = ui->taxLine->text().toDouble();
  int capitalizationPeriod = 1;
  int paymentsPeriod = 0;
  int day = ui->dateEdit->date().day();
  int month = ui->dateEdit->date().month();
  int year = ui->dateEdit->date().year();

  if (!ui->comboBox->currentText().compare("Лет")) {
    months *= 12;
  }

  Data results[months];
  int periodComboBoxIndex = ui->periodComboBox->currentIndex();

  if (periodComboBoxIndex == 0) {
    capitalizationPeriod = 1;
    paymentsPeriod = 1;
  } else if (periodComboBoxIndex == 1) {
    capitalizationPeriod = 6;
    paymentsPeriod = 6;
  } else if (periodComboBoxIndex == 2) {
    capitalizationPeriod = 12;
    paymentsPeriod = 12;
  } else {
    capitalizationPeriod = 0;
    paymentsPeriod = months;
  }

  if (ui->radioButton_2->isChecked()) {
    capitalizationPeriod = 0;
  }

  int depositPeriodIndex = ui->depositComboBox->currentIndex();
  int withdrawalsPeriodIndex = ui->withdrawalsComboBox->currentIndex();
  double *deposits;
  double *withdrawals;

  if (depositPeriodIndex == 0) {
    deposits = bank.generateDeposits(0, 1, months);
  } else if (depositPeriodIndex == 1) {
    deposits =
        bank.generateDeposits(ui->depositLine->text().toDouble(), 1, months);
  } else if (depositPeriodIndex == 2) {
    deposits =
        bank.generateDeposits(ui->depositLine->text().toDouble(), 6, months);
  } else {
    deposits =
        bank.generateDeposits(ui->depositLine->text().toDouble(), 12, months);
  }

  if (withdrawalsPeriodIndex == 0) {
    withdrawals = bank.generateDeposits(0, 1, months);
  } else if (withdrawalsPeriodIndex == 1) {
    withdrawals = bank.generateDeposits(ui->withdrawalsLine->text().toDouble(),
                                        1, months);
  } else if (withdrawalsPeriodIndex == 2) {
    withdrawals = bank.generateDeposits(ui->withdrawalsLine->text().toDouble(),
                                        6, months);
  } else {
    withdrawals = bank.generateDeposits(ui->withdrawalsLine->text().toDouble(),
                                        12, months);
  }

  balance = bank.calculateDepositEarnings(
      initialDeposit, months, interestRate, taxRate, capitalizationPeriod,
      paymentsPeriod, deposits, withdrawals, day, month, year, results);

  long double totalInterest = 0.0;
  long double totalTax = 0.0;
  long double depositsSum = 0.0;
  long double withdrawalsSum = 0.0;

  for (int i = 0; i < months; i++) {
    totalInterest += results[i].interest;
    totalTax += results[i].tax;
    depositsSum += results[i].deposits;
    withdrawalsSum += results[i].withdrawals;
  }

  char formattedPercent[20];
  sprintf(formattedPercent, "%.2Lf", totalInterest);

  char formattedDeposit[20];
  sprintf(formattedDeposit, "%.Lf", depositsSum);

  char formattedWithdrawal[20];
  sprintf(formattedWithdrawal, "%.Lf", withdrawalsSum);

  char formattedTax[20];
  sprintf(formattedTax, "%.2Lf", totalTax);

  char formattedIncome[20];
  sprintf(formattedIncome, "%.2Lf", totalInterest - totalTax);

  char formattedBalance[20];
  sprintf(formattedBalance, "%.2Lf", balance);

  ui->percentChargesLabel->setText(formattedPercent);
  ui->depositLabel->setText(formattedDeposit);
  ui->withdrawalsLabel->setText(formattedWithdrawal);
  ui->taxLabel->setText(formattedTax);
  ui->incomeLabel->setText(formattedIncome);
  ui->balanceLabel->setText(formattedBalance);

  QStandardItemModel *model = new QStandardItemModel(this);
  model->setColumnCount(5);
  model->setHorizontalHeaderLabels(QStringList() << "Проценты"
                                                 << "Налог"
                                                 << "Пополнение"
                                                 << "Снятие"
                                                 << "Сумма");

  for (int i = 0; i < months; ++i) {
    if (results[i].interest == 0 && results[i].deposits == 0 &&
        results[i].withdrawals == 0) {
      continue;
    }

    QList<QStandardItem *> row;
    char formatted1[20];
    sprintf(formatted1, "%.2Lf", results[i].interest);
    char formatted2[20];
    sprintf(formatted2, "%.2Lf", results[i].tax);
    char formatted3[20];
    sprintf(formatted3, "%.Lf", results[i].deposits);
    char formatted4[20];
    sprintf(formatted4, "%.Lf", results[i].withdrawals);
    char formatted5[20];
    sprintf(formatted5, "%.2Lf", results[i].sum);

    row << new QStandardItem(formatted1) << new QStandardItem(formatted2)
        << new QStandardItem(formatted3) << new QStandardItem(formatted4)
        << new QStandardItem(formatted5);
    model->appendRow(row);
  }

  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();

  free(deposits);
  free(withdrawals);
}
