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
    shapeName = "Circle";




    qreal radius= qSqrt(qPow(startPoint().x()-endPoint().x(),2)+qPow(startPoint().y()-endPoint().y(),2));

    painter->drawEllipse(startPoint(),radius,radius);
    this->perimeter=2*radius*M_PI;




    Q_UNUSED(option)
    Q_UNUSED(widget)
}
