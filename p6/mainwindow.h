#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QFile>
#include "system.h"
#include "QGraphicsView"
#include <QDebug>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent * mouse);

    bool stop;
public slots:
    void animate();
    void pause();
private:
    Ui::MainWindow * ui;
    QTimer * timer;
    System * system;

};

#endif // MAINWINDOW_H
