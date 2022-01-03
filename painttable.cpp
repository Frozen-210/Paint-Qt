#include "painttable.h"

PaintTable::PaintTable()
{

}

void PaintTable::UpdateTable(QTableWidget *table, QVector<Figure *> ItemVec)
{
    QStringList TableLabel;
    TableLabel<<"Name"<<"Type"<<"Perimter"<<"Color"<<"LineWeight";

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(TableLabel);
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }

    for(auto* item:ItemVec){
        QString name= item->name;
        QString Type= item->shapeName;
        QString Perimeter= QString::number(item->perimeter);
        QString Color= item->shapeColor.name(QColor::HexArgb);
        QString LW= QString::number(item->LineWeight);
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(name));
        table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(Type));
        table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(Perimeter));
        table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(Color));
        table->setItem(table->rowCount()-1, 4, new QTableWidgetItem(LW));

    }
}

void PaintTable::SortDVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareDs);
}

void PaintTable::SortAVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareAs);
}

bool PaintTable::compareAs(const Figure *first, const Figure *second)
{
    return first->perimeter < second->perimeter;
}

bool PaintTable::compareDs(const Figure *first, const Figure *second)
{
    return first->perimeter > second->perimeter;
}

