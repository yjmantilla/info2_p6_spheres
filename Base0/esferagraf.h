#ifndef ESFERAGRAF_H
#define ESFERAGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "esferasim.h"

class EsferaGraf: public QGraphicsItem          //Clase para graficar las esferas
{
public:
    EsferaGraf(float x, float y, float r);
    ~EsferaGraf();
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    void setEscala(float s);
    void actualizar(float dt, float v_lim);
    EsferaSim* getEsf();
private:
    EsferaSim* esf;
    float escala;
};

#endif // ESFERAGRAF_H
