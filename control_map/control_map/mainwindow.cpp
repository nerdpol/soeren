#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udplistener.h"

#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <QNetworkDatagram>
#include <iostream>


// TODO
// - draw GeoDataTrack real route
// - draw 'should' route


using namespace Marble;

class MyMarbleWidget : public MarbleWidget
{
public:
    virtual void customPaint(GeoPainter* painter);
};

void MyMarbleWidget::customPaint(GeoPainter* painter)
{
    GeoDataCoordinates home(8.4, 49.0, 0.0, GeoDataCoordinates::Degree);
    painter->setPen(Qt::green);
    painter->drawEllipse(home, 7, 7);
    painter->setPen(Qt::black);
    painter->drawText(home, QStringLiteral("Hello Marble!"));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup map stuff
    MyMarbleWidget *mapWidget = new MyMarbleWidget;
    mapWidget->setMapThemeId(QStringLiteral("earth/openstreetmap/openstreetmap.dgml"));
    mapWidget->centerOn(8.4, 49.0);
    mapWidget->show();

    // setup udp stuff
    UdpListener * listener = new UdpListener(this);
    connect(listener, &UdpListener::onPaketReady, this, &MainWindow::onDataPaket);
}

// handle incoming pakets (to update the map etc)
void MainWindow::onDataPaket(QNetworkDatagram datagram) {
    std::cout << "UDP paket: " << datagram.data().data() << std::endl;

    // 1. parse json

    // 2. save map point in GeoDataTrack Object

    // 3. udpate map data accordingly using this GeoDataTrack Object (GeoPainter above)
    //    (see protocol.yaml)
}

MainWindow::~MainWindow()
{
    delete ui;
}
