#include "json_utilities.h"
#include <QJsonArray>
#include <QStack>
#include"figure.h"
#include "square.h"
#include "commands.h"
#include"romb.h"
#include"line.h"
#include"triangle.h"

void json_utilities::save(PaintScene *scene, QString path)
{
    QVector<Figure*> *newVec = scene->ItemsVec;

    QFile saveFile(path);
    if (!saveFile.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open save file.");
        }
    saveFile.write("[");

    for(int i=0; i<newVec->size();i++){
        QVariantMap settings;

        QPointF point = newVec->at(i)->startPoint();
        QPointF point2 = newVec->at(i)->endPoint();
        QColor color = newVec->at(i)->shapeColor;
        int LineW = newVec->at(i)->LineWeight;
        QString shapeName = newVec->at(i)->shapeName;

        settings[QString("Shape")] = QString("%1").arg(shapeName);
        settings[QString("FirstPoint")] = QString("%1, %2").arg(point.rx()).arg(point.ry());
        settings[QString("EndPoint")] = QString("%1, %2").arg(point2.rx()).arg(point2.ry());

        // Color and Line Weight
        settings[QString("Color")] = QString("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        settings[QString("LineWeight")] = QString("%1").arg(LineW);

        QJsonObject jsonobj = QJsonObject::fromVariantMap(settings);
        QJsonDocument json = QJsonDocument(jsonobj);

        saveFile.write(json.toJson());
        if(i<newVec->size()-1){
            saveFile.write(",");
        }
    }
    saveFile.write("]");
    saveFile.close();
}
void json_utilities:: savePNG(PaintScene *scene, QString path){
     QFile saveFile(path);

     QPixmap pixMap = scene->view->grab(scene->sceneRect().toRect());
     pixMap.save(path);

}



void json_utilities::open(PaintScene *scene, QString path)
{
    QFile jsonFile(path);
    QString json_string;

    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            json_string = jsonFile.readAll();
            jsonFile.close();
    }


    auto json_doc = QJsonDocument::fromJson(json_string.toUtf8());
    QJsonArray jArr = json_doc.array();
    QJsonValue c_val, val2, val3, val4, val5;
    QStack<Figure*> tempStack;

    for(auto jsonObj : jArr)
    {
        c_val = jsonObj.toObject().value("Color");
        QString _color = c_val.toString();
        QStringList x = _color.split(", ");
        QColor color(x[0].toInt(), x[1].toInt(), x[2].toInt());


        val2 = jsonObj.toObject().value("FirstPoint");
        QString _FP = val2.toString();
        QStringList FP = _FP.split(", ");
        QPointF firstPoint(FP[0].toInt(), FP[1].toInt());

        val3 = jsonObj.toObject().value("EndPoint");
        QString _EP = val3.toString();
        QStringList EP = _EP.split(", ");
        QPointF endPoint(EP[0].toInt(), EP[1].toInt());

        val4 = jsonObj.toObject().value("LineWeight");
        QString _LW = val4.toString();
        int LW = _LW.toInt();

        val5 = jsonObj.toObject().value("Shape");
        QString _ST = val5.toString();

        if(_ST=="Rectangle"){
        Figure *item = new Square(firstPoint,color,LW);
        item->setPos(firstPoint);
        item->setEndPoint(endPoint,false);
        QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint);
        scene->undoStack->push(addCommand);}
        else if(_ST=="Circle"){
            Figure *item = new Romb(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Line"){
            Figure *item = new Line(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint);
            scene->undoStack->push(addCommand);
        }
        else if(_ST=="Triangle"){
            Figure *item = new Triangle(firstPoint,color,LW);
            item->setPos(firstPoint);
            item->setEndPoint(endPoint,false);
            QUndoCommand *addCommand = new AddCommand(scene,item,firstPoint);
            scene->undoStack->push(addCommand);
        }

    }
}
