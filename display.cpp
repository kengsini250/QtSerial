#include "display.h"

static QString p0=":/img/0.png";
static QString p1=":/img/1.png";
static QString p2=":/img/2.png";
static QString p3=":/img/3.png";
static QString back=":/img/back.png";

Display::Display(QMainWindow *p):QWidget (p)
  ,ch(' '),i(0)
{
    setGeometry(50,50,650,650);
    //setStyleSheet("background-color:black;");
}

void Display::getChar(char c)
{
    ch=c;
    update();
}

void Display::getInt(int _i)
{
    i=_i;
    update();
}

void Display::draw()
{

}

void Display::paintEvent(QPaintEvent */*event*/)
{
    QPainter p(this);
    QPixmap pix;

    switch(i)
    {
    case 2:
        pix.load(p2);
        break;
    case 1:
        pix.load(p1);
        break;
    default:
        pix.load(back);
    }


    p.drawPixmap(0,0,450,650,pix);
}
