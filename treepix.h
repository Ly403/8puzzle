/*
#ifndef TREEPIX_H
#define TREEPIX_H

//本类用来画搜索树
#include <QWidget>
#include <QPainter>
#include <QImage>
#include "item.h"
#include "constant.h"
#include <vector>
#include "eightpuzzle.h"

namespace Ui {
class treePix;
}

class treePix : public QWidget
{
    Q_OBJECT
public:
    explicit treePix(QWidget *parent = nullptr);
    ~treePix();
    void initVector(const eightPuzzle& t);
    void drawItem(int x,int y,const Item& t);//在某个位置画上一个局面
    void getSize();
    void init(const eightPuzzle& t);
    void drawTree();
    //void paintEvent(QPaintEvent *event);
public slots:
    void start(const eightPuzzle& t);
private:
    Ui::treePix *ui;
    int height;//图高
    int width;//图宽
    QPainter painter;
    QImage img;
    std::vector<std::vector<QPair<Item,Item>>> layerTree;
};

#endif // TREEPIX_H
*/
