
#ifndef BFRAMEVIDEO_H
#define BFRAMEVIDEO_H

#include <QObject>
#include <QString>

#include "bframeexit.h"

class BFrameVideo : public QObject
{
    Q_OBJECT

public:
    enum EndType {
        Loop = 1,
        Quit,
        Move,
        Stay
    };

    enum EndFlag {
        None = 0,
        Main,
        Alt1,
        Alt2,
        Alt3
    };

    explicit BFrameVideo(const QString& name, QObject* parent = 0);

    QString name() const;

    bool zoom() const;
    void setZoom(bool val);

    BFrameExit::ExitType triggerType() const;
    void setTriggerType(BFrameExit::ExitType type);

    BFrameVideo::EndType endType() const;
    void setEndType(BFrameVideo::EndType type);

    BFrameVideo::EndFlag endFlag() const;
    void setEndFlag(BFrameVideo::EndFlag flag);

    int volume() const;
    double volumeFloat() const;
    void setVolume(int vol);

    int setflag() const;
    void setSetFlag(int val);

    static BFrameVideo::EndType stringToEndType(const QString& type);
    static BFrameVideo::EndFlag stringToEndFlag(const QString& flag);

private:
    const QString m_name;
    bool m_zoom;

    BFrameExit::ExitType m_triggerType;
    BFrameVideo::EndType m_endType;
    BFrameVideo::EndFlag m_endFlag;

    int m_volume;
    int m_setFlag;
};

#endif //BFRAMEVIDEO_H
