#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(Width,Hight);
    CurrentX = CurrentY = 0;
    this->setMouseTracking(true);
    label->setGeometry(0,0,100,10);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //绘制棋盘
    painter.setPen(QPen(Qt::black,1));
    for(int i = 0;i<SizeOfBroad;i++){
        painter.drawLine(SpaceSize,SpaceSize + i * SizeOfGrid,Width - SpaceSize,SpaceSize + i * SizeOfGrid);
    }

    for(int i = 0;i<SizeOfBroad;i++){
        painter.drawLine(SpaceSize + i * SizeOfGrid,SpaceSize,SpaceSize + i * SizeOfGrid,Hight - SpaceSize);
    }

    //绘制棋盘上的9个点
    painter.setPen(QPen(Qt::black,5));
    for(int i = 3;i<SizeOfBroad;i+=4){
        for(int j = 3;j<SizeOfBroad;j+=4){
            painter.drawPoint(SpaceSize + i * SizeOfGrid,SpaceSize + j * SizeOfGrid);
        }
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){

}

void MainWindow::mouseReleaseEvent(QMouseEvent *){

}

