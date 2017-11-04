
#include "bgamemanager.h"

#include <QQmlEngine>
#include <QQmlContext>
#include <qqml.h>
#include <QDebug>

#include "platform/btraumaquickview.h"
#include "platform/btraumagameconfig.h"
#include "platform/bfilemanager.h"
#include "platform/btraumalevelconfig.h"

#include "game/bcoverprovider.h"
#include "game/btraumareader.h"
#include "game/blevel.h"
#include "game/bframe.h"
#include "game/bframeexit.h"

BGameManager::BGameManager(QObject* parent)
    : QObject(parent),
      m_state(BGameManager::Intro),
      m_view(0),
      m_level(0)
{
    qmlRegisterType<BTraumaLevelConfig>();

    m_view = new BTraumaQuickView();
    m_view->engine()->addImageProvider(QLatin1String("cover"), new BCoverProvider);

    BTraumaGameConfig* config = BTraumaGameConfig::instance();
    config->setView(m_view);

    m_view->engine()->rootContext()->setContextProperty(QLatin1String("Config"), config);
    m_view->engine()->rootContext()->setContextProperty(QLatin1String("GameManager"), this);

//     qmlRegisterType<BTraumaLevelConfig>();


    m_view->resize(700, 525);
    m_view->setMinimumHeight(525);
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);

    if (!config->introPlayed())
    {
        m_view->engine()->rootContext()->setContextProperty(QLatin1String("introMovie"), BFileManager::provideVideoPath(QLatin1String("intro.flv")));
        setTargetQml(QLatin1String("MainIntro.qml"));
    }
    else
    {
        setTargetQml(QLatin1String("MainMenu.qml"));
    }
    m_view->setSource(QUrl(BFileManager::provideQmlPath(QLatin1String("MainWrapper.qml"))));

    if (config->fullScreen())
//         m_view->setWindowState(m_view->windowState() | Qt::WindowFullScreen); // set
        m_view->setWindowState(Qt::WindowFullScreen); // set
//         m_view->showFullScreen();
    else
        m_view->show();
}

void BGameManager::introFinished()
{
//     m_view->engine()->clearComponentCache();

    BTraumaGameConfig* config = BTraumaGameConfig::instance();
    config->setIntroPlayed(true);
    config->writeConfig();

    setTargetQml(QLatin1String("MainMenu.qml"));
}

void BGameManager::loadLevel(const QString& levelId)
{
    qDebug() << "load:" << levelId;

    if (levelId == QLatin1String("uni"))
    {
        m_level = BTraumaReader::readLevel(QLatin1String("illucinated01"));
    }
    else if (levelId == QLatin1String("hafen"))
    {
        m_level = BTraumaReader::readLevel(QLatin1String("illucinated02"));
    }
    else if (levelId == QLatin1String("chicane"))
    {
        m_level = BTraumaReader::readLevel(QLatin1String("illucinated03"));
    }
    else if (levelId == QLatin1String("bridge"))
    {
        m_level = BTraumaReader::readLevel(QLatin1String("illucinated04"));
    }
    else
    {
        qWarning() << "unknown levelid, panic!" << levelId;
        return;
    }

    if (!m_level)
    {
        qWarning() << "failed to load level:" << levelId;
        return;
    }

    BFrame* frame = m_level->firstFrame();
    qDebug() << frame->name();
    
    setMainFrame(levelId, frame->name());
    setTargetQml(QLatin1String("MainScene.qml"));
    
    qDebug() << frame->x() << frame->y() << frame->z();
    qDebug() << "visible Frameexits:";
//     QVector<BFrameExit*> vector = frame->visibleExits();
    
    
    
    foreach (BFrameExit* exit, frame->visibleExits())
    {
        qDebug() << '\t' << exit->name();
        BFrame* tFrame = m_level->frame(exit->name());
        qDebug() << '\t' << tFrame->x() << tFrame->y() << tFrame->z() << tFrame->scale();
        qDebug() << "\t\t" << tFrame->x() << tFrame->y() << tFrame->z() << tFrame->scale();
    }
    
    
}

void BGameManager::setTargetQml(const QString& file)
{
    m_view->engine()->rootContext()->setContextProperty(QLatin1String("targetQmlFile"), BFileManager::provideQmlPath(file));
}

void BGameManager::setMainFrame(const QString& id, const QString& file)
{
    m_view->engine()->rootContext()->setContextProperty(QLatin1String("mainFrame"), BFileManager::providePath(id, file));
}


#include <bgamemanager.moc>

