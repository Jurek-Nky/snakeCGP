#include "menuwidget.h"
#include "../ui_menuwidget.h"
#include "widgetstack.h"
#include <iostream>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuWidget) {
  ui->setupUi(this);

  ui->menu->setTabText(0, "Audio");
  ui->menu->setTabText(1, "Video");

  ui->musicCheckbox->setCheckState(Qt::CheckState::Checked);
  ui->soundEffectCheckbox->setCheckState(Qt::CheckState::Checked);
  ui->soundOverallCheckbox->setCheckState(Qt::CheckState::Checked);

  ui->musicVolumeSlider->setRange(0, 100);
  ui->musicVolumeSlider->setTickInterval(5);
  ui->musicVolumeSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
  ui->musicVolumeSlider->setSingleStep(10);
  ui->musicVolumeSlider->setValue(Options::musicLevel);
  ui->soundEffectSlider->setRange(0, 100);
  ui->soundEffectSlider->setTickInterval(5);
  ui->soundEffectSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
  ui->soundEffectSlider->setSingleStep(10);
  ui->soundEffectSlider->setValue(Options::soundEffectLevel);
  ui->soundOverallSlider->setRange(0, 100);
  ui->soundOverallSlider->setTickInterval(5);
  ui->soundOverallSlider->setTickPosition(
      QSlider::TickPosition::TicksBothSides);
  ui->soundOverallSlider->setSingleStep(10);
  ui->soundOverallSlider->setValue(Options::soundOverallLevel);

  connect(this->ui->close, SIGNAL(clicked(bool)), this,
          SIGNAL(closeMenu()));

  connect(this->ui->musicCheckbox, SIGNAL(clicked(bool)), this,
          SLOT(setMusicEnabled(bool)));
  connect(this->ui->soundEffectCheckbox, SIGNAL(clicked(bool)), this,
          SLOT(setSoundEffectsEnabled(bool)));
  connect(this->ui->soundOverallCheckbox, SIGNAL(clicked(bool)), this,
          SLOT(setSoundEnabled(bool)));

  connect(this->ui->musicVolumeSlider, SIGNAL(sliderMoved(int)), this,
          SLOT(changeMusicLevel(int)));
  connect(this->ui->soundEffectSlider, SIGNAL(sliderMoved(int)), this,
          SLOT(changeSoundEffectLevel(int)));
  connect(this->ui->soundOverallSlider, SIGNAL(sliderMoved(int)), this,
          SLOT(changeSoundOverallLevel(int)));
}

MenuWidget::~MenuWidget() {}

void MenuWidget::changeMusicLevel(int l) {
  Options::musicLevel = l;
  emit updateAudio();
}

void MenuWidget::changeSoundEffectLevel(int l) {
  Options::soundEffectLevel = l;
  emit updateAudio();
}

void MenuWidget::changeSoundOverallLevel(int l) {
  Options::soundOverallLevel = l;
  emit updateAudio();
}

void MenuWidget::setMusicEnabled(bool b) {
  Options::musicEnabled = b;
  this->ui->musicVolumeSlider->setDisabled(!b);
  emit updateAudio();
}

void MenuWidget::setSoundEffectsEnabled(bool b) {
  Options::soundEffectsEnabled = b;
  this->ui->soundEffectSlider->setDisabled(!b);
  emit updateAudio();
}

void MenuWidget::setSoundEnabled(bool b) {
  Options::soundEnabled = b;
  this->ui->soundOverallSlider->setDisabled(!b);

  // disable all sliders and all other sound checkboxes
  this->ui->soundEffectSlider->setDisabled(!b || !Options::soundEffectsEnabled);
  this->ui->musicVolumeSlider->setDisabled(!b || !Options::musicEnabled);

  this->ui->musicCheckbox->setDisabled(!b);
  this->ui->musicCheckbox->setCheckState(!b ? Qt::CheckState::Unchecked
                                         : Options::musicEnabled
                                             ? Qt::CheckState::Checked
                                             : Qt::CheckState::Unchecked);
  this->ui->soundEffectCheckbox->setDisabled(!b);
  this->ui->soundEffectCheckbox->setCheckState(!b ? Qt::CheckState::Unchecked
                                               : Options::soundEffectsEnabled
                                                   ? Qt::CheckState::Checked
                                                   : Qt::CheckState::Unchecked);
  emit updateAudio();
}
