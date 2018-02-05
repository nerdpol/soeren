#ifndef MYMARBLEWIDGET_H
#define MYMARBLEWIDGET_H

#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataTrack.h>
#include <QNetworkDatagram>
#include <iostream>
#include <cstdlib>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>


using namespace Marble;

class MyMarbleWidget : public MarbleWidget
{
public:
    explicit MyMarbleWidget(QWidget * parent = 0);
    virtual void customPaint(GeoPainter* painter);

public slots:
    void addRealPointAsJson(const QJsonObject & json);
    void addDummyPoint();

private:
    Marble::GeoDataTrack *planned_track;
    Marble::GeoDataTrack *real_track;

    // only for testing purposes
    qreal dummy_lat;
    qreal dummy_lon;
    qreal dummy_x;
    void scheduleDummyTimer();
};


#endif // MYMARBLEWIDGET_H
