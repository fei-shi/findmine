#include "widget.h"
#include "ui_widget.h"

#include<QPushButton>
#include<QDialog>
#include<QVector>
#include<QMenuBar>
static ee level1={7,5};
static ee level2={10,9};
static ee level3={14,9};
static int winlength=350;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette pal(Qt::white);
    this->setPalette(pal);
    qsrand(QTime::currentTime().msec());
    setFixedSize(350,590);
    setWindowIcon(QIcon(":/new/prefix1/Img/n.gif"));
    setWindowTitle(QString::fromLocal8Bit("扫雷"));
    QLabel *mysign=new QLabel(QString::fromLocal8Bit("by: 迷芒果人"),this);
    mysign->move(width()-mysign->width(),height()-mysign->height()+10);
    numofmi=new QLabel(QString::fromLocal8Bit("number of mines:35"),this);
    QFont tem;
    tem.setPointSize(15);
    numofmi->setFont(tem);
    numofmi->move(width()-numofmi->text().length()*15,30);
    QMenuBar *bar=new QMenuBar(this);
    QAction *resettn=bar->addAction(QString::fromLocal8Bit("新的游戏"));
    QMenu *selectn=bar->addMenu(QString::fromLocal8Bit(("选择难度")));
    QAction *level1btn=selectn->addAction(QString::fromLocal8Bit("简单"));
    QAction *level2btn=selectn->addAction(QString::fromLocal8Bit("中等"));
    QAction *level3btn=selectn->addAction(QString::fromLocal8Bit("困难"));
    connect(resettn,&QAction::triggered,this,&Widget::dealre);
    connect(level1btn,&QAction::triggered,this,&Widget::deallc1);
    connect(level2btn,&QAction::triggered,this,&Widget::deallc2);
    connect(level3btn,&QAction::triggered,this,&Widget::deallc3);
    level=3;
    reset(level);

}


Widget::~Widget()
{
    delete ui;
}

void Widget::doit()
{
    QDialog *a=new QDialog();
    a->show();
}
void Widget::expl(int i,int j)
{
    deal(i,j);
}
void Widget::deal(int i,int j)
{
    if(f[i][j]->isactive())f[i][j]->setnu();
    else return;
    if(i>0)
    {
        if(f[i-1][j]->getnum()==0)
            deal(i-1,j);
        else
            f[i-1][j]->setnu();
    }
    if(j>0)
    {
        if(f[i][j-1]->getnum()==0)
            deal(i,j-1);
        else
            f[i][j-1]->setnu();
    }
    if(i<(size-1))
    {
        if(f[i+1][j]->getnum()==0)
            deal(i+1,j);
        else
            f[i+1][j]->setnu();
    }
    if(j<(colsize-1))
    {
        if(f[i][j+1]->getnum()==0)
            deal(i,j+1);
        else
            f[i][j+1]->setnu();
    }
}
void Widget::reset(int level)
{
    int minenum;
    for(int i=0;i<f.size();i++)
    {
        for(int j=0;j<f[i].size();j++)
        {
            delete(f[i][j]);
        }
    }
    f.resize(0);
    if(level==1)
    {
        size=level1.size;
        colsize=level1.colsize;
        minenum=4;
    }
    else if(level==2)
    {
        size=level2.size;
        colsize=level2.colsize;
        minenum=15;
    }
    else
    {
        size=level3.size;
        colsize=level3.colsize;
        minenum=35;
    }
    QVector<int> minelist;
    int xx=0;int l=0;
    while(xx<minenum)
    {
        int tem=rand()%(size*colsize);
        bool jug=true;int i=0;
        while(i<l){if(minelist.at(i)==tem){jug=false;break;}i++;}
        if(!jug)continue;
        l++;xx++;minelist.push_back(tem);
    }
    int oo=0;
    qDebug()<<f.size();
    for(int i=0;i<size;i++)
    {
        QVector<mybutton *> tmd;
        f.push_back(tmd);
        for(int j=0;j<colsize;j++)
        {
            mybutton *t=new mybutton(this);
            for(int md=0;md<minenum;md++)
            {
                if(minelist.at(md)==oo)
                {
                    t->setnum(9);break;
                }
            }
            t->ii=i;t->ij=j;
            void(mybutton:: *sig)(int,int)=&mybutton::isnull;
            void(Widget::*slo)(int,int)=&Widget::expl;
            connect(t,sig,this,slo);
            connect(t,&mybutton::callboom,this,&Widget::boom);
            f[i].push_back(t);
            t->show();
            t->move(j*t->width()+(width()-colsize*t->width())/2,i*t->height()+(height()-size*t->height())/2+20);
            oo++;
        }
    }
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<colsize;j++)
        {
            int tem=0;
            if(f[i][j]->getnum()!=9)
            {
                if(i!=0){if(f[i-1][j]->getnum()==9)tem++;}
                if(j!=0){if(f[i][j-1]->getnum()==9)tem++;}
                if(i!=(size-1)){if(f[i+1][j]->getnum()==9)tem++;}
                if(j!=(colsize-1)){if(f[i][j+1]->getnum()==9)tem++;}
                if(i!=0&&j!=0){if(f[i-1][j-1]->getnum()==9)tem++;}
                if(i!=0&&j!=(colsize-1)){if(f[i-1][j+1]->getnum()==9)tem++;}
                if(i!=(size-1)&&j!=0){if(f[i+1][j-1]->getnum()==9)tem++;}
                if(i!=(size-1)&&j!=(colsize-1)){if(f[i+1][j+1]->getnum()==9)tem++;}
                f[i][j]->setnum(tem);
            }
        }
    }
}
void Widget::boom()
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<colsize;j++)
        {
            f[i][j]->setnu();
        }
    }

    if(QMessageBox::Yes==QMessageBox::question(this,QString::fromLocal8Bit("再来一局"),"try again?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        reset(level);
}
void Widget::dealre()
{
    if(level==1)
        numofmi->setText(QString::fromLocal8Bit("number of mines:4"));
    if(level==2)
        numofmi->setText(QString::fromLocal8Bit("number of mines:15"));
    if(level==3)
        numofmi->setText(QString::fromLocal8Bit("number of mines:35"));
    this->reset(level);
}
void Widget::deallc1()
{
    level=1;
    dealre();
}
void Widget::deallc2()
{
    level=2;
    dealre();
}
void Widget::deallc3()
{
    level=3;
    dealre();
}
