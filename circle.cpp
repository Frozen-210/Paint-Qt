#include "circle.h"
#include <QPainter>
#include <QtMath>

Circle::Circle(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
    /*
     *  Setting the color and Line weight and then make the name
     *  Accoding to a counter to the class shapes (cCount)
     */
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Circle %1").arg(cCount);
    cCount++;
}


Circle::~Circle()
{

}


void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Setting the color and line weight and the shapeType
    painter->setPen(QPen(shapeColor, LineWeight));
    shapeTypeName = "Circle";

    // Determining the raduis
    qreal radius= qSqrt(qPow(startPoint().x()-endPoint().x(),2)+qPow(startPoint().y()-endPoint().y(),2));

    // The draw the circle according to this radius
    painter->drawEllipse(startPoint(),radius,radius);

    // Use the Arc length of circle law to calculate the perimeter
    this->perimeter=2*radius*M_PI;

    Q_UNUSED(option)
    Q_UNUSED(widget)
}