#include "line.h"
#include <QPainter>

Line::Line(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
}


Line::~Line()
{

}


// Реализуем метод отрисовки
void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(shapeColor, LineWeight));


    painter->drawLine(startPoint().x(),startPoint().y(),endPoint().x(),endPoint().y());


    Q_UNUSED(option)
    Q_UNUSED(widget)
}
