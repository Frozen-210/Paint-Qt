#include "romb.h"
#include <QPainter>

Romb::Romb(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
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


    Q_UNUSED(option)
    Q_UNUSED(widget)
}
