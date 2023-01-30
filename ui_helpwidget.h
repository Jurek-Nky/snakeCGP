/********************************************************************************
** Form generated from reading UI file 'helpwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWIDGET_H
#define UI_HELPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *HelpWidget)
    {
        if (HelpWidget->objectName().isEmpty())
            HelpWidget->setObjectName("HelpWidget");
        HelpWidget->resize(1006, 678);
        verticalLayout = new QVBoxLayout(HelpWidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(HelpWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(24);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(HelpWidget);
        tableWidget->setObjectName("tableWidget");

        verticalLayout->addWidget(tableWidget);

        widget = new QWidget(HelpWidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setLayoutDirection(Qt::LeftToRight);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(widget);


        retranslateUi(HelpWidget);

        QMetaObject::connectSlotsByName(HelpWidget);
    } // setupUi

    void retranslateUi(QWidget *HelpWidget)
    {
        HelpWidget->setWindowTitle(QCoreApplication::translate("HelpWidget", "HelpWidget", nullptr));
        label->setText(QCoreApplication::translate("HelpWidget", "Help", nullptr));
        pushButton->setText(QCoreApplication::translate("HelpWidget", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpWidget: public Ui_HelpWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWIDGET_H
