
#ifndef BCOMMENTONTRIGGER_H
#define BCOMMENTONTRIGGER_H

#include <QObject>
#include "bframeexit.h"

class BCommentOnTrigger : public QObject
{
    Q_OBJECT

public:
    explicit BCommentOnTrigger(const QString& name, QObject* parent = 0);

    QString name() const;

    BFrameExit::ExitType gesture() const;
    void setGesture(BFrameExit::ExitType type);

    bool showFail() const;
    void setShowFail(bool val);

    bool ignorePlayed() const;
    void setIgnorePlayed(bool val);

private:
    const QString m_name;

    BFrameExit::ExitType m_gesture;
    bool m_showFail;
    bool m_ignorePlayed;
};

#endif //BCOMMENTONTRIGGER_H
