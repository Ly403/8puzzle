#include "eightpuzzle.h"
#include "ui_eightpuzzle.h"
#include <QtDebug>


eightPuzzle::eightPuzzle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::eightPuzzle)
{
    ui->setupUi(this);
    this->start=false;
    this->init=false;
    this->ui->h1->setChecked(true);//默认状态
    this->mode=H1;
    this->width=this->height=0;
    this->model=new QStringListModel(this);
    connect(ui->autoPutton,&QPushButton::clicked,this,&eightPuzzle::startClick);
    connect(ui->autoPutton,&QPushButton::clicked,this,&eightPuzzle::stopClick);
    connect(ui->init,&QPushButton::clicked,this,&eightPuzzle::initClick);
    connect(&this->it,&input::inputOver,this,&eightPuzzle::initPuzzle);
    connect(this->ui->printTree,&QPushButton::clicked,this,&eightPuzzle::initTree);
    connect(this->ui->h1,&QRadioButton::clicked,this,[=](){
        this->mode=H1;
    });
    connect(this->ui->h2,&QRadioButton::clicked,this,[=](){
        this->mode=H2;
    });
    connect(this->ui->printImage,&QPushButton::clicked,this,[=](){
        this->imageInit();
    });
}

eightPuzzle::~eightPuzzle()
{
    delete ui;
}


void eightPuzzle::outputExec()
{
    if(this->start){
        QStringList s;
        int size=this->getItem.size();
        s<< QString("拓展节点数：") + QString::number(size);
        s<< QString("找到解花费的时间：")+QString::number(this->time,'f',6)+QString("ms");
        s<< QString("解步长：")+QString::number(this->itemList.back().getg());
        s<< QString("待拓展节点数：")+QString::number(this->itemQueue.size());
        this->model->setStringList(s);
        this->ui->View->setModel(model);
        auto iter=this->itemList.begin();
        auto pre = iter;
        for(iter++;iter!=this->itemList.end();pre=iter++){
            int temp=this->findMoveNum(*pre,*iter);
            this->move(temp);
        }
    }
}

QLabel* eightPuzzle::labelList(int i)
{
    switch (i) {
        case 0:
            return this->ui->i_0;
        case 1:
            return this->ui->i_1;
        case 2:
            return this->ui->i_2;
        case 3:
            return this->ui->i_3;
        case 4:
            return this->ui->i_4;
        case 5:
            return this->ui->i_5;
        case 6:
            return this->ui->i_6;
        case 7:
            return this->ui->i_7;
        case 8:
            return this->ui->i_8;
        default:
            break;//实际的使用之中用不到这个分支
    }
    return NULL;
}

void eightPuzzle::move(int i)
{
    int x=this->labelList(i)->pos().x();
    int y=this->labelList(i)->pos().y();
    int _x=this->labelList(BLANK)->pos().x();
    int _y=this->labelList(BLANK)->pos().y();
    this->labelList(i)->move(_x,_y);
    this->labelList(BLANK)->move(x,y);
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < 1000)
        QCoreApplication::processEvents();
}

/**
 * @brief eightPuzzle::initPuzzle 渲染初始状态的图像化表示
 * @param M
 */
void eightPuzzle::initPuzzle()
{

    this->init=true;
    this->ui->init->setText("恢复初始状态");
    this->first.initItem(this->it.Map);
    int x[10]={0};
    int y[10]={0};
    for(int i=0;i<9;i++){
        x[i]=this->labelList(i)->pos().x();
        y[i]=this->labelList(i)->pos().y();
    }
    for(int i=0;i<MX;i++){
        for(int j=0;j<MY;j++){
            int n=(i==2&&j==2)?0:3*i+j+1;
            this->labelList(this->first.getXY(i,j))->move(x[n],y[n]);
        }
    }
    this->start=true;//开始信号
    //this->initQueue();
    this->first.set(0,this->first.h1());
    bool judge;
    QElapsedTimer timer;
    timer.start();
    judge=this->exeGame(this->first);
    this->time=(double)timer.nsecsElapsed()/(double)(1000000);
    if(!judge){
        QMessageBox::critical(this,"critical","该局面设置下游戏无解");
        exit(-1);
    }
    this->initVector();
    this->getResult();
}

void eightPuzzle::startClick()
{
    if(!this->init){
        QMessageBox::critical(this,"critical","未完成初始状态的设置");
        return;
    }
    if(ui->autoPutton->text()=="自动演示"){
        this->ui->autoPutton->setText("暂停10秒钟");
        this->outputExec();
        QMessageBox::information(this,"information","已完成结果展示");
    }
}

void eightPuzzle::stopClick()
{
    if(!this->init){
        QMessageBox::critical(this,"critical","未完成初始状态的设置");
        return;
    }//其实这段用不到
    if(ui->autoPutton->text()=="暂停10秒钟"){
        QElapsedTimer t;
        t.start();
        while (t.elapsed()<10000)
            QCoreApplication::processEvents();
        this->ui->autoPutton->setText("自动演示");
    }
}

void eightPuzzle::initClick()
{
    if(!this->init)
        it.show();
    else{
        this->init=false;
        this->ui->init->setText("设置初始状态");
        this->itemSet.clear();
        this->itemList.clear();
        this->getItem.clear();

        while (!this->itemQueue.empty())
           this->itemQueue.pop();
        this->first=Item();
        QPair<int,int> xy[MX*MY];
        for(int i=0;i<MX*MY;i++){
            xy[i].first=this->labelList(i)->pos().x();
            xy[i].second=this->labelList(i)->pos().y();
        }

        for(int i=0;i<MX*MY-1;i++){
            for(int j=0;j<MX*MY-i-1;j++){
                if(xy[j].first+2*xy[j].second>xy[j+1].first+2*xy[j+1].second){
                    int tempa=xy[j].first;
                    int tempb=xy[j].second;
                    xy[j].first=xy[j+1].first;
                    xy[j].second=xy[j+1].second;
                    xy[j+1].first=tempa;
                    xy[j+1].second=tempb;
                }
            }
        }

        for(int n=0;n<MX*MY;n++){
            int pos=n==0?8:n-1;
            this->labelList(n)->move(xy[pos].first,xy[pos].second);
        }
    }
}

void eightPuzzle::initVector()
{
    for(auto iter=getItem.begin();iter!=getItem.end();iter++){
        if((int)this->layerTree.size()<(*iter).first.getg()+1)//某一层的第一个节点
            this->layerTree.push_back(std::vector<QPair<Item,Item>>());
        this->layerTree[(*iter).first.getg()].push_back(*iter);
    }
}

void eightPuzzle::fileOut()
{
    QString path=QCoreApplication::applicationDirPath();
    QFile file;
    int cnt=1;
    file.setFileName(path + "/tree.txt");
    bool judge=file.open(QIODevice::ReadWrite|QIODevice::Text);
    if(judge){
        QTextStream fout(&file);
        fout.setCodec("utf-8");
        for(auto it=this->layerTree.begin();it!=this->layerTree.end();it++){
            fout<<"layer:"<<cnt<<"\n\n\n";
            for(auto iter=(*it).begin();iter!=(*it).end();iter++){
                (*iter).first.output(fout);
                fout<<"\n";
            }
            cnt++;
            fout<<"==============================================\n";
        }
        file.close();
        QMessageBox::information(this,"infomation","文件路径是" + path+"/tree.txt");
    }
    else
        QMessageBox::critical(this,"critical","文件创建失败");
}


void eightPuzzle::initTree()
{
    if(!this->init){
        QMessageBox::critical(this,"critical","未完成初始状态的设置");
        return;
    }
    this->fileOut();
}

////////////////////////////////////////////////////////////////////
void eightPuzzle::drawItem(int x,int y,const Item& t)
{
    this->painter.drawRect(x,y,PER_WIDTH,PER_HEIGHT);
    this->painter.drawText(QRect(x,y,PER_WIDTH,PER_HEIGHT)
                           ,Qt::AlignHCenter|Qt::AlignVCenter,
                           QString("f(x)="+QString::number(t.getf())));
    this->painter.drawRect(x+PER_WIDTH,y,PER_WIDTH,PER_HEIGHT);
    this->painter.drawText(QRect(x+PER_WIDTH,y,PER_WIDTH,PER_HEIGHT)
                           ,Qt::AlignHCenter|Qt::AlignVCenter
                           ,QString("g(x)="+QString::number(t.getg())));
    this->painter.drawRect(x+2*PER_WIDTH,y,PER_WIDTH,PER_HEIGHT);
    this->painter.drawText(QRect(x+2*PER_WIDTH,y,PER_WIDTH,PER_HEIGHT)
                           ,Qt::AlignHCenter|Qt::AlignVCenter
                           ,QString("h(x)="+QString::number(t.geth())));
    for(int i=1;i<=MX;i++){
        for(int j=0;j<MY;j++){
            this->painter.drawRect(x+j*PER_WIDTH,y+i*PER_HEIGHT,PER_WIDTH,PER_HEIGHT);
            this->painter.drawText(QRect(x+j*PER_WIDTH,y+i*PER_HEIGHT,PER_WIDTH,PER_HEIGHT)
                                   ,Qt::AlignHCenter|Qt::AlignVCenter
                                   ,QString::number(t.getXY(i-1,j)));
        }
    }
}

void eightPuzzle::drawTree()
{
    int pos_x=INTERVAL;
    int pos_y=INTERVAL;
    for(auto it=this->layerTree.begin();it!=this->layerTree.end();it++){
        for(auto iter=(*it).begin();iter!=(*it).end();iter++){
            this->drawItem(pos_x,pos_y,(*iter).first);
            pos_x+=WIDTH+INTERVAL;
        }
        pos_x=INTERVAL;//回归
        pos_y+=HEIGHT+INTERVAL;
    }
}

void eightPuzzle::getSize()
{
    for(auto iter=this->layerTree.begin();iter!=this->layerTree.end();iter++){
        this->width=this->width<(int)(*iter).size()?(int)(*iter).size():this->width;
        this->height++;
    }
    this->height=INTERVAL+this->height*HEIGHT+(this->height-1)*INTERVAL+INTERVAL;
    this->width=INTERVAL+this->width*WIDTH+(this->width-1)*INTERVAL+INTERVAL;
}

void eightPuzzle::imageInit()
{
    this->getSize();
    QPixmap pix(this->width,this->height);
    pix.fill(Qt::white);//白色填充
    painter.begin(&pix);
    this->drawTree();
    QString path=QCoreApplication::applicationDirPath();
    path+="/tree.png";
    pix.save(path);
    painter.end();
    QMessageBox::information(this,"information","图片文件存储在"+path);
}


