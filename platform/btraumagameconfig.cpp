
#include "btraumagameconfig.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

#include "btraumaquickview.h"
#include "bfilemanager.h"
#include "btraumalevelconfig.h"

BTraumaGameConfig* BTraumaGameConfig::Instance = 0;

BTraumaGameConfig::BTraumaGameConfig(QObject* parent)
    : QObject(parent),
      m_view(0),
      m_fullScreen(false), //true
      m_introPlayed(false), //false
      m_outroPlayed(false),
      m_volumeMaster(1.0),
      m_volumeMusic(0.8),
      m_volumeVoice(0.8),
      m_volumeSound(0.8)
{
    m_levels.insert(QLatin1String("uni"), new BTraumaLevelConfig());
    m_levels.insert(QLatin1String("hafen"), new BTraumaLevelConfig());
    m_levels.insert(QLatin1String("chicane"), new BTraumaLevelConfig());
    m_levels.insert(QLatin1String("bridge"), new BTraumaLevelConfig());
}

#define readDoubleConfig(jsonObject, valueString, dest, defaultVal) \
    if (jsonObject.contains(valueString)) \
    { \
        dest = jsonObject.value(valueString).toDouble(defaultVal); \
    } \
    else \
    { \
        qDebug() << "jsonobject does not double contain: " << valueString; \
    }

#define readBoolConfig(jsonObject, valueString, dest, defaultVal) \
    if (jsonObject.contains(valueString)) \
    { \
        dest = jsonObject.value(valueString).toBool(defaultVal); \
    } \
    else \
    { \
        qDebug() << "jsonobject does not bool contain: " << valueString; \
    }

struct LevelIndex
{
    QString name;
    int index;
};

static const LevelIndex levelList[] =
{
    {QLatin1String("uni"), 0},
    {QLatin1String("hafen"), 1},
    {QLatin1String("chicane"), 2},
    {QLatin1String("bridge"), 3},

    {QLatin1String(""), -1},
};

void BTraumaGameConfig::readConfig()
{
    //NOTE: keep property names in sync with original trauma
    if (QFile::exists(BFileManager::configFilePath()))
    {
        QFile file(BFileManager::configFilePath());
        if (!file.open(QIODevice::ReadOnly))
            return;

        QByteArray arr = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(arr);
        QJsonObject obj = jsonDoc.object();

        readDoubleConfig(obj, QLatin1String("vol"), m_volumeMaster, 1)
        readDoubleConfig(obj, QLatin1String("volMusic"), m_volumeMusic, 0.8)
        readDoubleConfig(obj, QLatin1String("volSfx"), m_volumeSound, 0.8)
        readDoubleConfig(obj, QLatin1String("volSpeech"), m_volumeVoice, 0.8)

        readBoolConfig(obj, QLatin1String("sawIntro"), m_introPlayed, false)
        readBoolConfig(obj, QLatin1String("sawEnding"), m_outroPlayed, false)

        readBoolConfig(obj, QLatin1String("fullScreen"), m_fullScreen, true) //not in original sol

        if (obj.contains(QLatin1String("polaroids")))
        {
            QJsonValue arrValue = obj.value(QLatin1String("polaroids"));
            qDebug() << arrValue.isArray();
            QJsonArray arr = arrValue.toArray();

            int i = 0;
            LevelIndex lvlIndex = levelList[i];
            while (lvlIndex.index > -1)
            {
                QJsonArray photoArray = arr.at(lvlIndex.index).toArray();
                BTraumaLevelConfig* lvlConfig = level(lvlIndex.name);
                if (!lvlConfig)
                    qDebug() << "could not find level:" << lvlIndex.name;

                lvlConfig->setPhoto1(photoArray.at(0).toBool(false));
                lvlConfig->setPhoto2(photoArray.at(1).toBool(false));
                lvlConfig->setPhoto3(photoArray.at(2).toBool(false));
                lvlConfig->setPhoto4(photoArray.at(3).toBool(false));
                lvlConfig->setPhoto5(photoArray.at(4).toBool(false));
                lvlConfig->setPhoto6(photoArray.at(5).toBool(false));
                lvlConfig->setPhoto7(photoArray.at(6).toBool(false));
                lvlConfig->setPhoto8(photoArray.at(7).toBool(false));
                lvlConfig->setPhoto9(photoArray.at(8).toBool(false));

                lvlIndex = levelList[++i];
            }
        }

        if (obj.contains(QLatin1String("endings")))
        {
            QJsonValue arrValue = obj.value(QLatin1String("endings"));
            qDebug() << arrValue.isArray();
            QJsonArray arr = arrValue.toArray();

            int i = 0;
            LevelIndex lvlIndex = levelList[i];
            while (lvlIndex.index > -1)
            {
                QJsonArray photoArray = arr.at(lvlIndex.index).toArray();
                BTraumaLevelConfig* lvlConfig = level(lvlIndex.name);
                if (!lvlConfig)
                    qDebug() << "could not find level:" << lvlIndex.name;

                lvlConfig->setMainEnd(photoArray.at(0).toBool(false));
                lvlConfig->setAltEnd1(photoArray.at(1).toBool(false));
                lvlConfig->setAltEnd2(photoArray.at(2).toBool(false));
                lvlConfig->setAltEnd3(photoArray.at(3).toBool(false));

                lvlIndex = levelList[++i];
            }
        }
    }
}

void BTraumaGameConfig::writeConfig()
{
    QJsonDocument doc;
    QJsonObject obj;

    obj.insert(QLatin1String("vol"), QJsonValue(m_volumeMaster));

    obj.insert(QLatin1String("volMusic"), QJsonValue(m_volumeMusic));
    obj.insert(QLatin1String("volSfx"), QJsonValue(m_volumeSound));
    obj.insert(QLatin1String("volSpeech"), QJsonValue(m_volumeVoice));

    obj.insert(QLatin1String("sawIntro"), QJsonValue(m_introPlayed));
    obj.insert(QLatin1String("sawEnding"), QJsonValue(m_outroPlayed));

    obj.insert(QLatin1String("fullScreen"), QJsonValue(m_fullScreen));

    int i = 0;
    LevelIndex lvlIndex = levelList[i];
    QJsonArray polaroidsArray;
    QJsonArray endingsArray;
    while (lvlIndex.index > -1)
    {
        QJsonArray photoArr;
        BTraumaLevelConfig* lvlConfig = level(lvlIndex.name);
        if (!lvlConfig)
            qDebug() << "could not find level:" << lvlIndex.name;

        photoArr.insert(0, lvlConfig->photo1());
        photoArr.insert(1, lvlConfig->photo2());
        photoArr.insert(2, lvlConfig->photo3());
        photoArr.insert(3, lvlConfig->photo4());
        photoArr.insert(4, lvlConfig->photo5());
        photoArr.insert(5, lvlConfig->photo6());
        photoArr.insert(6, lvlConfig->photo7());
        photoArr.insert(7, lvlConfig->photo8());
        photoArr.insert(8, lvlConfig->photo9());
        polaroidsArray.insert(lvlIndex.index, photoArr);

        QJsonArray endArr;
        endArr.insert(0, lvlConfig->mainEnd());
        endArr.insert(1, lvlConfig->altEnd1());
        endArr.insert(2, lvlConfig->altEnd2());
        endArr.insert(3, lvlConfig->altEnd3());
        endingsArray.insert(lvlIndex.index, endArr);

        lvlIndex = levelList[++i];
    }
    obj.insert(QLatin1String("polaroids"), polaroidsArray);
    obj.insert(QLatin1String("endings"), endingsArray);

    doc.setObject(obj);

    if (!QFile::exists(BFileManager::configDir()))
    {
        QDir dir;
        if (!dir.mkpath(BFileManager::configDir()))
        {
            qWarning() << "creating config dir failed.";
            return;
        }
    }

    QFile file(BFileManager::configFilePath());
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "failed to open configfile.";
        qWarning() << BFileManager::configFilePath();
        return;
    }

    file.write(doc.toJson());
}

BTraumaLevelConfig* BTraumaGameConfig::level(const QString& name)
{
    if (m_levels.contains(name))
    {
        return m_levels.value(name);
    }
    else
    {
        qWarning() << QLatin1String("could not find level: ") + name;
        return 0;
    }
}

bool BTraumaGameConfig::fullScreen() const
{
    return m_fullScreen;
}

bool BTraumaGameConfig::introPlayed() const
{
    return m_introPlayed;
}

void BTraumaGameConfig::setIntroPlayed(bool val)
{
    m_introPlayed = val;
}

bool BTraumaGameConfig::outroPlayed() const
{
    return m_outroPlayed;
}

void BTraumaGameConfig::setOutroPlayed(bool val)
{
    m_outroPlayed = val;
}

void BTraumaGameConfig::toggleFullScreen()
{
    m_fullScreen = !m_fullScreen;

    if (m_view)
    {
        if (m_fullScreen)
        {
            m_windowGeometry = m_view->geometry();
//             qDebug() << m_windowGeometry;
//             m_view->setWindowState(m_view->windowState() | Qt::WindowFullScreen);
            m_view->setWindowState(Qt::WindowFullScreen);
        }
        else
        {
//             m_view->setWindowState(m_view->windowState() & ~Qt::WindowFullScreen);
            m_view->setWindowState(Qt::WindowNoState);
//             qDebug() << "setting geometry:" << m_windowGeometry;
            if (m_windowGeometry.isValid())
                m_view->setGeometry(m_windowGeometry);
        }
        emit fullScreenChanged();
    }
    else
    {
        qDebug() << "view not set, unabled to toggleFullScreen";
    }
}

void BTraumaGameConfig::setFullScreen(bool val)
{
    if (m_fullScreen != val)
        toggleFullScreen();
}

BTraumaGameConfig* BTraumaGameConfig::instance()
{
    if (BTraumaGameConfig::Instance == 0)
    {
        BTraumaGameConfig::Instance = new BTraumaGameConfig();
        BTraumaGameConfig::Instance->readConfig();
    }
    return BTraumaGameConfig::Instance;
}

void BTraumaGameConfig::setView(BTraumaQuickView* view)
{
    m_view = view;
}

double BTraumaGameConfig::volumeMaster() const
{
    return m_volumeMaster;
}

double BTraumaGameConfig::volumeMusic() const
{
    return m_volumeMusic;
}

double BTraumaGameConfig::volumeSound() const
{
    return m_volumeSound;
}

double BTraumaGameConfig::volumeVoice() const
{
    return m_volumeVoice;
}

void BTraumaGameConfig::setVolumeMaster(double val)
{
    qDebug() << "volMaster" << val;
    m_volumeMaster = val;
    emit volumeMasterChanged();
}

void BTraumaGameConfig::setVolumeMusic(double val)
{
    qDebug() << "volMusic" << val;
    m_volumeMusic = val;
    emit volumeMusicChanged();
}

void BTraumaGameConfig::setVolumeSound(double val)
{
    qDebug() << "volSound" << val;
    m_volumeSound = val;
    emit volumeSoundChanged();
}

void BTraumaGameConfig::setVolumeVoice(double val)
{
    qDebug() << "volVoice" << val;
    m_volumeVoice = val;
    emit volumeVoiceChanged();
}


#include "btraumagameconfig.moc"
