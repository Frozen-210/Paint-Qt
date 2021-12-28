#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>
#include <QUndoView>
#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QTimer *timer;

private:

    void resizeEvent(QResizeEvent * event);
    QUndoView *undoView;

private slots:
    void slotTimer();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionColor_triggered();
    void on_horizontalSlider_sliderMoved(int position);
    void on_pushButton_4_clicked();
    void on_sortA_Btn_clicked();
    void on_actionSave_Json_triggered();
    void on_sortD_Btn_clicked();
    void on_srch_Btn_clicked();

    void on_actionOpen_File_triggered();
};

#endif // MAINWINDOW_H
