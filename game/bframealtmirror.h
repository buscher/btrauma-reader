
#ifndef BFRAMEALTMIRROR_H
#define BFRAMEALTMIRROR_H
#include <QObject>

class BFrameAltMirror : public QObject
{
    Q_OBJECT

public:
    explicit BFrameAltMirror(const QString& name, QObject* parent = 0);

    QString name() const;

    int onflag() const;
    void setOnflag(int val);

private:
    const QString m_name;
    int m_onflag;
};

#endif //BFRAMEALTMIRROR_H
