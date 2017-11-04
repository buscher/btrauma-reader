
#include "game/bcommentonvisit.h"

BCommentOnVisit::BCommentOnVisit(const QString name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_markGroupAsPlayed(false)
{
}

bool BCommentOnVisit::markGroupAsPlayed() const
{
    return m_markGroupAsPlayed;
}

QString BCommentOnVisit::name() const
{
    return m_name;
}

void BCommentOnVisit::setMarkGroupAsPlayed(bool val)
{
    m_markGroupAsPlayed = val;
}

