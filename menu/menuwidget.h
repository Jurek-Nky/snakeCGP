//
// Created by jurek on 25.11.22.
//

#ifndef SNAKECGP_MENUWIDGET_H
#define SNAKECGP_MENUWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MenuWidget; }
QT_END_NAMESPACE


class MenuWidget : public QWidget {
Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent);

    ~MenuWidget() override;

private:
    Ui::MenuWidget *ui;
};


#endif //SNAKECGP_MENUWIDGET_H
