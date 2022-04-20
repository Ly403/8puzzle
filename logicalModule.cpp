#include "eightpuzzle.h"
#include <iostream>

bool eightPuzzle::isTravel(const Item& t)
{
    return this->itemSet.count(t)==1;
}

/**
 * @brief eightPuzzle::isGameOver
 * @param t
 * @return 判断局面是否已经到达终止状态
 */
bool eightPuzzle::isGameOver(const Item& t)
{
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){
            if(t.getXY(i,j)!=end_matrix[i][j])
                return false;
        }
    }
    return true;
}

/*
void eightPuzzle::initQueue()
{
    this->first.set(0,this->first.h1());
    this->itemQueue.push(this->first);
}*/


void eightPuzzle::step(int x,int y,int mode,const Item& node)
{
    Item temp;
    node.move(x,y,mode,temp);
    int g=node.getg()+1;//深度加一
    int h;
    if(this->mode==H1)
        h=temp.h1();
    else
        h=temp.h2();
    temp.set(g,h);

    if(!this->isTravel(temp)){//判断有没有走过
        QPair<Item,Item> both;
        both.first=temp;
        both.second=node;
        this->itemQueue.push(both);//放入队列,注意本节点和父节点组成一个对
    }
}

void eightPuzzle::next(int x,int y,const Item& node)
{
    int cnt;
    if(x==1 && y==1){
        for(cnt=0;cnt<4;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYleft,node);
                    break;
                case 1:
                    this->step(x,y,MYright,node);
                    break;
                case 2:
                    this->step(x,y,up,node);
                    break;
                case 3:
                    this->step(x,y,down,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==1 && y==0){
        for(cnt=0;cnt<3;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYleft,node);
                    break;
                case 1:
                    this->step(x,y,up,node);
                    break;
                case 2:
                    this->step(x,y,down,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==1 && y==2){
        for(cnt=0;cnt<3;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYright,node);
                    break;
                case 1:
                    this->step(x,y,down,node);
                    break;
                case 2:
                    this->step(x,y,up,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==0 && y==1){
        for(cnt=0;cnt<3;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYright,node);
                    break;
                case 1:
                    this->step(x,y,up,node);
                    break;
                case 2:
                    this->step(x,y,MYleft,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==0 && y==0){
        for(cnt=0;cnt<2;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYleft,node);
                    break;
                case 1:
                    this->step(x,y,up,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==0 && y==2){
        for(cnt=0;cnt<2;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYright,node);
                    break;
                case 1:
                    this->step(x,y,up,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==2 && y==1){
        for(cnt=0;cnt<3;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYleft,node);
                    break;
                case 1:
                    this->step(x,y,MYright,node);
                    break;
                case 2:
                    this->step(x,y,down,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==2 && y==0){
        for(cnt=0;cnt<2;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYleft,node);
                    break;
                case 1:
                    this->step(x,y,down,node);
                    break;
                default:
                    break;
            }
        }
    }
    else if(x==2 && y==2){
        for(cnt=0;cnt<2;cnt++){
            switch (cnt) {
                case 0:
                    this->step(x,y,MYright,node);
                    break;
                case 1:
                    this->step(x,y,down,node);
                    break;
                default:
                    break;
            }
        }
    }
}

void eightPuzzle::findBlank(const Item& t,int &x,int &y)
{
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){
            if(t.getXY(i,j)==BLANK){
                x=i;
                y=j;
                return;
            }
        }
    }
}

void eightPuzzle::extend(const Item& t)
{
    int x,y;
    this->findBlank(t,x,y);
    this->next(x,y,t);
}

/**
 * @brief eightPuzzle::findMoveNum
 * @param a
 * @param b
 * @return 两个相邻不同局面，找出是哪一个数码被移动了，返回数码值
 */
int eightPuzzle::findMoveNum(const Item& a,const Item& b)
{
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){
            int _a=a.getXY(i,j);
            int _b=b.getXY(i,j);
            if(_a!=_b && _a != BLANK)
                return _a;
        }
    }
    return 0;//一般是到不了这的
}

bool eightPuzzle::exeGame(Item& t)
{
    QPair<Item,Item> temp;
    temp.first=temp.second=t;
    this->getItem.push_back(temp);

    this->itemQueue.push(temp);//初始化
    while (!this->itemQueue.empty()) {
        if(this->isGameOver(temp.first)){
            this->getItem.pop_front();
            return true;
        }
        temp=this->itemQueue.top();
        this->itemQueue.pop();
        this->getItem.push_back(temp);
        this->itemSet.insert(temp.first);
        this->extend(temp.first);
    }
    this->getItem.pop_front();
    return false;
}

/*
QPair<std::list<Item>,bool> eightPuzzle::exeGame(Item& t)
{
    QPair<std::list<Item>,bool> pair;
    if(this->isGameOver(t)){
        std::list<Item> ql;
        ql.push_back(t);
        pair.first=ql;
        pair.second=true;
        return pair;
    }
    this->extend(t);
    while (!this->itemQueue.empty()) {
        QPair<Item,Item>ItemPair=this->itemQueue.top();
        this->itemQueue.pop();
        this->getItem.push_back(ItemPair);
        pair =this->exeGame(ItemPair.first);
        if(pair.second)
            return pair;
    }
    std::list<Item> temp;
    pair.first=temp;
    pair.second=false;
    return pair;
}
*/
void eightPuzzle::getResult()
{
    auto iter=this->getItem.end();
    auto itend=--this->getItem.begin();
    Item temp=(*iter).first;
    for(iter--;iter!=itend;iter--){
        //最后一个元素肯定是终态
        if(this->isGameOver((*iter).first)){
            this->itemList.push_front((*iter).first);
            temp=(*iter).second;
        }
        else{
            if((*iter).first==temp){
                this->itemList.push_front((*iter).first);
                temp=(*iter).second;
            }
        }
    }
    //处理最后一个节点
    this->itemList.push_front(temp);
}
