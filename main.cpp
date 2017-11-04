#include <QGuiApplication>
#include <QDebug>
#include <QQuickView>
#include <QUrl>
#include <QQmlContext>
#include <QVariant>

#include "platform/bgamemanager.h"
#include "game/btraumareader.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);


    qDebug() << "+++++++++++++++++++++++++illucinated01+++++++++++++++++++++++++";
    BTraumaReader::readLevel( QLatin1String("illucinated01") );

    qDebug() << "+++++++++++++++++++++++++illucinated02+++++++++++++++++++++++++";
    BTraumaReader::readLevel( QLatin1String("illucinated02") );

    qDebug() << "+++++++++++++++++++++++++illucinated03+++++++++++++++++++++++++";
    BTraumaReader::readLevel( QLatin1String("illucinated03") );

    qDebug() << "+++++++++++++++++++++++++illucinated04+++++++++++++++++++++++++";
    BTraumaReader::readLevel( QLatin1String("illucinated04") );
#if 0
#if 1
//     QQuickView view;
    BTraumaQuickView view;
    view.engine()->addImageProvider(QLatin1String("cover"), new BCoverProvider);
    
    
    BTraumaGameConfig* config = BTraumaGameConfig::instance();
    config->setView(&view);
//     BTraumaConfig config;

    view.engine()->rootContext()->setContextProperty(QLatin1String("config"), config);



    view.resize(700, 525);
    view.setMinimumHeight(525);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl( BFileManager::provideQmlPath(QLatin1String("Main.qml")) ));
    
    view.show();
//     view.showFullScreen();
    return app.exec();
#endif


    return 0;
#endif
    BGameManager manager;

    return app.exec();
}
