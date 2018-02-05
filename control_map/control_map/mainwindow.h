#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkDatagram>
#include <mymarblewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onDataPaket(QNetworkDatagram datagram);

signals:
    void onNewRealPoint(const QJsonObject & obj);

private:
    Ui::MainWindow *ui;
    MyMarbleWidget *mapWidget;

    void startDummyTimer();
};

#endif // MAINWINDOW_H
