#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
class mybutton : public QPushButton
{
    Q_OBJECT
public:
    mybutton(QWidget *parent = nullptr);
    //void paintEvent(QPaintEvent *) override;
    void setnum(int num);
    int getnum(void);
    void setnu(void);
    bool isactive();
    int ii,ij;
signals:
    void isnull(int i,int j);
    void callboom();
private:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

    int nom;
    bool active;
private slots:
    void change();
};

#endif // MYBUTTON_H
