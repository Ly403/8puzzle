#ifndef CONSTANT_H
#define CONSTANT_H
//本头文件为所有常量的集合
#include <QWidget>
#include <QLabel>

const int MX = 3;
const int MY = 3;
const int BLANK = 0;
const int end_matrix[MX][MY]={
    {1,2,3},
    {4,5,6},
    {7,8,0}
};//用来参考的终止状态

const QPair<int,int>res[MX*MY]=
{
  QPair<int,int>(2,2),QPair<int,int>(0,0),QPair<int,int>(0,1),
  QPair<int,int>(0,2),QPair<int,int>(1,0),QPair<int,int>(1,1),
  QPair<int,int>(1,2),QPair<int,int>(2,0),QPair<int,int>(2,1)
};//所有数对应最终的参考位置

enum {
    up,down,MYleft,MYright
};

#define PER_WIDTH 50
#define PER_HEIGHT 50

#define WIDTH 150
#define HEIGHT 200
#define INTERVAL 50 //间隔

#define H1 1
#define H2 2

//const QString PATH = "./tree.png";
#endif // CONSTANT_H
