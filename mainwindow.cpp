#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    music_flag(No),
    stm("/dev/ttyACM0"),
    stu("/dev/ttyUSB0")
{
    resize(1000,750);

    _start=new QPushButton(this);
    _start->setGeometry(700,500,150,50);
    _start->setText("START");
    connect(_start,&QAbstractButton::clicked,this,
            &MainWindow::Init_Serial);

    _read=new QPushButton(this);
    _read->setGeometry(700,570,150,50);
    _read->setText("READ");
    connect(_read,&QAbstractButton::clicked,this,
            &MainWindow::newCard);

    input=new QLineEdit(this);
    input->setGeometry(900,570,50,50);


    _stop=new QPushButton(this);
    _stop->setGeometry(700,640,150,50);
    _stop->setText("STOP");
    connect(_stop,&QAbstractButton::clicked,this,
            &MainWindow::stop);

    title=new QLabel(this);
    title->setGeometry(700,450,300,50);

    display=new Display(this);

    num=new QListWidget(this);
    num -> setGeometry(700,50,250,350);

    //    QHeaderView* headerView=num->horizontalHeader();
    //    headerView->setSectionResizeMode(QHeaderView::Stretch);

    card = new Music("/home/jyannuoruta/音乐/card.mp3");
    didi = new Music("/home/jyannuoruta/音乐/didi.mp3");
    hit= new Music("/home/jyannuoruta/音乐/hit.mp3");
    miss=new Music("/home/jyannuoruta/音乐/miss.mp3");
}

MainWindow::~MainWindow()
{
    if(stm.isOpen())
    {
        stm.clear();
        stm.close();
    }
    if(stu.isOpen())
    {
        stu.clear();
        stu.close();
    }
}

void MainWindow::Init_Serial()//finish
{
    OpenStm();

    connect(&stm,&QIODevice::readyRead,this,
            &MainWindow::Stm_RX,Qt::UniqueConnection);
    OpenStu();
    connect(&stu,&QIODevice::readyRead,this,
            &MainWindow::Stu_TXRX,Qt::UniqueConnection);
}

void MainWindow::newCard()//finish
{
    title->setText("Add New Card");

    OpenStm();
    connect(&stm,&QIODevice::readyRead,this,
            &MainWindow::card_RX,Qt::UniqueConnection);
}

void MainWindow::card_RX()//finish
{
    card->play();
    while(stm.waitForReadyRead(10))
        stm_temp+=stm.readAll();
    QByteArray temp(10,' ');
    std::copy(stm_temp.begin()+1,stm_temp.end()-1,temp.begin());
    int i= input->text().toInt();

    if(!cardNum.contains(temp))
        cardNum.insert(temp,i);

    num->addItem(temp);
    num->addItem(QString(i+'0'));
    input->clear();
    stm_temp.clear();
}

void MainWindow::OpenStm()   //finish
{
    if(stm.isOpen()){
        stm.clear();
        stm.close();
    }
    stm.setBaudRate(QSerialPort::Baud9600);
    stm.setDataBits(QSerialPort::Data8);
    stm.setParity(QSerialPort::NoParity);
    stm.setStopBits(QSerialPort::OneStop);
    if(!stm.open(QIODevice::ReadOnly))
        title->setText("stm not open");
        //qDebug()<<"stm not open";
}

void MainWindow::OpenStu()//finish
{
    title->setText("Start");
    if(stu.isOpen()){
        stu.clear();
        stu.close();
    }
    stu.setBaudRate(QSerialPort::Baud9600);
    stu.setDataBits(QSerialPort::Data8);
    stu.setParity(QSerialPort::NoParity);
    stu.setStopBits(QSerialPort::OneStop);
    if(!stu.open(QIODevice::ReadWrite))
        title->setText("stu not open");
        //qDebug()<<"stu not open";

}

void MainWindow::Stm_RX()  //finish
{
    card->play();
    while(stm.waitForReadyRead(10))
        stm_temp+=stm.readAll();
    QByteArray temp(10,' ');
    std::copy(stm_temp.begin()+1,stm_temp.end()-1,temp.begin());

    QMap<QByteArray,int>::iterator p=cardNum.find(temp);
    display->getInt(p.value());
    char i=p.value()+'0';

    stu.write(&i);

    stm_temp.clear();
}

void MainWindow::Stu_TXRX()
{
    stu_temp=stu.readAll();//get x,y,z

    if(stu_temp[0]=='x'){
        didi->play();
    }
    if(stu_temp[0]=='y'){
        hit->play();
    }
    if(stu_temp[0]=='z'){
        miss->play();
    }
    if(stu_temp[0]=='w'){
        miss->stop();
        hit->stop();
    }
}

void MainWindow::stop()//finish
{
    title->setText("Stop");
    if(stm.isOpen())
    {
        stm.clear();
        stm.close();
    }
    if(stu.isOpen())
    {
        stu.clear();
        stu.close();
    }

    disconnect(&stm,0,0,0);
}
