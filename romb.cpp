#include "romb.h"
#include <QPainter>
#include <QtMath>

Romb::Romb(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Circle %1").arg(cCount);
    cCount++;

}


Romb::~Romb()
{

}


// Реализуем метод отрисовки
void Romb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(shapeColor, LineWeight));

    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().x() - startPoint().x()));

   // painter->drawRect(rect);
    painter->drawEllipse(rect);
    QLineF line(rect.bottomLeft().x(),rect.bottomLeft().y(),rect.bottomRight().x(),rect.bottomRight().y());
    this->perimeter=line.length()*M_PI;
    painter->drawEllipse(rect);




    Q_UNUSED(option)
    Q_UNUSED(widget)
}
