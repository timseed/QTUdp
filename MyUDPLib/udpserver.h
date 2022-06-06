#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QDebug>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);

    int getPort() const;
    void setPort(int newPort);

    const QString &getMessage() const;
    void setMessage(const QString &newMessage);
    QTimer *clock;
    int getTimer_interval() const;
    void setTimer_interval(int newTimer_interval);
    void Start();
    void End();

public slots:
    void SendBroardCast();

signals:

 private:
    int port=9020;
    int timer_interval=10;
    QString message="Test";


};

#endif // UDPSERVER_H
