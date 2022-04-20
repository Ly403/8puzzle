#ifndef ITEM_H
#define ITEM_H

#include <cmath>
#include <QWidget>
#include "./constant.h"
#include <QTextStream>
/**
封装一个用来存储8数码局面数据的类
  */
class Item
{
private:
    int Map[MX][MY];
    int f_x;
    int g_x;
    int h_x;
    //内部使用的函数
    int factorial(int n) const;
    int getRank() const ;
public:
    Item();
    void initItem(int M[MX][MY]);
    void set(int g=0,int h=0);
    void setXY(int x,int y,int value);
    int getXY(int x,int y)const;
    int geth()const;
    int getf()const;
    int getg()const;
    void move(int x,int y,int mode,Item& t) const;
    int h1() const;//第一种评估方法
    int h2() const;//第二种评估方法
    bool operator==(Item a) const;
    Item& operator=(const Item& a);
    friend bool operator<(const Item& a,const Item& b);
    void output(QTextStream& fout);
};


#endif // ITEM_H
