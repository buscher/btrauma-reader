
#include "bframealtmirror.h"

BFrameAltMirror::BFrameAltMirror(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name)
{
}

QString BFrameAltMirror::name() const
{
    return m_name;
}

int BFrameAltMirror::onflag() const
{
    return m_onflag;
}

void BFrameAltMirror::setOnflag(int val)
{
    m_onflag = val;
}

