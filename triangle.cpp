#include "triangle.h"
#include <QPainter>

Triangle::Triangle(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;

}

Triangle::~Triangle()
{

}

// Реализуем метод отрисовки
void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(shapeColor, LineWeight));
    QPolygonF polygon;



    polygon << QPointF(startPoint().x() + (endPoint().x() > startPoint().x() ? + 1 : - 1)*
                           abs((endPoint().x() - startPoint().x())/2), startPoint().y())
                << QPointF((endPoint().x() > startPoint().x()) ? endPoint().x() : startPoint().x(),
                           endPoint().y())
                << QPointF((endPoint().x() > startPoint().x()) ? startPoint().x() : endPoint().x(),
                           endPoint().y());

    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
