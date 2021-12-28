#include "json_utilities.h"


void json_utilities::save(PaintScene *scene)
{

    QFile saveFile(QStringLiteral("C:\\Users\\zizo\\Downloads\\MyGitHub\\New folder\\CMP2241_F21_Team01\\save.json"));
    if (!saveFile.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open save file.");
        }

    while(!scene->ItemsVec->empty()){
        QVariantMap settings;

        QPointF point = scene->ItemsVec->back()->startPoint();
        QPointF point2 = scene->ItemsVec->back()->endPoint();
        QColor color = scene->ItemsVec->back()->shapeColor;
        int LineW = scene->ItemsVec->back()->LineWeight;
        QString shapeName = scene->ItemsVec->back()->shapeName;

        scene->ItemsVec->pop_back();

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
