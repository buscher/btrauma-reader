
#include "bcommentontrigger.h"

BCommentOnTrigger::BCommentOnTrigger(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_gesture(BFrameExit::None),
      m_showFail(false),
      m_ignorePlayed(false)
{
}

BFrameExit::ExitType BCommentOnTrigger::gesture() const
{
    return m_gesture;
}

bool BCommentOnTrigger::ignorePlayed() const
{
    return m_ignorePlayed;
}

QString BCommentOnTrigger::name() const
{
    return m_name;
}

bool BCommentOnTrigger::showFail() const
{
    return m_showFail;
}

void BCommentOnTrigger::setGesture(BFrameExit::ExitType type)
{
    m_gesture = type;
}

void BCommentOnTrigger::setIgnorePlayed(bool val)
{
    m_ignorePlayed = val;
}

void BCommentOnTrigger::setShowFail(bool val)
{
    m_showFail = val;
}
