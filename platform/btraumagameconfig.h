#ifndef BTRAUMAGAMECONFIG_H
#define BTRAUMAGAMECONFIG_H

#include <QObject>
#include <QRect>
#include <QHash>
#include <QString>

class BTraumaQuickView;
class BTraumaLevelConfig;

class BTraumaGameConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool fullScreen READ fullScreen WRITE setFullScreen NOTIFY fullScreenChanged)

    Q_PROPERTY(double volumeMaster READ volumeMaster WRITE setVolumeMaster NOTIFY volumeMasterChanged)
    Q_PROPERTY(double volumeMusic READ volumeMusic WRITE setVolumeMusic NOTIFY volumeMusicChanged)
    Q_PROPERTY(double volumeVoice READ volumeVoice WRITE setVolumeVoice NOTIFY volumeVoiceChanged)
    Q_PROPERTY(double volumeSound READ volumeSound WRITE setVolumeSound NOTIFY volumeSoundChanged)
public:
    static BTraumaGameConfig* instance();

    void setView(BTraumaQuickView* view);

    bool fullScreen() const;
    bool introPlayed() const;
    bool outroPlayed() const;

    double volumeMaster() const;
    double volumeMusic() const;
    double volumeVoice() const;
    double volumeSound() const;

public slots:
    void toggleFullScreen();
    void setFullScreen(bool val);

    void setIntroPlayed(bool val);
    void setOutroPlayed(bool val);

    void setVolumeMaster(double val);
    void setVolumeMusic(double val);
    void setVolumeVoice(double val);
    void setVolumeSound(double val);

    void writeConfig();
    void readConfig();

    BTraumaLevelConfig* level(const QString& name);

signals:
    void fullScreenChanged();

    void volumeMasterChanged();
    void volumeMusicChanged();
    void volumeVoiceChanged();
    void volumeSoundChanged();

private:
    static BTraumaGameConfig* Instance;

    BTraumaGameConfig(QObject* parent = 0);

    BTraumaQuickView* m_view;
    QRect m_windowGeometry;

    bool m_fullScreen;

    bool m_introPlayed;
    bool m_outroPlayed;

    double m_volumeMaster;
    double m_volumeMusic;
    double m_volumeVoice;
    double m_volumeSound;
    
    QHash<QString, BTraumaLevelConfig*> m_levels;
};

#endif //BTRAUMAGAMECONFIG_H
