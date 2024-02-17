#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

Graph::Graph(const QString &text, MainWindow *mainWindow,
             Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::Graph), controllerRef(controller) {
  ui->setupUi(this);
  ui->lineEdit->setText(text);

  setValidators();

  setMainWindowRef(mainWindow);
  drawGraph(text);
}

void Graph::drawGraph(const QString &text) {
  x.clear();
  y.clear();
  ui->widget->clearGraphs();

  int xMax = ui->xMaxLine->text().toInt();
  int xMin = ui->xMinLine->text().toInt();
  int yMax = ui->yMaxLine->text().toInt();
  int yMin = ui->yMinLine->text().toInt();

  int ratio = 1;

  if (xMax > 19) {
    ratio = xMax / 10;
  }

  h = 0.1 * ratio;

  xBegin = ui->xMinLine->text().toDouble();
  xEnd = ui->xMaxLine->text().toDouble() + h;

  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);

  for (X = xBegin; X <= xEnd; X += h) {
    double result = controllerRef->onExpressionEntered(text, X);
    x.push_back(X);
    y.push_back(result);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void Graph::setValidators() {
  QIntValidator *xMaxValidator = new QIntValidator(-1000000, 1000000);
  QIntValidator *xMinValidator = new QIntValidator(-1000000, 1000000);
  QIntValidator *yMaxValidator = new QIntValidator(-1000000, 1000000);
  QIntValidator *yMinValidator = new QIntValidator(-1000000, 1000000);

  ui->xMaxLine->setValidator(xMaxValidator);
  ui->xMinLine->setValidator(xMinValidator);
  ui->yMaxLine->setValidator(yMaxValidator);
  ui->yMinLine->setValidator(yMinValidator);
}

void Graph::on_pushButton_clicked() { drawGraph(ui->lineEdit->text()); }

MainWindow *Graph::getMainWindowRef() const { return mainWindowRef; }

void Graph::setMainWindowRef(MainWindow *newMainWindowRef) {
  mainWindowRef = newMainWindowRef;
}
