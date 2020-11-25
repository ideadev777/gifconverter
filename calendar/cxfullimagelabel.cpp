#include "cxfullimagelabel.h"
#include <QPainter>
#include <QFileInfo>
#include <QMouseEvent>
#define CONTROLSZ 10

CxFullImageLabel::CxFullImageLabel(QWidget *parent)
	: QLabel(parent)
{
	m_isGifFile = m_isGifWatermark = false ;
	m_movie = new QMovie ;
	m_watermarkMovie = new QMovie ;
	m_isRenderingState = false ;
	m_control = new QLabel(this) ;
	m_control->setStyleSheet("QLabel{background-color:red;}") ;
	m_control->hide() ;
	m_showWatermark = false ;
	m_isResizing = false ;
	m_deltaX = m_deltaY = 0.05 ;
	m_watermarkRatio = QSizeF(0.2,0.2) ;
	m_hasImage = false ;
}

CxFullImageLabel::~CxFullImageLabel()
{

}

void CxFullImageLabel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this) ;
	int w = width() ;
	int h = height() ;

	if( m_isRenderingState && 0 )
	{
		painter.setFont(QFont("Impact",45)) ;
		painter.drawText(0, 0, w, h, Qt::AlignCenter, "Creating MP4 File..." ) ;
		painter.setPen(QPen(Qt::yellow,3)) ;
		painter.setBrush(Qt::NoBrush) ;
		painter.drawRect(0,0,w,h) ;
		return ;
	}
	if( !m_hasImage && !m_showWatermark )
	{
		painter.setFont(QFont("Franklin Gothic Heavy",15)) ;
		painter.setPen(QPen(Qt::yellow,3)) ;
		painter.setPen(Qt::NoPen) ;
		painter.setBrush(QBrush("#f0f0f0")) ;
		painter.drawRect(0,0,w,h) ;
		painter.setPen(QPen(Qt::black,3)) ;
		painter.drawText(0, 0, w, h, Qt::AlignCenter, "ADD IMAGE" ) ;
		return ;
	}
	QPixmap pix = m_curPix.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation) ;
	painter.setPen(Qt::NoPen) ;
	painter.setBrush(Qt::gray) ;
	painter.drawRect(0,0,w,h) ;
	if( m_hasImage ) painter.drawPixmap((w-pix.width())/2,(h-pix.height())/2,pix) ;
	if( m_showWatermark )
	{
//		QSize waterSz(w*m_watermarkRatio.width(),h*m_watermarkRatio.height()) ;
		painter.drawPixmap( watermarkRect().topLeft(), m_watermarkPix ) ;
	}
	painter.setPen(QPen(Qt::yellow,3)) ;
	painter.setBrush(Qt::NoBrush) ;
	painter.drawRect(0,0,w,h) ;
	if( m_isRenderingState )
	{
		painter.setOpacity(0.5) ;
		painter.setPen(Qt::NoPen) ;
		painter.setBrush(Qt::black) ;
		painter.drawRect( 0, 0, w, h ) ;
	}
}

void CxFullImageLabel::timerEvent(QTimerEvent* event)
{
	if( m_isRenderingState ) return ;
	if( m_isGifWatermark && event->timerId() == m_watermarkTimer.timerId() )
	{
		m_watermarkPix = m_watermarkMovie->currentPixmap().scaled(watermarkRect().size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation) ;
		repaint() ;
	}
	if( event->timerId() != m_timer.timerId() ) return ;
	if( m_isGifFile ) m_curPix = m_movie->currentPixmap() ;
	repaint() ;
}

void CxFullImageLabel::setImagePath(QString str)
{
	m_imgPath = str ;
	if( !str.length() )
	{
		m_hasImage = false ;
		repaint() ;
		return ;
	}
	m_hasImage = true ;
	if( QFileInfo(str).suffix().compare("gif",Qt::CaseInsensitive) == 0 )
	{
		m_movie->stop() ;
		m_movie->setFileName(str) ;
		m_timer.start(m_movie->nextFrameDelay(),this) ;
		m_movie->start() ;
		m_isGifFile = true ;
	}
	else
	{
		m_timer.stop() ;
		m_isGifFile = false ;
		m_curPix = QPixmap(str) ;
	}
	repaint() ;
}

void CxFullImageLabel::setRenderState( bool on )
{
	m_isRenderingState = on ;
	repaint() ;
}

void CxFullImageLabel::setWatermark(QString fileName)
{
	if( !fileName.length() )
	{
		m_showWatermark = false ;
		m_control->hide() ;
		m_watermarkTimer.stop() ;
		m_movie->stop() ;
		return ;
	}
	m_watermarkPath = fileName ;
	m_isGifWatermark = (QFileInfo(fileName).suffix().compare("gif",Qt::CaseInsensitive) == 0) ;
	if( m_isGifWatermark )
	{
		m_watermarkMovie->stop() ;
		m_watermarkMovie->setFileName(fileName) ;
		m_watermarkTimer.start(m_movie->nextFrameDelay(),this) ;
		m_watermarkMovie->start() ;
	}
	m_showWatermark = true ;
	int w = width() ;
	int h = height() ;

	m_watermarkPix = QPixmap(fileName).scaled(w*m_watermarkRatio.width(),h*m_watermarkRatio.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation) ;
	m_watermarkRatio = QSizeF( 1.0*m_watermarkPix.width()/w,1.0*m_watermarkPix.height()/h ) ;
	QRect rc = watermarkRect() ;
	m_control->setGeometry(QRect(rc.topLeft()-QPoint(CONTROLSZ/2,CONTROLSZ/2),QSize(CONTROLSZ,CONTROLSZ))) ;
	m_control->show() ;
	repaint() ;
}

void CxFullImageLabel::resizeEvent(QResizeEvent* event)
{
	QLabel::resizeEvent(event) ;
}

void CxFullImageLabel::showEvent(QShowEvent* event)
{
	QLabel::showEvent(event) ;
}

void CxFullImageLabel::mousePressEvent(QMouseEvent *ev)
{
	QPoint pnt = ev->pos() ;
	if( !m_control->geometry().contains(pnt) ) return ;
	m_isResizing = true ;
	m_pressPoint = pnt ;
	m_oriControlRect = m_control->geometry() ;
}

void CxFullImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
	if( !m_isResizing ) return ;
	QPoint pnt = ev->pos() ;
	int w = width()-width()*m_deltaX-pnt.x();
	int h = height()-height()*m_deltaY-pnt.y();
	QRect rc = m_oriControlRect.translated(pnt.x()-m_pressPoint.x(),pnt.y()-m_pressPoint.y()) ;
	m_control->setGeometry(rc) ;
	m_watermarkPix = QPixmap(m_watermarkPath).scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation) ;
	m_watermarkRatio = QSizeF(1.0*w/width(),1.0*h/height()) ;
	repaint() ;
}

void CxFullImageLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	m_isResizing = false ;
}

QRect CxFullImageLabel::watermarkRect()
{
	int w(width()), h(height()) ;
	int x = w*(1-m_deltaX-m_watermarkRatio.width()) ;
	int y = h*(1-m_deltaY-m_watermarkRatio.height()) ;
	return QRect( x, y, w*m_watermarkRatio.width(), h*m_watermarkRatio.height() ) ;
}

QRectF CxFullImageLabel::watermarkGeo()
{
	QRect rc = watermarkRect() ;
	qreal w = width() ;
	qreal h = height() ;
	return QRectF(rc.topLeft().x()/w,rc.topLeft().y()/h, rc.width()/w,rc.height()/h ) ;
}

void CxFullImageLabel::resizeWatermark( QSizeF ratio )
{
	m_watermarkRatio = ratio ;
	QRect rc = watermarkRect() ;
	m_control->setGeometry(QRect(rc.topLeft()-QPoint(CONTROLSZ/2,CONTROLSZ/2),QSize(CONTROLSZ,CONTROLSZ))) ;
	if( m_isGifWatermark )
	{
		return ;
	}
	m_watermarkPix = QPixmap(m_watermarkPath).scaled(width()*ratio.width(),height()*ratio.height()) ;
	repaint() ;
}