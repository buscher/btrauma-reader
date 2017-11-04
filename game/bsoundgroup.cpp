
#include "bsoundgroup.h"

#include <QDebug>

#include "bsoundcomment.h"

BSoundGroup::BSoundGroup(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_soundPriority(BSoundGroup::Mid),
      m_playedIndex(0),
      m_played(false),
      m_ending(false)
{
}

BSoundGroup::~BSoundGroup()
{
    while (!m_commentList.isEmpty())
        delete m_commentList.takeFirst();
}

void BSoundGroup::addComment(BSoundComment* comment)
{
    m_commentList.append(comment);
}

BSoundComment* BSoundGroup::comment()
{
    BSoundComment* ret = m_commentList.at(m_playedIndex);
    Q_ASSERT(ret != 0);

    m_playedIndex++;
    if (m_playedIndex >= m_commentList.count())
        m_playedIndex = 0;
    return ret;
}

QString BSoundGroup::name() const
{
    return m_name;
}

void BSoundGroup::setSoundPriority(BSoundGroup::SoundPriority val)
{
    m_soundPriority = val;
}

BSoundGroup::SoundPriority BSoundGroup::soundPriority() const
{
    return m_soundPriority;
}

BSoundGroup::SoundPriority BSoundGroup::stringToSoundPriority(const QString& prio)
{
    QString prioLower = prio.toLower();

    if (prioLower == QLatin1String("low"))
        return BSoundGroup::Low;
    else if (prioLower == QLatin1String("mid"))
        return BSoundGroup::Mid;
    else if (prioLower == QLatin1String("high"))
        return BSoundGroup::High;

    qDebug() << "unknown soundpriority:" << prio;
    return BSoundGroup::Mid;
}

bool BSoundGroup::played() const
{
    return m_played;
}

void BSoundGroup::setPlayed(bool val)
{
    m_played = val;
}

bool BSoundGroup::ending() const
{
    return m_ending;
}

void BSoundGroup::setEnding(bool val)
{
    m_ending = val;
}

