#ifndef COMMON_H
#define COMMON_H

#define DEFAULTFRAMERATE 29.7

#include <QMessageBox>
#include <QString>
#include <QObject>
#include <QTime>
#include <QPixmap>


QString  createUuid() ;
QString createSimpleUuid() ;
int getMSec(QTime t) ;
QTime getTime(qint64 msec) ;


void runProcess( QObject* parent, QString path, QStringList arg ) ;
#endif // COMMON_H
