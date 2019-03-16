#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include<QMainWindow>
#include <QString>
#include <QPaintEvent>
#include<QPainter>
#include <QPixmap>

class Display: public QWidget
{
public:
    Display(QMainWindow *p);
    void getChar(char c);
    void getInt(int _i);
    void draw();

protected:
    void paintEvent(QPaintEvent *event);

private:
    char ch;
    int i;
};

#endif // DISPLAY_H
