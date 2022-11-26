/********************************************************************************
** Form generated from reading UI file 'menuwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWIDGET_H
#define UI_MENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *menu;
    QWidget *Audio;
    QWidget *Video;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *close;

    void setupUi(QWidget *MenuWidget)
    {
        if (MenuWidget->objectName().isEmpty())
            MenuWidget->setObjectName(QString::fromUtf8("MenuWidget"));
        MenuWidget->resize(1042, 664);
        verticalLayout = new QVBoxLayout(MenuWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        menu = new QTabWidget(MenuWidget);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setTabPosition(QTabWidget::North);
        menu->setTabShape(QTabWidget::Rounded);
        menu->setIconSize(QSize(16, 16));
        menu->setElideMode(Qt::ElideLeft);
        Audio = new QWidget();
        Audio->setObjectName(QString::fromUtf8("Audio"));
        menu->addTab(Audio, QString());
        Video = new QWidget();
        Video->setObjectName(QString::fromUtf8("Video"));
        menu->addTab(Video, QString());

        verticalLayout->addWidget(menu);

        frame = new QFrame(MenuWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        close = new QPushButton(frame);
        close->setObjectName(QString::fromUtf8("close"));

        horizontalLayout->addWidget(close);


        verticalLayout->addWidget(frame);


        retranslateUi(MenuWidget);

        menu->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuWidget)
    {
        MenuWidget->setWindowTitle(QCoreApplication::translate("MenuWidget", "MenuWidget", nullptr));
        menu->setTabText(menu->indexOf(Audio), QCoreApplication::translate("MenuWidget", "Tab 1", nullptr));
        menu->setTabText(menu->indexOf(Video), QCoreApplication::translate("MenuWidget", "Tab 2", nullptr));
        close->setText(QCoreApplication::translate("MenuWidget", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWidget: public Ui_MenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWIDGET_H
