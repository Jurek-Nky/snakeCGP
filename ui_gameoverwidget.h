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
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *scoreLabel;
    QFrame *line_2;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QPushButton *nameButton;
    QLineEdit *nameInput;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *exitButton;
    QPushButton *playAgainButton;
    QFrame *line;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_6;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QTableWidget *tableWidget;

    void setupUi(QWidget *GameOverWidget)
    {
        if (GameOverWidget->objectName().isEmpty())
            GameOverWidget->setObjectName("GameOverWidget");
        GameOverWidget->resize(1302, 771);
        horizontalLayout_2 = new QHBoxLayout(GameOverWidget);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        widget_2 = new QWidget(GameOverWidget);
        widget_2->setObjectName("widget_2");
        QFont font;
        font.setPointSize(18);
        widget_2->setFont(font);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        scoreLabel = new QLabel(widget_2);
        scoreLabel->setObjectName("scoreLabel");
        QFont font1;
        font1.setPointSize(48);
        font1.setItalic(false);
        font1.setUnderline(false);
        scoreLabel->setFont(font1);
        scoreLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(scoreLabel);

        line_2 = new QFrame(widget_2);
        line_2->setObjectName("line_2");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setMaximumSize(QSize(16777215, 40));
        line_2->setBaseSize(QSize(0, 0));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(50);
        formLayout->setVerticalSpacing(15);
        nameLabel = new QLabel(widget_2);
        nameLabel->setObjectName("nameLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameButton = new QPushButton(widget_2);
        nameButton->setObjectName("nameButton");
        nameButton->setMaximumSize(QSize(16777215, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameButton);

        nameInput = new QLineEdit(widget_2);
        nameInput->setObjectName("nameInput");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
        nameInput->setSizePolicy(sizePolicy1);
        nameInput->setMaximumSize(QSize(16777215, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameInput);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        exitButton = new QPushButton(widget);
        exitButton->setObjectName("exitButton");
        sizePolicy1.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy1);
        exitButton->setMinimumSize(QSize(250, 80));
        exitButton->setFont(font);
        exitButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(exitButton);

        playAgainButton = new QPushButton(widget);
        playAgainButton->setObjectName("playAgainButton");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playAgainButton->sizePolicy().hasHeightForWidth());
        playAgainButton->setSizePolicy(sizePolicy2);
        playAgainButton->setMinimumSize(QSize(0, 80));
        playAgainButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(playAgainButton);


        verticalLayout_2->addWidget(widget);


        horizontalLayout_2->addWidget(widget_2);

        line = new QFrame(GameOverWidget);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100)"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        widget_3 = new QWidget(GameOverWidget);
        widget_3->setObjectName("widget_3");
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_6);

        label = new QLabel(widget_3);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(24);
        font2.setUnderline(true);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_7);

        tableWidget = new QTableWidget(widget_3);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy3);
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(tableWidget);


        horizontalLayout_2->addWidget(widget_3);


        retranslateUi(GameOverWidget);

        QMetaObject::connectSlotsByName(GameOverWidget);
    } // setupUi

    void retranslateUi(QWidget *GameOverWidget)
    {
        GameOverWidget->setWindowTitle(QCoreApplication::translate("GameOverWidget", "MenuWidget", nullptr));
        scoreLabel->setText(QCoreApplication::translate("GameOverWidget", "Score:", nullptr));
        nameLabel->setText(QCoreApplication::translate("GameOverWidget", "Enter your Name", nullptr));
        nameButton->setText(QCoreApplication::translate("GameOverWidget", "Add to Scoreboard", nullptr));
        nameInput->setInputMask(QString());
        nameInput->setText(QString());
        nameInput->setPlaceholderText(QCoreApplication::translate("GameOverWidget", "name", nullptr));
        exitButton->setText(QCoreApplication::translate("GameOverWidget", "Close", nullptr));
        playAgainButton->setText(QCoreApplication::translate("GameOverWidget", "Play Again", nullptr));
        label->setText(QCoreApplication::translate("GameOverWidget", "Highscores", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverWidget: public Ui_GameOverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERWIDGET_H
