#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QUndoStack;
class DiagramScene;
class DiagramItem;
class QUndoView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool TriangleTriggered=0;


public slots:
    void itemMoved(DiagramItem *movedDiagram, const QPointF &moveStartPosition);

private slots:
    void addBox();
    void on_Triangle_clicked();
    void deleteItem();
    void on_Rectangle_clicked();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    QUndoStack *undoStack;
    DiagramScene *diagramScene;
    QAction *addBoxAction;
    QAction *undoAction;
    QAction *redoAction;
    QUndoView *undoView;
    bool isDrawing;
    QPointF LastPoint;
    QPointF EndPoint;
    int type;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
