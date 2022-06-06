#ifndef MYUDPLIB_GLOBAL_H
#define MYUDPLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYUDPLIB_LIBRARY)
#  define MYUDPLIB_EXPORT Q_DECL_EXPORT
#else
#  define MYUDPLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MYUDPLIB_GLOBAL_H
