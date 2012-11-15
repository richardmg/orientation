#include <QApplication>
#include <QDesktopWidget>
#include <QtGui/QScreen>
#include <QtGui/QWindow>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>

#include <qplatformdefs.h>

class ScreenProxy : public QObject {
    Q_OBJECT

    public:
    ScreenProxy(QObject *parent = 0) :
        QObject(parent)
    {
        QScreen *s = QGuiApplication::primaryScreen();
        connect(s, SIGNAL(orientationChanged(Qt::ScreenOrientation)),
           this, SIGNAL(orientationChanged(Qt::ScreenOrientation)));

        s->setOrientationUpdateMask(
            Qt::PortraitOrientation 
            | Qt::LandscapeOrientation
            | Qt::InvertedPortraitOrientation
            | Qt::InvertedLandscapeOrientation);
    }

signals:
    void orientationChanged(Qt::ScreenOrientation orientation);
public slots:
    void requestOrientation(Qt::ScreenOrientation orientation)
    {
        qDebug("request called");
        qApp->focusWindow()->requestOrientation(orientation);
    }
};

#include "main.moc"

int qt_main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QDeclarativeView view;

    QDeclarativeContext *context = view.engine()->rootContext();
    context->setContextProperty("application", &application);
    context->setContextProperty("screen", new ScreenProxy());

    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.setAttribute(Qt::WA_NoSystemBackground);
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(480, 700);
    view.show();

    return application.exec();
}
