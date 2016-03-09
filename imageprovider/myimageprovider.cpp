#include "myimageprovider.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

MyImageProvider::MyImageProvider(ImageType type, Flags flags) :
    QQuickImageProvider(type,flags)
{
    manager = new QNetworkAccessManager;
}

MyImageProvider::~MyImageProvider()
{
    delete manager;
}

QImage MyImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "id: " << id;
    qDebug() << "reequestedSize: " << requestedSize.width() + " " + requestedSize.height();
    QUrl url("http://lorempixel.com/" + id);
    QNetworkReply* reply = manager->get(QNetworkRequest(url));
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    if (reply->error() != QNetworkReply::NoError)
        return QImage();
    QImage image = QImage::fromData(reply->readAll());
    size->setWidth(image.width());
    size->setHeight(image.height());
    return image;
}
