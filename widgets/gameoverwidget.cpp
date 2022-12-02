//
// Created by jurek on 02.12.22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gameOver.h" resolved

#include "gameoverwidget.h"
#include "../ui_gameoverwidget.h"


GameOverWidget::GameOverWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::GameOverWidget) {
    ui->setupUi(this);
}

GameOverWidget::~GameOverWidget() {
    delete ui;
}
