#ifndef CXSEEKBAR_H
#define CXSEEKBAR_H

#include <QLabel>
#include "common.h"

class CxSeekBar : public QLabel
{
	Q_OBJECT

public:
	CxSeekBar(QWidget *parent);
	~CxSeekBar();
	void setDuration( qint64 msec ) ;
	void setCurrentSeek( qint64 mSec, bool isclicked = false ) ;
signals:
	void __seek( qint64 ) ;
protected:
	void paintEvent(QPaintEvent *event) ;
	void mousePressEvent(QMouseEvent *ev) ;
	void mouseMoveEvent(QMouseEvent* ev) ;
	void mouseReleaseEvent(QMouseEvent *ev) ;
private:
	QLabel* m_seekItem ;
	qint64 m_totMSec ;
	qint64 m_curSeekSec; 
	bool m_isPressing ;
	int m_mousePressPos ;
	QRect m_originRect ;
};

#endif // CXSEEKBAR_H
