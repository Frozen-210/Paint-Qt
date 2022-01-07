#include "json_utilities.h"
#include <QJsonArray>
#include <QStack>
#include"figure.h"
#include "rectangle.h"
#include "commands.h"
#include"circle.h"
#include"line.h"
#include"triangle.h"
#include "painttable.h"

/*
 * ----------------------Save Method----------------------
 * Take the path and the scene then save each figure in
 * the sene to a JSON File in a specific path
 * -------------------------------------------------------
 */
void json_utilities::save(PaintScene *scene, QString path)
{
    QVector<Figure*> *newVec = scene->ItemsVec;

    // Making JSON File in a specific Path
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open save file.");
        }

    // Writing [ to open a list of maps in the file
    saveFile.write("[");

    // Looping on the vector to save it
    for(int i=0; i<newVec->size();i++){
        QVariantMap settings;

        // Getting the Vector start point, end point, color, line weight, and shape type
        QPointF point = newVec->at(i)->startPoint();
        QPointF point2 = newVec->at(i)->endPoint();
        QColor color = newVec->at(i)->shapeColor;
        int LineW = newVec->at(i)->LineWeight;
        QString shapeName = newVec->at(i)->shapeTypeName;
        QString name = newVec->at(i)->name;

        // Setting the above values to the setting to path it the file
        settings[QString("Shape")] = QString("%1").arg(shapeName);
        settings[QString("FirstPoint")] = QString("%1, %2").arg(point.rx()).arg(point.ry());
        settings[QString("EndPoint")] = QString("%1, %2").arg(point2.rx()).arg(point2.ry());
        settings[QString("Color")] = QString("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        settings[QString("LineWeight")] = QString("%1").arg(LineW);
        settings[QString("ShapeName")] = QString("%1").arg(name);

        // Make a JSON Object and pass it to the file
        QJsonObject jsonobj = QJsonObject::fromVariantMap(settings);
        QJsonDocument json = QJsonDocument(jsonobj);

        saveFile.write(json.toJson());

        // Condition to avoid writing "," after the last element
        if(i<newVec->size()-1){
            saveFile.write(",");
        }
    }
    // Closing the List in the file
    saveFile.write("]");

    // Closing the file
    saveFile.close();
}

/*
 * ----------------------SavePNG Method----------------------
 * Take the path and save a PNG image in it
 * -------------------------------------------------------
 */
void json_utilities:: savePNG(PaintScene *scene, QString path){
     QFile saveFile(path);

     QPixmap pixMap = scene->view->grab(scene->sceneRect().toRect());
     pixMap.save(path);
}

/*
 * ----------------------open Method----------------------
 * Take the path and the scene then initialine each figure
 * of the JSON File in the scene
 * -------------------------------------------------------
 */

void json_utilities::open(PaintScene *scene,QTableWidget* table, QString path)
{
    // Opening the file of the path
    QFile jsonFile(path);
    QString json_string;

    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            json_string = jsonFile.readAll();
            jsonFile.close();
    }

    auto json_doc = QJsonDocument::fromJson(json_string.toUtf8());
    QJsonArray jArr = json_doc.array();
    QJsonValue c_val, val2, val3, val4, val5, name_val;

    // Looping in the file shapes
    for(auto jsonObj : jArr)
    {
        // Getting the color Value as RGB
        c_val = jsonObj.toObject().value("Color");
        QString _color = c_val.toString();
        QStringList x = _color.split(", ");
        QColor color(x[0].toInt(), x[1].toInt(), x[2].toInt());

        // Getting The First Point as x, y values
        val2 = jsonObj.toObject().value("FirstPoint");
        QString _FP = val2.toString();
        QStringList FP = _FP.split(", ");
        QPointF firstPoint(FP[0].toInt(), FP[1].toInt());

        // Getting The End Point as x, y values
        val3 = jsonObj.toObject().value("EndPoint");
        QString _EP = val3.toString();
        QStringList EP = _EP.split(", ");
        QPointF endPoint(EP[0].toInt(), EP[1].toInt());

        // Getting The Line Weigh Value
        val4 = jsonObj.toObject().value("LineWeight");
        QString _LW = val4.toString();
        int LW = _LW.toInt();

        // Getting the shape Type
        val5 = jsonObj.toObject().value("Shape");
        QString _ST = val5.toString();

        // Getting the shape name
        name_val = jsonObj.toObject().value("ShapeName");
        QString _SN = name_val.toString();

        // Conditions for each shape to initialize it

        if(_ST=="Rectangle"){
            Figure *item = new Rectangle(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);}

        else if(_ST=="Circle"){
            Figure *item = new Circle(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Line"){
            Figure *item = new Line(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Triangle"){
            Figure *item = new Triangle(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            item->name = _SN;
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint,table);
            scene->undoStack->push(addCommand);
        }
    }
    PaintTable::UpdateTable(table,*scene->ItemsVec);
}
