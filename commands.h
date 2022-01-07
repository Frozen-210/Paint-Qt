#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "figure.h"
#include "paintscene.h"
#include "rectangle.h"
#include <QTableWidget>

class AddCommand : public QUndoCommand
{
public:
    AddCommand(PaintScene *graphicsScene,
               Figure* item,QPointF LastPoint,QTableWidget* table,QUndoCommand *parent = 0);

    ~AddCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Figure *myDiagramItem;
    PaintScene *myGraphicsScene;
    QPointF initialPosition;
    QTableWidget* table;
    bool WasModified;
    bool IsFirstTime;
    bool WillModify;
};


 class DeleteCommand : public QUndoCommand
 {
 public:
     DeleteCommand(PaintScene *graphicsScene,
                Figure* item,QPointF LastPoint,QTableWidget* table,QUndoCommand *parent = 0);

     ~DeleteCommand();

     void undo() Q_DECL_OVERRIDE;
     void redo() Q_DECL_OVERRIDE;

 private:
     Figure *myDiagramItem;
     PaintScene *myGraphicsScene;
     QPointF initialPosition;
     QTableWidget* table;
     bool WasModified;
     bool IsFirstTime;
     bool WillModify;
     int ItemIndex;
 };

 class ButtonsCommand{
 public:
     static void clearScene(PaintScene* scene);
 };

#endif // COMMANDS_H
