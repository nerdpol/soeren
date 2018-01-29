#include "udplistener.h"

#include <QUdpSocket>
#include <QNetworkDatagram>

UdpListener::UdpListener(QObject *parent, int udpPort) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, udpPort);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void UdpListener::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        emit this->onPaketReady(datagram);
    }
}
