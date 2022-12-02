//
// Created by jurek on 02.12.22.
//

#ifndef SNAKECGP_GAMEOVERWIDGET_H
#define SNAKECGP_GAMEOVERWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class GameOverWidget; }
QT_END_NAMESPACE

class GameOverWidget : public QWidget {
Q_OBJECT

public:
    explicit GameOverWidget(QWidget *parent = nullptr);

    ~GameOverWidget() override;

private:
    Ui::GameOverWidget *ui;
};


#endif //SNAKECGP_GAMEOVERWIDGET_H
