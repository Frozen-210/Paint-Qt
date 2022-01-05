#include "commands.h"
#include<QGraphicsScene>
#include "paintscene.h"
#include"painttable.h"
//PaintScene p;


AddCommand::AddCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QTableWidget* table,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    scene->update();
    ++itemCount;
    this->table= table;
    Q_UNUSED(LastPoint)

}

AddCommand::~AddCommand()
{
    if (!myDiagramItem->scene())
        myDiagramItem->hide();
}

void AddCommand::undo()
{

    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->pop_back();
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);


}

void AddCommand::redo()
{   myGraphicsScene->ItemsVec->push_back(myDiagramItem);
    myGraphicsScene->addItem(myDiagramItem);
    myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);


}

DeleteCommand::DeleteCommand(PaintScene *scene,Figure* item, QPointF LastPoint,QTableWidget* table,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = item;
    this->table= table;
    scene->update();
    ++itemCount;
    Q_UNUSED(LastPoint)


}

DeleteCommand::~DeleteCommand()
{
    if (!myDiagramItem->scene())
        myDiagramItem->hide();
}

void DeleteCommand::undo()
{
        myGraphicsScene->ItemsVec->push_back(myDiagramItem);
        myGraphicsScene->addItem(myDiagramItem);
        myDiagramItem->setPos(initialPosition);
        myGraphicsScene->clearSelection();
        myGraphicsScene->update();
        PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);
}

void DeleteCommand::redo()
{
    myGraphicsScene->removeItem(myDiagramItem);
    // remove figure from the vector
    myGraphicsScene->ItemsVec->remove(myGraphicsScene->ItemsVec->indexOf(myDiagramItem));
    myGraphicsScene->update();
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);

}

