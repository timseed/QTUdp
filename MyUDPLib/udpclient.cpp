#include "udpclient.h"

UdpClient::UdpClient(QObject *parent)
    : QObject{parent}
{

}

int UdpClient::getPort() const
{
    return port;
}

void UdpClient::setPort(int newPort)
{
    port = newPort;
}

void UdpClient::Setup()
{
      udpSocket = new QUdpSocket(this);
      udpSocket->bind(getPort(),QUdpSocket::ShareAddress);
      connect(udpSocket,SIGNAL(readyRead()),
              this, SLOT(processPendingDatagrams()));
}

void UdpClient::processPendingDatagrams()
{
    qInfo() << "UDPClient received a packet";
    QByteArray datagram;
      while (udpSocket->hasPendingDatagrams()) {
          datagram.resize(int(udpSocket->pendingDatagramSize()));
          udpSocket->readDatagram(datagram.data(), datagram.size());
          qInfo() << "Received datagram "<< datagram.constData();
      }
}
