#include "item.h"
#include <iostream>
#include <vector>

int Item::factorial(int n) const
{
    int result = 1 ;
    for ( int i = n ; i >= 1 ; i--)
             result *= i ;
    return result ;
}

/**
 * @brief Item::getRank 求二维数组展开成一维数组的字典序
 * @return 字典序
 */
int Item::getRank() const
{
    int n=9;
    std::vector<int>temp(n);
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++)
            temp[3*i+j]=this->Map[i][j]+1;
    }
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += (temp[i] - 1) * factorial(n - i - 1);
        for (int j = i + 1; j < n; j++) {
            if (temp[j] > temp[i])
                temp[j]--;
        }
    }
    return result;
}

void Item::initItem(int M[MX][MY])
{
    this->Map[0][0]=M[0][0];
    this->Map[0][1]=M[0][1];
    this->Map[0][2]=M[0][2];
    this->Map[1][0]=M[1][0];
    this->Map[1][1]=M[1][1];
    this->Map[1][2]=M[1][2];
    this->Map[2][0]=M[2][0];
    this->Map[2][1]=M[2][1];
    this->Map[2][2]=M[2][2];
}

Item::Item()
{
    this->Map[0][0]=1;
    this->Map[0][1]=2;
    this->Map[0][2]=3;
    this->Map[1][0]=4;
    this->Map[1][1]=5;
    this->Map[1][2]=6;
    this->Map[2][0]=7;
    this->Map[2][1]=8;
    this->Map[2][2]=BLANK;//0代表空
    this->f_x=this->g_x=this->h_x=0;
}

void Item::set(int g,int h)
{
    this->g_x=g;
    this->h_x=h;
    this->f_x=this->g_x+this->h_x;
}

void Item::setXY(int x,int y,int value)
{
    this->Map[x][y]=value;
}

int Item::geth()const{return this->h_x;}
int Item::getf()const{return this->f_x;}
int Item::getg()const{return this->g_x;}

/**
  第一种评估的方法，即不在位置上的棋子数
  */
int Item::h1() const
{
    int score=0;
    int i,j;
    for(i=0;i<MX;i++){
        for(j=0;j<MY;j++){
            if(this->Map[i][j]!=end_matrix[i][j])
                score++;
        }
    }
    return score;
}

/**
  第二种评估方法，所有棋子到其对应位置的距离和
 */
int Item::h2() const
{
    int score=0;
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){  
            score += abs(i-res[this->Map[i][j]].first)+abs(j-res[this->Map[i][j]].second);
        }
    }
    return score;
}

int Item::getXY(int x,int y)const
{
    return this->Map[x][y];
}

bool Item::operator==(Item a) const
{
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){
            if(this->Map[i][j]!=a.getXY(i,j))
                return false;
        }
    }
    return true;
}

Item& Item::operator=(const Item& a)
{
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++)
            this->Map[i][j]=a.getXY(i,j);
    }
    this->f_x=a.getf();
    this->h_x=a.geth();
    this->g_x=a.getg();
    return *this;
}

/**
 * @brief operator < 写这个函数用来给set容器重载小于号
 * 为了防止序数重复，将二位数组折到一维，计算其字典序
 * @param a
 * @param b
 * @return bool
 */
bool operator<(const Item& a,const Item& b)
{
    int _a=a.getRank();
    int _b=b.getRank();
    return _a<_b;
}

/**
 * @brief Item::move 选择某个方向把某个数码移动一步
 * @param x 原始位置的x坐标
 * @param y 原始位置的y坐标
 * @param mode 方向
 * @param t 改变后的局面
 */
void Item::move(int x,int y,int mode,Item& t) const
{
    Item temp=*this;
    switch (mode) {
        case MYleft:
            temp.setXY(x,y,temp.getXY(x,y+1));
            temp.setXY(x,y+1,0);
            break;
        case MYright:
            temp.setXY(x,y,temp.getXY(x,y-1));
            temp.setXY(x,y-1,0);
            break;
        case up:
            temp.setXY(x,y,temp.getXY(x+1,y));
            temp.setXY(x+1,y,0);
            break;
        case down:
            temp.setXY(x,y,temp.getXY(x-1,y));
            temp.setXY(x-1,y,0);
            break;
        default:
            break;
    }
    t = temp;
}

void Item::output(QTextStream& fout){
    fout << Map[0][0] <<" "<<Map[0][1]<<" "<<Map[0][2]<<'\n';
    fout << Map[1][0] <<" "<<Map[1][1]<<" "<<Map[1][2]<<'\n';
    fout << Map[2][0] <<" "<<Map[2][1]<<" "<<Map[2][2]<<'\n';
    fout<<"f(x)="<<f_x<<"\n";
    fout<<"g(x)="<<g_x<<"\n";
    fout<<"h(x)="<<h_x<<"\n";
}
