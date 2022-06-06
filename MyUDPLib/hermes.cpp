#include "hermes.h"



Hermes::Hermes(QObject *parent)
    : QObject{parent}
{
    discoveryMsg[0] = (char) 0xEF;
    discoveryMsg[1] = (char) 0xFE;
    discoveryMsg[2] = (char) 0x04;
    discoveryMsg[3] = (char) 0x00;
    /* This is to listen for the Response */

        stopMsg[0] = (char) 0xEF;
        stopMsg[1] = (char) 0xFE;
        stopMsg[2] = (char) 0x04;
        stopMsg[3] = (char) 0x00;

    rp_client = new QUdpSocket(this);
    rp_client->bind(HERMESPORT,QUdpSocket::ShareAddress);
    connect(rp_client,SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));


}

void Hermes::SendDiscovery()
{
    QUdpSocket *discoverySock =  new QUdpSocket(this);
    QByteArray dgram =discoveryMsg;
    INFO << "Sending Discovery";
    discoverySock->writeDatagram(dgram.data(), dgram.size(), QHostAddress::Broadcast, HERMESPORT);
}

int Hermes::GetVersion(const char *bytesReceived)
{
    /*
     * Decode the Discovert Packet.
     *
     */
   if (bytesReceived[0]== (char)0xEF &&
           bytesReceived[1]==(char)0xFE)
        return HermesVersion::Version1;
   else if (bytesReceived[0]== (char)0x00 &&
           bytesReceived[1]==(char)0x00 &&
            bytesReceived[3]==(char)0x00 &&
            bytesReceived[4]==(char)0x00 )
        return HermesVersion::Version2;
   else return HermesVersion::Unknown;
}

void Hermes::processPendingDatagrams()
{
    INFO << "UDPClient received a packet";
    QByteArray datagram;
      while (rp_client->hasPendingDatagrams()) {
          datagram.resize(int(rp_client->pendingDatagramSize()));
          rp_client->readDatagram(datagram.data(), datagram.size());
          int ver = GetVersion(datagram.constData());
          switch (ver)
          {
          case HermesVersion::Version1:
              INFO << "Version 1 device responded";
              break;
          case HermesVersion::Version2:
              INFO << "Version 2 device responded";
              break;
          case HermesVersion::Unknown:
              INFO << "Unknown device responded";
              break;
          }

      }
}
