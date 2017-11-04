#include "bframe.h"

#include "bframevideo.h"
#include "bframealtmirror.h"
#include "bcommentonvisit.h"
#include "bframeexit.h"
#include "bcommentontrigger.h"

BFrame::BFrame(const QString& name, QObject* parent)
    : QObject(parent),
      m_name(name),
      m_scale(1.0),
      m_video(0),
      m_altMirror(0),
      m_priority(0), //find correct default
      m_extraBright(false),
      m_nearplane(0),
      m_antiGimbleX(0),
      m_antiGimbleY(0),
      m_polaroid(-1),
      m_deadEnd(false),
      m_commentOnVisit(0)
{
}

BFrame::~BFrame()
{
    delete m_video;
    m_video = 0;

    delete m_altMirror;
    m_altMirror = 0;

    while (!m_visibleExits.isEmpty())
        delete m_visibleExits.takeFirst();

    while (!m_actionExits.isEmpty())
        delete m_actionExits.takeFirst();

    delete m_commentOnVisit;
    m_commentOnVisit = 0;

    while (!m_commentOnTriggerList.isEmpty())
        delete m_commentOnTriggerList.takeFirst();
}

QString BFrame::name() const
{
    return m_name;
}

double BFrame::antiGimbleX() const
{
    return m_antiGimbleX;
}

double BFrame::antiGimbleY() const
{
    return m_antiGimbleY;
}

double BFrame::nearPlane() const
{
    return m_nearplane;
}

int BFrame::priority() const
{
    return m_priority;
}

double BFrame::rx() const
{
    return m_rx;
}

double BFrame::ry() const
{
    return m_ry;
}

double BFrame::rz() const
{
    return m_rz;
}

double BFrame::scale() const
{
    return m_scale;
}

void BFrame::setAntiGimbleX(double value)
{
    m_antiGimbleX = value;
}

void BFrame::setAntiGimbleY(double value)
{
    m_antiGimbleY = value;
}

void BFrame::setNearPlane(double nearplane)
{
    m_nearplane = nearplane;
}

void BFrame::setPriority(int prio)
{
    m_priority = prio;
}

void BFrame::setRX(double rx)
{
    m_rx = rx;
}

void BFrame::setRY(double ry)
{
    m_ry = ry;
}

void BFrame::setRZ(double rz)
{
    m_rz = rz;
}

void BFrame::setScale(double scale)
{
    m_scale = scale;
}

void BFrame::setX(double x)
{
    m_x = x;
}

void BFrame::setY(double y)
{
    m_y = y;
}

void BFrame::setZ(double z)
{
    m_z = z;
}

double BFrame::x() const
{
    return m_x;
}

double BFrame::y() const
{
    return m_y;
}

double BFrame::z() const
{
    return m_z;
}

bool BFrame::extraBright() const
{
    return m_extraBright;
}

void BFrame::setExtraBright(bool val)
{
    m_extraBright = val;
}

int BFrame::polaroid() const
{
    return m_polaroid;
}

void BFrame::setPolaroid(int pol)
{
    m_polaroid = pol;
}

bool BFrame::deadEnd() const
{
    return m_deadEnd;
}

void BFrame::setDeadEnd(bool val)
{
    m_deadEnd = val;
}

int BFrame::setFlag() const
{
    return m_setFlag;
}

void BFrame::setSetFlag(int setflag)
{
    m_setFlag = setflag;
}

QVector< BFrameExit* > BFrame::actionExits() const
{
    return m_actionExits;
}

QVector< BFrameExit* > BFrame::visibleExits() const
{
    return m_visibleExits;
}

void BFrame::addActionExit(BFrameExit* exit)
{
    m_actionExits.append(exit);
}

void BFrame::addVisibleExit(BFrameExit* exit)
{
    m_visibleExits.append(exit);
}

void BFrame::setVideo(BFrameVideo* video)
{
    m_video = video;
}

BFrameVideo* BFrame::video() const
{
    return m_video;
}

BFrameAltMirror* BFrame::altMirror() const
{
    return m_altMirror;
}

void BFrame::setAltMirror(BFrameAltMirror* altmirror)
{
    m_altMirror = altmirror;
}

QString BFrame::bgSound() const
{
    return m_bgSound;
}

int BFrame::bgVolume() const
{
    return m_bgVolume;
}

void BFrame::setBgSound(const QString& sound)
{
    m_bgSound = sound;
}

void BFrame::setBgVolume(int vol)
{
    m_bgVolume = vol;
}

BCommentOnVisit* BFrame::commentOnVisit() const
{
    return m_commentOnVisit;
}

void BFrame::setCommentOnVisit(BCommentOnVisit* visit)
{
    m_commentOnVisit = visit;
}

void BFrame::addCommentOnTrigger(BCommentOnTrigger* trigger)
{
    m_commentOnTriggerList.append(trigger);
}


