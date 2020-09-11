#ifndef CXFULLIMAGELABEL_H
#define CXFULLIMAGELABEL_H

#include <QLabel>
#include <QTimerEvent>
#include <QTimeLine>
#include <QBasicTimer>
#include <QMovie>

class CxFullImageLabel : public QLabel
{
	Q_OBJECT

public:
	CxFullImageLabel(QWidget *parent);
	~CxFullImageLabel();
	void setImagePath(QString str) ;
	void setRenderState( bool on ) ;
	bool isGifFile(){ return m_isGifFile ; }
	void setWatermark(QString fileName) ;
	bool isShowWatermark(){ return m_showWatermark; }
	QRect watermarkRect() ;
	QRectF watermarkGeo() ;
	bool hasImage(){ return m_hasImage ; }
	QString watermarkPath(){ return m_watermarkPath ; }
	void resizeWatermark( QSizeF ratio ) ;
protected:
	void paintEvent(QPaintEvent *event) ;
	void timerEvent(QTimerEvent* event) ;
	void resizeEvent(QResizeEvent* event) ;
	void showEvent(QShowEvent* event) ;
	void mousePressEvent(QMouseEvent *ev) ;
	void mouseMoveEvent(QMouseEvent *ev) ;
	void mouseReleaseEvent(QMouseEvent *ev) ;
private:
	QString m_imgPath ;
	QBasicTimer m_timer, m_watermarkTimer ;
	QPixmap m_curPix ;
	bool m_hasImage ;
	bool m_isGifFile, m_isGifWatermark ;
	QMovie* m_movie ;
	QMovie* m_watermarkMovie ;

	bool m_isRenderingState ;
	QString m_watermarkPath ;
	QLabel* m_control ;
	qreal m_deltaX, m_deltaY ;
	QPixmap m_watermarkPix ;
	bool m_showWatermark ;
	QPoint m_pressPoint ;
	bool m_isResizing ;
	QRect m_oriControlRect ;
	QSizeF m_watermarkRatio ;
};

#endif // CXFULLIMAGELABEL_H
