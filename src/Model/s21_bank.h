#ifndef S21_BANK_H
#define S21_BANK_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
struct Data {
  int number;
  long double interest;
  long double tax;
  long double deposits;
  long double withdrawals;
  long double sum;
};

class BankModel {
 public:
  BankModel();
  ~BankModel();

  long double calculateAnnuity(double creditSum, double percent, int months);
  long double calculateOverpayment(double totalPayment, double creditSum);
  long double calculateDifferentiated(double creditSum, double percent,
                                      int months, int currentMonth);
  long double calculateInterest(long double balance, double rate, int days,
                                int daysInYear);
  long double calculateTax(long double income, long double untaxedIncome,
                           double taxRate);
  int getDaysInMonth(int year, int month);
  long double calculateDepositEarnings(double initialDeposit, int months,
                                       double interestRate, double taxRate,
                                       int capitalizationPeriod,
                                       int paymentsPeriod, double *deposits,
                                       double *withdrawals, int startDay,
                                       int startMonth, int startYear,
                                       struct s21::Data *results);
  double *generateDeposits(double depositAmount, int periodType,
                           int totalMonths);

 private:
  bool isLeapYear(int year);
};
}  // namespace s21

#endif  // S21_BANK_H
