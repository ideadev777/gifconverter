#include "cxseekbar.h"
#include <QPainter>
#include <QMouseEvent>

#define SEEKW 30
#define SEEKH 40

CxSeekBar::CxSeekBar(QWidget *parent)
	: QLabel(parent)
{
	m_seekItem = new QLabel(this) ;
	m_seekItem->setStyleSheet("QLabel{background-color:yellow;}") ;
	m_seekItem->show() ;
	m_seekItem->setGeometry(0,0,SEEKW,SEEKH) ;
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
	painter.setBrush(QBrush(QColor("#007ACC"))) ;
	int w = width() ;
	int h = height() ;
	painter.drawRect( 0, 0, w, h ) ;
}

void CxSeekBar::mousePressEvent(QMouseEvent *ev)
{
	QPoint pnt = ev->pos() ;
	QRect geo = m_seekItem->geometry() ;
	int px = ev->pos().x() ;
	if( !geo.contains(pnt) ) {
		setCurrentSeek(m_totMSec*px/(width()-SEEKW),true) ;
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
	nx = qMin(width()-SEEKW,nx) ;
	QRect rc = m_originRect ;
	rc.moveLeft(nx) ;
	setCurrentSeek(nx*1.0/(width()-SEEKW)*m_totMSec,true) ;
}

void CxSeekBar::mouseReleaseEvent(QMouseEvent *event)
{
	QLabel::mouseReleaseEvent(event) ;
	m_isPressing = false ;
}

void CxSeekBar::setCurrentSeek( qint64 mSec, bool isclicked )
{
	m_curSeekSec = mSec ;
	int w = width() ;
	m_seekItem->setGeometry( (w-SEEKW)*mSec/m_totMSec, 0, SEEKW, SEEKH ) ;
	if( isclicked ) emit __seek(mSec) ;
}

void CxSeekBar::setDuration( qint64 msec )
{
	m_totMSec = msec ;
	setCurrentSeek(0) ;
}