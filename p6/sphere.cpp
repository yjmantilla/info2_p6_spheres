#include "sphere.h"
#define PI 3.14

Sphere::Sphere()
{
    this->p = new VectorXY();
    this->v = new VectorXY();
    this->a = new VectorXY();
}

Sphere::Sphere(qreal px, qreal py, qreal vx, qreal vy, qreal ax, qreal ay, qreal radius, qreal mass, qreal drag, qreal rest)
{
    this->p = new VectorXY();
    this->v = new VectorXY();
    this->a = new VectorXY();

    this->p->setVector(px,py);
    this->v->setVector(vx,vy);
    this->a->setVector(ax,ay);

    this->setRadius(radius);
    this->setMass(mass);
    this->setDrag(drag);
    this->setRestitution(rest);
    this->setRefArea(PI * this->getRadius() * this->getRadius());
    VectorXY dummyPos = this->centerToItemCoordinates(*(this->p));
    this->setRect(0,0,2*this->getRadius(),2*this->getRadius());
    this->setPos(dummyPos.getX(),dummyPos.getY());

}

Sphere::~Sphere()
{
    delete this->p;
    delete this->v;
    delete this->a;
}

qreal Sphere::getRadius()
{
    return this->radius;
}

void Sphere::setRadius(qreal r)
{
    this->radius = r;
    return;
}

qreal Sphere::getMass()
{
    return this->mass;
}

void Sphere::setMass(qreal m)
{
    this->mass = m;
    return;
}

qreal Sphere::getDrag()
{
    return this->drag;
}

void Sphere::setDrag(qreal d)
{
    this->drag = d;
    return;
}

qreal Sphere::getRestitution()
{
    return this->restitution;
}

void Sphere::setRestitution(qreal r)
{
    this->restitution = r;
    return;
}

qreal Sphere::getRefArea()
{
    return this->ref_area;
}

void Sphere::setRefArea(qreal a)
{
    this->ref_area = a;
    return;
}

void Sphere::updateVelocity(qreal dt)
{
    /*v=v0 + a*deltat*/
    this->v->setX(this->v->getX()+this->a->getX()*dt);
    this->v->setY(this->v->getY()+this->a->getY()*dt);
    return;
}

void Sphere::updatePosition(qreal dt)
{
    /* r = r0 + v0*deltat + 0.5*a*deltat^2 */

    this->p->setX(this->p->getX()+(this->v->getX()*dt)+(0.5 * this->a->getX() * qPow(dt,2)));
    this->p->setY(this->p->getY()+(this->v->getY()*dt)+(0.5 * this->a->getY() * qPow(dt,2)));

    VectorXY dummyPos = this->centerToItemCoordinates(*(this->p));
    this->setPos(dummyPos.getX(),dummyPos.getY());
    return;

}

VectorXY Sphere::centerToItemCoordinates(VectorXY centerPos)
{
    VectorXY itemPos;
    itemPos.setX(centerPos.getX() - this->getRadius());
    itemPos.setY(centerPos.getY() - this->getRadius());
    return itemPos;
}

void Sphere::setColor(QColor color)
{

    this->setBrush(*(new QBrush(color,Qt::SolidPattern)));
    //, Qt::SolidPattern
    return;
}
