/********************************************************************************
** Form generated from reading UI file 'gameoverwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERWIDGET_H
#define UI_GAMEOVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameOverWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *scoreLabel;
    QSpacerItem *verticalSpacer_4;
    QFrame *line;
    QSpacerItem *verticalSpacer_5;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QLabel *nameLabel;
    QLineEdit *nameInput;
    QPushButton *nameButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *playAgainButton;
    QTableWidget *tableWidget;

    void setupUi(QWidget *GameOverWidget)
    {
        if (GameOverWidget->objectName().isEmpty())
            GameOverWidget->setObjectName("GameOverWidget");
        GameOverWidget->resize(1078, 735);
        verticalLayout = new QVBoxLayout(GameOverWidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(GameOverWidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        QFont font;
        font.setPointSize(18);
        widget_2->setFont(font);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);

        scoreLabel = new QLabel(widget_2);
        scoreLabel->setObjectName("scoreLabel");
        QFont font1;
        font1.setPointSize(20);
        font1.setItalic(false);
        font1.setUnderline(true);
        scoreLabel->setFont(font1);
        scoreLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(scoreLabel);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        line = new QFrame(widget_2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_5);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(0, QFormLayout::FieldRole, verticalSpacer);

        nameLabel = new QLabel(widget_2);
        nameLabel->setObjectName("nameLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameInput = new QLineEdit(widget_2);
        nameInput->setObjectName("nameInput");
        nameInput->setMaximumSize(QSize(500, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameInput);

        nameButton = new QPushButton(widget_2);
        nameButton->setObjectName("nameButton");
        nameButton->setMaximumSize(QSize(500, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, nameButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_2);


        verticalLayout_2->addLayout(formLayout);

        playAgainButton = new QPushButton(widget_2);
        playAgainButton->setObjectName("playAgainButton");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playAgainButton->sizePolicy().hasHeightForWidth());
        playAgainButton->setSizePolicy(sizePolicy);
        playAgainButton->setMinimumSize(QSize(0, 80));
        playAgainButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(playAgainButton);


        horizontalLayout->addWidget(widget_2);

        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(tableWidget);


        verticalLayout->addWidget(widget);


        retranslateUi(GameOverWidget);

        QMetaObject::connectSlotsByName(GameOverWidget);
    } // setupUi

    void retranslateUi(QWidget *GameOverWidget)
    {
        GameOverWidget->setWindowTitle(QCoreApplication::translate("GameOverWidget", "MenuWidget", nullptr));
        scoreLabel->setText(QCoreApplication::translate("GameOverWidget", "Score:", nullptr));
        nameLabel->setText(QCoreApplication::translate("GameOverWidget", "Enter your Name", nullptr));
        nameInput->setInputMask(QString());
        nameInput->setText(QString());
        nameInput->setPlaceholderText(QCoreApplication::translate("GameOverWidget", "name", nullptr));
        nameButton->setText(QCoreApplication::translate("GameOverWidget", "Add to Scoreboard", nullptr));
        playAgainButton->setText(QCoreApplication::translate("GameOverWidget", "Play Again", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverWidget: public Ui_GameOverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERWIDGET_H
