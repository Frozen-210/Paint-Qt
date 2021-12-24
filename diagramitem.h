#ifndef DIAGRAMITEM_H
  #define DIAGRAMITEM_H

  #include <QGraphicsPolygonItem>
  class QGraphicsItem;
  class QGraphicsScene;
  class QGraphicsSceneMouseEvent;
  class QPointF;

  class DiagramItem : public QGraphicsPolygonItem
  {
  public:
      enum { Type = UserType + 1 };
      enum DiagramType { Box, Triangle };

      explicit DiagramItem(DiagramType diagramType,QPointF LastPoint,QPointF EndPoint, QGraphicsItem *item = 0);

      DiagramType diagramType() const {
          return polygon() == boxPolygon ? Box : Triangle;
      }
      int type() const Q_DECL_OVERRIDE { return Type; }

  private:
      QPolygonF boxPolygon;
      QPolygonF trianglePolygon;
  };

  #endif
