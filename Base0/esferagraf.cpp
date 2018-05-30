#include "esferagraf.h"
#include "QDebug"



EsferaGraf::EsferaGraf(float x, float y, float r) : escala(1)
{
    esf=new EsferaSim(x,y,r);
}

EsferaGraf::~EsferaGraf()
{
    delete esf;
}

QRectF EsferaGraf::boundingRect() const
{
        return QRectF(-1*escala*esf->getR(),-1*escala*esf->getR(),2*escala*esf->getR(),2*escala*esf->getR());
}

void EsferaGraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);        //asigna el color
    painter->drawEllipse(boundingRect());    //dibuja una elipse encerrada en la boundingRect
}

void EsferaGraf::setEscala(float s)
{
    escala=s;
}

void EsferaGraf::actualizar(float dt, float v_lim)
{
    esf->actualizar(dt);
    setPos((esf->getX()-esf->getR())*escala,(/*v_lim-*/esf->getY()-esf->getR())*escala);
}

EsferaSim *EsferaGraf::getEsf()
{
    return esf;
}


