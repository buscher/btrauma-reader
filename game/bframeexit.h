#ifndef BFRAMEEXIT_H
#define BFRAMEEXIT_H

#include <QObject>

class BFrameExit : public QObject
{
    Q_OBJECT

public:
    
// "OVERRIDE_LEFT"
// "OVERRIDE_RIGHT"
// "LIFT"
// "LEFT"
// "RIGHT"
// "TURN"
// "backzoom"

    enum ExitType {
        None         = 0, //default
        OverrideLeft = 1,
        OverrideRight,
        Lift,
        Left,
        Right,
        Turn,
        Backzoom,
        Plant,
        Person,
        Enter,
        Sink,
        VideoMove,
        Clone
    };

    explicit BFrameExit(const QString& name, QObject* parent = 0);

    QString name() const;

    bool trigger() const;
    void setTrigger(bool trigger);

    ExitType exitTpye() const;
    void setExitType(BFrameExit::ExitType type);

    bool doNotForce() const;
    void setDoNotForce(bool val);

    int onflag() const;
    int offflag() const;
    void setOnflag(int val);
    void setOffflag(int val);

    bool isVisible() const;

    static BFrameExit::ExitType stringToExitType(const QString& name);

private:
    const QString m_name;
    bool m_trigger;
    ExitType m_exitType;
    bool m_doNotForce; //?
    int m_onflag;
    int m_offflag;
};

#endif //BFRAMEEXIT_H
