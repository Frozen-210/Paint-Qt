#ifndef COMMANDS_H
  #define COMMANDS_H

  #include <QUndoCommand>

  #include "diagramitem.h"

  class MoveCommand : public QUndoCommand
  {
  public:
      enum { Id = 1234 };

      MoveCommand(DiagramItem *diagramItem, const QPointF &oldPos,
                  QUndoCommand *parent = 0);

      void undo() Q_DECL_OVERRIDE;
      void redo() Q_DECL_OVERRIDE;
      bool mergeWith(const QUndoCommand *command) Q_DECL_OVERRIDE;
      int id() const Q_DECL_OVERRIDE { return Id; }

  private:
      DiagramItem *myDiagramItem;
      QPointF myOldPos;
      QPointF newPos;
  };

  class DeleteCommand : public QUndoCommand
  {
  public:
      explicit DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);

      void undo() Q_DECL_OVERRIDE;
      void redo() Q_DECL_OVERRIDE;

  private:
      DiagramItem *myDiagramItem;
      QGraphicsScene *myGraphicsScene;
  };

  class AddCommand : public QUndoCommand
  {
  public:
      AddCommand(DiagramItem::DiagramType addType, QGraphicsScene *graphicsScene,
                 QPointF LastPoint,QPointF EndPoint,QUndoCommand *parent = 0);
      ~AddCommand();

      void undo() Q_DECL_OVERRIDE;
      void redo() Q_DECL_OVERRIDE;

  private:
      DiagramItem *myDiagramItem;
      QGraphicsScene *myGraphicsScene;
      QPointF initialPosition;
  };

  QString createCommandString(DiagramItem *item, const QPointF &point);

  #endif
