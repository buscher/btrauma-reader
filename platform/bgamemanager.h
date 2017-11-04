#ifndef BGAMEMANAGER_H
#define BGAMEMANAGER_H

#include <QObject>

class BTraumaQuickView;
class BLevel;

class BGameManager : public QObject
{
    Q_OBJECT
public:
    enum GameState
    {
        Intro = 1,
        Menu,
        Level
    };

    explicit BGameManager(QObject* parent = 0);

public slots:
    void introFinished();
    
    void loadLevel(const QString& levelId);

private:
    
    void setTargetQml(const QString& file);
    void setMainFrame(const QString& id, const QString& file);
    
    GameState m_state;
    BTraumaQuickView* m_view;
    BLevel* m_level;
};

#endif //BGAMEMANAGER_H
