#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QPushButton>
#include <QValidator>
#include <QMessageBox>
#include "constant.h"

namespace Ui {
class input;
}

class input : public QWidget
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr);
    ~input();
    bool check();
    int Map[MX][MY];
    Ui::input *ui;
public slots:
    void getNum();
signals:
    void inputOver();
};

#endif // INPUT_H
