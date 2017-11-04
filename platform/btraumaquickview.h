
#ifndef BTRAUMAQUICKVIEW_H
#define BTRAUMAQUICKVIEW_H

#include <QQuickView>

class QWindow;

class BTraumaQuickView : public QQuickView
{
public:
    explicit BTraumaQuickView(QWindow *parent = 0);
    
    void setGeometry(const QRect& rect);
    
    void registerGestures();
    void unregisterGestures();
    
protected:
    virtual void resizeEvent(QResizeEvent *);
    
    virtual void mouseMoveEvent(QMouseEvent* ev);

private:

};

#endif //BTRAUMAQUICKVIEW_H
