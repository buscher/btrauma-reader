
#ifndef BCOMMENTONVISIT_H
#define BCOMMENTONVISIT_H

#include <QObject>
#include <QString>

class BCommentOnVisit : public QObject
{
    Q_OBJECT

public:
    explicit BCommentOnVisit(const QString name, QObject* parent = 0);

    QString name() const;

    bool markGroupAsPlayed() const;
    void setMarkGroupAsPlayed(bool val);

private:
    const QString m_name;
    bool m_markGroupAsPlayed;
};

#endif //BCOMMENTONVISIT_H
