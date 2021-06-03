#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>

#include <mybutton.h>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
struct ee
{
    int size;
    int colsize;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Create();
    void deal(int i,int j);
public slots:
    void expl(int ,int );
    void boom();
private:
    Ui::Widget *ui;
    int mine_n;
    QVector<QVector<mybutton *>> f;
    int colsize;
    int size;
    int level;
    QLabel *numofmi;
    void reset(int level);
private slots:
    void doit();
    void dealre();
    void deallc1();
    void deallc2();
    void deallc3();
};
#endif // WIDGET_H
