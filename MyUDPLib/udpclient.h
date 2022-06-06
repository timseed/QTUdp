#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include "Helper.h"

#include "QtNetwork/qudpsocket.h"
#include <QObject>

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = nullptr);
    QUdpSocket *udpSocket = nullptr;
    int getPort() const;
    void setPort(int newPort);
    void Setup();

public slots:
    void processPendingDatagrams();

signals:

 private:
    int port=9020;
};

#endif // UDPCLIENT_H
