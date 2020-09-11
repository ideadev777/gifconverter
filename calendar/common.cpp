#include "common.h"
#include <QUuid>
#include <QProcess>

QString createUuid()
{
	return QUuid::createUuid().toString() ;
}

QString createSimpleUuid()
{
	QString ret = createUuid() ;
	ret.chop(1) ;
	ret = ret.right(ret.length()-1) ;
	return ret ;
}

int getMSec(QTime t) 
{
	int ret = t.hour()*3600 ;
	ret += t.minute()*60 ;
	ret += t.second() ;
	ret = ret*1000+t.msec() ;
	return ret ;
}

QTime getTime(qint64 msec) 
{
	int s = msec/1000 ;
	msec %= 1000 ;
	int h = s/3600 ;
	s %= 3600 ;
	int m = s/60 ;
	s%=60 ;
	return QTime(h,m,s,msec) ;
}

void runProcess( QObject* parent, QString path, QStringList arg )
{
	QProcess *myProcess = new QProcess(parent);
	myProcess->start(path,arg);
	if (myProcess->waitForStarted(-1)) {
		while(myProcess->waitForReadyRead(-1)) {
		}
	}
}