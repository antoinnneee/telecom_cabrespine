#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QTextFormat>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <QMenu>
#include <QMediaPlayer>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QStandardPaths>
#define PATHLOCAL (QString)"/storage/emulated/0/Download"
#define PATHCONF PATHLOCAL+(QString)"/Pupitre/"
#define PATHIMG PATHLOCAL+(QString)"/img/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    ui->setupUi(this);
    ui->label->setStyleSheet("color : #DD0A21 ");
    qDebug("<USER>/Downloads");
    QString ft_path = QStandardPaths::locate(QStandardPaths::DownloadLocation, QString(), QStandardPaths::LocateDirectory);

    qDebug() << ft_path;

    //Bouton 1
    QFile fichier(ft_path + "/img/ar.png");
    if(fichier.exists()) {
        qDebug("Bouton_0");
    ui->pushButton->setStyleSheet("background-image: url( " + ft_path + "/img/ar.png);""background-repeat: no-repeat;""background-position: center;");
    }
    //Bouton2
    QFile fichier1(ft_path + "/img/fr.png");
    if(fichier1.exists()){
        ui->pushButton_2->setStyleSheet("background-image: url( " + ft_path + "/img/fr.png);""background-repeat: no-repeat;""background-position: center;");
    }
    fichier1.close();

    QFile fichierB_R(ft_path + "/img/B_Right.png");
    if(fichierB_R.exists()){
        ui->pushButton_6->setStyleSheet("background-image: url( " + ft_path + "/img/B_Right.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierB_R.close();

    QFile fichierB_TOP(ft_path + "/img/B_TOP.png");
    if(fichierB_TOP.exists()){
        ui->pushButton_3->setStyleSheet("background-image: url( " + ft_path + "/img/B_TOP.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierB_TOP.close();

    QFile fichierB_BOT(ft_path + "/img/B_BOT.png");
    if(fichierB_BOT.exists()){
        ui->pushButton_4->setStyleSheet("background-image: url( " + ft_path + "/img/B_BOT.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierB_BOT.close();

    QFile fichierB_L(ft_path + "/img/B_Left.png");
    if(fichierB_L.exists()){
        ui->pushButton_5->setStyleSheet("background-image: url( " + ft_path + "/img/B_Left.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierB_L.close();
    QFile fichierV_L(ft_path + "/img/V_L.png");
    if(fichierV_L.exists()){
        ui->pushButton_8->setStyleSheet("background-image: url( " + ft_path + "/img/V_L.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierV_L.close();

    QFile fichierV_M(ft_path + "/img/V_M.png");
    if(fichierV_M.exists()){
        qDebug("Bouton_2");
        ui->pushButton_7->setStyleSheet("background-image: url( " + ft_path + "/img/V_M.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierV_M.close();

    QFile fichierV(ft_path + "/img/V.png");
    if(fichierV.exists()){
        qDebug("Bouton_2");
        ui->label_4->setStyleSheet("background-image: url( " + ft_path + "/img/V.png);""background-repeat: no-repeat;""background-position: center; ");
    }
    fichierV.close();

    QFile fichierACT(ft_path + "/img/ACTION.png");
    if(fichierACT.exists()){
        qDebug("Bouton_2");
        ui->label_5->setPixmap(QPixmap(ft_path + "/img/ACTION.png"));
        ui->label_5->setScaledContents(true);
//        ui->label_5->setStyleSheet("background-image: url( /storage/sdcard0/Download/img/ACTION.png);""background-repeat: no-repeat;""background-position: center;");
    }
    fichierACT.close();

    QFile fichierconf(ft_path + "/Pupitre/titre.txt");
    if(fichierconf.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!fichierconf.atEnd())
        {
            qDebug("Read Line -> Titre\n");

             QString RDLINE = fichierconf.readLine();
             qDebug() << ft_path;
             qDebug() << RDLINE;
             NamePup << RDLINE;

        }
    }
    fichierconf.close();

    QFile fichierconf2(ft_path + "/Pupitre/conf.txt");
    if(fichierconf2.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!fichierconf2.atEnd())
        {
                        qDebug("Read Line -> conf\n");
            QTextStream flux(&fichierconf2);
            qDebug() << ft_path;
            LOWRANGE = flux.readLine().toInt();
             MAXRANGE = flux.readLine().toInt();
             PAS = flux.readLine().toInt();
             BASEVOLUME = flux.readLine().toInt();
             MAXPROGBUTTON = flux.readLine().toInt();
             VALUEQUIT = flux.readLine().toInt();
             VALUERESET = flux.readLine().toInt();
        }
    }
    fichierconf2.close();

    QFile fichierconf3(ft_path + "/Pupitre/Wifi.txt");
    if(fichierconf3.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!fichierconf3.atEnd())
        {
                        qDebug("Read Line -> passerelle\n");
            QString RDPSRL = fichierconf3.readLine();
            GrpPup << RDPSRL;
        }
    }
    fichierconf3.close();

    VALEURSON = BASEVOLUME;
    ReCheck();

    ui->label_3->setText(QString::number(VALEURSON));
    ui->label->setText(NamePup[0].mid(0 , NamePup[0].count() - 1));
    tableFormat.setBorder(0);
    PupNbr = 1;
    IDGRP = GrpPup[0].mid(0,2);
    STATE = 0;
    strPupNbr= '0' + QString::number(PupNbr);
    myNickName = client.nickName();
    ui->label->setScaledContents(true);
    CheckWifiState();
//connect(ui->SonSlider, SIGNAL(valueChanged(int)),this, SLOT(on_SonSlider_Move()));// initialis  e le slider
connect(&client, SIGNAL(newMessage(QString,QString)),
        this, SLOT(appendMessage(QString,QString)));
    player = new QMediaPlayer(this);

    player->setMedia(QUrl::fromLocalFile(ft_path + "/son/ting.mp3"));

}
void MainWindow::appendMessage(const QString &from, const QString &message)
{

    qDebug() << "Ping Receive";
    if (from.isEmpty() || message.isEmpty())
        return;
    if (message.contains(IDGRP.mid(0,2) + "ping"))
        client.sendMessage(IDGRP + "pong");
    else if (message.contains("POK"))
        client.sendMessage(IDGRP + "VALID");
    else if(message.contains("VALIDOK"))
        STATE = 1;
    else if (message.contains("OK"))
    {
        QString ft_path = QStandardPaths::locate(QStandardPaths::DownloadLocation, QString(), QStandardPaths::LocateDirectory);
        player->setMedia(QUrl::fromLocalFile(ft_path + "/son/ting.mp3"));
        player->play();
        STATE = 1;
    }

}

void MainWindow::ReCheck()
{
//    client.sendMessage(strPupNbr + "pong");
//    QTimer::singleShot(300,this, SLOT(ReCheck()));

}
void MainWindow::CheckWifiState()
{

    if(STATE)
    {
        ui->label->setStyleSheet("color : #1EC81B ");
    }
    else
    {
        ui->label->setStyleSheet("color : #DD0A21 ");
    }
    if (LAST != STATE)
        if (LAST == 0)
            player->play();

    LAST = STATE;
    STATE = 0;
    QTimer::singleShot(2000, this, SLOT(CheckWifiState()));
}


void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << "Push Left";
    qDebug() << PupNbr;
    STATE = 0;
    ui->label->setStyleSheet("color : #DD0A21 ");
    PupNbr--;
    if (PupNbr < 1)
    {
        PupNbr = NamePup.count();
        qDebug() << NamePup[PupNbr - 1];
        ui->label->setText(NamePup[PupNbr - 1].mid(0,NamePup[PupNbr - 1].count() - 1));
    }
    else
    {
        qDebug() << NamePup[PupNbr - 1];

    ui->label->setText(NamePup[PupNbr - 1].mid(0,NamePup[PupNbr - 1].count() - 1));
    }

    if(PupNbr <= 9)
        strPupNbr = '0' + QString::number(PupNbr);
    else
        strPupNbr= QString::number(PupNbr);
        qDebug() << "Apres les if";

//    IDGRP = GrpPup[PupNbr - 1].mid(0,2); Surrement inutile, a verifier quand meme
        qDebug() << "Apres le groupe";
}

void MainWindow::on_pushButton_6_clicked()
{
    qDebug() << "Push Left";
    STATE = 0;
    ui->label->setStyleSheet("color : #DD0A21 ");
    PupNbr++;
    if (PupNbr <= NamePup.count())
    {
        ui->label->setText(NamePup[PupNbr - 1].mid(0,NamePup[PupNbr - 1].count() - 1));
    }
    else
    {
        PupNbr = 1;
        ui->label->setText(NamePup[PupNbr - 1].mid(0,NamePup[PupNbr - 1].count() - 1));
    }

    if(PupNbr <= 9)
        strPupNbr = '0' + QString::number(PupNbr);
    else
        strPupNbr= QString::number(PupNbr);

//    IDGRP = GrpPup[PupNbr - 1].mid(0,2); Surrement inutile, a verifier quand meme

}
MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::CheckForRfcomm()
{
    return(NULL);
}

void MainWindow::on_pushButton_clicked()
{
    client.sendMessage(IDGRP + strPupNbr + "!H");

}
void MainWindow::on_pushButton_2_clicked(){
    client.sendMessage(IDGRP + strPupNbr + "!OIFG");
}

void MainWindow::on_pushButton_7_clicked()
{
    VALEURSON = VALEURSON + PAS;
    if (VALEURSON >= 100)
    {
        VALEURSON = 100;
        STRINGSON=QString::number(VALEURSON - 1);
        client.sendMessage(IDGRP + strPupNbr + "!V" + STRINGSON);
    }
    else
    {
        if (VALEURSON <= 9)
        {
            STRINGSON=QString::number(VALEURSON);
            client.sendMessage(IDGRP + strPupNbr + "!V" + '0' +STRINGSON);
        }
        else
        {
            STRINGSON=QString::number(VALEURSON);
            client.sendMessage(IDGRP + strPupNbr + "!V" + STRINGSON);
        }
    }
    ui->label_3->setText(STRINGSON);
}
void MainWindow::on_pushButton_8_clicked()
{
    VALEURSON = VALEURSON - PAS;
    if (VALEURSON <= 0)
    {
        VALEURSON = 0;
        STRINGSON=QString::number(VALEURSON);
        client.sendMessage(IDGRP + strPupNbr + "!V" + STRINGSON);
    }
    else
    {
        if (VALEURSON <= 9)
        {
        STRINGSON=QString::number(VALEURSON);
        client.sendMessage(IDGRP + strPupNbr + "!V" + '0' + STRINGSON);
        }
        else
        {
            STRINGSON=QString::number(VALEURSON);
            client.sendMessage(IDGRP + strPupNbr + "!V" + STRINGSON);
        }
    }
    ui->label_3->setText(STRINGSON);
}
void MainWindow::on_pushButtonVar_clicked()
{
    if ( ui->pushButtonVar->text().toInt() == VALUEQUIT)
    {
       client.sendMessage(strPupNbr + "QUIT");
    }
    if ( ui->pushButtonVar->text().toInt() == VALUERESET)
    {
       client.sendMessage(strPupNbr + "!RC");
    }
    else
    {
    if (ui->pushButtonVar->text().toInt() <= 9)
    {
        QString msg(IDGRP + strPupNbr + "!L0" + ui->pushButtonVar->text());
        client.sendMessage(msg);
        qDebug() << msg;

    }
    else
    client.sendMessage(IDGRP + strPupNbr + "!L" + ui->pushButtonVar->text());
    }
}
void MainWindow::on_pushButton_3_clicked()
{
        if(ui->pushButtonVar->text().toInt() + 1 >= MAXPROGBUTTON + 1)
        {
            int inc = 1;
            if ( inc == VALUEQUIT )
            {
                ui->centralWidget->setStyleSheet("background-color: #FF0000;");
            }
            else if (inc == VALUERESET)
            {
                     ui->centralWidget->setStyleSheet("background-color : #0B04F8;");
            }

            ui->pushButtonVar->setText(QString::number(inc));
        }
        else
        {
            int inc = ui->pushButtonVar->text().toInt() + 1;
            if (inc == VALUEQUIT)
                ui->centralWidget->setStyleSheet("background-color: #FF0000;");
            else if (inc == VALUERESET)
                ui->centralWidget->setStyleSheet("background-color : #0B04F8;");
            else
                ui->centralWidget->setStyleSheet("background-color: #3A1400;");
            ui->pushButtonVar->setText(QString::number(inc));
        }
}

void MainWindow::on_pushButton_4_clicked()
{
        if(ui->pushButtonVar->text().toInt() - 1 <= 0)
        {
            int inc = MAXPROGBUTTON;
            ui->pushButtonVar->setText(QString::number(inc));
        }
        else
        {
            int inc = ui->pushButtonVar->text().toInt() - 1;
            ui->pushButtonVar->setText(QString::number(inc));
        }
            ui->centralWidget->setStyleSheet("background-color: #3A1400;");
            int inc = ui->pushButtonVar->text().toInt();
            if ( inc == VALUEQUIT )
            {
                ui->centralWidget->setStyleSheet("background-color: #FF0000;");
            }
            else if (inc == VALUERESET)
                ui->centralWidget->setStyleSheet("background-color : #0B04F8;");
}
