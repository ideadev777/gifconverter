#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QCloseEvent>
#include "common.h"

#define LOGOW 50
#define LOGOH 60

#define TITLEHEIGHT 45
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this) ;
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint );
//	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

	m_iconSizeLW = ui.listWidget ;
	m_iconSizeLW->setViewMode(QListView::IconMode) ;
	m_iconSizeLW->setLayoutDirection(Qt::LeftToRight) ;
	m_iconSizeLW->setSpacing(2) ;
	m_iconSizeLW->setIconSize(QSize(LOGOW,LOGOH)) ;
	m_iconSizeLW->setFlow(QListView::LeftToRight) ;
	m_iconSizeLW->setDragDropMode(QAbstractItemView::NoDragDrop) ;
	m_iconSizeLW->setWrapping(false);

	imgW = 1600 ; imgH = 900 ;
	m_process = new QProcess(this) ;
	m_process->setProcessChannelMode(QProcess::MergedChannels);
	m_player = new QMediaPlayer;
	m_videoWidget = new QVideoWidget(ui.w_video);
	m_progressBar = new CxProgressDlg(this) ;

	connect( m_iconSizeLW, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onLWDoubleClicked(QListWidgetItem*))) ;

	connect( m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayStateChanged(QMediaPlayer::State))) ;
	connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(onVideoDurationChanged(qint64)));
	connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(onVideoPositionChanged(qint64)));

	connect(ui.lbl_seek, SIGNAL(__seek(qint64)), this, SLOT(onSeek(qint64))) ;
	connect( m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onProcessFinished(int,QProcess::ExitStatus))) ;
	connect (m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessStandardOutput()));
	connect( ui.tb_create, SIGNAL(clicked()), this, SLOT(onCreate())) ;
	connect( ui.tb_play, SIGNAL(clicked()), this, SLOT(onPlay())) ;
	connect( ui.tb_image, SIGNAL(clicked()), this, SLOT(onImage())) ;
	connect( ui.tb_audio, SIGNAL(clicked()), this, SLOT(onAudio())) ;
	connect( ui.tb_minimize, SIGNAL(clicked()), this, SLOT(onMinimize())) ;
	connect( ui.tb_close, SIGNAL(clicked()), this, SLOT(onClose())) ;

	connect( ui.tb_next, SIGNAL(clicked()), this, SLOT(onNextImage())) ;
	connect( ui.tb_prev, SIGNAL(clicked()), this, SLOT(onPrevImage())) ;
	connect( ui.tb_delete, SIGNAL(clicked()), this, SLOT(onDelete())) ;
	connect( ui.tb_watermark, SIGNAL(clicked()), this, SLOT(onWatermark())) ;

	connect( ui.tb_add_size, SIGNAL(clicked()), this, SLOT(onAddSize())) ;
	connect( ui.tb_del_size, SIGNAL(clicked()), this, SLOT(onRemoveSize())) ;
	ui.tb_play->setEnabled(false) ;
	setFixedSize(1030,677) ;

	ui.w_video->hide() ;
	ui.w_seek->hide() ;
	ui.w_duration->hide() ;
	ui.w_control->hide() ;
	ui.tb_delete->hide() ;


	m_audioPath = m_savePath = "" ;
	m_isPressing = false ;
//	QFile styleSheet("D:/qss/3.qss");
	loadSetting() ;
	m_audioDuration = 10 ;
} 

MainWindow::~MainWindow()
{

}

void MainWindow::onWatermark()
{
	if( !m_imageList.count() )
	{
		QMessageBox::information(this, "", "Please upload image first.") ;
		return ;
	}
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Watermark File"), "", tr("Images (*.png *.gif *.jpg)"));
	if( !fileName.length() ) return ;
	QPixmap pix(fileName) ;
	if( pix.isNull() )
	{
		QMessageBox::information(this, "", "Invalid image format") ;
		return ;
	}
	ui.lbl_pix->setWatermark(fileName) ;
}

void MainWindow::onAudio()
{
	stopPlaying() ;

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Audio File"),"",	tr("Audios (*.wav *.mp3)"));
	if( fileName.length() == 0 )    return ;
	m_audioTmp = fileName ;
	QApplication::setOverrideCursor(Qt::WaitCursor) ;
	QStringList arg ;
	arg << "-i" << fileName ;
	m_process->start("ffmpeg",arg ) ;
}

void MainWindow::onImage()
{
	stopPlaying() ;

	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Image File"), "", tr("Images (*.png *.gif *.jpg)"));
	if( fileNames.count() == 0 )    return ;
	foreach( QString fileName, fileNames )
	{
		QPixmap pix(fileName) ;
		if( pix.isNull() ) continue ;
		m_imageList << fileName ;
	}
	int cnt = m_imageList.count() ;
	if( !cnt ) return ;
	setCurrentImage(cnt-1) ;
	ui.lbl_pix->setImagePath(m_imageList.at(cnt-1)) ;
}

void MainWindow::setCurrentImage( int id )
{
	int cnt = m_imageList.count() ;
	ui.w_control->setVisible(cnt) ;
//	ui.tb_delete->setVisible(cnt>1) ;
	if( id >= cnt || id < 0 ) return ;
	m_curImageIndex = id ;
	ui.lbl_pix->setImagePath(m_imageList.at(id)) ;
	ui.lbl_index->setText(QString("%1 / %2").arg(id+1).arg(cnt)) ;
}

void MainWindow::onCreate()
{
	stopPlaying() ;
	if( !m_audioPath.length() )
	{
		QMessageBox::information(this, "Error", "Audio File is not selected.") ;
		return ;
	}
	if( !m_imageList.count() )
	{
		QMessageBox::information(this, "Error", "Image File is not selected.") ;
		return ;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Mp4 files (*.mp4)"));
	if( fileName.length() == 0 ) return ;
	m_tmpVideoList.clear() ;
	m_savePath = fileName ;


	QApplication::setOverrideCursor(Qt::WaitCursor) ;
	ui.lbl_pix->setRenderState(true) ;
	int cnt = m_imageList.count() ;
	QStringList arg ;
	arg << "-y" ;
	QString filter ;
	for( int i = 0; i < cnt; i++ )
	{
		startRender(i) ;
		filter.append(QString("[%1:v:0] ").arg(i)) ;
		arg <<"-i"<< m_tmpVideoList.at(i) ;
	}
	filter.append(QString("concat=n=%1:v=1:a=0 [v]").arg(cnt)) ;
	QString map1("[v]") ;
	QString lastsavePath = m_savePath ;
	if( ui.lbl_pix->isShowWatermark() )
	{
		lastsavePath = QString("tmpgif/%1.mp4").arg(createSimpleUuid()) ;
	}
	arg << "-i" << m_audioPath << "-filter_complex" << filter <<"-map" << map1 << "-map" <<QString("%1:a").arg(cnt) <<"-c:v" <<"libx264" << "-shortest" <<"-acodec" <<"copy" <<"-r" <<"29.7" << "-y" << lastsavePath ;

	m_progressBar->startProgress(arg,m_audioDuration,QString("Finalizing ...")) ;
	if( ui.lbl_pix->isShowWatermark() )
	{
		QString iconPath = ui.lbl_pix->watermarkPath() ;
		bool isGif = (QFileInfo(iconPath).suffix().compare("gif",Qt::CaseInsensitive) == 0) ;
		//ffmpeg -i 1.mp4 -i 2.png -filter_complex "overlay=10:10" watermarked.mp4
		arg.clear() ;
		QRectF rc = ui.lbl_pix->watermarkGeo() ;
		int iconW = imgW*rc.width() ;
		int iconH = imgH*rc.height() ;
		QString imgUuid = QString("tmpgif/%1.%2").arg(createSimpleUuid()).arg(isGif?"gif":"png") ;
		if( isGif )
		{
			QStringList str ;
			QString iconFilter = QString("[0:v] scale=%1:%2:flags=lanczos,split [a][b]; [a] palettegen=reserve_transparent=on:transparency_color=ffffff [p]; [b][p] paletteuse").arg(iconW).arg(iconH) ;
			str << "-hide_banner" <<"-v"<<"warning"<<"-i"<< iconPath <<"-filter_complex"<<iconFilter<<imgUuid ;
//			QProcess::execute("ffmpeg",str) ;
			m_progressBar->startProgress(str,-1,"Resizing Watermark...") ;
//  -v warning -i 1.gif -filter_complex
//"[0:v] scale=320:-1:flags=lanczos,split [a][b]; [a] palettegen=reserve_transparent=on:transparency_color=ffffff [p]; [b][p] paletteuse" logo-320.gif
		}
		else
		{
			QPixmap pix = QPixmap(iconPath).scaled(iconW,iconH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation) ;
			pix.save(imgUuid) ;
		}
//ffmpeg -i 1.mp4 -ignore_loop 0 -i 1.gif -filter_complex "overlay=10:10" -shortest -y watermarked.mp4
		QString overlay = QString("overlay=%1:%2").arg(imgW*rc.topLeft().x()).arg(imgH*rc.topLeft().y()) ;
		arg << "-i" << lastsavePath ;
		if( isGif ) arg << "-ignore_loop" <<"0" <<"-t"<< QString("%1").arg(m_audioDuration/1000.0) ; 
		arg << "-i" << imgUuid << "-filter_complex" << overlay << "-y" << m_savePath ;

		QString tmp ;
		foreach(QString str, arg) tmp.append(str), tmp.append(" ") ;
		m_progressBar->startProgress(arg,m_audioDuration,QString("Drawing Watermark ...")) ;
		QFile::remove(lastsavePath) ;
		QFile::remove(imgUuid) ;
	}
	for( int i = 0; i < cnt; i++ ) QFile::remove(m_tmpVideoList[i]) ;

	QApplication::restoreOverrideCursor() ;
	ui.tb_play->setEnabled(true) ;
	QMessageBox::information(this,"","Finished") ;
	ui.lbl_pix->setRenderState(false) ;

	/*
	//-y -i 1.mp4 -i 2.mp4 -i 3.mp4 -i audio.wav -filter_complex "[0:v:0] [1:v:0] [2:v:0] concat=n=3:v=1:a=0 [v]" -map "[v]" -map 3:a -c:v libx264 -shortest -acodec copy -r 29.7 output.mp4
	return ;
	*/
}

void MainWindow::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	QString str = m_process->readAllStandardOutput();
	if( str.length() )
	{
		QString token = "Duration: " ;
		int pos ;
		if( str.contains(token) && str.contains("kb/s") )
		{
			pos = str.indexOf(token) ;
			QTime tt = QTime::fromString(str.mid(pos+token.length(),11),"hh:mm:ss.z") ;
			int dur = getMSec(tt) ;
			if( dur < 0 ) return ;
			m_audioDuration = dur ;
			m_audioPath = m_audioTmp ;
			ui.lbl_audio_path->setText(m_audioPath) ;
		}
	}
	QApplication::restoreOverrideCursor() ;
}

void MainWindow::startRender( int id )
{
	m_renderId = id ;
	int cnt = m_imageList.count() ;
	if( id >= cnt ) return ;

	//ffmpeg -loop 1 -i 1.png -c:v libx264 -t 15 -pix_fmt yuv420p -vf scale=320:240 out.mp4
	QStringList arg ;
	qreal dur = m_audioDuration/(1000.0*m_imageList.count()) ;
	QString newvideouuid = QString("tmpgif/%1.mp4").arg(createSimpleUuid()) ;
	m_tmpVideoList<<newvideouuid ;
	

	QString scale = "scale=trunc(iw/2)*2:trunc(ih/2)*2" ;
//	scale = "scale=1280:720:force_original_aspect_ratio=decrease,pad=1280:720:(ow-iw)/2:(oh-ih)/2" ;
	scale = QString("scale=%1:%2:force_original_aspect_ratio=decrease,pad=%3:%4:(ow-iw)/2:(oh-ih)/2").arg(imgW).arg(imgH).arg(imgW).arg(imgH) ;
	if( QFileInfo(m_imageList[id]).suffix().compare("gif",Qt::CaseInsensitive) == 0 )
	{
		arg <<"-stream_loop" <<"-1" <<"-i" <<m_imageList[id]<< "-t" <<QString("%1").arg(dur)<< "-codec:v" 
			<<"libx264" <<"-preset"<< "slow"<< "-tune" <<"animation" <<"-vf" <<
			scale<< "-pix_fmt" <<"yuv420p" <<"-shortest" <<newvideouuid ;
	}
	else
	{
		arg << "-loop" <<"1"<<"-i"<<m_imageList[id]<<"-c:v"<<"libx264"<<"-t"<<QString("%1").arg(dur) <<"-vf" << scale <<"-pix_fmt" <<"yuv420p"<<newvideouuid ;
	}
	m_progressBar->startProgress(arg,dur*1000,QString("Rendering Image %1 ...").arg(id+1)) ;
}

void MainWindow::onPlay()
{
	if( ui.tb_play->isChecked() )
	{
		m_videoDuration = 0 ;
		ui.tb_play->setText("STOP") ;
//		m_player->setMedia(QUrl::fromLocalFile("D://1.wmv")) ;
		m_player->setMedia(QUrl::fromLocalFile(m_savePath)) ;
		int w = ui.w_container->height() ;
		switchPlayState(true) ;
		m_player->setVideoOutput(m_videoWidget);
		m_videoWidget->setGeometry(0,0,ui.w_video->width(),ui.w_video->height()) ;
//		m_videoWidget->setGeometry(0,0,ui.w_video->width(),400) ;
		m_player->play() ;
	}
	else
	{
		switchPlayState(false) ;
		ui.tb_play->setText("PLAY") ;
		m_player->stop() ;
	}
}

void MainWindow::switchPlayState( bool on )
{
	int w = ui.w_container->height() ;
	ui.lbl_pix->setVisible(!on) ;
	ui.w_audio->setVisible(!on) ;
	ui.w_duration->setVisible(on) ;
	ui.w_seek->setVisible(on) ;
//	ui.w_progress->setVisible(false) ;
	ui.w_video->setVisible(on) ;
	m_videoWidget->setVisible(on) ;
//	QMessageBox::information(NULL,"",QString::number(ui.w_container->height()-w)) ;
}

void MainWindow::onPlayStateChanged(QMediaPlayer::State state)
{
	if( state == QMediaPlayer::StoppedState )
	{
		stopPlaying() ;
	}
}
void MainWindow::onClose()
{
	close() ;
}

void MainWindow::onMinimize()
{
	showMinimized() ;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	m_oriRect = geometry() ;
	m_oriPnt = event->globalPos() ;
	if( event->pos().y() < 0 || event->pos().y() > TITLEHEIGHT ) return ;
	m_isPressing = true ;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if( !m_isPressing ) return ;
	QPoint tmp = event->globalPos()-m_oriPnt ;
	QRect geo = m_oriRect.translated(tmp.x(),tmp.y()) ;
	setGeometry(geo);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressing = false ;
}


void MainWindow::onProcessStandardOutput()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event) ;
	fitToScreen() ;
}

void MainWindow::showEvent(QShowEvent *event)
{
	QWidget::showEvent(event) ;
	fitToScreen() ;
}

void MainWindow::fitToScreen()
{
//	QRect rc(ui.lbl_pix->mapTo(this,QPoint(0,0)), ui.lbl_pix->size()) ;
//	m_videoWidget->setGeometry(rc) ;
}

void MainWindow::onVideoDurationChanged( qint64 dur )
{
	ui.lbl_seek->setDuration(dur) ;
	m_videoDuration = dur ;
	ui.lbl_curtime->setText(QString(" %1 / %2 ").arg(getTime(0).toString("mm:ss")).arg(getTime(dur).toString("mm:ss"))) ;
}

void MainWindow::onVideoPositionChanged( qint64 pos )
{
	ui.lbl_seek->setCurrentSeek(pos) ;
	ui.lbl_curtime->setText(QString(" %1 / %2 ").arg(getTime(pos).toString("mm:ss")).arg(getTime(m_videoDuration).toString("mm:ss"))) ;
}

void MainWindow::onSeek( qint64 pos )
{
	m_player->setPosition(pos) ;
}

void MainWindow::onNextImage()
{
	setCurrentImage(m_curImageIndex+1) ;
}

void MainWindow::onPrevImage()
{
	setCurrentImage(m_curImageIndex-1) ;
}

void MainWindow::onDelete()
{
	int cnt = m_imageList.count() ;
	if( !cnt ) return ;
	if( cnt == 1 )
	{
		return ;
	}
	if( m_curImageIndex == cnt-1 ) 
	{
		m_imageList.takeAt(cnt-1) ;
		setCurrentImage(cnt-2) ;
	}
	else
	{
		m_imageList.takeAt(m_curImageIndex) ;
		setCurrentImage(m_curImageIndex) ;
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this) ;
	int w = width() ;
	int h = height() ;
	int delta = 2 ;
	painter.setPen(Qt::NoPen) ;
	painter.setBrush(QBrush("#DC4E41")) ;
	painter.drawRect( 0, 0, w,h ) ;

	painter.setBrush(QBrush(QColor("#FFFFFF"))) ;
	painter.drawRect( delta,delta,w-2*delta,h-2*delta ) ;
}

void MainWindow::stopPlaying()
{
	if( ui.tb_play->isChecked() ) ui.tb_play->click() ;
}

void MainWindow::onAddSize()
{
	if( !ui.lbl_pix->isShowWatermark() )
	{
		QMessageBox::information(this,"","Icon does not exist.") ;
		return ;
	}
	addIconSizeItem(ui.lbl_pix->watermarkPath(),ui.lbl_pix->watermarkGeo().size()) ;
}

void MainWindow::addIconSizeItem(QString path, QSizeF sz)
{
//	QString path = ui.lbl_pix->watermarkPath() ;
	QSize wsz = QSize(sz.width()*imgW, sz.height()*imgH ) ;
	QListWidgetItem* item = new QListWidgetItem ;
//	QListWidgetItem* item = new QListWidgetItem(QString("%1%2x%3%4").arg(wsz.width()).arg('\n').arg('\n').arg(wsz.height())) ;
	item->setSizeHint(QSize(LOGOW,LOGOH)) ;
	item->setData(Qt::EditRole+1,sz) ;
	item->setData(Qt::EditRole+2,path) ;
	item->setIcon(QIcon(QPixmap(path))) ;
	item->setFont(QFont("arial",9)) ;
	item->setBackground(QBrush(QColor("#FEDA00"))) ;
	item->setTextAlignment(Qt::AlignCenter) ;
	m_iconSizeLW->addItem(item) ;
}

void MainWindow::onRemoveSize()
{
	int cur = m_iconSizeLW->currentRow() ;
	m_iconSizeLW->takeItem(cur) ;
}

void MainWindow::onLWDoubleClicked( QListWidgetItem* item )
{
	if( !ui.lbl_pix->hasImage() )
	{
		QMessageBox::information(this,"","Please upload image first.") ;
		return ;
	}
	QSizeF ratio = item->data(Qt::EditRole+1).toSizeF() ;
	QString path = item->data(Qt::EditRole+2).toString() ;
	if( !QFile(path).exists() )
	{
		QMessageBox::information(this,"","Image does noe exist.") ;
		return ;
	}
	ui.lbl_pix->setWatermark(path) ;
	ui.lbl_pix->resizeWatermark(ratio) ;
}

void MainWindow::loadSetting()
{
	QFile styleSheet(":/res/qss/3.qss");
	if (styleSheet.open(QIODevice::ReadOnly)) setStyleSheet(styleSheet.readAll());

	QFile file("iconinfo.dat") ;
	QDataStream in(&file) ;
	if( file.open(QIODevice::ReadOnly))
	{
		QSizeF sz ;
		QString path ;
		while( !in.atEnd() )
		{
			in >> sz ;
			in >> path ;
			addIconSizeItem(path,sz) ;
		}
	}
	file.close() ;
}

void MainWindow::saveSetting()
{
//	return ;
	QFile file("iconinfo.dat") ;
	QDataStream out(&file) ;
	if( file.open(QIODevice::WriteOnly) )
	{
		for( int i = 0; i < m_iconSizeLW->count(); i++ )
		{
			out << m_iconSizeLW->item(i)->data(Qt::EditRole+1).toSizeF() ;
			out << m_iconSizeLW->item(i)->data(Qt::EditRole+2).toString() ;
		}
		file.close() ;
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	saveSetting() ;
	event->accept() ;
}