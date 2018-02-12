#include "mymarblewidget.h"


MyMarbleWidget::MyMarbleWidget(QWidget * parent) : MarbleWidget(parent) {
    this->real_track = new GeoDataTrack();

    // add some dummy map data
    this->dummy_lat = 48.36;
    this->dummy_lon = 10.98;
    this->dummy_x = 0;
    this->planned_track = new GeoDataTrack();
    qreal offset = 0;
    for (int i = 0; i < 30; i++) {

        qreal lon = 10.98 + sin(i/4) / 16;
        qreal lat = 48.36 - offset*2;
        offset += 0.005;

        GeoDataCoordinates coord(lon, lat, 100.0 - i*2.0, GeoDataCoordinates::Degree);
        this->planned_track->addPoint(QDateTime::currentDateTime(), coord);
    }

    this->setShowAtmosphere(true);
    this->setShowRelief(true);
    this->setShowFrameRate(true);

    // Access the shared route request (start, destination and parameters)
    RoutingManager* manager = this->model()->routingManager();
    //this->model()
    RouteRequest* request = manager->routeRequest();

    // Use default routing settings for cars
    request->setRoutingProfile( manager->defaultProfile( RoutingProfile::Pedestrian) );

    // Set start and destination
    request->append( GeoDataCoordinates( 8.38942, 48.99738, 0.0, GeoDataCoordinates::Degree ) );
    request->append( GeoDataCoordinates( 8.42002, 49.0058, 0.0, GeoDataCoordinates::Degree ) );
    request->append( GeoDataCoordinates( 8.43002, 49.0158, 0.0, GeoDataCoordinates::Degree ) );

    // Calculate the route
    manager->retrieveRoute();

}

void MyMarbleWidget::customPaint(GeoPainter* painter)
{
    // draw planned track
    QPen pen(Qt::blue);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolyline(*(this->planned_track->lineString()), "Planned Route");
    painter->setBackground(Qt::transparent);

    // draw real track
    QPen pen2(Qt::green);
    pen2.setWidth(3);
    painter->setPen(pen2);
    painter->drawPolyline(*(this->real_track->lineString()), "Real Route");
    painter->setBackground(Qt::transparent);
}



/*
gps:
  char: "G"
  fields:
          - {type: "uint32_t", name: "latitude", unit: "°"}
          - {type: "uint32_t", name: "longitude", unit: "°"}
          - {type: "uint16_t", name: "altitude", unit: "m"}
          - {type: "uint8_t", name: "links", unit: "1"}
          - {type: "uint16_t", name: "yaw", unit: "1/100 °"}
          - {type: "uint16_t", name: "velocity", unit: "1/100 m/s"}
*/
void MyMarbleWidget::addRealPointAsJson(const QJsonObject &json) {
    // qDebug() << "addRealPointAsJson() -> " << json;
    qreal lat = json["latitude"].toDouble();
    qreal lon = json["longitude"].toDouble();

    GeoDataCoordinates coord(lon, lat, 0, GeoDataCoordinates::Degree);
    this->real_track->addPoint(QDateTime::currentDateTime(), coord);
    this->update();
}

void MyMarbleWidget::addDummyPoint() {
    QJsonObject obj;
    obj.insert("_type", QJsonValue("gps"));
    obj.insert("longitude", QJsonValue(this->dummy_lon));
    obj.insert("latitude", QJsonValue(this->dummy_lat));
    obj.insert("links", QJsonValue(12));
    obj.insert("yaw", QJsonValue(1));
    obj.insert("velocity", QJsonValue(10));
    addRealPointAsJson(obj);
    this->dummy_x += 0.01;
    this->dummy_lat += sin(this->dummy_x) / 1010;
    this->dummy_lon += cos(this->dummy_x) / 1080;
}
