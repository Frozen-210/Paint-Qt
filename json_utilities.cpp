#include "json_utilities.h"


void json_utilities::save(PaintScene *scene, QString path)
{
    QVector<Figure*> *newVec = scene->ItemsVec;

    QFile saveFile(path);
    if (!saveFile.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open save file.");
        }


    for(int i=0; i<newVec->size();i++){
        QVariantMap settings;

        QPointF point = newVec->at(i)->startPoint();
        QPointF point2 = newVec->at(i)->endPoint();
        QColor color = newVec->at(i)->shapeColor;
        int LineW = newVec->at(i)->LineWeight;
        QString shapeName = newVec->at(i)->shapeName;



        settings[QString("Shape")] = QString("%1").arg(shapeName);
        settings[QString("FirstPoint")] = QString("(%1, %2)").arg(point.rx()).arg(point.ry());
        settings[QString("EndPoint")] = QString("(%1, %2)").arg(point2.rx()).arg(point2.ry());

        // Color and Line Weight
        settings[QString("Color")] = QString("(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
        settings[QString("LineWeight")] = QString("%1").arg(LineW);

        QJsonObject jsonobj = QJsonObject::fromVariantMap(settings);
        QJsonDocument json = QJsonDocument(jsonobj);

        saveFile.write(json.toJson());
    }
        saveFile.close();

}
