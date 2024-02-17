#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>

#include "../Controller/s21_controller.h"
#include "../Model/s21_stack.h"
#include "credit.h"
#include "deposit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using namespace s21;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  bool getEqualsState() const { return equalsState; }

  void setEqualsState(bool state) { equalsState = state; }

  Controller *getController() const { return controller; }
 public slots:
  void startDrawingGraph();
  void stopDrawingGraph();

 private slots:
  void buttons_clicked();
  void operators_clicked();
  void functions_clicked();
  void sign_clicked();

  void on_pushButton_Equals_clicked();
  void on_pushButton_Ac_clicked();
  void on_pushButton_Mod_clicked();
  void on_pushButton_Graph_clicked();

  void on_actionCredit_triggered();

  void on_actionDeposit_triggered();

  void onResultReady(double result);
  void onErrorOccurred(const QString &errorMessage);
  void onGraphFinished();

 private:
  Ui::MainWindow *ui;
  bool equalsState = false;
  Graph *graphWindow;
  Credit *creditWindow;
  Deposit *depositWindow;
  Controller *controller;
  bool drawingGraph = false;
};
#endif  // MAINWINDOW_H
