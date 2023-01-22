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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameOverWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *scoreLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QLabel *nameLabel;
    QLineEdit *nameInput;
    QPushButton *nameButton;
    QSpacerItem *verticalSpacer_2;
    QTableView *tableView;

    void setupUi(QWidget *GameOverWidget)
    {
        if (GameOverWidget->objectName().isEmpty())
            GameOverWidget->setObjectName("GameOverWidget");
        GameOverWidget->resize(1042, 664);
        verticalLayout = new QVBoxLayout(GameOverWidget);
        verticalLayout->setObjectName("verticalLayout");
        scoreLabel = new QLabel(GameOverWidget);
        scoreLabel->setObjectName("scoreLabel");

        verticalLayout->addWidget(scoreLabel);

        widget = new QWidget(GameOverWidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::FieldRole, verticalSpacer);

        nameLabel = new QLabel(widget);
        nameLabel->setObjectName("nameLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameInput = new QLineEdit(widget);
        nameInput->setObjectName("nameInput");

        formLayout->setWidget(1, QFormLayout::FieldRole, nameInput);

        nameButton = new QPushButton(widget);
        nameButton->setObjectName("nameButton");

        formLayout->setWidget(2, QFormLayout::FieldRole, nameButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_2);


        horizontalLayout->addLayout(formLayout);

        tableView = new QTableView(widget);
        tableView->setObjectName("tableView");

        horizontalLayout->addWidget(tableView);


        verticalLayout->addWidget(widget);


        retranslateUi(GameOverWidget);

        QMetaObject::connectSlotsByName(GameOverWidget);
    } // setupUi

    void retranslateUi(QWidget *GameOverWidget)
    {
        GameOverWidget->setWindowTitle(QCoreApplication::translate("GameOverWidget", "MenuWidget", nullptr));
        scoreLabel->setText(QCoreApplication::translate("GameOverWidget", "TextLabel", nullptr));
        nameLabel->setText(QCoreApplication::translate("GameOverWidget", "Enter your Name", nullptr));
        nameButton->setText(QCoreApplication::translate("GameOverWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverWidget: public Ui_GameOverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERWIDGET_H
