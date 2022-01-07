#include "rectangle.h"
#include <QPainter>
#include<QUndoCommand>
#include "commands.h"

Rectangle::Rectangle(QPointF point,QColor color,int LineWeight, QObject *parent) :
    Figure(point,parent)
{
    /*
     *  Setting the color and Line weight and then make the name
     *  Accoding to a counter to the class shapes (rCount)
     */
    Q_UNUSED(point)
    shapeColor=color;
    this->LineWeight=LineWeight;
    this->name=QString("Rectangle %1").arg(rCount);
    rCount++;
}



Rectangle::~Rectangle()
{

}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(shapeColor, LineWeight));

    shapeTypeName = "Rectangle";


    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));
    QLineF line(rect.bottomLeft().x(),rect.bottomLeft().y(),rect.bottomRight().x(),rect.bottomRight().y());
    this->sideLen= line.length();
    this-> perimeter=sideLen*4;
    //painter->setBrush(QBrush(Qt::yellow));
    //painter->fillRect(rect, Qt::SolidPattern);

    painter->drawRect(rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

