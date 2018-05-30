#include "esferasim.h"
#include <QDebug>

EsferaSim::EsferaSim(float x, float y, float r):px(x),py(y),rad(r),vx(0),vy(0)
{

}

EsferaSim::~EsferaSim()
{

}

void EsferaSim::setVel(float x, float y)
{
    vx=x;
    vy=y;
}

void EsferaSim::setPoint(float x, float y)
{
    px=x;
    py=y;
    vx=0;
    vy=0;
}

void EsferaSim::actualizar(float dt)
{
    px+=vx*dt;
    py+=vy*dt;
}

float EsferaSim::getX() const
{
    return px;
}

float EsferaSim::getY() const
{
    return py;
}

float EsferaSim::getR() const
{
    return rad;
}

float EsferaSim::getVx() const
{
    return vx;
}

float EsferaSim::getVy() const
{
    return vy;
}



