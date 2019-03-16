#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

#include "music.h"
#include "display.h"
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <algorithm>
#include <QMap>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    enum Music_Flag
    {
        No,Gaming,Hit,MIss
    };
    int flag,music_flag;

    Music *card,*didi,*hit,*miss;
    Display *display;

    QSerialPort stm,stu;
    QByteArray stm_temp,stu_temp;
    QMap<QByteArray,int>cardNum;

    QPushButton *_start,*_read,*_stop;
    QLabel *title;
    QLineEdit *input;
    QListWidget *num;

    void OpenStm();
    void OpenStu();

private slots:
    void Init_Serial();
    void newCard();
    void card_RX();
    void Stm_RX();//stm->pc
    void Stu_TXRX();//stu<--->pc
    void stop();
};

#endif // MAINWINDOW_H
