#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include<QUndoStack>
#include"square.h"
#include <QGraphicsView>


class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:
    QGraphicsView* view;
    QPointF startPoint;
    QPointF EndPoint;
    QVector<Figure*> *ItemsVec;
    QUndoStack *undoStack;
    explicit PaintScene(QGraphicsView *view, QObject *parent = 0);
    ~PaintScene();

    int typeFigure() const;
    void setTypeFigure(const int type);

    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType,
        LineType,
        EraserType
    };
    void setColor(QColor color);
    void setWeight(int Value);

signals:
    void typeFigureChanged();

private:
    Figure *tempFigure;


private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QColor paintingColor;
    int LineWeight;
    int m_typeFigure;
    bool selectingItem;


};

#endif // PAINTSCENE_H
