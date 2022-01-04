#ifndef PAINTTABLE_H
#define PAINTTABLE_H

#include<QTableWidget>
#include"figure.h"
#include<QVector>
class PaintTable
{
public:
    PaintTable();
    static void UpdateTable(QTableWidget* table, QVector<Figure*> ItemVec);
    static void SortDVec(QVector<Figure*>* ItemVec);
    static void SortAVec(QVector<Figure*>* ItemVec);


private:
    static bool compareAs(const Figure* first, const Figure* second);
    static bool compareDs(const Figure* first, const Figure* second);
};

#endif // PAINTTABLE_H
