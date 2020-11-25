#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QCloseEvent>
#include "common.h"
#include <QFileInfo>
#include <QUuid>
#include <QDir>
#include "license.h"

#define LOGOW 50
#define LOGOH 60

#define TITLEHEIGHT 45
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
//	if( !isLicensed() ) exit(1) ;
	ui.setupUi(this) ;
	QDir().mkdir("INTRO LIBARY") ;
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
	connect(ui.lbl_seek_intro, SIGNAL(__seek(qint64)), this, SLOT(onSeek(qint64))) ;
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
	connect( ui.tb_next_1, SIGNAL(clicked()), this, SLOT(onNextImage1())) ;
	connect( ui.tb_prev_1, SIGNAL(clicked()), this, SLOT(onPrevImage1())) ;
	connect( ui.tb_detail, SIGNAL(clicked()), this, SLOT(onDelete())) ;
//	connect( ui.tb_delete, SIGNAL(clicked()), this, SLOT(onDelete())) ;
	connect( ui.tb_watermark, SIGNAL(clicked()), this, SLOT(onWatermark())) ;

	connect( ui.tb_add_size, SIGNAL(clicked()), this, SLOT(onAddSize())) ;
	connect( ui.tb_del_size, SIGNAL(clicked()), this, SLOT(onRemoveSize())) ;
	
	connect( ui.tb_upload_intro, SIGNAL(clicked()), this, SLOT(onUploadIntro())) ;
	connect( ui.tb_play_intro, SIGNAL(clicked()), this, SLOT(onIntroPlay())) ;
	connect( ui.tb_library_intro, SIGNAL(clicked()), this, SLOT(onLibrary())) ;

	ui.tb_play->setEnabled(false) ;
	setFixedSize(1096,822) ;

	ui.w_video->hide() ;
	ui.w_seek->hide() ;
	ui.w_duration->hide() ;
	ui.w_control->hide() ;
//	ui.tb_delete->hide() ;

	ui.tb_next->hide() ;
	ui.tb_prev->hide() ;

	m_audioPath = m_savePath = "" ;
	m_isPressing = false ;
//	QFile styleSheet("D:/qss/3.qss");
	loadSetting() ;
	m_audioDuration = 10 ;
	if( !QDir("tmp").exists() )
	{
		QDir().mkpath("tmp") ;
	}
	m_isIntroPlay = false ;
} 

MainWindow::~MainWindow()
{

}

QString MainWindow::createSimpleUuid()
{
	QString ret = QUuid::createUuid().toString() ;
	ret.chop(1) ;
	ret = ret.right(ret.length()-1) ;
	return ret ;
}


void MainWindow::onWatermark()
{
	if( !m_imageList.count() )
	{
//		QMessageBox::information(this, "", "Please upload image first.") ;
//		return ;
	}
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Watermark File"), "", tr("Images (*.png *.gif *.jpg)"));
	if( !fileName.length() ) return ;
	QString filePath = QString("tmp/%1.%2").arg(createSimpleUuid()).arg(QFileInfo(fileName).suffix()) ;
	QFile(fileName).copy(filePath) ;
	QPixmap pix(filePath) ;
	if( pix.isNull() )
	{
		QMessageBox::information(this, "", "Invalid image format") ;
		return ;
	}
	ui.lbl_pix->setWatermark(filePath) ;
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
	setCurrentImage1(cnt-1) ;
	if( !cnt ) return ;
	setCurrentImage(cnt-1) ;
	ui.lbl_pix->setImagePath(m_imageList.at(cnt-1)) ;
}

void MainWindow::setCurrentImage1( int id )
{
	
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
	if( cnt == 1 )
	{
		ui.tb_bg_1->setIcon(QIcon(m_imageList[id])) ;
		ui.tb_bg_2->setIcon(QIcon()) ;
		ui.tb_bg_1->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg("border:3px solid red;")) ;
		ui.tb_bg_2->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg("")) ;
	}
	if( cnt > 1 )
	{
		bool last = (id==cnt-1) ;
		ui.tb_bg_1->setIcon(QIcon(m_imageList[last?id-1:id])) ;
		ui.tb_bg_2->setIcon(QIcon(m_imageList[last?id:id+1])) ;
		ui.tb_bg_1->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg(!last?"border:3px solid red;":"")) ;
		ui.tb_bg_2->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg(!last?"":"border:3px solid red;")) ;
	}
	if( cnt == 0 )
	{
		ui.tb_bg_1->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg("")) ;
		ui.tb_bg_2->setStyleSheet(QString("QToolButton{background:#c3c3c3;%1}").arg("")) ;
	}
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

	if( m_introVideo.length() )
	{
		QString res = QString("tmpgif/%1.mp4").arg(createSimpleUuid()) ;

		arg.clear() ;

//ffmpeg   out.mp4
		QString str ;
		arg << "-y" <<"-i"<<m_introVideo<<"-i"<<m_savePath<<"-filter_complex"<<"[0:v]setsar=1:1[v0];[1:v]scale=1600:900,setsar=1:1[v1];[v0][0:a][v1][1:a] concat=n=2:v=1:a=1"<<"-r" <<"29.7" << res ;
//		arg << "-i" << m_introVideo << "-i" << m_savePath <<"-f"<< "lavfi"<< "-i" <<"color=s=1600x900:r=30" <<"-filter_complex" <<"[0]scale=1600x900:force_original_aspect_ratio=decrease[vid1];[1]scale=1600x900:force_original_aspect_ratio=decrease[vid2];[2][vid1]overlay=x='(W-w)/2':y='(H-h)/2':shortest=1[vid1];[2][vid2]overlay=x='(W-w)/2':y='(H-h)/2':shortest=1[vid2];[vid1][vid2]concat=n=2:v=1:a=0,setsar=1" << res ;
		foreach(QString tmp,arg) str.append(tmp), str.append(" ") ;
//		QMessageBox::information(NULL,"",str) ;
//		QProcess::execute("ffmpeg",arg) ;
		m_progressBar->startProgress(arg,m_audioDuration*2,QString("Adding Intro Video...")) ;// Hard coded
		QFile(m_savePath).remove() ;
		QFile(res).rename(m_savePath) ;
	}

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

void MainWindow::onIntroPlay()
{
	m_isIntroPlay = true ;
	if( ui.tb_play_intro->isChecked() )
	{
		m_videoDuration = 0 ;
		ui.tb_play_intro->setText("STOP") ;
		m_player->setMedia(QUrl::fromLocalFile(m_introVideo)) ;
		int w = ui.w_container->height() ;
		switchPlayState(true) ;
		m_player->setVideoOutput(m_videoWidget);
		m_videoWidget->setGeometry(0,0,ui.w_video->width(),ui.w_video->height()) ;
		m_player->play() ;
	}
	else
	{
		switchPlayState(false) ;
		ui.tb_play_intro->setText("PLAY") ;
		m_player->stop() ;
	}
}

void MainWindow::onUploadIntro()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Intro File"), "", tr("Mp4 files (*.mp4)"));
	if( !fileName.length() ) return ;
	ui.tb_play_intro->setEnabled(true) ;
	m_introVideo = fileName ;
}

void MainWindow::onLibrary()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Intro File"), "INTRO LIBARY" , tr("Mp4 files (*.mp4)"));
	if( !fileName.length() ) return ;
	ui.tb_play_intro->setEnabled(true) ;
	m_introVideo = fileName ;
}

void MainWindow::onPlay()
{
	m_isIntroPlay = false ;
	if( ui.tb_play->isChecked() )
	{
		m_videoDuration = 0 ;
		ui.tb_play->setText("STOP") ;
		m_player->setMedia(QUrl::fromLocalFile(m_savePath)) ;
		int w = ui.w_container->height() ;
		switchPlayState(true) ;
		m_player->setVideoOutput(m_videoWidget);
		m_videoWidget->setGeometry(0,0,ui.w_video->width(),ui.w_video->height()) ;
//		ui.lbl_seek->hide() ;
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
//	ui.w_seek->setVisible(on) ;
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
	ui.lbl_seek_intro->setDuration(dur) ;
	m_videoDuration = dur ;
	ui.lbl_curtime->setText(QString(" %1 / %2 ").arg(getTime(0).toString("mm:ss")).arg(getTime(dur).toString("mm:ss"))) ;
}

void MainWindow::onVideoPositionChanged( qint64 pos )
{
	ui.lbl_seek_intro->setCurrentSeek(pos) ;
	ui.lbl_seek->setCurrentSeek(pos) ;
	ui.lbl_curtime->setText(QString(" %1 / %2 ").arg(getTime(pos).toString("mm:ss")).arg(getTime(m_videoDuration).toString("mm:ss"))) ;
}

void MainWindow::onSeek( qint64 pos )
{
	m_player->setPosition(pos) ;
}

void MainWindow::onNextImage1()
{
	onNextImage() ;
}

void MainWindow::onPrevImage1()
{
	onPrevImage() ;
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
	if( ui.tb_play_intro->isChecked() ) ui.tb_play_intro->click() ;
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
//		QMessageBox::information(this,"","Please upload image first.") ;
//		return ;
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
//	if (styleSheet.open(QIODevice::ReadOnly)) setStyleSheet(styleSheet.readAll());

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