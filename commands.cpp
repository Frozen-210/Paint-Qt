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
    setText(QObject::tr("Add %1")
        .arg(createCommandString(LastPoint)));
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
    PaintTable::UpdateTable(table, *myGraphicsScene->ItemsVec);


}
QString createCommandString( const QPointF &pos)
{
    return QObject::tr("Square at (%2, %3)")
        .arg(pos.x()).arg(pos.y());
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
    setText(QObject::tr("Add %1")
        .arg(createCommandString(LastPoint)));

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
//    for (int i=0;i<ItemsVec->size();i++){
//       qDebug()<<(*ItemsVec)[i]->name;
//    }
}
QString createDeleteString(const QPointF &pos)
{
    return QObject::tr("Square at (%2, %3)")
        .arg(pos.x()).arg(pos.y());
}

