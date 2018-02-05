#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udplistener.h"

#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataTrack.h>
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <iostream>
#include <cstdlib>
#include <QDateTime>
#include <QTimer>
#include "mymarblewidget.h"



// parameters
#define UDP_PORT 5005

// demo options
// #define DEMO_SHOW
#define DEMO_TIMESTEP 10


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup map
    mapWidget = new MyMarbleWidget;
    mapWidget->setMapThemeId(QStringLiteral("earth/openstreetmap/openstreetmap.dgml"));
    mapWidget->centerOn(10.894446, 48.366512);
    mapWidget->setDistance(100);
    mapWidget->show();

    // setup udp
    UdpListener * listener = new UdpListener(this, UDP_PORT);
    connect(listener, &UdpListener::onPaketReady, this, &MainWindow::onDataPaket);
    connect(this, &MainWindow::onNewRealPoint, mapWidget, &MyMarbleWidget::addRealPointAsJson);

#ifdef DEMO_SHOW
    // start demo
    startDummyTimer();
#endif
}

// handle incoming pakets (to update the map etc)
void MainWindow::onDataPaket(QNetworkDatagram datagram) {
    std::cout << "UDP paket: " << datagram.data().data() << std::endl;

    // 1. parse json
    QJsonParseError err;
    char * raw = datagram.data().data();
    QString str = QString::fromUtf8(datagram.data());
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &err);
    qDebug() << "Error: " << err.errorString();
    if(doc.isNull()){
        qDebug() << "Failed to create JSON doc.";
        exit(2);
    }
    if(!doc.isObject()){
        qDebug() << "JSON is not an object.";
        exit(3);
    }
    QJsonObject obj = doc.object();
    qDebug() << "UDP -> Json object ->" << obj;
    if(obj["_type"].isString() && obj["_type"] == "gps") {

        // 2. notify if it is a suitable paket
        emit onNewRealPoint(doc.object());

    } else {
        qDebug() << "unsuitable paket, _type=" << obj["_type"];
    }
}

// start a dummy timer to show real time functionality
void MainWindow::startDummyTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, mapWidget, &MyMarbleWidget::addDummyPoint);
    timer->start(DEMO_TIMESTEP);
}

MainWindow::~MainWindow()
{
    delete ui;
}
