#include "mybutton.h"



mybutton::mybutton(QWidget *parent):QPushButton(parent)
{
   active=true;
    nom=0;
   QPixmap pix(":/new/prefix1/Img/normal.gif");
   this->resize(35,35);this->setIcon(pix);
    this->setIconSize(QSize(this->frameGeometry().width(),this->height()));
    connect(this,&QPushButton::clicked,this,&mybutton::change);
}

void mybutton::enterEvent(QEvent *)
{
    if(active)
    this->setIcon(QPixmap(":/new/prefix1/Img/highlight.gif"));
}
void mybutton::leaveEvent(QEvent *)
{
    if(active)
    this->setIcon(QPixmap(":/new/prefix1/Img/normal.gif"));
}
void mybutton::change()
{
    if(nom==9)
    {
        //this->bom();
        active=false;
        this->setIcon(QPixmap(":/new/prefix1/Img/explode.gif"));
        callboom();
        return ;
    }

    QChar ttt='0'+nom;
    QString tem1=":/new/prefix1/Img/";
    tem1.append(ttt);
    tem1.append(".gif");
    this->setIcon(QPixmap(tem1));

    if(nom==0){isnull(ii,ij);}
    else active=false;
}
void mybutton::setnum(int num)
{
    this->nom=num;
}
int mybutton::getnum(void)
{
    return this->nom;
}
void mybutton::setnu()
{
    QChar ttt='0'+nom;
    QString tem1=":/new/prefix1/Img/";
    tem1.append(ttt);
    tem1.append(".gif");
    this->setIcon(QPixmap(tem1));
    active=false;
}

bool mybutton::isactive()
{
    return active;
}
