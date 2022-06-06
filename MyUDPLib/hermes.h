#ifndef HERMES_H
#define HERMES_H

#include "Helper.h"
#include "QtNetwork/qudpsocket.h"
#include "udpclient.h"
#include <QObject>
#define HERMESPORT 1024

enum HermesVersion { Version1 = 1, Version2 = 2, UnknownVersion = -1 };
enum HermesHardware {
  METIS_Hardware = 1,
  HERMES_Hardware = 2,
  GRIFFIN_Hardware = 3,
  ANGELIA_Hardware = 4,
  HERMESLT_Hardware = 5,
  RTLDNGL_Hardware = 6,
  REDPITAYA_Hardware = 7,
  AFEDRI_Hardware = 8,
  ORION_Hardware = 9,
  ORION2_Hardware = 10,
  ANAN10_HardwareE = 11,
  Unknown_Hardware = -1
};

enum HermesReceivers {
  OneRX = 1,
  TwoRX = 2,
  ThreeRX = 3,
  FourRX = 4,
  FiveRX = 5,
  SixRX = 6,
  SevenRX = 7,
  EightRX = 8,
  UnknownRX = -1
};

class Hermes : public QObject {
  Q_OBJECT
public:
  explicit Hermes(QObject *parent = nullptr);

  void SendDiscovery();
  char discoveryMsg[64] = {0};
  char stopMsg[64] = {0};

  int GetVersion(const char *bytesReceived);
  int GetHardware(const char *bytesReceived);
  QUdpSocket *rp_client;
  const QString &getMac_address() const;
  void setMac_address(const QString &newMac_address);

  int getMax_recvrs() const;
  void setMax_recvrs(int newMax_recvrs);

  int getAtt() const;
  void setAtt(int newAtt);

  int getMaxAtt() const;
  void setMaxAtt(int newMaxAtt);

  int getDeviceHw() const;
  void setDeviceHw(int newDeviceHw);
  QString HwSummary();

public slots:
  void processPendingDatagrams();
signals:

private:
  QString mac_address;
  int max_recvrs;
  int Att;
  int MaxAtt;
  int DeviceHw;
};

#endif // HERMES_H
