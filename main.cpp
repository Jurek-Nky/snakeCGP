#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL

#include "widgets/widgetstack.h"

#endif

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");

#ifndef QT_NO_OPENGL
    WidgetStack widgetStack;
    widgetStack.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
