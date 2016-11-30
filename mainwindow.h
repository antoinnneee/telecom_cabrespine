#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "androidrfcomm.h"
#include "client.h"
#include <QTextTableFormat>
#include <QMainWindow>
#include <QListWidgetItem>
#include <qbluetoothglobal.h>
#include <qbluetoothlocaldevice.h>
#include <QMediaPlayer>
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

QT_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString CheckForRfcomm();
public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButtonVar_clicked();
//    void on_SonSlider_Move();
    void appendMessage(const QString &from, const QString &message);
    void CheckWifiState();
    void ReCheck();
private:
    QString msgo;
    int VALUERESET;
    int LOWRANGE;
    int MAXRANGE;
    int MAXPROGBUTTON;
    int VALUEQUIT;
    int BASEVOLUME;
    int PAS;
    int LAST;
    QMediaPlayer *player;
    QString strPupNbr;
    int PupNbr;
    QString IDGRP;
    QStringList NamePup;
    QStringList GrpPup;
    Ui::MainWindow *ui;
    Client client;
    int STATE;
    QString myNickName;
    int VALEURSON;
    QString STRINGSON;
    QTextTableFormat tableFormat;
};

#endif // MAINWINDOW_H
