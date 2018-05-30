#ifndef FIELD_H
#define FIELD_H
#include <QtGlobal>
#include "vectorxy.h"
#include "wall.h"

class Field
{
public:

    VectorXY * size;
    qreal density;
    qreal gravity;

    Field();
    Field(qreal width, qreal height, qreal density, qreal gravity);
    ~Field();
    qreal getDensity();
    void setDensity(qreal d);
    qreal getGravity();
    void setGravity(qreal g);

    Wall * VL;
    Wall * VR;
    Wall * HT;
    Wall * HB;

};

#endif // FIELD_H
