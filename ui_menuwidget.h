/********************************************************************************
** Form generated from reading UI file 'menuwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWIDGET_H
#define UI_MENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QVBoxLayout *verticalLayout_2;
    QGroupBox *musicBox;
    QHBoxLayout *horizontalLayout_2;
    QSlider *musicVolumeSlider;
    QCheckBox *musicCheckbox;
    QGroupBox *soundEffectBox;
    QHBoxLayout *horizontalLayout_3;
    QSlider *soundEffectSlider;
    QCheckBox *soundEffectCheckbox;
    QGroupBox *soundOverallBox;
    QHBoxLayout *horizontalLayout_4;
    QSlider *soundOverallSlider;
    QCheckBox *soundOverallCheckbox;
    QSpacerItem *verticalSpacer;
    QWidget *Video;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *close;

    void setupUi(QWidget *MenuWidget)
    {
        if (MenuWidget->objectName().isEmpty())
            MenuWidget->setObjectName("MenuWidget");
        MenuWidget->resize(1042, 664);
        verticalLayout = new QVBoxLayout(MenuWidget);
        verticalLayout->setObjectName("verticalLayout");
        menu = new QTabWidget(MenuWidget);
        menu->setObjectName("menu");
        menu->setTabPosition(QTabWidget::North);
        menu->setTabShape(QTabWidget::Rounded);
        menu->setIconSize(QSize(16, 16));
        menu->setElideMode(Qt::ElideLeft);
        Audio = new QWidget();
        Audio->setObjectName("Audio");
        verticalLayout_2 = new QVBoxLayout(Audio);
        verticalLayout_2->setObjectName("verticalLayout_2");
        musicBox = new QGroupBox(Audio);
        musicBox->setObjectName("musicBox");
        horizontalLayout_2 = new QHBoxLayout(musicBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        musicVolumeSlider = new QSlider(musicBox);
        musicVolumeSlider->setObjectName("musicVolumeSlider");
        musicVolumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(musicVolumeSlider);

        musicCheckbox = new QCheckBox(musicBox);
        musicCheckbox->setObjectName("musicCheckbox");

        horizontalLayout_2->addWidget(musicCheckbox);


        verticalLayout_2->addWidget(musicBox);

        soundEffectBox = new QGroupBox(Audio);
        soundEffectBox->setObjectName("soundEffectBox");
        horizontalLayout_3 = new QHBoxLayout(soundEffectBox);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        soundEffectSlider = new QSlider(soundEffectBox);
        soundEffectSlider->setObjectName("soundEffectSlider");
        soundEffectSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(soundEffectSlider);

        soundEffectCheckbox = new QCheckBox(soundEffectBox);
        soundEffectCheckbox->setObjectName("soundEffectCheckbox");

        horizontalLayout_3->addWidget(soundEffectCheckbox);


        verticalLayout_2->addWidget(soundEffectBox);

        soundOverallBox = new QGroupBox(Audio);
        soundOverallBox->setObjectName("soundOverallBox");
        horizontalLayout_4 = new QHBoxLayout(soundOverallBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        soundOverallSlider = new QSlider(soundOverallBox);
        soundOverallSlider->setObjectName("soundOverallSlider");
        soundOverallSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(soundOverallSlider);

        soundOverallCheckbox = new QCheckBox(soundOverallBox);
        soundOverallCheckbox->setObjectName("soundOverallCheckbox");

        horizontalLayout_4->addWidget(soundOverallCheckbox);


        verticalLayout_2->addWidget(soundOverallBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        menu->addTab(Audio, QString());
        Video = new QWidget();
        Video->setObjectName("Video");
        menu->addTab(Video, QString());

        verticalLayout->addWidget(menu);

        frame = new QFrame(MenuWidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        close = new QPushButton(frame);
        close->setObjectName("close");

        horizontalLayout->addWidget(close);


        verticalLayout->addWidget(frame);


        retranslateUi(MenuWidget);

        menu->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuWidget)
    {
        MenuWidget->setWindowTitle(QCoreApplication::translate("MenuWidget", "MenuWidget", nullptr));
        musicBox->setTitle(QCoreApplication::translate("MenuWidget", "Music", nullptr));
        musicCheckbox->setText(QString());
        soundEffectBox->setTitle(QCoreApplication::translate("MenuWidget", "Soundeffects", nullptr));
        soundEffectCheckbox->setText(QString());
        soundOverallBox->setTitle(QCoreApplication::translate("MenuWidget", "Sound Global", nullptr));
        soundOverallCheckbox->setText(QString());
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
