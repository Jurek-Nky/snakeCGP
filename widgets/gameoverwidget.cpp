#include "gameoverwidget.h"
#include "../options.h"
#include "../ui_gameoverwidget.h"
#include "numericallistitem.h"
#include <QFile>
#include <iostream>

GameOverWidget::GameOverWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameOverWidget) {
  ui->setupUi(this);
  connect(ui->nameButton, SIGNAL(clicked(bool)), this,
          SLOT(onNameButtonClicked()));
  connect(ui->nameInput, SIGNAL(returnPressed()), this,
          SLOT(onNameButtonClicked()));
  connect(ui->playAgainButton, SIGNAL(clicked(bool)), this->parentWidget(),
          SLOT(restartGame()));
  connect(ui->exitButton, SIGNAL(clicked(bool)), this,
          SLOT(onExitButtonClicked()));
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->columnAt(0);
  QStringList *tableHeaders = new QStringList();
  tableHeaders->append("Name");
  tableHeaders->append("Score");
  ui->tableWidget->setHorizontalHeaderLabels(*tableHeaders);
  ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->tableWidget->setSortingEnabled(true);
  ui->tableWidget->setGridStyle(Qt::PenStyle::DashLine);
  fillTableFromFile();
  ui->playAgainButton->setStyleSheet("background-color: green");
  ui->exitButton->setStyleSheet("background-color: red");
}

GameOverWidget::~GameOverWidget() {}
void GameOverWidget::focusInEvent(QFocusEvent *event) {
  nameAdded = false;
  ui->scoreLabel->setText("Score: " + QString::number(Options::score));
  ui->nameInput->setFocus();
}
void GameOverWidget::onNameButtonClicked() {
  if (nameAdded) {
    return;
  }
  ui->tableWidget->insertRow(0);
  ui->tableWidget->setItem(0, 0, new QTableWidgetItem(ui->nameInput->text()));
  ui->tableWidget->item(0, 0)->setTextAlignment(Qt::AlignCenter);
  numericalListItem *score = new numericalListItem;
  score->setTextAlignment(Qt::AlignCenter);
  score->setText(QString::number(Options::score));
  ui->tableWidget->setItem(0, 1, score);
  QFile file("scores.txt");
  file.open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream out(&file);
  out << ui->nameInput->text().replace(' ', '_') << " " << Options::score
      << Qt::endl;
  file.close();
  ui->tableWidget->sortByColumn(1, Qt::DescendingOrder);
  nameAdded = true;
}
void GameOverWidget::fillTableFromFile() {
  QFile file("scores.txt");
  // read all scores and insert them into table
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList list = line.split(" ");
      ui->tableWidget->insertRow(0);
      QTableWidgetItem *name = new QTableWidgetItem(list[0]);
      name->setTextAlignment(Qt::AlignCenter);
      numericalListItem *score = new numericalListItem;
      score->setTextAlignment(Qt::AlignCenter);
      score->setText(list[1]);

      ui->tableWidget->setItem(0, 0, name);
      ui->tableWidget->setItem(0, 1, score);
    }
    file.close();
  }
  ui->tableWidget->sortByColumn(1, Qt::DescendingOrder);
}
void GameOverWidget::onExitButtonClicked() { exit(0); }
