#include "udpserver.h"

UdpServer::UdpServer(QObject *parent)
    : QObject{parent}
{

}

int UdpServer::getPort() const
{
    return port;
}

void UdpServer::setPort(int newPort)
{
    port = newPort;
}

const QString &UdpServer::getMessage() const
{
    return message;
}

void UdpServer::setMessage(const QString &newMessage)
{
    message = newMessage;
}

int UdpServer::getTimer_interval() const
{
    return timer_interval;
}

void UdpServer::setTimer_interval(int newTimer_interval)
{
    timer_interval = newTimer_interval;
}

void UdpServer::Start()
{
    clock = new QTimer(this);
    connect(clock, SIGNAL(timeout()), this, SLOT(SendBroardCast()));
    clock->start(1000*getTimer_interval());
}

void UdpServer::SendBroardCast()
{
    qInfo() << "Send Broardcast";
    QUdpSocket *udp = new QUdpSocket(this);
    QByteArray dgram = getMessage().toLatin1();
    udp->writeDatagram(dgram.data(), dgram.size(), QHostAddress::Broadcast, getPort());
}
