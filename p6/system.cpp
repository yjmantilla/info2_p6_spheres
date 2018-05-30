#include "system.h"
#include <QDebug>

#define MIN_RAD 5
#define MAX_RAD 30
#define MIN_MASS 50
#define MAX_MASS 700
#define MIN_V 0
#define MAX_V 50
#define MIN_REST 0.5
#define MAX_REST 1
#define MIN_DRAG 0
#define MAX_DRAG 0.01

System::System(qreal timeStep, qreal startTime)
{
    this->field = new Field();
    this->scene = new QGraphicsScene();
    this->timeStep = timeStep;
    this->time = startTime;
}

System::~System()
{
    delete this->field;
}

void System::addField(Field * field)
{
    this->field = field;
    this->scene->addItem(this->field->HT);
    this->scene->addItem(this->field->HB);
    this->scene->addItem(this->field->VL);
    this->scene->addItem(this->field->VR);
    this->scene->setSceneRect(0,0,this->field->size->getX(),this->field->size->getY());
    return;
}

void System::addSphere(Sphere * sphere)
{
    this->spheres.append(sphere);
    this->scene->addItem(this->spheres.last());
    //this->spheres.last()->setBrush(QBrush(Qt::darkBlue));
    //this->spheres.last()->setColor(Qt::darkBlue);
    this->spheres.last()->setColor(this->randomColor());
    return;
}


qreal System::getTime()
{
    return this->time;
}

void System::setTime(qreal t)
{
    this->time = t;
    return;
}

qreal System::getTimeStep()
{
    return this->timeStep;
}

void System::setTimeStep(qreal ts)
{
    this->timeStep = ts;
    return;
}

void System::updateAccelerationOfSphere(quint32 i)
{
    qreal dummyMagnitude = 0;

    dummyMagnitude = -1 * 0.5 * this->field->getDensity() * this->spheres.at(i)->v->getMagnitudeSquared() * this->spheres.at(i)->getDrag() * this->spheres.at(i)->getRefArea();
    qreal angle = this->spheres.at(i)->v->getAngle();

    this->spheres.at(i)->a->setVectorByMagnitudeAngle(dummyMagnitude,angle);



    if(this->spheres.at(i)->p->getY() + this->spheres.at(i)->getRadius() < this->field->size->getY())
    {
        this->spheres.at(i)->a->setY(this->spheres.at(i)->a->getY()+ this->field->getGravity()); //+ since gravity goes along y axis (axis is pointing downward)
    }

    return;

}

void System::sphereCollidesWithLimits(Sphere * sphere)
{
    if(sphere->p->getX() < sphere->getRadius())
    {
        if(sphere->v->getX() < 0)
        {
            sphere->v->setX(-1 * sphere->getRestitution() * sphere->v->getX());
        }
    }

    if(sphere->p->getX() + sphere->getRadius() > this->field->size->getX())
    {
        if(sphere->v->getX() > 0)
        {
            sphere->v->setX(-1 * sphere->getRestitution() * sphere->v->getX());
        }
    }


    if(sphere->p->getY() < sphere->getRadius())
    {
        if(sphere->v->getY() < 0)
        {
            sphere->v->setY(-1 * sphere->getRestitution() * sphere->v->getY());
        }
    }

    if(sphere->p->getY() + sphere->getRadius() > this->field->size->getY())
    {
        if(sphere->v->getY() > 0)
        {
            sphere->v->setY(-1 * sphere->getRestitution() * sphere->v->getY());
        }
    }

    return;
}

void System::evolveSystem(quint32 numberOfSteps)
{
    for(quint32 i = 0; i < numberOfSteps; i++)//we dont define it for negative steps (what would happen though???)
    {

        for(qint32 j = 0; j < this->spheres.size(); j++)
        {
            this->sphereCollidesWithLimits(this->spheres.at(j));
            this->spheres.at(j)->updatePosition(this->timeStep);            
            this->spheres.at(j)->updateVelocity(this->timeStep);
            this->updateAccelerationOfSphere(j);//for next iteration of evolve system
            //qDebug()<<"v:"<<this->spheres.at(j)->v->getMagnitude()<<"a:"<<this->spheres.at(j)->a->getMagnitude();
            //qDebug()<<"cpos:"<<this->spheres.at(j)->p->getY()<<"ipos"<<this->spheres.at(j)->pos().y();
        }

        this->time = this->time + this->timeStep;
    }

    return;
}

void System::loadSystemFromFile(QString filename)
{
    QFile file(filename);
    qDebug() << "file opened:"<<file.open(QIODevice::ReadOnly);

    qDebug() << "loading data:";

    QString buffer;
    QList<QString> data;

    while(!file.atEnd())
    {
        buffer = file.readLine();
        if(buffer.length() > 3)
        {
            data.append(buffer);
            if(data.last().endsWith("\r\n"))
            {
                data.last().remove("\r\n");
            }
            qDebug() << data.last();
        }

    }

    qDebug() << "data loaded";

    qDebug() << "loading data to system:";

    for (qint32 i = 0; i < data.size(); i++)
    {
        //qDebug() << i;
        if(data.at(i).contains("S"))
        {
            qDebug() << "Sphere:" << data.at(i).section(",",1);
            qreal px = data.at(i).section(",",1,1).toFloat();
            qreal py = data.at(i).section(",",2,2).toFloat();
            qreal vx = data.at(i).section(",",3,3).toFloat();
            qreal vy = data.at(i).section(",",4,4).toFloat();
            qreal ax = data.at(i).section(",",5,5).toFloat();
            qreal ay = data.at(i).section(",",6,6).toFloat();
            qreal rad = data.at(i).section(",",7,7).toFloat();
            qreal mass = data.at(i).section(",",8,8).toFloat();
            qreal drag = data.at(i).section(",",9,9).toFloat();
            qreal rest = data.at(i).section(",",10,10).toFloat();
            this->addSphere(new Sphere(px,py,vx,vy,ax,ay,rad,mass,drag,rest));
        }

        if(data.at(i).contains("F"))
        {
            qDebug() << "Field:" << data.at(i).section(",",1);
            qreal width = data.at(i).section(",",1,1).toFloat();
            qreal height = data.at(i).section(",",2,2).toFloat();
            qreal density = data.at(i).section(",",3,3).toFloat();
            qreal gravity = data.at(i).section(",",4,4).toFloat();
            this->addField(new Field(width,height,density,gravity));
        }
    }

}

qreal System::boundedRandomizer(int min, int max)
{
    return QRandomGenerator::global()->bounded(min,max + 1);
}

qreal System::signRandomizer()
{
    int dummy;

    while(1)
    {
        //remember the upper bound is exclusive
        dummy = QRandomGenerator::global()->bounded(-1,2);

        if(dummy != 0){break;}
    }

    //qDebug()<<dummy;
    return dummy;
}

void System::addRandomSphere()
{
    this->addSphere(new Sphere(this->boundedRandomizer(0+MAX_RAD,this->field->size->getX()-MAX_RAD),this->boundedRandomizer(0+MAX_RAD,this->field->size->getY()-MAX_RAD),this->boundedRandomizer(MIN_V,MAX_V),this->boundedRandomizer(MIN_V,MAX_V),0,0,this->boundedRandomizer(MIN_RAD,MAX_RAD),this->boundedRandomizer(MIN_MASS,MAX_MASS),this->boundedRandomizer(MIN_DRAG,MAX_DRAG),this->boundedRandomizer(MIN_REST,MAX_REST)));
    return;
}

void System::addSphereAt(qreal px, qreal py)
{
    this->addSphere(new Sphere(px,py,this->signRandomizer()*this->boundedRandomizer(MIN_V,MAX_V),this->signRandomizer()*this->boundedRandomizer(MIN_V,MAX_V),0,0,this->boundedRandomizer(MIN_RAD,MAX_RAD),this->boundedRandomizer(MIN_MASS,MAX_MASS),this->boundedRandomizer(MIN_DRAG,MAX_DRAG),this->boundedRandomizer(MIN_REST,MAX_REST)));
    return;
}

QColor System::randomColor()
{
    return QColor(this->boundedRandomizer(0,255),this->boundedRandomizer(0,255),this->boundedRandomizer(0,255));
}

