#ifndef CIRCLE_H
#define CIRCLE_H
#include "rectangle.h"

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Circle : public Figure
{
    Q_OBJECT

public:

    explicit Circle(QPointF point,QColor color,int LineWeight, bool isFilled, QObject *parent = 0);
    ~Circle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, bool isFilled);

};

#endif // CIRCLE_H
