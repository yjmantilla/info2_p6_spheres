#include "field.h"

Field::Field()
{
    this->size = new VectorXY();
}

Field::Field(qreal width, qreal height, qreal density, qreal gravity)
{
    this->size = new VectorXY();
    this->HT = new Wall(0,0,width,0,Qt::black);
    this->HB = new Wall(0,height,width,height,Qt::black);
    this->VL = new Wall(0,0,0,height,Qt::black);
    this->VR = new Wall(width,0,width,height,Qt::black);

    this->size->setX(width);
    this->size->setY(height);

    this->setDensity(density);
    this->setGravity(gravity);
}

Field::~Field()
{
    delete this->size;
    delete this->HT;
    delete this->HB;
    delete this->VL;
    delete this->VR;
}

qreal Field::getDensity()
{
    return this->density;
}

void Field::setDensity(qreal d)
{
    this->density = d;
    return;
}

qreal Field::getGravity()
{
    return this->gravity;
}

void Field::setGravity(qreal g)
{
    this->gravity = g;
    return;
}
