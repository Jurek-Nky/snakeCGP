//
// Created by jurek on 25.11.22.
//

#ifndef SNAKECGP_WIDGETSTACK_H
#define SNAKECGP_WIDGETSTACK_H


#include <QStackedWidget>
#include <QOpenGLFunctions>
#include "menu/menuwidget.h"
#include "game/gamewidget.h"

class WidgetStack : public QWidget {
Q_OBJECT
public:
    using QWidget = QWidget;

    explicit WidgetStack(QWidget *parent = 0);

    virtual ~WidgetStack();

public slots:

    void closeMenu();

    void openMenu();

protected:

    void keyPressEvent(QKeyEvent *e) override;

signals:

    void resumeGame();

private:
    QStackedWidget *stack = nullptr;
    MenuWidget *menu = nullptr;
    GameWidget *game = nullptr;
};


#endif //SNAKECGP_WIDGETSTACK_H
