#include "blevel.h"

#include <QDebug>

BLevel::BLevel(const QString& configFileName, QObject* parent)
    : QObject(parent),
      m_configFileName(configFileName),
      m_version(1),
      m_firstFrame(0),
      m_defaultSoundGroupVolume(100)
{
}

int BLevel::version() const
{
    return m_version;
}

void BLevel::setVersion(int ver)
{
    m_version = ver;
}

void BLevel::addFrame(const QString& name, BFrame* frame)
{
    if (!m_firstFrame)
        m_firstFrame = frame;
    m_frameHash.insert(name, frame);
}

BFrame* BLevel::frame(const QString& name) const
{
    if (m_frameHash.contains(name))
        return m_frameHash.value(name);
    return 0;
//     return m_frameHash.value(name);
}

BFrame* BLevel::firstFrame() const
{
    return m_firstFrame;
}

QString BLevel::name() const
{
    return m_name;
}

QString BLevel::configFileName() const
{
    return m_configFileName;
}

int BLevel::defaultSoundGroupVolume() const
{
    return m_defaultSoundGroupVolume;
}

void BLevel::setDefaultSoundGroupVolume(int vol)
{
    m_defaultSoundGroupVolume = vol;
}

void BLevel::addSoundGroup(const QString& name, BSoundGroup* group)
{
    m_soundGroups.insert(name, group);
}

BSoundGroup* BLevel::soundGroup(const QString& name) const
{
    if (m_soundGroups.contains(name))
        return m_soundGroups.value(name);
    
    qDebug() << "level does NOT contain soundgroup:" << name;
    return 0;
}

