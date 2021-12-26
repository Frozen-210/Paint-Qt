#include "line.h"
#include <QPainter>

Line::Line(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Line %1").arg(lCount);
    lCount++;

}


Line::~Line()
{

}


// Реализуем метод отрисовки
void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(shapeColor, LineWeight));

    QLineF line(startPoint().x(),startPoint().y(),endPoint().x(),endPoint().y());
    painter->drawLine(line);
    this->perimeter=line.length();


    Q_UNUSED(option)
    Q_UNUSED(widget)
}
