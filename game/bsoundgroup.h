
#ifndef BSOUNDGROUP_H
#define BSOUNDGROUP_H

#include <QObject>
#include <QString>
#include <QVector>

class BSoundComment;

class BSoundGroup : public QObject
{
    Q_OBJECT

public:
    enum SoundPriority {
        Low,
        Mid,
        High
    };

    explicit BSoundGroup(const QString& name, QObject* parent = 0);
    ~BSoundGroup();

    QString name() const;

    BSoundGroup::SoundPriority soundPriority() const;
    void setSoundPriority(BSoundGroup::SoundPriority val);

    static BSoundGroup::SoundPriority stringToSoundPriority(const QString& prio);

    void addComment(BSoundComment* comment);
    BSoundComment* comment();

    bool played() const;
    void setPlayed(bool val);

    bool ending() const;
    void setEnding(bool val);

private:
    const QString m_name;

    SoundPriority m_soundPriority;

    QVector<BSoundComment*> m_commentList;
    int m_playedIndex;
    bool m_played;
    
    bool m_ending;
};

#endif //BSOUNDGROUP_H
