#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "myimageprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    QQmlEngine *engine = view.engine();
    MyImageProvider *imageProvider = new MyImageProvider(QQmlImageProviderBase::Image);
    engine->addImageProvider("myprovider", imageProvider );
    view.setSource(QUrl(QStringLiteral("qrc:///Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}

