#ifndef JSON_UTILITIES_H
#define JSON_UTILITIES_H

#include <QJsonObject>
#include <QString>
#include "paintscene.h"
#include "figure.h"
#include <QFile>
#include <QFileDialog>

// ------
#include <QCoreApplication>
#include <QVariantMap>
#include <QPoint>
#include <QPointF>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

class json_utilities
{
public:
    json_utilities();
    void save(PaintScene *scene, QString path);
    void open(PaintScene *scene, QString path);

private:
    PaintScene *myGraphicsScene;
};
#endif // JSON_UTILITIES_H
