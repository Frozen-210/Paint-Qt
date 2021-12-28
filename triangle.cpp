#include "triangle.h"
#include <QPainter>

Triangle::Triangle(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Triangle %1").arg(tCount);
    tCount++;
    this->perimeter=side1+side2+side3;

}

Triangle::~Triangle()
{

}

// Реализуем метод отрисовки
void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(shapeColor, LineWeight));
    QPolygonF polygon;
    shapeName = "Triangle";


    QPointF p1(startPoint().x() + (endPoint().x() > startPoint().x() ? + 1 : - 1)*
                              abs((endPoint().x() - startPoint().x())/2), startPoint().y());
    QPointF p2((endPoint().x() > startPoint().x()) ? endPoint().x() : startPoint().x(),
                              endPoint().y());
    QPointF p3((endPoint().x() > startPoint().x()) ? startPoint().x() : endPoint().x(),
                               endPoint().y());
    polygon <<p1<<p2<< p3;

    QLineF line1(p1.x(),p1.y(),p2.x(),p2.y());
    QLineF line2(p1.x(),p1.y(),p3.x(),p3.y());
    QLineF line3(p2.x(),p2.y(),p2.x(),p2.y());

    this->side1=line1.length();
    this->side2=line2.length();
    this->side3=line3.length();
    this->perimeter=side1+side2+side3;



    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
