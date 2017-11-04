
#ifndef BFILEMANAGER_H
#define BFILEMANAGER_H

#include <QString>
#include <QVector>

class BFileManager
{
public:
    static QString provideXmlPath(const QString& file);
    static QString provideVideoPath(const QString& file);
    static QString provideSystemsoundsPath(const QString& file);

    static QString provideUniPath(const QString& file);

    static QString providePath(const QString& folder, const QString& file);

    static QString provideQmlPath(const QString& file);

    static QString configFilePath();
    static QString configDir();

    static QVector<QString> baseDirs();
    static QVector<QString> qmlDirs();
private:
    static QVector<QString> S_BaseDirs;
    static QVector<QString> S_QMLDirs;
};

#endif //BFILEMANAGER_H
