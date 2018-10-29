#include "leaderboardwindow.h"
#include "ui_leaderboardwindow.h"
#include "startwindow.h"
#include "searchplayerwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <QTimeEdit>
#include <QTimer>
#include <QBasicTimer>
#include <QtDebug>
#include <QScreen>
#include "mainwindow.h"

static QTimer *timer1 = new QTimer();

leaderboardWindow::leaderboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaderboardWindow)
{
    ui->setupUi(this);

    // get screen size
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rec = screen->geometry();
    int w = rec.width();
    int h = rec.height();

    ui->CloseGUI->setGeometry(w-50,0,50,50);
    ui->pushButtonBack->setGeometry(150,0,150,50);
    ui->pushButtonBACK2->setGeometry(0,0,150,50);
    ui->Label_date->setGeometry(w-400,0,350,50);
    ui->labelTopBar->setGeometry(0,0,w-50,50);
    ui->groupBox->setGeometry(w/2+250,h/2-280,625,600);
    ui->groupBox_2->setGeometry(w/2-235,20,470,80);
    ui->groupBoxGIF->setGeometry(w/2-850,h/2-280,570,200);
    ui->groupBoxEvents->setGeometry(w/2-850,h/2,570,400);

    ui->pushButtonBack->setStyleSheet("background-color: lightGray");
    ui->pushButtonBACK2->setStyleSheet("background-color: Gray");
    ui->groupBox_2->setStyleSheet("Background-color: lightblue");
    ui->Label_date->setStyleSheet("background-color: lightblue");
    ui->CloseGUI->setStyleSheet("background-color: red");
    ui->labelTopBar->setStyleSheet("background-color: lightblue");
    ui->groupBox->setStyleSheet("QGroupBox { border: 6px solid black;}");
    ui->groupBoxEvents->setStyleSheet("QGroupBox { border: 6px solid black;}");
    ui->groupBoxGIF->setStyleSheet("QGroupBox { border: 6px solid black;}");

    this->setStyleSheet("background-color: white;");
    ui->timeEdit->setDisplayFormat("mm:ss");

    ui->pushButton_3->setStyleSheet("background-color: lightGreen");
    ui->pushButton_4->setStyleSheet("background-color: red");
    ui->textBrowser_2->setStyleSheet(" { border: 4px solid black;}");
    ui->centralWidget->setGeometry(500,500,500,500);

    QFile gm(game_mode);
    QString game_time;

    gm.open(QIODevice::ReadOnly);

    QTextStream gm_stream(&gm);
    while(!gm_stream.atEnd())
    {
        game_time = gm_stream.readLine();
    }

    int minutes = game_time.toInt();

    ui->timeEdit->setTime(QTime(0, minutes, 0));

    connect (timer1, SIGNAL(timeout()),this,SLOT(timerupdater()));

}

leaderboardWindow::~leaderboardWindow() {
    delete ui;
}

void leaderboardWindow::on_pushButton_3_clicked() {

    //start timer to keep time, timer sends events
    auto current_time = ui->timeEdit->time();
    if(current_time.second() == 0 && current_time.minute() == 0) {
        return;
    }

    timer1->start(1000);

    //do file i/o stuff
    QFile file("C:\\test.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        ui->textBrowser_2->append(line);
    }
    //ui->textBrowser_2->setText(in.readAll());
}

void leaderboardWindow::on_pushButton_4_clicked() {

    //do timer stuff
    timer1->stop();
    QTime zero_time(0,0);
    ui->timeEdit->setTime(zero_time);
}

void leaderboardWindow::timerupdater() {

    auto input_time = ui->timeEdit->time();
    int minutes = input_time.minute();
    int seconds = input_time.second();

    if(seconds == 0) {
        seconds = 59;
        minutes--;
    } else {
        seconds--;
    }

    if(seconds == 0 && minutes == 0) {
        on_pushButton_4_clicked();
    }


    ui->timeEdit->setTime(QTime(0, minutes, seconds));
}

void leaderboardWindow::on_pushButtonBack_clicked()
{
    close();
    SearchPlayerWindow *SPW;
    SPW = new SearchPlayerWindow(this);
    SPW->showFullScreen();
}

void leaderboardWindow::on_pushButtonBACK2_clicked()
{
    close();
    StartWindow *SW;
    SW = new StartWindow(this);
    SW->showFullScreen();

}
