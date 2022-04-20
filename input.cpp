#include "input.h"
#include "ui_input.h"

input::input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
    QRegExp regx("^[0-8]$");
    QValidator * qv = new QRegExpValidator(regx);
    this->ui->Edit1->setValidator(qv);
    this->ui->Edit2->setValidator(qv);
    this->ui->Edit3->setValidator(qv);
    this->ui->Edit4->setValidator(qv);
    this->ui->Edit5->setValidator(qv);
    this->ui->Edit6->setValidator(qv);
    this->ui->Edit7->setValidator(qv);
    this->ui->Edit8->setValidator(qv);
    this->ui->Edit9->setValidator(qv);
    connect(ui->pushButton,&QPushButton::clicked,this,&input::getNum);
}

input::~input()
{
    delete ui;
}

void input::getNum()
{
    this->Map[0][0]=this->ui->Edit1->text().toInt();
    this->Map[0][1]=this->ui->Edit2->text().toInt();
    this->Map[0][2]=this->ui->Edit3->text().toInt();
    this->Map[1][0]=this->ui->Edit4->text().toInt();
    this->Map[1][1]=this->ui->Edit5->text().toInt();
    this->Map[1][2]=this->ui->Edit6->text().toInt();
    this->Map[2][0]=this->ui->Edit7->text().toInt();
    this->Map[2][1]=this->ui->Edit8->text().toInt();
    this->Map[2][2]=this->ui->Edit9->text().toInt();
    if(this->check()){
        emit this->inputOver();
        this->close();
    }
    else
        QMessageBox::critical(this,"critical","输入信息错误，请重新输入");
}

bool input::check()
{
    bool judge[9]={0};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(!judge[this->Map[i][j]])
                judge[this->Map[i][j]]=true;
            else
                return false;
        }
    }
    return true;
}
