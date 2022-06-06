#include <QCoreApplication>
#include "hermes.h"
#include "udpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Hermes *rp_hw = new Hermes();
    rp_hw->SendDiscovery();
    return a.exec();
}
