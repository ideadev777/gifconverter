#include "cxseekbar.h"
#include <QPainter>
#include <QMouseEvent>

#define SEEKW 10
#define SEEKH 40

CxSeekBar::CxSeekBar(QWidget *parent)
	: QLabel(parent)
{
	m_seekItem = new QLabel(this) ;
	m_seekItem->setStyleSheet("QLabel{background-color:#00dfff;}") ;
	m_seekItem->show() ;
	m_seekItem->setGeometry(5,5,SEEKW,SEEKH) ;
	m_isPressing = false ;
	m_totMSec = 1000 ;
}

CxSeekBar::~CxSeekBar()
{

}

void CxSeekBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this) ;
	painter.setPen(Qt::NoPen) ;
	painter.setBrush(QBrush(QColor("#202d64"))) ;
	int w = width() ;
	int h = height() ;
	//202d64
	int dx, dy ;
	dx = dy = 5 ;
	painter.drawRect( 0, 0, w, h ) ;
	painter.setBrush(QBrush(QColor("#d6d6d6"))) ;
	painter.drawRect(dx,dy,w-2*dx,h-2*dy) ;

}

void CxSeekBar::mousePressEvent(QMouseEvent *ev)
{
	QPoint pnt = ev->pos() ;
	QRect geo = m_seekItem->geometry() ;
	int px = ev->pos().x() ;
	if( !geo.contains(pnt) ) {
		setCurrentSeek(m_totMSec*px/(width()-SEEKW-10),true) ;
		return ;
	}
	m_isPressing = true ;
	m_originRect = geo ;
	m_mousePressPos = px ;
}

void CxSeekBar::mouseMoveEvent(QMouseEvent* event)
{
	QLabel::mouseMoveEvent(event) ;
	if( !m_isPressing ) return ;
	int nx = event->pos().x()-m_mousePressPos+m_originRect.topLeft().x() ;
	nx = qMax(0,nx) ;
	nx = qMin(width()-SEEKW-10,nx) ;
	QRect rc = m_originRect ;
	rc.moveLeft(nx) ;
	setCurrentSeek(nx*1.0/(width()-SEEKW-10)*m_totMSec,true) ;
}

void CxSeekBar::mouseReleaseEvent(QMouseEvent *event)
{
	QLabel::mouseReleaseEvent(event) ;
	m_isPressing = false ;
}

void CxSeekBar::setCurrentSeek( qint64 mSec, bool isclicked )
{
	m_curSeekSec = mSec ;
	int w = width()-10 ;
	int dx = 5;
	int dy = 5 ;
	m_seekItem->setGeometry( (w-SEEKW)*mSec/m_totMSec, dy, SEEKW, SEEKH ) ;
	if( isclicked ) emit __seek(mSec) ;
}

void CxSeekBar::setDuration( qint64 msec )
{
	m_totMSec = msec ;
	setCurrentSeek(0) ;
}