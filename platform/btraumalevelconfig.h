
#ifndef BTRAUMALEVELCONFIG_H
#define BTRAUMALEVELCONFIG_H

#include <QObject>

class BTraumaLevelConfig : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool mainEnd READ mainEnd WRITE setMainEnd NOTIFY mainEndChanged)
    Q_PROPERTY(bool altEnd1 READ altEnd1 WRITE setAltEnd1 NOTIFY altEnd1Changed)
    Q_PROPERTY(bool altEnd2 READ altEnd2 WRITE setAltEnd2 NOTIFY altEnd2Changed)
    Q_PROPERTY(bool altEnd3 READ altEnd3 WRITE setAltEnd3 NOTIFY altEnd3Changed)

    Q_PROPERTY(bool photo1 READ photo1 WRITE setPhoto1 NOTIFY photo1Changed)
    Q_PROPERTY(bool photo2 READ photo2 WRITE setPhoto2 NOTIFY photo2Changed)
    Q_PROPERTY(bool photo3 READ photo3 WRITE setPhoto3 NOTIFY photo3Changed)
    Q_PROPERTY(bool photo4 READ photo4 WRITE setPhoto4 NOTIFY photo4Changed)
    Q_PROPERTY(bool photo5 READ photo5 WRITE setPhoto5 NOTIFY photo5Changed)
    Q_PROPERTY(bool photo6 READ photo6 WRITE setPhoto6 NOTIFY photo6Changed)
    Q_PROPERTY(bool photo7 READ photo7 WRITE setPhoto7 NOTIFY photo7Changed)
    Q_PROPERTY(bool photo8 READ photo8 WRITE setPhoto8 NOTIFY photo8Changed)
    Q_PROPERTY(bool photo9 READ photo9 WRITE setPhoto9 NOTIFY photo9Changed)

public:
    explicit BTraumaLevelConfig(QObject* parent = 0);

public slots:
    bool mainEnd() const;
    bool altEnd1() const;
    bool altEnd2() const;
    bool altEnd3() const;

    bool photo1() const;
    bool photo2() const;
    bool photo3() const;
    bool photo4() const;
    bool photo5() const;
    bool photo6() const;
    bool photo7() const;
    bool photo8() const;
    bool photo9() const;

    int photosFound();

    void setMainEnd(bool val);
    void setAltEnd1(bool val);
    void setAltEnd2(bool val);
    void setAltEnd3(bool val);

    void setPhoto1(bool val);
    void setPhoto2(bool val);
    void setPhoto3(bool val);
    void setPhoto4(bool val);
    void setPhoto5(bool val);
    void setPhoto6(bool val);
    void setPhoto7(bool val);
    void setPhoto8(bool val);
    void setPhoto9(bool val);

signals:
    void mainEndChanged();
    void altEnd1Changed();
    void altEnd2Changed();
    void altEnd3Changed();

    void photo1Changed();
    void photo2Changed();
    void photo3Changed();
    void photo4Changed();
    void photo5Changed();
    void photo6Changed();
    void photo7Changed();
    void photo8Changed();
    void photo9Changed();

private:
    bool m_mainEnd;
    bool m_altEnd1;
    bool m_altEnd2;
    bool m_altEnd3;

    bool m_photo1;
    bool m_photo2;
    bool m_photo3;
    bool m_photo4;
    bool m_photo5;
    bool m_photo6;
    bool m_photo7;
    bool m_photo8;
    bool m_photo9;
};

#endif //BTRAUMALEVELCONFIG_H
