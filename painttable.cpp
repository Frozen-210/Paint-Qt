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
        // Initializing the Figure Values
        QString name= item->name;
        QString Type= item->shapeTypeName;
        QString Perimeter= QString::number(item->perimeter);
        QString Color= item->shapeColor.name(QColor::HexArgb);
        QString LW= QString::number(item->LineWeight);

        // Insert New row in the table
        table->insertRow(table->rowCount());

        // Setting the row values
        table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(name));
        table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(Type));
        table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(Perimeter));
        table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(Color));
        table->setItem(table->rowCount()-1, 4, new QTableWidgetItem(LW));
    }
}

/*
 * Table Buttons
 */
void PaintTable::SortDVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareDs);
}

void PaintTable::SortAVec(QVector<Figure *> *ItemVec)
{
    std::sort(ItemVec->begin(), ItemVec->end(), compareAs);
}

/*
 * Function for the above buttons
 */
bool PaintTable::compareAs(const Figure *first, const Figure *second)
{
    return first->perimeter < second->perimeter;
}

bool PaintTable::compareDs(const Figure *first, const Figure *second)
{
    return first->perimeter > second->perimeter;
}


