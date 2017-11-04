#ifndef btrauma_reader_H
#define btrauma_reader_H

#include <QObject>
#include <QString>

class BLevel;

class BTraumaReader : public QObject
{
Q_OBJECT
public:
    BTraumaReader();
    virtual ~BTraumaReader();

    static BLevel* readLevel(const QString& name);

private:
    static BLevel* readFrames(const QString& name);
    static BLevel* readExits(BLevel* level);
    static BLevel* readMusic(BLevel* level);
    static BLevel* readSoundGroups(BLevel* level);
    static BLevel* readSounds(BLevel* level);
};

#endif // btrauma_reader_H
