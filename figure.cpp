#include "figure.h"
#include <QPainter>

Figure::Figure(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    setFlag(QGraphicsItem::ItemIsSelectable);

    connect(this, &Figure::pointChanged, this, &Figure::updateRomb);
}

Figure::~Figure()
{

}

QRectF Figure::boundingRect() const
{

    return QRectF((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                  (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                  qAbs(endPoint().x() - startPoint().x()) + 10,
                  qAbs(endPoint().y() - startPoint().y()) + 10);
}

void Figure::updateRomb()
{
    this->update((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                 (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                 qAbs(endPoint().x() - startPoint().x()) + 10,
                 qAbs(endPoint().y() - startPoint().y()) + 10);
}

void Figure::setStartPoint(const QPointF point)
{
    m_startPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setEndPoint(const QPointF point, bool test)
{
    if(test){
    m_endPoint = mapFromScene(point);
    emit pointChanged();}
    else{
        m_endPoint = point;
        emit pointChanged();
    }
}

QPointF Figure::startPoint() const
{
    return m_startPoint;
}

QPointF Figure::endPoint() const
{
    return m_endPoint;
}
