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

