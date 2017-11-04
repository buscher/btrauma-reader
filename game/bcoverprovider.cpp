
#include "bcoverprovider.h"

#include <QDebug>

#include "platform/bfilemanager.h"

BCoverProvider::BCoverProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

struct Cover
{
    QString id;
    QString imgname;
    int x, y;
    int xTo, yTo;
};

static const Cover coverList[] = {
    {QLatin1String("uni"),     QLatin1String("uni_kugel_kugelnear1.jpg"),332, 48, 467, 445},
    {QLatin1String("hafen"),   QLatin1String("hafen_block_up.jpg"),      208, 0, 348, 359},
    {QLatin1String("chicane"), QLatin1String("chicane_tunnel1_06.jpg"),  281, 179, 370, 427},
    {QLatin1String("bridge"),  QLatin1String("bridge_leftdown5.jpg"),    299, 80, 386, 435},

    {QLatin1String(""),        QLatin1String(""),                        0, 0, 0, 0}
};

QPixmap BCoverProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    const int width = 175;
    const int height = 505;

    if (size)
        *size = QSize(width, height);
    const int realWidth = requestedSize.width() > 0 ? requestedSize.width() : width;
    const int realHeight = requestedSize.height() > 0 ? requestedSize.height() : height;

    int i = 0;
    forever
    {
        Cover cov = coverList[i++];
        if (cov.id.isEmpty())
            break;

        if (cov.id != id)
            continue;

        QString file = BFileManager::providePath(cov.id, cov.imgname);
        QImage origIage(file);
        QImage imgPart = origIage.copy(cov.x, cov.y, cov.xTo - cov.x, cov.yTo - cov.y).scaled(realWidth, realHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        return QPixmap::fromImage(imgPart);
    }

    qWarning() << "could no find cover:" << id;
    QPixmap pix(realWidth, realHeight);
    pix.fill(Qt::red);

    return pix;
}
