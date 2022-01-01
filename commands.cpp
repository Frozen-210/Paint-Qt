#include "commands.h"
#include<QGraphicsScene>
#include "paintscene.h"
//PaintScene p;


AddCommand::AddCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    scene->update();
    ++itemCount;
    setText(QObject::tr("Add %1")
        .arg(createCommandString( LastPoint)));

}

AddCommand::~AddCommand()
{
    if (!myDiagramItem->scene())
        delete myDiagramItem;
}

void AddCommand::undo()
{

    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->pop_back();
    myGraphicsScene->update();
//    for (int i=0;i<v.size();i++){
//        qDebug()<<v[i]->name<<"perimeter "<<v[i]->perimeter;
//    }

}

void AddCommand::redo()
{   myGraphicsScene->ItemsVec->push_back(myDiagramItem);
    myGraphicsScene->addItem(myDiagramItem);
    myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();


}
QString createCommandString( const QPointF &pos)
{
    return QObject::tr("Square at (%2, %3)")
        .arg(pos.x()).arg(pos.y());
}

DeleteCommand::DeleteCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    scene->update();
    ++itemCount;
    setText(QObject::tr("Add %1")
        .arg(createCommandString( LastPoint)));

}

DeleteCommand::~DeleteCommand()
{
    if (!myDiagramItem->scene())
        delete myDiagramItem;
}

void DeleteCommand::undo()
{
        myGraphicsScene->ItemsVec->push_back(myDiagramItem);
        myGraphicsScene->addItem(myDiagramItem);
        myDiagramItem->setPos(initialPosition);
        myGraphicsScene->clearSelection();
        myGraphicsScene->update();
}

void DeleteCommand::redo()
{
    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->remove(myGraphicsScene->ItemsVec->indexOf(myDiagramItem));
    myGraphicsScene->update();
//    for (int i=0;i<ItemsVec->size();i++){
//       qDebug()<<(*ItemsVec)[i]->name;
//    }
}
QString createDeleteString( const QPointF &pos)
{
    return QObject::tr("Square at (%2, %3)")
        .arg(pos.x()).arg(pos.y());
}

