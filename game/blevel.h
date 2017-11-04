
#ifndef BLEVEL_H
#define BLEVEL_H

#include <QObject>
#include <QHash>
#include <QString>

class BSoundGroup;
class BFrame;

class BLevel: public QObject
{
    Q_OBJECT

public:
    explicit BLevel(const QString& configFileName, QObject* parent = 0);

    int version() const;
    void setVersion(int ver);

    void addFrame(const QString& name, BFrame* frame);
    BFrame* frame(const QString& name) const;
    BFrame* firstFrame() const;

    QString name() const;
    QString configFileName() const;

    int defaultSoundGroupVolume() const;
    void setDefaultSoundGroupVolume(int vol);

    void addSoundGroup(const QString& name, BSoundGroup* group);
    BSoundGroup* soundGroup(const QString& name) const;

private:
    const QString m_name;
    QString m_configFileName;

    int m_version;
    QHash<QString, BFrame*> m_frameHash;
    BFrame* m_firstFrame;

    //soundgroup
    int m_defaultSoundGroupVolume;
    QHash<QString, BSoundGroup*> m_soundGroups;
};

#endif //BLEVEL_H
