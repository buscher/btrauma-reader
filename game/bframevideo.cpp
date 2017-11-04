
#include "bframevideo.h"

#include <QDebug>

BFrameVideo::BFrameVideo(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_zoom(false),
      m_triggerType(BFrameExit::None),
      m_endType(BFrameVideo::Loop),
      m_endFlag(BFrameVideo::None),
      m_volume(0),
      m_setFlag(0)
{
}

BFrameVideo::EndFlag BFrameVideo::endFlag() const
{
    return m_endFlag;
}

BFrameVideo::EndType BFrameVideo::endType() const
{
    return m_endType;
}

QString BFrameVideo::name() const
{
    return m_name;
}

void BFrameVideo::setZoom(bool val)
{
    m_zoom = val;
}

bool BFrameVideo::zoom() const
{
    return m_zoom;
}

void BFrameVideo::setEndFlag(BFrameVideo::EndFlag flag)
{
    m_endFlag = flag;
}

void BFrameVideo::setEndType(BFrameVideo::EndType type)
{
    m_endType = type;
}

void BFrameVideo::setTriggerType(BFrameExit::ExitType type)
{
    m_triggerType = type;
}

void BFrameVideo::setVolume(int vol)
{
    m_volume = vol;
}

BFrameExit::ExitType BFrameVideo::triggerType() const
{
    return m_triggerType;
}

int BFrameVideo::volume() const
{
    return m_volume;
}

double BFrameVideo::volumeFloat() const
{
    return static_cast<double>(m_volume)/100.0;
}

int BFrameVideo::setflag() const
{
    return m_setFlag;
}

void BFrameVideo::setSetFlag(int val)
{
    m_setFlag = val;
}


BFrameVideo::EndFlag BFrameVideo::stringToEndFlag(const QString& flag)
{
    QString flagLower = flag.toLower();
    if (flagLower == QLatin1String("main"))
        return BFrameVideo::Main;
    else if (flagLower == QLatin1String("alt1"))
        return BFrameVideo::Alt1;
    else if (flagLower == QLatin1String("alt2"))
        return BFrameVideo::Alt2;
    else if (flagLower == QLatin1String("alt3"))
        return BFrameVideo::Alt3;
    else
        qDebug() << "unknown endflag:" << flag;
    return BFrameVideo::Main;
}

BFrameVideo::EndType BFrameVideo::stringToEndType(const QString& type)
{
    QString typeLower = type.toLower();
    if (typeLower == QLatin1String("loop"))
        return BFrameVideo::Loop;
    else if (typeLower == QLatin1String("quit"))
        return BFrameVideo::Quit;
    else if (typeLower == QLatin1String("move"))
        return BFrameVideo::Move;
    else if (typeLower == QLatin1String("stay"))
        return BFrameVideo::Stay;
    else
        qDebug() << "unknown endtype:" << type;
    return BFrameVideo::Loop;
}
