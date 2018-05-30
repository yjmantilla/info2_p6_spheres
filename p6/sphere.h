#ifndef SPHERE_H
#define SPHERE_H

#include "vectorxy.h"
#include <QtMath>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>


class Sphere: public QGraphicsEllipseItem
{
public:
    qreal radius;
    qreal mass;

    qreal drag;
    /* In general, Cd, is not an absolute constant for a given body shape.
     * It varies with the speed of airflow (or more generally with Reynolds number.
     * A smooth sphere, for example, has a Cd, that varies from high values for laminar flow to 0.47 for turbulent flow.
     * see: https://en.wikipedia.org/wiki/Drag_coefficient
    */

    qreal restitution;
    qreal ref_area;

    /*
     * The reference area depends on what type of drag coefficient is being measured.
     * see: https://en.wikipedia.org/wiki/Drag_coefficient
    */

    VectorXY * p; //position
    VectorXY * v; //velocity
    VectorXY * a; //acceleration

    Sphere();
    Sphere(qreal px, qreal py, qreal vx, qreal vy, qreal ax, qreal ay, qreal radius, qreal mass, qreal drag, qreal rest);
    ~Sphere();

    qreal getRadius();
    void setRadius(qreal r);
    qreal getMass();
    void setMass(qreal m);
    qreal getDrag();
    void setDrag(qreal d);
    qreal getRestitution();
    void setRestitution(qreal r);
    qreal getRefArea();
    void setRefArea(qreal a);


    void updateVelocity(qreal dt);
    void updatePosition(qreal dt);
    VectorXY centerToItemCoordinates(VectorXY centerPos);

    void setColor(QColor color);
};

#endif // SPHERE_H
