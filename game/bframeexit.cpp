#include "bframeexit.h"

#include <QDebug>

BFrameExit::BFrameExit(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_trigger(false),
      m_exitType(BFrameExit::None),
      m_doNotForce(false),
      m_onflag(0),
      m_offflag(0)
{
}

bool BFrameExit::doNotForce() const
{
    return m_doNotForce;
}

BFrameExit::ExitType BFrameExit::exitTpye() const
{
    return m_exitType;
}

bool BFrameExit::isVisible() const
{
    if (exitTpye() <= BFrameExit::OverrideRight)
        return true;
    return false;
}

QString BFrameExit::name() const
{
    return m_name;
}

int BFrameExit::offflag() const
{
    return m_offflag;
}

int BFrameExit::onflag() const
{
    return m_onflag;
}

void BFrameExit::setDoNotForce(bool val)
{
    m_doNotForce = val;
}

void BFrameExit::setExitType(BFrameExit::ExitType type)
{
    m_exitType = type;
}

void BFrameExit::setOnflag(int val)
{
    m_onflag = val;
}

void BFrameExit::setOffflag(int val)
{
    m_offflag = val;
}

void BFrameExit::setTrigger(bool trigger)
{
    m_trigger = trigger;
}

BFrameExit::ExitType BFrameExit::stringToExitType(const QString& name)
{
// "OVERRIDE_LEFT"
// "OVERRIDE_RIGHT"
// "LIFT"
// "LEFT"
// "RIGHT"
// "TURN"
// "backzoom"

    QString nameLower = name.toLower();

    if (nameLower == QLatin1String("override_left"))
        return BFrameExit::OverrideLeft;
    else if (nameLower == QLatin1String("override_right"))
        return BFrameExit::OverrideRight;
    else if (nameLower == QLatin1String("lift"))
        return BFrameExit::Lift;
    else if (nameLower == QLatin1String("left"))
        return BFrameExit::Left;
    else if (nameLower == QLatin1String("right"))
        return BFrameExit::Right;
    else if (nameLower == QLatin1String("turn"))
        return BFrameExit::Turn;
    else if (nameLower == QLatin1String("backzoom"))
        return BFrameExit::Backzoom;
    else if (nameLower == QLatin1String("plant")) //unsure
        return BFrameExit::Plant;
    else if (nameLower == QLatin1String("person")) //unsure
        return BFrameExit::Person;
    else if (nameLower == QLatin1String("enter")) //unsure
        return BFrameExit::Enter;
    else if (nameLower == QLatin1String("sink")) //unsure
        return BFrameExit::Sink;
    else if (nameLower == QLatin1String("videomove")) //unsure
        return BFrameExit::VideoMove;
    else if (nameLower == QLatin1String("clone")) //unsure
        return BFrameExit::Clone;
    else
        qDebug() << "unknown ExitTypeString:" << name;
    return BFrameExit::None;
}

bool BFrameExit::trigger() const
{
    return m_trigger;
}

