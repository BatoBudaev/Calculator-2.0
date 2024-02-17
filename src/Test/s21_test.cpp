#include <gtest/gtest.h>

#include "../Model/s21_bank.h"
#include "../Model/s21_model.h"
#include "../Model/s21_stack.h"

TEST(CalcTest, Test0) {
  const char *str = "0.07*(1 + 0.07)^12";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 0.15765341122, 1e-7);
}

TEST(CalcTest, Test1) {
  const char *str = "2 * tan(6) / (1 + tan(5)^2)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -0.0468311814, 1e-7);
}

TEST(CalcTest, Test2) {
  const char *str = "tan(5)^2";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 11.4278817075, 1e-7);
}

TEST(CalcTest, Test3) {
  const char *str = "/0";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_FALSE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test4) {
  const char *str =
      "+10833.33+10750.00+10666.67+10583.33+10500.00+10416.67+10333.33+10250."
      "00+10166.67+10083.33";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 104583.33, 1e-7);
}

TEST(CalcTest, Test5) {
  const char *str = "100000 * (0.07*(1 + 0.07)^12)/((1+0.07)^12 - 1)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 12590.1988655, 1e-7);
}

TEST(CalcTest, Test6) {
  const char *str = "tan(log(x))/cos(x)- tan(log(x))/sin(x)=";
  s21::Model model;

  model.processExpression(str, 2);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -1.08748127511, 1e-7);
}

TEST(CalcTest, Test7) {
  const char *str = "x/cos(x)";
  s21::Model model;

  model.processExpression(str, 2);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -4.80599592344, 1e-7);
}

TEST(CalcTest, Test8) {
  const char *str = "5-*-5";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_FALSE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test9) {
  const char *str = "2^3^2";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 512, 1e-7);
}

TEST(CalcTest, Test10) {
  const char *str = "-(3)*(-1-(7*(-(-(-(-7))))))";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -144, 1e-7);
}

TEST(CalcTest, Test11) {
  const char *str = "(1+2)*4*(cos(2*7-2)+sin(2*3))*70^(-10)+5*(-3)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -15, 1e-7);
}

TEST(CalcTest, Test12) {
  const char *str = "-cos(5) - tan(4 % 5)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -1.44148346781, 1e-7);
}

TEST(CalcTest, Test13) {
  const char *str = "-tan((4)%5)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -1.15782128235, 1e-7);
}

TEST(CalcTest, Test14) {
  const char *str = "";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test15) {
  const char *str = "-7-----7";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_FALSE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test16) {
  const char *str = "cos(-5) +(-1/sin(3))";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -6.80250521027, 1e-7);
}

TEST(CalcTest, Test17) {
  const char *str = "QString::number";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_FALSE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test18) {
  const char *str = "-9-8";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -17, 1e-7);
}

TEST(CalcTest, Test19) {
  const char *str = "9 + 8 * 7 - 6 / 5";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 63.8, 1e-7);
}

TEST(CalcTest, Test20) {
  const char *str = "100.235+x-(x+10)";
  s21::Model model;

  model.processExpression(str, 2);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 90.235, 1e-7);
}
TEST(CalcTest, Test21) {
  const char *str = "cos(4)+(3-1)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 1.34635637914, 1e-7);
}

TEST(CalcTest, Test22) {
  const char *str = "2 * tan(6) / (1 + tan(5)^2)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -0.0468311814, 1e-7);
}

TEST(CalcTest, Test23) {
  const char *str = "2 ^ (-3))";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_FALSE(
      model
          .isNoError());  // Adjust this based on your error reporting mechanism
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test24) {
  const char *str = "2 ^ (-3)";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 0.125, 1e-7);
}

TEST(CalcTest, Test25) {
  const char *str =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -30.0721649485, 1e-7);
}

TEST(CalcTest, Test26) {
  const char *str = "4^acos(x/4)/tan(2*x)";
  s21::Model model;

  model.processExpression(str, 3.5);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 2.31214930869, 1e-7);
}

TEST(CalcTest, Test27) {
  const char *str = "-sqrt(x^log(5-x))+ln(55/(2+x))";
  s21::Model model;

  model.processExpression(str, 3.5);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 1.18597174919, 1e-7);
}

TEST(CalcTest, Test28) {
  const char *str = "4^cos(x/4)/tan(2*x) + sin(4)";
  s21::Model model;

  model.processExpression(str, 3);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -10.2326565899, 1e-7);
}

TEST(CalcTest, Test29) {
  const char *str = "4^acos(x/4)/tan(2*x)";
  s21::Model model;

  model.processExpression(str, 3);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -9.35895040639, 1e-7);
}

TEST(CalcTest, Test30) {
  const char *str = "4^asin(x/4)/tan(2*x)";
  s21::Model model;

  model.processExpression(str, 3);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, -11.1347896959, 1e-7);
}

TEST(CalcTest, Test31) {
  const char *str = "4^sin(x/4)/atan(2*x)";
  s21::Model model;

  model.processExpression(str, 3);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 1.83025227465, 1e-7);
}

TEST(CalcTest, Test32) {
  const char *str = "-";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 0, 1e-7);
}

TEST(CalcTest, Test33) {
  const char *str = "2+";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 2, 1e-7);
}

TEST(CalcTest, Test34) {
  const char *str = "+2";
  s21::Model model;

  model.processExpression(str, 1);
  double result = model.getResult();

  EXPECT_TRUE(model.isNoError());
  EXPECT_NEAR(result, 2, 1e-7);
}

TEST(CalcTest, CreditTest0) {
  double creditSum = 157150;
  int months = 24;
  double percent = 14;

  s21::BankModel bankModel;

  double monthPayment = bankModel.calculateAnnuity(creditSum, percent, months);
  double totalPayment = monthPayment * months;
  double overpayment = bankModel.calculateOverpayment(totalPayment, creditSum);

  EXPECT_NEAR(monthPayment, 7545.22, 1e-2);
  EXPECT_NEAR(overpayment, 23935.39, 1e-2);
  EXPECT_NEAR(totalPayment, 181085.39, 1e-2);
}

TEST(CalcTest, CreditTest1) {
  double creditSum = 25000;
  int months = 12;
  double percent = 7.7;

  s21::BankModel bankModel;

  double totalPayment = 0, overpayment = 0;
  double payments[months];

  for (int month = 1; month <= months; month++) {
    payments[month - 1] =
        bankModel.calculateDifferentiated(creditSum, percent, months, month);
  }

  for (int i = 0; i < months; i++) {
    totalPayment += payments[i];
    overpayment += payments[i] - creditSum / months;
  }

  EXPECT_NEAR(payments[0], 2243.75, 1e-2);
  EXPECT_NEAR(payments[months - 1], 2096.70, 1e-2);
  EXPECT_NEAR(overpayment, 1042.71, 1e-2);
  EXPECT_NEAR(totalPayment, 26042.71, 1e-2);
}

TEST(CalcTest, DepositTest0) {
  double initialDeposit = 1000000;
  long double balance = 0;
  int months = 18;
  double interestRate = 20;
  double taxRate = 5.25;
  int capitalizationPeriod = 1;
  int paymentsPeriod = 0;

  s21::BankModel bankModel;

  double *deposits = bankModel.generateDeposits(5000, 1, months);
  double *withdrawals = bankModel.generateDeposits(0, 1, months);
  struct s21::Data results[months];

  balance = bankModel.calculateDepositEarnings(
      initialDeposit, months, interestRate, taxRate, capitalizationPeriod,
      paymentsPeriod, deposits, withdrawals, 1, 8, 2023, results);

  long double totalInterest = 0.0;
  long double totalTax = 0.0;
  long double depositsSum = 0;

  for (int i = 0; i < months; i++) {
    totalInterest += results[i].interest;
    totalTax += results[i].tax;
    depositsSum += results[i].deposits;
  }

  delete[] deposits;
  delete[] withdrawals;

  EXPECT_NEAR(totalInterest, 358884.83, 1e-2);
  EXPECT_NEAR(depositsSum, 85000.00, 1e-2);
  EXPECT_NEAR(totalTax, 18841.45, 1e-2);
  EXPECT_NEAR(totalInterest - totalTax, 340043.38, 1e-2);
  EXPECT_NEAR(balance, 1425043.38, 1e-2);
}

TEST(CalcTest, DepositTest_1) {
  double initialDeposit = 1000000;
  long double balance = 0;
  int months = 12;
  double interestRate = 20;
  double taxRate = 5.25;
  int capitalizationPeriod = 0;
  int paymentsPeriod = 1;

  s21::BankModel bankModel;

  double *deposits = bankModel.generateDeposits(0, 1, months);
  double *withdrawals = bankModel.generateDeposits(0, 1, months);
  struct s21::Data results[months];

  balance = bankModel.calculateDepositEarnings(
      initialDeposit, months, interestRate, taxRate, capitalizationPeriod,
      paymentsPeriod, deposits, withdrawals, 1, 8, 2023, results);

  long double totalInterest = 0.0;
  long double totalTax = 0.0;
  long double depositsSum = 0;

  for (int i = 0; i < months; i++) {
    totalInterest += results[i].interest;
    totalTax += results[i].tax;
    depositsSum += results[i].deposits;
  }

  delete[] deposits;
  delete[] withdrawals;

  EXPECT_NEAR(totalInterest, 200229.06, 1e-2);
  EXPECT_NEAR(depositsSum, 0.00, 1e-2);
  EXPECT_NEAR(totalTax, 10512.03, 1e-2);
  EXPECT_NEAR(totalInterest - totalTax, 189717.03, 1e-2);
  EXPECT_NEAR(balance, 1189717.03, 1e-2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
