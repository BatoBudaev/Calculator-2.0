#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  controller = new Controller(this);
  connect(controller, &Controller::resultReady, this,
          &MainWindow::onResultReady);
  connect(controller, &Controller::errorOccurred, this,
          &MainWindow::onErrorOccurred);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_Dot, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_Plus, SIGNAL(clicked()), this, SLOT(sign_clicked()));
  connect(ui->pushButton_Minus, SIGNAL(clicked()), this, SLOT(sign_clicked()));
  connect(ui->pushButton_Mult, SIGNAL(clicked()), this,
          SLOT(operators_clicked()));
  connect(ui->pushButton_Div, SIGNAL(clicked()), this,
          SLOT(operators_clicked()));
  connect(ui->pushButton_LeftBracket, SIGNAL(clicked()), this,
          SLOT(buttons_clicked()));
  connect(ui->pushButton_RightBracket, SIGNAL(clicked()), this,
          SLOT(buttons_clicked()));
  connect(ui->pushButton_Pow, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
  connect(ui->pushButton_Sqrt, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Log, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Ln, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Sin, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Cos, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Tan, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Asin, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Acos, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_Atan, SIGNAL(clicked()), this,
          SLOT(functions_clicked()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(buttons_clicked()));

  QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
  QDoubleValidator *validator = new QDoubleValidator(-1000000.0, 1000000.0, 7);
  ui->lineEdit_2->setValidator(validator);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::buttons_clicked() {
  QPushButton *button = (QPushButton *)sender();

  if (getEqualsState() == false) {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  } else {
    ui->lineEdit->setText(button->text());
    setEqualsState(false);
  }
}

void MainWindow::functions_clicked() {
  QPushButton *button = (QPushButton *)sender();

  if (getEqualsState() == false) {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text() + "(");
  } else {
    ui->lineEdit->setText(button->text() + "(");
    setEqualsState(false);
  }
}

void MainWindow::operators_clicked() {
  QString text = ui->lineEdit->text();

  if (text.isEmpty()) {
    return;
  }

  QPushButton *button = (QPushButton *)sender();
  int compare2 = ui->lineEdit->text().compare("ERROR");

  if (compare2 == 0) {
    ui->lineEdit->setText(button->text());
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  }

  setEqualsState(false);
}

void MainWindow::on_pushButton_Equals_clicked() {
  QString text = ui->lineEdit->text();

  if (text.isEmpty()) {
    return;
  }

  text.replace(",", ".");

  QChar lastChar = text.at(text.length() - 1);

  while (lastChar == '+' || lastChar == '-' || lastChar == '*' ||
         lastChar == '/' || lastChar == '.' || lastChar == '%' ||
         lastChar == '^') {
    text = text.chopped(1);

    if (text.length() == 0) {
      ui->lineEdit->clear();
      return;
    }

    lastChar = text.at(text.length() - 1);
  }

  double x = 0;

  if (ui->lineEdit_2->text().isEmpty()) {
    x = 0;
  } else {
    x = ui->lineEdit_2->text().toDouble();
  }

  controller->onExpressionEntered(text, x);

  setEqualsState(true);
}

void MainWindow::onResultReady(double result) {
  if (!drawingGraph) {
    ui->lineEdit->setText(QString::number(result, 'g', 15));
  }
}

void MainWindow::onErrorOccurred(const QString &errorMessage) {
  if (!drawingGraph) {
    ui->lineEdit->setText(errorMessage);
  }
}

void MainWindow::on_pushButton_Ac_clicked() {
  ui->lineEdit->clear();
  setEqualsState(false);
}

void MainWindow::sign_clicked() {
  QPushButton *button = (QPushButton *)sender();
  int compare2 = ui->lineEdit->text().compare("ERROR");

  if (compare2 == 0) {
    ui->lineEdit->setText(button->text());
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  }

  setEqualsState(false);
}

void MainWindow::on_pushButton_Mod_clicked() {
  if (getEqualsState() == false) {
    ui->lineEdit->setText(ui->lineEdit->text() + "%");
  } else {
    ui->lineEdit->setText("%");
    setEqualsState(false);
  }
}

void MainWindow::onGraphFinished() { stopDrawingGraph(); }

void MainWindow::startDrawingGraph() { drawingGraph = true; }

void MainWindow::stopDrawingGraph() { drawingGraph = false; }

void MainWindow::on_pushButton_Graph_clicked() {
  startDrawingGraph();
  graphWindow = new Graph(ui->lineEdit->text(), this, getController(), this);
  connect(graphWindow, &QDialog::finished, this, &MainWindow::onGraphFinished);

  graphWindow->setModal(true);
  graphWindow->show();
}

void MainWindow::on_actionCredit_triggered() {
  creditWindow = new Credit(this);
  creditWindow->setLocale(QLocale("C"));
  creditWindow->setModal(true);
  creditWindow->show();
}

void MainWindow::on_actionDeposit_triggered() {
  depositWindow = new Deposit(this);
  depositWindow->setLocale(QLocale("C"));
  depositWindow->setModal(true);
  depositWindow->show();
}
