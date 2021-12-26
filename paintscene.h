#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include<QUndoStack>
#include"square.h"
static QVector<Figure*> v;

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    // Свойство текущего типа используемой фигуры
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:
    QPointF startPoint;
    QPointF EndPoint;

    QUndoStack *undoStack;
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    int typeFigure() const;                 // Возвращение текщего типа
    void setTypeFigure(const int type);     // Установка текущего типа

    // Перечисление типов используемых фигур
    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType,
        LineType
    };
    void setColor(QColor color);
    void setWeight(int Value);

signals:
    void typeFigureChanged();               // Сигнал об изменении типа текущей фигуры

private:
    /* Объект для временного хранения рисуемой фигуры
     * Является объектом базового класса для всех трёх типов фигур в примере
     * */
    Figure *tempFigure;


private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QColor paintingColor;
    int LineWeight;
    int m_typeFigure;


};

#endif // PAINTSCENE_H
