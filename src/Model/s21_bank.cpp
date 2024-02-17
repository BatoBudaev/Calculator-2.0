#include "s21_bank.h"

namespace s21 {
BankModel::BankModel() {}

BankModel::~BankModel() {}

long double BankModel::calculateAnnuity(double creditSum, double percent,
                                        int months) {
  double monthlyPercent = percent / 12 / 100;
  double numerator = monthlyPercent * pow(1 + monthlyPercent, months);
  double denominator = pow(1 + monthlyPercent, months) - 1;
  double monthPayment = creditSum * (numerator / denominator);

  return monthPayment;
}

long double BankModel::calculateOverpayment(double totalPayment,
                                            double creditSum) {
  return totalPayment - creditSum;
}

long double BankModel::calculateDifferentiated(double creditSum, double percent,
                                               int months, int currentMonth) {
  double monthlyPercent = percent / 12 / 100;
  double basePayment = creditSum / months;
  double remainingBalance = creditSum - basePayment * (currentMonth - 1);
  double interestPayment = remainingBalance * monthlyPercent;

  return basePayment + interestPayment;
}

long double BankModel::calculateInterest(long double balance, double rate,
                                         int days, int daysInYear) {
  return balance * rate / 100 * days / daysInYear;
}

long double BankModel::calculateTax(long double income,
                                    long double untaxedIncome, double taxRate) {
  long double taxableIncome = income - untaxedIncome;
  if (taxableIncome <= 0) {
    return 0.0;
  }
  return taxableIncome * taxRate / 100;
}

int BankModel::getDaysInMonth(int year, int month) {
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return daysInMonth[month - 1];
}

long double s21::BankModel::calculateDepositEarnings(
    double initialDeposit, int months, double interestRate, double taxRate,
    int capitalizationPeriod, int paymentsPeriod, double *deposits,
    double *withdrawals, int startDay, int startMonth, int startYear,
    struct s21::Data *results) {
  long double totalInterest = 0.0;
  long double totalInterestForPeriod = 0.0;
  long double totalTax = 0.0;
  long double totalTaxForPeriod = 0.0;
  long double balance = initialDeposit;
  long double depositsSum = 0;
  long double taxForYear = 0;

  int currentYear = startYear;
  int currentMonth = startMonth;
  int nextYear = 0;
  int nextYearDays = 365;

  if (paymentsPeriod < 1) {
    paymentsPeriod = 1;
  }

  for (int month = 1; month <= months; month++) {
    if (currentMonth > 12) {
      currentMonth -= 12;
      currentYear++;
    }

    int daysInYear = 365;

    if (isLeapYear(currentYear)) {
      daysInYear++;
    }

    int daysInMonth = getDaysInMonth(currentYear, currentMonth);

    long double earnedInterest = 0;

    if (currentMonth == 12) {
      nextYear = currentYear + 1;
      if (isLeapYear(nextYear)) {
        nextYearDays = 366;
      } else {
        nextYearDays = 365;
      }
    }

    if (currentMonth == 12 &&
        (isLeapYear(currentYear) || isLeapYear(nextYear))) {
      int decemberDays = 31 - startDay + 1;
      long double dec =
          calculateInterest(balance, interestRate, decemberDays, daysInYear);
      long double jan = calculateInterest(balance, interestRate,
                                          31 - decemberDays, nextYearDays);
      earnedInterest = dec + jan;
      totalInterestForPeriod += earnedInterest;
      totalInterest += earnedInterest;
    } else {
      earnedInterest =
          calculateInterest(balance, interestRate, daysInMonth, daysInYear);
      totalInterestForPeriod += earnedInterest;
      totalInterest += earnedInterest;
    }

    long double tax = calculateTax(earnedInterest, 0, taxRate);
    totalTaxForPeriod += tax;
    totalTax += tax;

    balance += deposits[month - 1];
    depositsSum += deposits[month - 1];

    if (balance > withdrawals[month - 1]) {
      balance -= withdrawals[month - 1];
    } else {
      withdrawals[month - 1] = 0;
    }

    if (capitalizationPeriod > 0 && month % capitalizationPeriod == 0) {
      balance += totalInterestForPeriod;
      balance -= totalTaxForPeriod;

      results[month - 1].number = month;
      results[month - 1].interest = totalInterestForPeriod;
      results[month - 1].tax = totalTaxForPeriod;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;

      taxForYear += totalTaxForPeriod;
      totalInterestForPeriod = 0;
      totalTaxForPeriod = 0;

    } else if (capitalizationPeriod > 0) {
      results[month - 1].number = month;
      results[month - 1].interest = 0;
      results[month - 1].tax = 0;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;
    }

    if (capitalizationPeriod == 0 && month % paymentsPeriod == 0) {
      results[month - 1].number = month;
      results[month - 1].interest = totalInterestForPeriod;
      results[month - 1].tax = totalTaxForPeriod;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;

      totalInterestForPeriod = 0;
      totalTaxForPeriod = 0;
    } else if (capitalizationPeriod == 0 && paymentsPeriod > 0) {
      results[month - 1].number = month;
      results[month - 1].interest = 0;
      results[month - 1].tax = 0;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;
    }
    currentMonth++;
  }

  if (capitalizationPeriod == 0) {
    balance += totalInterest;
    balance -= totalTax;
  }

  std::cout << "Начисленные проценты: " << totalInterest << std::endl;
  std::cout << "Сумма довложений: " << depositsSum << std::endl;
  std::cout << "Сумма налога: " << totalTax << std::endl;
  std::cout << "Доход за вычетом налогов: " << totalInterest - totalTax
            << std::endl;
  std::cout << "Сумма на вкладе к концу срока: " << balance << std::endl;

  return balance;
}

double *s21::BankModel::generateDeposits(double depositAmount, int periodType,
                                         int totalMonths) {
  if (totalMonths < 1) {
    return nullptr;
  }

  double *deposits = new double[totalMonths];

  if (deposits == nullptr) {
    return nullptr;
  }

  for (int i = 0; i < totalMonths - 1; i++) {
    deposits[i] = 0.0;

    if (periodType == 1) {
      deposits[i] = depositAmount;
    } else if (periodType == 6 && i % 6 == 0) {
      deposits[i] = depositAmount;
    } else if (periodType == 12 && i % 12 == 0) {
      deposits[i] = depositAmount;
    }
  }

  deposits[totalMonths - 1] = 0.0;

  return deposits;
}

bool BankModel::isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
}  // namespace s21
