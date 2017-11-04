
#include "btraumalevelconfig.h"

BTraumaLevelConfig::BTraumaLevelConfig(QObject* parent)
    : QObject(parent),
      m_mainEnd(false),
      m_altEnd1(false),
      m_altEnd2(false),
      m_altEnd3(false),
      m_photo1(false),
      m_photo2(false),
      m_photo3(false),
      m_photo4(false),
      m_photo5(false),
      m_photo6(false),
      m_photo7(false),
      m_photo8(false),
      m_photo9(false)
{
}

bool BTraumaLevelConfig::mainEnd() const
{
#warning test
    return true;
    return m_mainEnd;
}

bool BTraumaLevelConfig::altEnd1() const
{
    return m_altEnd1;
}

bool BTraumaLevelConfig::altEnd2() const
{
    return m_altEnd2;
}

bool BTraumaLevelConfig::altEnd3() const
{
    return m_altEnd3;
}

bool BTraumaLevelConfig::photo1() const
{
    return m_photo1;
}

bool BTraumaLevelConfig::photo2() const
{
    return m_photo2;
}

bool BTraumaLevelConfig::photo3() const
{
#warning test
    return true;
    return m_photo3;
}

bool BTraumaLevelConfig::photo4() const
{
    return m_photo4;
}

bool BTraumaLevelConfig::photo5() const
{
    return m_photo5;
}

bool BTraumaLevelConfig::photo6() const
{
    return m_photo6;
}

bool BTraumaLevelConfig::photo7() const
{
    return m_photo7;
}

bool BTraumaLevelConfig::photo8() const
{
    return m_photo8;
}

bool BTraumaLevelConfig::photo9() const
{
    return m_photo9;
}

int BTraumaLevelConfig::photosFound()
{
    int found = 0;

    if (photo1())
        ++found;
    if (photo2())
        ++found;
    if (photo3())
        ++found;
    if (photo4())
        ++found;
    if (photo5())
        ++found;
    if (photo6())
        ++found;
    if (photo7())
        ++found;
    if (photo8())
        ++found;
    if (photo9())
        ++found;

    return found;
}

void BTraumaLevelConfig::setMainEnd(bool val)
{
    m_mainEnd = val;
    emit mainEndChanged();
}

void BTraumaLevelConfig::setAltEnd1(bool val)
{
    m_altEnd1 = val;
    emit altEnd1Changed();
}

void BTraumaLevelConfig::setAltEnd2(bool val)
{
    m_altEnd2 = val;
    emit altEnd2Changed();
}

void BTraumaLevelConfig::setAltEnd3(bool val)
{
    m_altEnd3 = val;
    emit altEnd3Changed();
}

void BTraumaLevelConfig::setPhoto1(bool val)
{
    m_photo1 = val;
    emit photo1Changed();
}

void BTraumaLevelConfig::setPhoto2(bool val)
{
    m_photo2 = val;
    emit photo2Changed();
}

void BTraumaLevelConfig::setPhoto3(bool val)
{
    m_photo3 = val;
    emit photo3Changed();
}

void BTraumaLevelConfig::setPhoto4(bool val)
{
    m_photo4 = val;
    emit photo4Changed();
}

void BTraumaLevelConfig::setPhoto5(bool val)
{
    m_photo5 = val;
    emit photo5Changed();
}

void BTraumaLevelConfig::setPhoto6(bool val)
{
    m_photo6 = val;
    emit photo6Changed();
}

void BTraumaLevelConfig::setPhoto7(bool val)
{
    m_photo7 = val;
    emit photo7Changed();
}

void BTraumaLevelConfig::setPhoto8(bool val)
{
    m_photo8 = val;
    emit photo8Changed();
}

void BTraumaLevelConfig::setPhoto9(bool val)
{
    m_photo9 = val;
    emit photo9Changed();
}



#include "btraumalevelconfig.moc"
