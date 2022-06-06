#include <QCoreApplication>
#include "udpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdpClient *client=new UdpClient();
    client->Setup();
    return a.exec();
}
