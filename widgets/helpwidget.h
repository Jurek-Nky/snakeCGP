//
// Created by jurek on 30.01.23.
//

#ifndef SNAKECGP_WIDGETS_HELPWIDGET_H
#define SNAKECGP_WIDGETS_HELPWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class HelpWidget;
}
QT_END_NAMESPACE

class HelpWidget : public QWidget {
  Q_OBJECT

public:
  explicit HelpWidget(QWidget *parent = nullptr);
  ~HelpWidget() override;

public slots:
  void onCloseButton();
signals:
  void closeHelp();

private:
  Ui::HelpWidget *ui;

  void fillTable();
};

#endif // SNAKECGP_WIDGETS_HELPWIDGET_H
