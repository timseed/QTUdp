#ifndef HERMES_H
#define HERMES_H

#include <QObject>
#include "QtNetwork/qudpsocket.h"
#include "Helper.h"
#include "udpclient.h"
#define HERMESPORT 1024


enum HermesVersion {Version1=1, Version2=2,Unknown=-1};

class Hermes : public QObject
{
    Q_OBJECT
public:
    explicit Hermes(QObject *parent = nullptr);


    void SendDiscovery();
    char discoveryMsg[64]={0};
    char stopMsg[64]={0};

    int GetVersion(const char *bytesReceived);

    QUdpSocket *rp_client;
public slots:
    void processPendingDatagrams();
signals:

};


#endif // HERMES_H
