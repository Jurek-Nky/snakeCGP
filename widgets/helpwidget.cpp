//
// Created by jurek on 30.01.23.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_helpwidget.h" resolved

#include "helpwidget.h"
#include "../ui_helpwidget.h"
#include <string>

HelpWidget::HelpWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::HelpWidget) {
  ui->setupUi(this);
  ui->tableWidget->setColumnCount(2);
  QStringList *tableHeaders = new QStringList();
  tableHeaders->append("Action");
  tableHeaders->append("Keys");
  ui->tableWidget->setHorizontalHeaderLabels(*tableHeaders);
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  fillTable();

  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onCloseButton()));
}

HelpWidget::~HelpWidget() { delete ui; }
void HelpWidget::fillTable() {
  std::vector<std::string> helpTable = {"W, K, Up arrow",
                                        "Move up",
                                        "S, J, Down arrow",
                                        "Move down",
                                        "A, H, Left arrow",
                                        "Move left",
                                        "D, L, Right arrow",
                                        "Move right",
                                        "Q",
                                        "Quit Game",
                                        "F",
                                        "Toggle Fullscreen",
                                        "Space",
                                        "Pause",
                                        "Esc",
                                        "Exit",
                                        "?",
                                        "show Help"};

  for (int i = helpTable.size(); i > 0; --i) {
    if (i % 2 == 0) {
      ui->tableWidget->insertRow(0);
    }
    ui->tableWidget->setItem(0, i % 2,
                             new QTableWidgetItem(helpTable[i - 1].c_str()));
    ui->tableWidget->item(0, i % 2)->setTextAlignment(Qt::AlignCenter);
  }
}
void HelpWidget::onCloseButton() {
  emit closeHelp();
}
