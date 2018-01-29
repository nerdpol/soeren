#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

#define UDP_PORT 5005

class UdpListener : public QObject
{
    Q_OBJECT
public:
    explicit UdpListener(QObject *parent = nullptr, int port = UDP_PORT);

signals:

public slots:
    void readPendingDatagrams();

signals:
    void onPaketReady(QNetworkDatagram datagram);

private:
    QUdpSocket * udpSocket;
};

#endif // UDPLISTENER_H
