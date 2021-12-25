#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Triangle : public Figure
{
    Q_OBJECT

public:
    explicit Triangle(QPointF point,QColor color,int LineWeight, QObject *parent = 0);

    ~Triangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor shapeColor;
    int LineWeight;

};

#endif // TRIANGLE_H
