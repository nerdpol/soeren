#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class UdpListener : public QObject
{
    Q_OBJECT
public:
    explicit UdpListener(QObject *parent, int port);

signals:

public slots:
    void readPendingDatagrams();

signals:
    void onPaketReady(QNetworkDatagram datagram);

private:
    QUdpSocket * udpSocket;
};

#endif // UDPLISTENER_H
