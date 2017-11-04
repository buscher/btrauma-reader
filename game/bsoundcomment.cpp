
#include "bsoundcomment.h"

#include <QDebug>

BSoundComment::BSoundComment()
    : QObject(),
      m_subdelay(0)
{
}

void BSoundComment::addSubtitle(int lang, const QString& string)
{
    m_subtitles.insert(lang, string);
}

void BSoundComment::setSound(const QString& sound)
{
    m_sound = sound;
}

QString BSoundComment::sound() const
{
    return m_sound;
}

QString BSoundComment::subtitle(int lang) const
{
    if (m_subtitles.contains(lang))
        return m_subtitles.value(lang);

    qDebug() << "does not contain lang number:" << lang;
    return QString();
}

void BSoundComment::setSubdelay(int delay)
{
    m_subdelay = delay;
}

int BSoundComment::subdelay() const
{
    return m_subdelay;
}
