#ifndef COMMANDS_H
#define COMMANDS_H
#include"romb.h"
#include <QUndoCommand>

#include "square.h"

class AddCommand : public QUndoCommand
{
public:
    AddCommand(QGraphicsScene *graphicsScene,
               Figure* item,QPointF LastPoint,QUndoCommand *parent = 0);

    ~AddCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
  //  Square *myDiagramItem;
    Figure *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
    QPointF initialPosition;
};
 QString createCommandString( const QPointF &point);

#endif // COMMANDS_H
