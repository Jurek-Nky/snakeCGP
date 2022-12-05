#include "gameoverwidget.h"
#include "../ui_gameoverwidget.h"
#include <QLayout>
#include <QTableWidget>

struct tableItem {
    QString itemName;
    int itemScore;
};

GameOverWidget::GameOverWidget(QWidget *parent) :
        QWidget(parent) {
    auto *page = new QVBoxLayout(this);
    setLayout(page);
    auto *scoreBoard = new QTableWidget(3, 2, this);
    auto *lowerHalf = new QWidget(this);
    lowerHalf->setLayout(new QHBoxLayout(lowerHalf));
    int score = 55;

    auto *scoreLabel = new QLabel(QString("Score: %1").arg(score), this);

    page->addWidget(scoreLabel);
    page->addWidget(lowerHalf);
    lowerHalf->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    lowerHalf->layout()->addWidget(scoreBoard);

    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel {color: white; font-size: 30px; font-weight: bold; }");
    return;

    scoreBoard->setHorizontalHeaderLabels(QStringList() << "Name" << "Score");

    tableItem t[] = {{"jurek",   100},
                     {"tobi",    99},
                     {"lennart", 77}};

}

GameOverWidget::~GameOverWidget() {
}
