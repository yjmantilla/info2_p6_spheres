#ifndef SYSTEM_H
#define SYSTEM_H
#include <QVector>
#include "sphere.h"
#include "field.h"
#include <QFile>
#include <QString>
#include <QList>
#include <QGraphicsScene>
//#include <QRandomGenerator>
#include <QColor>
#include <QTime>

class System
{
public:

    QVector<Sphere *> spheres;
    Field * field;
    qreal time;
    qreal timeStep;
    QGraphicsScene * scene;

    System(qreal timeStep, qreal startTime);
    ~System();

    void addField(Field * field);
    void addSphere(Sphere * sphere);    
    qreal getTime();
    void setTime(qreal t);
    qreal getTimeStep();
    void setTimeStep(qreal ts);
    void updateAccelerationOfSphere(quint32 i);
    void sphereCollidesWithLimits(Sphere * sphere);
    void evolveSystem(quint32 numberOfSteps);
    void loadSystemFromFile(QString filename);
    qreal boundedRandomizer(int min, int max);
    qreal signRandomizer();
    void addRandomSphere();
    void addSphereAt(qreal px, qreal py);
    QColor randomColor();

};

#endif // SYSTEM_H
