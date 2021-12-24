#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include "commands.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
undoStack = new QUndoStack(this);
paintingColor=Qt::black;
LineWeight=1;
}

PaintScene::~PaintScene()
{

}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
}

void PaintScene::setColor(QColor color)
{
    paintingColor=color;
}

void PaintScene::setWeight(int Value)
{
    LineWeight=Value;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем конечную координату положения мыши
     * в текущую отрисовываемую фигуру
     * */
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);

    /* Обновляем содержимое сцены,
     * необходимо для устранения артефактов при отрисовке фигур
     * */

    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);

       this->update();
       QUndoCommand *addCommand = new AddCommand(this,tempFigure,startPoint);
       undoStack->push(addCommand);

}

/* Как только нажали кнопку мыши, создаём фигуру одного из трёх типов
 * и помещаем её на сцену, сохранив указатель на неё в переменной
 * tempFigure
 * */
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        startPoint = event->scenePos();
        Square *item = new Square(startPoint,paintingColor,LineWeight);
        EndPoint = event->pos();
        item->setPos(EndPoint);
        tempFigure = item;
        break;
    }
    case RombType: {
        Romb *item = new Romb(event->scenePos());
        item->setPos(event->pos());
        break;
    }
    case TriangleType: {
        Triangle *item = new Triangle(event->scenePos());
        item->setPos(event->pos());
        break;
    }
    default:{
        Square *item = new Square(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    }
    this->addItem(tempFigure);
}


