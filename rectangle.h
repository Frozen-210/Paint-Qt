#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"
#include "paintscene.h"

class Rectangle : public Figure
{
    Q_OBJECT

public:
    explicit Rectangle(QPointF point,QColor color,int LineWeightbool, bool isFilled, QObject *parent = 0);
    ~Rectangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, bool isFilled);

    float sideLen;
};

#endif // RECTANGLE_H
