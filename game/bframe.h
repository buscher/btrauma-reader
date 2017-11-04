#ifndef BFRAME_H
#define BFRAME_H

#include <QObject>
#include <QVector>

class BCommentOnVisit;
class BFrameAltMirror;
class BFrameVideo;
class BFrameExit;
class BCommentOnTrigger;

class BFrame : public QObject
{
    Q_OBJECT

public:
    explicit BFrame(const QString& name, QObject* parent = 0);
    ~BFrame();

    QString name() const;

    double x() const;
    double y() const;
    double z() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double rx() const;
    double ry() const;
    double rz() const;
    void setRX(double rx);
    void setRY(double ry);
    void setRZ(double rz);

    double scale() const;
    void setScale(double scale);

    BFrameVideo* video() const;
    void setVideo(BFrameVideo* video);
    BFrameAltMirror* altMirror() const;
    void setAltMirror(BFrameAltMirror* altmirror);

    //optional-main stuff
    int priority() const;
    void setPriority(int prio);

    bool extraBright() const;
    void setExtraBright(bool val);

    double nearPlane() const;
    void setNearPlane(double nearplane);

    double antiGimbleX() const;
    double antiGimbleY() const;
    void setAntiGimbleX(double value);
    void setAntiGimbleY(double value);

    //exit
    int polaroid() const;
    void setPolaroid(int pol);

    bool deadEnd() const;
    void setDeadEnd(bool val);

    int setFlag() const;
    void setSetFlag(int setflag);

    void addVisibleExit(BFrameExit* exit);
    QVector<BFrameExit*> visibleExits() const;
    void addActionExit(BFrameExit* exit);
    QVector<BFrameExit*> actionExits() const;

    //music
    QString bgSound() const;
    void setBgSound(const QString& sound);

    int bgVolume() const;
    void setBgVolume(int vol);

    //sounds
    BCommentOnVisit* commentOnVisit() const;
    void setCommentOnVisit(BCommentOnVisit* visit);

    void addCommentOnTrigger(BCommentOnTrigger* trigger);


private:
    const QString m_name;

    double m_x;
    double m_y;
    double m_z;

    double m_rx;
    double m_ry;
    double m_rz;

    double m_scale;

    BFrameVideo* m_video;
    BFrameAltMirror* m_altMirror;

    int m_priority;

    bool m_extraBright;

    double m_nearplane;

    double m_antiGimbleX; //wth is that?
    double m_antiGimbleY; //wth is that?

    //exit
    int m_polaroid;
    bool m_deadEnd;
    int m_setFlag;

    QVector<BFrameExit*> m_visibleExits;
    QVector<BFrameExit*> m_actionExits;

    //music
    QString m_bgSound;
    int m_bgVolume;

    //sounds
    BCommentOnVisit* m_commentOnVisit;
    QVector<BCommentOnTrigger*> m_commentOnTriggerList;
};

#endif //BFRAME_H
