#include <QApplication>
#include <QDesktopWidget>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>

#include <qplatformdefs.h>

int qt_main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QDeclarativeView view;
    QDeclarativeContext *context = view.engine()->rootContext();
    context->setContextProperty("application", &application);
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.setAttribute(Qt::WA_NoSystemBackground);
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(480, 700);
    view.show();

    return application.exec();
}
