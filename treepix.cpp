/*
#include "treepix.h"
#include "ui_treepix.h"

treePix::treePix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::treePix)
{
    ui->setupUi(this);
    void (eightPuzzle::*a)(const eightPuzzle&)=&eightPuzzle::draw;
    void (treePix::*b)(const eightPuzzle&)=&treePix::start;
    connect()
}

void treePix::start(const eightPuzzle& t)
{
    this->init(t);
    this->drawTree();
}

void treePix::drawTree()
{
    int pos_x=INTERVAL;
    int pos_y=INTERVAL;
    for(auto it=this->layerTree.begin();it!=this->layerTree.end();it++){
        for(auto iter=(*it).begin();iter!=(*it).end();iter++){
            this->drawItem(pos_x,pos_y,(*iter).first);
            pos_x+=WIDTH+INTERVAL;
        }
        pos_y+=HEIGHT+INTERVAL;
    }
}

treePix::~treePix()
{
    img.save(PATH);
    painter.end();
    delete ui;
}

void treePix::initVector(const eightPuzzle& t)
{
    for(auto iter=t.getItem.begin();iter!=t.getItem.end();iter++){
        if((int)this->layerTree.size()<(*iter).first.getg()+1)//某一层的第一个节点
            this->layerTree.push_back(std::vector<QPair<Item,Item>>());
        this->layerTree[(*iter).first.getg()].push_back(*iter);
    }
}


void treePix::getSize()
{
    for(auto iter=this->layerTree.begin();iter!=this->layerTree.end();iter++){
        this->width=this->width<(int)(*iter).size()?(int)(*iter).size():this->width;
        this->height++;
    }
    this->height=INTERVAL+this->height*HEIGHT+(this->height-1)*INTERVAL+INTERVAL;
    this->width=INTERVAL+this->width*WIDTH+(this->width-1)*INTERVAL+INTERVAL;
}

void treePix::init(const eightPuzzle& t)
{
    this->initVector(t);
    this->getSize();
    img.scaled(this->width,this->height);
    img.fill(Qt::white);//白色填充
    painter.begin(&img);
    //以上为简单初始化
}


void treePix::drawItem(int x,int y,const Item& t)
{
    this->painter.drawText(QRect(x,y,PER_WIDTH,PER_HEIGHT),QString("f(x)="+QString(t.getf())));
    this->painter.drawText(QRect(x+PER_WIDTH,y,PER_WIDTH,PER_HEIGHT),QString("g(x)="+QString(t.getg())));
    this->painter.drawText(QRect(x+2*PER_WIDTH,y,PER_WIDTH,PER_HEIGHT),QString("h(x)="+QString(t.geth())));
    for(int i=0;i<MX;i++){
        for(int j=1;j<=MY;j++)
            this->painter.drawText(QRect(x+i*PER_WIDTH,y+j*PER_HEIGHT,PER_WIDTH,PER_HEIGHT)
                                   ,QString(t.getXY(i,j)));
    }
}
**/
