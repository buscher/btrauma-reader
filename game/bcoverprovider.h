#ifndef BCOVERPROVIDER_H
#define BCOVERPROVIDER_H

#include <QQuickImageProvider>
#include <QSize>


class BCoverProvider : public QQuickImageProvider
{
public:
    BCoverProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif //BCOVERPROVIDER_H
