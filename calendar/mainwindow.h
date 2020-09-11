#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QProcess>
#include <QMouseEvent>
#include <QProcess>

#include "ui_mainwindow.h"
#include <QTimeLine>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include "cxprogressdlg.h"


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0 );
	~MainWindow();
protected:
	void mouseMoveEvent(QMouseEvent *) ;
	void mousePressEvent(QMouseEvent *) ;
	void mouseReleaseEvent(QMouseEvent *) ;
	void showEvent(QShowEvent *event) ;
	void resizeEvent(QResizeEvent *event) ;
	void paintEvent(QPaintEvent* event) ;
	void closeEvent(QCloseEvent *event) ;
public slots:
	void onCreate() ;
	void onImage() ;
	void onAudio() ;
	void onPlay() ;
	void onMinimize() ;
	void onClose() ;
	void onProcessFinished(int,QProcess::ExitStatus) ;
	void onProcessStandardOutput() ;
	void onPlayStateChanged(QMediaPlayer::State) ;
	void onVideoDurationChanged( qint64 dur ) ;
	void onVideoPositionChanged( qint64 pos ) ;
	void onSeek( qint64 pos ) ;
	void onNextImage() ;
	void onPrevImage() ;
	void onDelete() ;
	void onWatermark() ;
	void onAddSize() ;
	void onRemoveSize() ;
	void onLWDoubleClicked( QListWidgetItem* item ) ;
private:
	void loadSetting() ;
	void saveSetting() ;
	void fitToScreen() ;
	void switchPlayState( bool on ) ;
	void setCurrentImage( int ) ;
	void startRender( int id ) ;
	void stopPlaying() ;
	void addIconSizeItem( QString path, QSizeF sz) ;
	Ui::Form_MainWindow ui ;
	QString m_audioPath, m_audioTmp ;
//	QString m_imagePath ;
	QRect m_oriRect;
	int m_curImageIndex ;
	QPoint m_oriPnt ;
	QString m_savePath ;
	QProcess* m_process ;
	bool m_isPressing ;
	QMediaPlayer* m_player ;
	QVideoWidget* m_videoWidget ;
	QStringList m_imageList ;
	qint64 m_videoDuration ;
	qreal m_audioDuration ;
	QStringList m_tmpVideoList ;
	int m_renderId ;
	CxProgressDlg* m_progressBar ;
	int imgW, imgH ;
	QListWidget* m_iconSizeLW ;
};

#endif // MAINWINDOW_H
