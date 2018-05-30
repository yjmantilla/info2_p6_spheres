#include "mainwindow.h"
#include "ui_mainwindow.h"

#define WIDTH 1000
#define HEIGHT 500
#define BOUNDARY 100
#define MAX_N 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    this->system = new System(0.1,0);
    this->system->loadSystemFromFile("sys.txt");

    this->ui->graphicsView->setFixedSize(this->system->field->size->getX()+BOUNDARY,this->system->field->size->getY()+BOUNDARY);
    this->ui->graphicsView->setScene(this->system->scene);

    this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->system->addField(new Field(1000,500,0.005,10));
    //this->system->addSphere(new Sphere(50,100,550,550,0,0,30,5,0.001,0.5));
    //this->system->addSphere(new Sphere(150,300,-40,10,0,0,5,600,0.01,0.5));
    //qDebug()<<this->system->spheres.at(0)->rect().x();
    //qDebug()<<this->system->spheres.at(0)->rect().y();

    connect(this->timer,SIGNAL(timeout()),this,SLOT(animate()));
    connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(pause()));
    this->stop = true;
    this->timer->start(10);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *mouse)
{
    for(qint32 i = 0; i < MAX_N; i++)
    {
        this->system->addSphereAt(mouse->x(),mouse->y());
    }

}

void MainWindow::animate()
{
    if(!this->stop)
    {
        this->system->evolveSystem(1);
    }
    return;
}

void MainWindow::pause()
{
    this->stop = !this->stop;
    return;
}

