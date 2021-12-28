#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Square : public Figure
{
    Q_OBJECT

public:
    explicit Square(QPointF point,QColor color,int LineWeight, QObject *parent = 0);
    ~Square();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float sideLen;
};

#endif // SQUARE_H
