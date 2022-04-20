#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include <QWidget>
#include <QLabel>
#include <queue>
#include <QFile>
#include <QTextStream>
#include <QElapsedTimer>
#include <QStringListModel>
#include <QPainter>
#include <QPixmap>
#include "./constant.h"
#include <set>
#include <list>
#include "treepix.h"
#include "item.h"
#include "input.h"

QT_BEGIN_NAMESPACE
namespace Ui { class eightPuzzle; }
QT_END_NAMESPACE

class eightPuzzle : public QWidget
{
    Q_OBJECT

private:
    class cmp {
        public:
            bool operator()(const QPair<Item,Item>& a, const QPair<Item,Item>& b) {
                return a.first.getf() > b.first.getf();
            }
    };
    friend class treePix;
    bool init;
    bool start;
    int mode;
    double time;//运行花的时间
    input it;//输入信息
    Item first;//当前局面信息
    Ui::eightPuzzle *ui;
    std::set<Item> itemSet;//集合
    std::list<Item> itemList;
    std::list<QPair<Item,Item>> getItem;
    std::vector<std::vector<QPair<Item,Item>>> layerTree;
    std::priority_queue<QPair<Item,Item>,std::vector<QPair<Item,Item>>,cmp>itemQueue;//最小优先队列
    QStringListModel *model;
    int findMoveNum(const Item& a,const Item& b);//对比前后两个局面，找到是哪一个数码发生了移动
    QLabel* labelList(int i);


    /*=================分割线========================*/
    long long int height;//图高
    long long int width;//图宽
    QPainter painter;

public:
    eightPuzzle(QWidget *parent = nullptr);
    ~eightPuzzle();
    void initQueue();//专门为边缘队列做初始化
    bool isTravel(const Item& t);
    bool isGameOver(const Item& t);//判断是否结束
    void next(int x,int y,const Item& node);//尝试下一步
    void step(int x,int y,int mode,const Item& node);//选择向某个方向移动数码，mode决定方向
    void extend(const Item& t);
    void findBlank(const Item& t,int &x,int &y);
 //   QPair<std::list<Item>,bool> exeGame(Item&);
    bool exeGame(Item&);
 //   int output();
    void initVector();
    void fileOut();//打印搜索树到文件中
    void getResult();
    void outputExec();//整个游戏的进行
    void move(int i);//把某个数码移动空白位置

    /*=================分割线========================*/
    void drawItem(int x,int y,const Item& t);//在某个位置画上一个局面
    void drawTree();
    void getSize();

public slots:
    void initPuzzle();
    void startClick();//开始按键
    void stopClick();
    void initClick();
    void initTree();
    void imageInit();
};

#endif // EIGHTPUZZLE_H
