#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QString>
#include <QMessageBox>
#include <QMenu>
#include <game.h>
#include <windows.h>

#define SizeOfBroad 15
#define SizeOfGrid 40
#define SizeOfCrossing 15
#define Width 650
#define Hight 650
#define SpaceSize 45
#define SpaceGrid 5
#define ChessSize 15
#define SpaceCross 5
#define CrossSize 5

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    QLabel *label = new QLabel(this);
    Game *game = new Game();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void PaintPieces();
    void TestPrint(int x,int y);
    void GameInit();
private:
    int MoveX,MoveY;
    int CurrentX,CurrentY;
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
