
#include "bfilemanager.h"

#include "btraumaconfig.h"

#include <QtGlobal>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

QVector< QString > BFileManager::S_BaseDirs;
QVector< QString > BFileManager::S_QMLDirs;

QVector< QString > BFileManager::baseDirs()
{
    if (S_BaseDirs.isEmpty())
    {
        QString homePath = BFileManager::configDir() + QDir::separator() + QLatin1String("data");
        if (QFile::exists(homePath))
            S_BaseDirs.append(homePath);
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC) || defined(Q_OS_UNIX)
        QString installPath = QLatin1String(BTRAUMA_INSTALL_PREFIX) + QDir::separator() + QLatin1String("share/btrauma/data/");
        if (QFile::exists(installPath))
            S_BaseDirs.append(installPath);

        if (S_BaseDirs.isEmpty())
        {
            qWarning() << "no TRAUMA datadir found! this will cause trouble!";
            qWarning() << "Possible locations are:";
            qWarning() << '\t' << homePath;
            qWarning() << '\t' << installPath;
        }
#elif defined(Q_OS_WIN)
        QString runPath = QCoreApplication::applicationDirPath + QDir::separator() + QLatin1String("data") + QDir::separator();
        if (QFile::exists(runPath))
            S_BaseDirs.append(runPath);

        if (S_BaseDirs.isEmpty())
        {
            qWarning() << "no TRAUMA datadir found! this will cause trouble!";
            qWarning() << "Possible locations are:";
            qWarning() << '\t' << homePath;
            qWarning() << '\t' << runPath;
        }
#else
        qDebug() << "unknown platform, hopefully home is enough";
#endif
    }

    return S_BaseDirs;
}


QVector< QString > BFileManager::qmlDirs()
{
    if (S_QMLDirs.isEmpty())
    {
        QString homePath = BFileManager::configDir() + QDir::separator() + QLatin1String("qml");
        if (QFile::exists(homePath))
            S_QMLDirs.append(homePath);

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC) || defined(Q_OS_UNIX)
        QString installPath = QLatin1String(BTRAUMA_INSTALL_PREFIX) + QDir::separator() + QLatin1String("share/btrauma/qml/");
        if (QFile::exists(installPath))
            S_QMLDirs.append(installPath);

        if (S_QMLDirs.isEmpty())
        {
            qWarning() << "no TRAUMA qmldir found! this will cause trouble!";
            qWarning() << "Possible locations are:";
            qWarning() << '\t' << homePath;
            qWarning() << '\t' << installPath;
        }
#elif defined(Q_OS_WIN)
        QString runPath = QCoreApplication::applicationDirPath + QDir::separator() + QLatin1String("qml") + QDir::separator();
        if (QFile::exists(runPath))
            S_QMLDirs.append(runPath);

        if (S_QMLDirs.isEmpty())
        {
            qWarning() << "no TRAUMA qmldir found! this will cause trouble!";
            qWarning() << "Possible locations are:";
            qWarning() << '\t' << homePath;
            qWarning() << '\t' << runPath;
        }
#else
        qDebug() << "unknown platform, hopefully home is enough";
#endif
    }

    return S_QMLDirs;
}


QString BFileManager::provideXmlPath(const QString& file)
{
    return providePath(QLatin1String("xml"), file);
}

QString BFileManager::provideVideoPath(const QString& file)
{
    return providePath(QLatin1String("video"), file);
}

QString BFileManager::provideSystemsoundsPath(const QString& file)
{
    return providePath(QLatin1String("systemsounds"), file);
}

QString BFileManager::provideUniPath(const QString& file)
{
    return providePath(QLatin1String("uni"), file);
}

QString BFileManager::providePath(const QString& folder, const QString& file)
{
    foreach (const QString& path, baseDirs())
    {
        QString filePath = path + QDir::separator() + folder + QDir::separator() + file;
        if (QFile::exists(filePath))
            return filePath;
    }
    qWarning() << "could not find:" << file << " in:" << folder;
    return QString();
}

QString BFileManager::provideQmlPath(const QString& file)
{
    foreach (const QString& path, qmlDirs())
    {
        QString filePath = path + QDir::separator() + file;
        if (QFile::exists(filePath))
            return filePath;
    }
    qWarning() << "could not qml find:" << file;
    return QString();
}

QString BFileManager::configDir()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC) || defined(Q_OS_UNIX)
    return QDir::homePath() + QDir::separator() + QLatin1String(".config/btrauma");
#elif defined(Q_OS_WIN)
    return QDir::homePath() + QDir::separator() + QLatin1String("btrauma")
#else
    //unknown platform, assume unix alike
    return QDir::homePath() + QDir::separator() + QLatin1String(".config/btrauma");
#endif
}

QString BFileManager::configFilePath()
{
    return configDir() + QDir::separator() + QLatin1String("btrauma.json");
}

