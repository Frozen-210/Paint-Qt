#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include<QColor>
static int lCount=1;
static int rCount=1;
static int cCount=1;
static int tCount=1;


class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint
               READ startPoint WRITE setStartPoint
               NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint
               READ endPoint WRITE setEndPoint
               NOTIFY pointChanged)
public:
    explicit Figure(QPointF point, QObject *parent = 0);
    ~Figure();

    QPointF startPoint() const;
    QPointF endPoint() const;

    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point, bool test= true);

    float perimeter;
    QString name;
    QColor shapeColor;
    int LineWeight;
    QString shapeName;


signals:
    void pointChanged();



private:
    QPointF m_startPoint;
    QPointF m_endPoint;

    QRectF boundingRect() const;


public slots:
    void updateRomb();
};

#endif // FIGURE_H
