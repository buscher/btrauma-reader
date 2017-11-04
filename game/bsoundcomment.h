
#ifndef BSOUNDCOMMENT_H
#define BSOUNDCOMMENT_H

#include <QObject>
#include <QHash>

class BSoundComment : public QObject
{
    Q_OBJECT

public:
    enum Language {
        English     = 1,
        German      = 2,
        Russian     = 3,
        Japanse     = 4
    };

    BSoundComment();

    void addSubtitle(int lang, const QString& string);
    QString subtitle(int lang) const;

    void setSound(const QString& sound);
    QString sound() const;

    int subdelay() const;
    void setSubdelay(int delay);

private:
    QString m_sound;
    int m_subdelay;
    QHash<int, QString> m_subtitles;
};

#endif //BSOUNDCOMMENT_H
