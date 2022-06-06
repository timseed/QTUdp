#ifndef HELPER_H
#define HELPER_H
#include <QDebug>
#include <QTime>

#define DEBUG qDebug() << QTime::currentTime().toString("hh:mm:ss.zzz")
#define INFO qInfo() << QTime::currentTime().toString("hh:mm:ss.zzz")

#endif // HELPER_H
