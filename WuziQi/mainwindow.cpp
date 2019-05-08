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

    //绘制棋子
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(QPen(Qt::black,0));
    for(int i = 1;i<14;i++){
        for(int j = 1;j<14;j++){
            int GradX = SpaceSize + i * SizeOfGrid;
            int GradY = SpaceSize + j * SizeOfGrid;
            if(game->GetChessOnBroad(i,j) == 1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(GradX - ChessSize ,GradY - ChessSize ,ChessSize*2,ChessSize*2);
            }
            else if(game->GetChessOnBroad(i,j) == 2){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(GradX - ChessSize,GradY - ChessSize ,ChessSize*2,ChessSize*2);
            }
        }
    }

    //绘制鼠标移动的时候的下棋位置
    painter.setPen(QPen(Qt::red,2));
    for(int i = 1;i<14;i++){
        for(int j = 1;j<14;j++){
            int GradX = SpaceSize + i * SizeOfGrid;
            int GradY = SpaceSize + j * SizeOfGrid;
            if(MoveX < GradX + SizeOfGrid / 2 && MoveX > GradX - SizeOfGrid /2 &&MoveY < GradY + SizeOfGrid / 2 && MoveY > GradY - SizeOfGrid /2){
                //label->setText(QString::number(GradX)+","+QString::number(GradY - SpaceGrid));
                if(game->GetChessOnBroad(i,j) != 0) break;
                painter.drawLine(GradX - SizeOfCrossing,GradY - SpaceGrid,GradX - SpaceGrid,GradY - SpaceGrid);
                painter.drawLine(GradX - SpaceGrid,GradY - SizeOfCrossing,GradX - SpaceGrid,GradY - SpaceGrid);

                painter.drawLine(GradX + SizeOfCrossing,GradY - SpaceGrid,GradX + SpaceGrid,GradY - SpaceGrid);
                painter.drawLine(GradX + SpaceGrid,GradY - SizeOfCrossing,GradX + SpaceGrid,GradY - SpaceGrid);

                painter.drawLine(GradX - SizeOfCrossing,GradY + SpaceGrid,GradX - SpaceGrid,GradY + SpaceGrid);
                painter.drawLine(GradX - SpaceGrid,GradY + SizeOfCrossing,GradX - SpaceGrid,GradY + SpaceGrid);

                painter.drawLine(GradX + SizeOfCrossing,GradY + SpaceGrid,GradX + SpaceGrid,GradY + SpaceGrid);
                painter.drawLine(GradX + SpaceGrid,GradY + SizeOfCrossing,GradX + SpaceGrid,GradY + SpaceGrid);
            }
        }
    }

    if(CurrentX != 0 && CurrentY != 0) {
        painter.setPen(QPen(Qt::red,2));
        painter.drawLine(CurrentX - SpaceCross,CurrentY,CurrentX - SpaceCross - CrossSize,CurrentY);
        painter.drawLine(CurrentX + SpaceCross,CurrentY,CurrentX + SpaceCross + CrossSize,CurrentY);
        painter.drawLine(CurrentX,CurrentY - SpaceCross,CurrentX,CurrentY - SpaceCross - CrossSize);
        painter.drawLine(CurrentX,CurrentY + SpaceCross,CurrentX,CurrentY + SpaceCross + CrossSize);
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint pos = event->pos();
    int posx = pos.x();
    int posy = pos.y();
    MoveX = posx;
    MoveY = posy;
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){
    int posx = 0,posy = 0,GradX = 0,GradY = 0;
    for(int i = 1;i<14;i++){
        for(int j = 1;j<14;j++){
            GradX = SpaceSize + i * SizeOfGrid;
            GradY = SpaceSize + j * SizeOfGrid;
            if(MoveX < GradX + SizeOfGrid / 2 && MoveX > GradX - SizeOfGrid /2 &&MoveY < GradY + SizeOfGrid / 2 && MoveY > GradY - SizeOfGrid /2){
                posx = i;
                posy = j;
                break;
            }
        }
        if(posx) break;
    }
    if(posx == 0 && posy == 0) return ;
    if(game->canPutChess(posx,posy)) {
        game->PutChessOn(posx,posy);
        CurrentX = GradX;
        CurrentY = GradY;
        update();
        //game->SetNowPlayer(!game->GetNowPlayer());
    }
    if(game->CheckWin(posx,posy)){
        QString str;
        str = game->GetNowPlayer() == 1 ? "black" : "white";
        str += " win!";
        QMessageBox::information(this,"提示",str);
        game->GameInit();
    }
}

