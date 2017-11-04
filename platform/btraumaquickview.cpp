
#include "btraumaquickview.h"

#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>

BTraumaQuickView::BTraumaQuickView(QWindow* parent)
    : QQuickView(parent)
{
}

void BTraumaQuickView::setGeometry(const QRect& rect)
{
//     qDebug() << rect;
    setMinimumWidth(rect.height() * 700/525);
    QQuickView::setGeometry(rect);
}

void BTraumaQuickView::registerGestures()
{
    //TODO
}

void BTraumaQuickView::unregisterGestures()
{
    //TODO
}

void BTraumaQuickView::resizeEvent(QResizeEvent* event)
{
//     qDebug() << event->size();
    setMinimumWidth(event->size().height() * 700/525);

    QQuickView::resizeEvent(event);
}

void BTraumaQuickView::mouseMoveEvent(QMouseEvent* ev)
{
//     qDebug() << ev->pos();
    QQuickView::mouseMoveEvent(ev);
}
