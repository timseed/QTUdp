#include "hermes.h"

Hermes::Hermes(QObject *parent) : QObject{parent} {
  discoveryMsg[0] = (char)0xEF;
  discoveryMsg[1] = (char)0xFE;
  discoveryMsg[2] = (char)0x04;
  discoveryMsg[3] = (char)0x00;
  /* This is to listen for the Response */

  stopMsg[0] = (char)0xEF;
  stopMsg[1] = (char)0xFE;
  stopMsg[2] = (char)0x04;
  stopMsg[3] = (char)0x00;

  rp_client = new QUdpSocket(this);
  rp_client->bind(HERMESPORT, QUdpSocket::ShareAddress);
  connect(rp_client, SIGNAL(readyRead()), this,
          SLOT(processPendingDatagrams()));
}

void Hermes::SendDiscovery() {
  QUdpSocket *discoverySock = new QUdpSocket(this);
  QByteArray dgram = discoveryMsg;
  INFO << "Sending Discovery";
  discoverySock->writeDatagram(dgram.data(), dgram.size(),
                               QHostAddress::Broadcast, HERMESPORT);
}

int Hermes::GetVersion(const char *bytesReceived) {
  /*
   * Decode the Discovert Packet.
   *
   */
  if (bytesReceived[0] == (char)0xEF && bytesReceived[1] == (char)0xFE)
    return HermesVersion::Version1;
  else if (bytesReceived[0] == (char)0x00 && bytesReceived[1] == (char)0x00 &&
           bytesReceived[3] == (char)0x00 && bytesReceived[4] == (char)0x00)
    return HermesVersion::Version2;
  else
    return HermesVersion::UnknownVersion;
}

int Hermes::GetHardware(const char *bytesReceived) {
  char ver = bytesReceived[9];
  switch (bytesReceived[10]) {
  case 0x00:
    setDeviceHw(HermesHardware::METIS_Hardware);
    setMax_recvrs(HermesReceivers::FourRX);
    setAtt(0);
    setMaxAtt(0);
    break;
  case 0x01:
    setDeviceHw(HermesHardware::HERMES_Hardware);
    setMax_recvrs(HermesReceivers::FourRX);
    setAtt(0);
    setMaxAtt(0);

    if (ver == 18) {
      setMax_recvrs(HermesReceivers::SevenRX);

    } else if (ver == 25) {
      setMax_recvrs(HermesReceivers::FiveRX);
    } else if (ver == 29) {
      setMax_recvrs(HermesReceivers::FourRX);
    } else if (ver >= 15 && ver < 18) {
      // ANAN10E board masquerades as a Hermes but sends a lower firmware
      // version
      setMax_recvrs(HermesHardware::ANAN10_HardwareE);

    } else {
      setMax_recvrs(HermesReceivers::FourRX);
    }
    setAtt(0);
    setMaxAtt(31);
    break;
  case 0x02:
    setDeviceHw(HermesHardware::GRIFFIN_Hardware);
    setMax_recvrs(HermesReceivers::TwoRX);
    setAtt(0);
    setMaxAtt(31);
    break;
  case 0x04:
    setDeviceHw(HermesHardware::ANGELIA_Hardware);
    setMax_recvrs(HermesReceivers::SevenRX);
    setAtt(0);
    setMaxAtt(31);

    break;
  case 0x05:
    setDeviceHw(HermesHardware::ORION_Hardware);
    setMax_recvrs(HermesReceivers::SevenRX);
    setAtt(0);
    setMaxAtt(31);

    break;
  case 0x06:
    setDeviceHw(HermesHardware::HERMESLT_Hardware);
    setMax_recvrs(HermesReceivers::SevenRX);
    setAtt(0);
    setMaxAtt(31);

    // Hermes-Lite may have different number of receivers
    // Always advertised here though
    max_recvrs = bytesReceived[19];
    setAtt(0);
    setMaxAtt(0);
    // Gain controlled automatically in FPGA with dither=on
    MaxAtt = 0;
    break;
  case 0x0A:
    setDeviceHw(HermesHardware::ORION2_Hardware);
    setMax_recvrs(HermesReceivers::SevenRX);
    setAtt(0);
    setMaxAtt(31);

    break;
  default:
    setDeviceHw(HermesHardware::Unknown_Hardware);
    setMax_recvrs(HermesReceivers::TwoRX);
    // Guessing at these values.
    setAtt(0);
    setMaxAtt(0);
    char ch_emulation_id[9];
    std::memcpy(ch_emulation_id,&bytesReceived[11],8);
    ch_emulation_id[8]='\0';
    QString emulation_id;
    emulation_id=ch_emulation_id;
    INFO << "EmulationID is " << emulation_id;
  }
  return 0;
}

void Hermes::processPendingDatagrams() {
  INFO << "UDPClient received a packet";
  QByteArray datagram;
  while (rp_client->hasPendingDatagrams()) {
    datagram.resize(int(rp_client->pendingDatagramSize()));
    rp_client->readDatagram(datagram.data(), datagram.size());
    int ver = GetVersion(datagram.constData());
    switch (ver) {
    case HermesVersion::Version1: {
      QString mac;
      INFO << "Version 1 device responded";
      mac = QString::asprintf("%02X%02X%02X", datagram.constData()[6] & 0xFF,
                              datagram.constData()[7] & 0xFF,
                              datagram.constData()[8] & 0xFF);
      setMac_address(mac);

      GetHardware(datagram.constData());
      INFO << HwSummary();
    } break;
    case HermesVersion::Version2:
      INFO << "Version 2 device responded";
      break;
    case HermesVersion::UnknownVersion:
      INFO << "Unknown device responded";
      break;
    }
  }
}

int Hermes::getDeviceHw() const { return DeviceHw; }

void Hermes::setDeviceHw(int newDeviceHw) { DeviceHw = newDeviceHw; }

QString Hermes::HwSummary() {
  QString hw;

  switch (getDeviceHw()) {
  case METIS_Hardware:
    hw += "Metis ";
    break;
  case HERMES_Hardware:
    hw += "Hermes ";
    break;
  case GRIFFIN_Hardware:
    hw += "Griffin ";
    break;
  case ANGELIA_Hardware:
    hw += "Angelia ";
    break;
  case HERMESLT_Hardware:
    hw += "Hermes ";
    break;
  case RTLDNGL_Hardware:
    hw += "RTLDNGL ";
    break;
  case REDPITAYA_Hardware:
    hw += "RedPitaya ";
    break;
  case AFEDRI_Hardware:
    hw += "Afedri ";
    break;
  case ORION_Hardware:
    hw += "Orion ";
    break;
  case ORION2_Hardware:
    hw += "Orion2 ";
    break;
  case ANAN10_HardwareE:
    hw += "Anan10 ";
    break;
  case Unknown_Hardware:
    hw += "Unknown ";
    break;
  }
  hw+= " Rx: "+QString::number(getMax_recvrs());
  return hw;
}

int Hermes::getMaxAtt() const { return MaxAtt; }

void Hermes::setMaxAtt(int newMaxAtt) { MaxAtt = newMaxAtt; }

int Hermes::getAtt() const { return Att; }

void Hermes::setAtt(int newAtt) { Att = newAtt; }

int Hermes::getMax_recvrs() const { return max_recvrs; }

void Hermes::setMax_recvrs(int newMax_recvrs) { max_recvrs = newMax_recvrs; }

const QString &Hermes::getMac_address() const { return mac_address; }

void Hermes::setMac_address(const QString &newMac_address) {
  mac_address = newMac_address;
}
