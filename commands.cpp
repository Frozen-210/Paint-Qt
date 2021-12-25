#include "commands.h"
#include<QGraphicsScene>


AddCommand::AddCommand(QGraphicsScene *scene,Figure* item, QPointF LastPoint,QUndoCommand *parent)
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
    myGraphicsScene->update();
}

void AddCommand::redo()
{
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

