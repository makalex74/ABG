#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <QObject>
#include <QTCore>

#include "triangle.h"

class Triangles : public QObject
{
    Q_OBJECT
public:
    explicit Triangles(QObject *parent = 0);

protected:
    QVector<Triangle*> vecTriWhite;
    QVector<Triangle*> vecTriBlack;

signals:

public slots:
};

#endif // TRIANGLES_H
