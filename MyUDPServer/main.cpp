#include <QCoreApplication>
#include "udpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdpServer *USrv = new UdpServer(a.parent());
    USrv->setTimer_interval(3);
    USrv->Start();

    return a.exec();
}
