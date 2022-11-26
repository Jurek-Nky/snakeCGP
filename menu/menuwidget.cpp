//
// Created by jurek on 25.11.22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_menuWidget.h" resolved

#include <iostream>
#include "menuwidget.h"
#include "../ui_menuwidget.h"
#include "../widgetstack.h"


MenuWidget::MenuWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MenuWidget) {
    ui->setupUi(this);

    ui->menu->setTabText(0, "Audio");
    ui->menu->setTabText(1, "Video");

    connect(this->ui->close, SIGNAL(clicked(bool)), parentWidget(), SLOT(closeMenu()));
}

MenuWidget::~MenuWidget() {
}
