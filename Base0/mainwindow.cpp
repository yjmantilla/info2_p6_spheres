#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#define RUTA_ARCHIVO "arch.txt"     //ruta en que se encuentra el archivo

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString info;                       //String para leer los datos del archivo

    QFile file(RUTA_ARCHIVO);           //Objeto para manejar la lectura del archivo
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    info=file.readLine();

    QList<QString> dats;
    int n=0;
    while(n>=0){      //Ciclo para guardar cada dato de la linea de texto en su posicion correspondiente en el arreglo vec
        n = info.indexOf(" ");
        if(n!=0){
            dats.append(info.left(n));
        }
        info=info.remove(0,n+1);
    }
/*    for(int i=0;i<dats.size();i++){
        qDebug()<<dats.at(i);

    }*/
    n=0;
    h_limit=dats.at(n++).toFloat();                   //Asigna los valores leidos el archivo
    v_limit=dats.at(n++).toFloat();
    dt=0.02;                            //Asigna el lapso de tiempo

    timer=new QTimer(this);                 //crea el timer
    scene=new QGraphicsScene(this);         //crea la scene
    scene->setSceneRect(0,0,h_limit,v_limit);     //asigna el rectangulo que encierra la scene, determinado por h_limit y v_limit
    //scene->setSceneRect(0,0,1000,500);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1000,500);
    ui->graphicsView->setFrameRect(QRect(0,0,1000,500));
            qDebug()<<ui->graphicsView->size();
    ui->centralWidget->adjustSize();
    ui->centralWidget->setFixedSize(1000,500);
            qDebug()<<ui->centralWidget->size();
    //this->adjustSize();

    this->setFixedSize(1280,600);
        qDebug()<<this->size();
    scene->addRect(scene->sceneRect());

    timer->stop();                              //para el timer
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    while(n<dats.size()){
        if(dats.at(n)=="E"){
            bars.append(new EsferaGraf(dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat()));
            bars.last()->getEsf()->setVel(dats.at(++n).toFloat(),dats.at(++n).toFloat());
        }
        n++;
    }

    for(int i=0;i<bars.size();i++){
        bars.at(i)->actualizar(dt,v_limit);
        scene->addItem(bars.at(i));
    }

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
    for(int i=0;i<bars.size();i++){
        bordercollision(bars.at(i)->getEsf());
        bars.at(i)->actualizar(dt,v_limit);

    }
}

void MainWindow::bordercollision(EsferaSim *b)
{
    if(b->getX()<b->getR() || b->getX()>h_limit-b->getR()){
        b->setVel(-1*b->getVx(),b->getVy());
    }
    if(b->getY()<b->getR() || b->getY()>v_limit-b->getR()){
        b->setVel(b->getVx(),-1*b->getVy());
    }
}



void MainWindow::on_pushButton_clicked()
{
     timer->start(1000*dt);
}
