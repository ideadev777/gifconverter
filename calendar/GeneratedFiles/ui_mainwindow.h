/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "cxfullimagelabel.h"
#include "cxseekbar.h"

QT_BEGIN_NAMESPACE

class Ui_Form_MainWindow
{
public:
    QGridLayout *gridLayout_5;
    QWidget *w_title;
    QGridLayout *gridLayout_7;
    QToolButton *tb_minimize;
    QLabel *lbl_title;
    QLabel *label_4;
    QToolButton *tb_close;
    QWidget *widget;
    QGridLayout *gridLayout;
    QWidget *w_main;
    QGridLayout *gridLayout_2;
    QWidget *w_container;
    QGridLayout *gridLayout_8;
    CxFullImageLabel *lbl_pix;
    QWidget *w_video;
    QWidget *w_seek;
    QGridLayout *gridLayout_9;
    CxSeekBar *lbl_seek;
    QWidget *w_audio;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLabel *lbl_audio_path;
    QWidget *w_duration;
    QGridLayout *gridLayout_11;
    QLabel *lbl_curtime;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_5;
    QGridLayout *gridLayout_16;
    CxSeekBar *lbl_seek_intro;
    QWidget *w_button;
    QGridLayout *gridLayout_6;
    QWidget *w_control;
    QGridLayout *gridLayout_10;
    QLabel *lbl_index;
    QToolButton *tb_prev;
    QToolButton *tb_next;
    QFrame *line_2;
    QToolButton *tb_play;
    QToolButton *tb_watermark;
    QToolButton *tb_create;
    QSpacerItem *verticalSpacer;
    QToolButton *tb_audio;
    QToolButton *tb_image;
    QFrame *line;
    QWidget *w_watermark;
    QGridLayout *gridLayout_3;
    QListWidget *listWidget;
    QWidget *widget_3;
    QGridLayout *gridLayout_12;
    QToolButton *tb_add_size;
    QToolButton *tb_del_size;
    QLabel *label;
    QWidget *widget_2;
    QGridLayout *gridLayout_13;
    QToolButton *tb_next_1;
    QToolButton *tb_prev_1;
    QToolButton *tb_bg_2;
    QToolButton *tb_bg_1;
    QToolButton *tb_detail;
    QWidget *widget_6;
    QGridLayout *gridLayout_14;
    QLabel *label_3;
    QToolButton *tb_upload_intro;
    QWidget *widget_7;
    QGridLayout *gridLayout_15;
    QToolButton *tb_library_intro;
    QToolButton *tb_play_intro;
    QWidget *widget_4;
    QGridLayout *gridLayout_17;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *Form_MainWindow)
    {
        if (Form_MainWindow->objectName().isEmpty())
            Form_MainWindow->setObjectName(QStringLiteral("Form_MainWindow"));
        Form_MainWindow->resize(1096, 822);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Form_MainWindow->setWindowIcon(icon);
        Form_MainWindow->setStyleSheet(QStringLiteral("background-color:#c7c7c7;"));
        gridLayout_5 = new QGridLayout(Form_MainWindow);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(4, 4, 4, 4);
        w_title = new QWidget(Form_MainWindow);
        w_title->setObjectName(QStringLiteral("w_title"));
        w_title->setMinimumSize(QSize(0, 45));
        w_title->setMaximumSize(QSize(16777215, 45));
        w_title->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"background-color:#00ACEB;\n"
"color:black;\n"
"}"));
        gridLayout_7 = new QGridLayout(w_title);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(5);
        gridLayout_7->setVerticalSpacing(0);
        gridLayout_7->setContentsMargins(5, 0, 8, 0);
        tb_minimize = new QToolButton(w_title);
        tb_minimize->setObjectName(QStringLiteral("tb_minimize"));
        tb_minimize->setMinimumSize(QSize(30, 30));
        tb_minimize->setMaximumSize(QSize(30, 30));
        QFont font;
        font.setPointSize(11);
        tb_minimize->setFont(font);

        gridLayout_7->addWidget(tb_minimize, 0, 2, 1, 1);

        lbl_title = new QLabel(w_title);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        QFont font1;
        font1.setFamily(QStringLiteral("Impact"));
        font1.setPointSize(20);
        lbl_title->setFont(font1);

        gridLayout_7->addWidget(lbl_title, 0, 1, 1, 1);

        label_4 = new QLabel(w_title);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(40, 40));
        label_4->setMaximumSize(QSize(40, 40));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/res/icon/Play-icon.png")));
        label_4->setScaledContents(true);

        gridLayout_7->addWidget(label_4, 0, 0, 1, 1);

        tb_close = new QToolButton(w_title);
        tb_close->setObjectName(QStringLiteral("tb_close"));
        tb_close->setMinimumSize(QSize(30, 30));
        tb_close->setMaximumSize(QSize(30, 30));
        tb_close->setFont(font);

        gridLayout_7->addWidget(tb_close, 0, 3, 1, 1);


        gridLayout_5->addWidget(w_title, 0, 1, 1, 1);

        widget = new QWidget(Form_MainWindow);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        w_main = new QWidget(widget);
        w_main->setObjectName(QStringLiteral("w_main"));
        gridLayout_2 = new QGridLayout(w_main);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(13);
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        w_container = new QWidget(w_main);
        w_container->setObjectName(QStringLiteral("w_container"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(w_container->sizePolicy().hasHeightForWidth());
        w_container->setSizePolicy(sizePolicy);
        w_container->setMinimumSize(QSize(800, 450));
        w_container->setMaximumSize(QSize(800, 450));
        gridLayout_8 = new QGridLayout(w_container);
        gridLayout_8->setSpacing(0);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        lbl_pix = new CxFullImageLabel(w_container);
        lbl_pix->setObjectName(QStringLiteral("lbl_pix"));
        sizePolicy.setHeightForWidth(lbl_pix->sizePolicy().hasHeightForWidth());
        lbl_pix->setSizePolicy(sizePolicy);
        lbl_pix->setScaledContents(false);

        gridLayout_8->addWidget(lbl_pix, 1, 0, 1, 1);

        w_video = new QWidget(w_container);
        w_video->setObjectName(QStringLiteral("w_video"));
        sizePolicy.setHeightForWidth(w_video->sizePolicy().hasHeightForWidth());
        w_video->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(w_video, 0, 0, 1, 1);


        gridLayout_2->addWidget(w_container, 1, 0, 1, 1);

        w_seek = new QWidget(w_main);
        w_seek->setObjectName(QStringLiteral("w_seek"));
        w_seek->setMinimumSize(QSize(0, 40));
        w_seek->setMaximumSize(QSize(16777215, 40));
        gridLayout_9 = new QGridLayout(w_seek);
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        lbl_seek = new CxSeekBar(w_seek);
        lbl_seek->setObjectName(QStringLiteral("lbl_seek"));
        lbl_seek->setMinimumSize(QSize(0, 40));
        lbl_seek->setMaximumSize(QSize(16777215, 40));

        gridLayout_9->addWidget(lbl_seek, 0, 0, 1, 1);


        gridLayout_2->addWidget(w_seek, 5, 0, 1, 1);

        w_audio = new QWidget(w_main);
        w_audio->setObjectName(QStringLiteral("w_audio"));
        w_audio->setMinimumSize(QSize(0, 45));
        w_audio->setMaximumSize(QSize(1111111, 45));
        w_audio->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"border:1px solid black;\n"
"}"));
        gridLayout_4 = new QGridLayout(w_audio);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(1, 1, 1, 1);
        label_2 = new QLabel(w_audio);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setFamily(QStringLiteral("Franklin Gothic Heavy"));
        font2.setPointSize(16);
        label_2->setFont(font2);
        label_2->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border:none;\n"
"}"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        lbl_audio_path = new QLabel(w_audio);
        lbl_audio_path->setObjectName(QStringLiteral("lbl_audio_path"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbl_audio_path->sizePolicy().hasHeightForWidth());
        lbl_audio_path->setSizePolicy(sizePolicy1);
        lbl_audio_path->setFont(font2);
        lbl_audio_path->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border:none;\n"
"}"));
        lbl_audio_path->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lbl_audio_path, 0, 1, 1, 1);


        gridLayout_2->addWidget(w_audio, 3, 0, 1, 1);

        w_duration = new QWidget(w_main);
        w_duration->setObjectName(QStringLiteral("w_duration"));
        w_duration->setMinimumSize(QSize(0, 40));
        w_duration->setMaximumSize(QSize(16777215, 40));
        gridLayout_11 = new QGridLayout(w_duration);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setHorizontalSpacing(10);
        gridLayout_11->setVerticalSpacing(0);
        gridLayout_11->setContentsMargins(10, 0, 0, 0);
        lbl_curtime = new QLabel(w_duration);
        lbl_curtime->setObjectName(QStringLiteral("lbl_curtime"));
        lbl_curtime->setMinimumSize(QSize(0, 40));
        lbl_curtime->setMaximumSize(QSize(16777215, 40));
        QFont font3;
        font3.setFamily(QStringLiteral("Impact"));
        font3.setPointSize(14);
        lbl_curtime->setFont(font3);

        gridLayout_11->addWidget(lbl_curtime, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout_2->addWidget(w_duration, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 6, 0, 1, 1);

        widget_5 = new QWidget(w_main);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMinimumSize(QSize(0, 120));
        widget_5->setMaximumSize(QSize(16777215, 120));
        gridLayout_16 = new QGridLayout(widget_5);
        gridLayout_16->setSpacing(0);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout_16->setContentsMargins(0, 15, 0, 0);
        lbl_seek_intro = new CxSeekBar(widget_5);
        lbl_seek_intro->setObjectName(QStringLiteral("lbl_seek_intro"));
        lbl_seek_intro->setMinimumSize(QSize(0, 50));
        lbl_seek_intro->setMaximumSize(QSize(16777215, 50));

        gridLayout_16->addWidget(lbl_seek_intro, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget_5, 0, 0, 1, 1);


        gridLayout->addWidget(w_main, 0, 2, 1, 1);

        w_button = new QWidget(widget);
        w_button->setObjectName(QStringLiteral("w_button"));
        w_button->setMinimumSize(QSize(200, 0));
        w_button->setMaximumSize(QSize(200, 16777215));
        gridLayout_6 = new QGridLayout(w_button);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(0);
        gridLayout_6->setVerticalSpacing(10);
        gridLayout_6->setContentsMargins(5, 5, 5, 0);
        w_control = new QWidget(w_button);
        w_control->setObjectName(QStringLiteral("w_control"));
        w_control->setMinimumSize(QSize(0, 60));
        w_control->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"background-color:transparent;\n"
"}"));
        gridLayout_10 = new QGridLayout(w_control);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        lbl_index = new QLabel(w_control);
        lbl_index->setObjectName(QStringLiteral("lbl_index"));
        lbl_index->setMinimumSize(QSize(0, 40));
        lbl_index->setMaximumSize(QSize(16777215, 40));
        QFont font4;
        font4.setFamily(QStringLiteral("Impact"));
        font4.setPointSize(16);
        lbl_index->setFont(font4);
        lbl_index->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(lbl_index, 0, 1, 1, 1);

        tb_prev = new QToolButton(w_control);
        tb_prev->setObjectName(QStringLiteral("tb_prev"));
        tb_prev->setMinimumSize(QSize(40, 40));
        tb_prev->setMaximumSize(QSize(40, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/icon/arrow-left-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_prev->setIcon(icon1);
        tb_prev->setIconSize(QSize(30, 30));

        gridLayout_10->addWidget(tb_prev, 0, 0, 1, 1);

        tb_next = new QToolButton(w_control);
        tb_next->setObjectName(QStringLiteral("tb_next"));
        tb_next->setMinimumSize(QSize(40, 40));
        tb_next->setMaximumSize(QSize(40, 40));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/icon/arrow-right-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_next->setIcon(icon2);
        tb_next->setIconSize(QSize(30, 30));

        gridLayout_10->addWidget(tb_next, 0, 2, 1, 1);


        gridLayout_6->addWidget(w_control, 13, 0, 1, 1);

        line_2 = new QFrame(w_button);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_2, 6, 0, 1, 1);

        tb_play = new QToolButton(w_button);
        tb_play->setObjectName(QStringLiteral("tb_play"));
        tb_play->setMinimumSize(QSize(190, 50));
        tb_play->setMaximumSize(QSize(190, 16777215));
        tb_play->setFont(font3);
        tb_play->setCheckable(true);
        tb_play->setChecked(false);

        gridLayout_6->addWidget(tb_play, 11, 0, 1, 1);

        tb_watermark = new QToolButton(w_button);
        tb_watermark->setObjectName(QStringLiteral("tb_watermark"));
        tb_watermark->setMinimumSize(QSize(190, 50));
        tb_watermark->setMaximumSize(QSize(190, 16777215));
        tb_watermark->setFont(font3);

        gridLayout_6->addWidget(tb_watermark, 7, 0, 1, 1);

        tb_create = new QToolButton(w_button);
        tb_create->setObjectName(QStringLiteral("tb_create"));
        tb_create->setMinimumSize(QSize(190, 50));
        tb_create->setMaximumSize(QSize(190, 16777215));
        tb_create->setFont(font3);

        gridLayout_6->addWidget(tb_create, 10, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 14, 0, 1, 1);

        tb_audio = new QToolButton(w_button);
        tb_audio->setObjectName(QStringLiteral("tb_audio"));
        tb_audio->setMinimumSize(QSize(190, 50));
        tb_audio->setMaximumSize(QSize(190, 16777215));
        tb_audio->setFont(font3);

        gridLayout_6->addWidget(tb_audio, 2, 0, 1, 1);

        tb_image = new QToolButton(w_button);
        tb_image->setObjectName(QStringLiteral("tb_image"));
        tb_image->setMinimumSize(QSize(190, 50));
        tb_image->setMaximumSize(QSize(190, 16777215));
        tb_image->setFont(font3);

        gridLayout_6->addWidget(tb_image, 1, 0, 1, 1);

        line = new QFrame(w_button);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line, 9, 0, 1, 1);

        w_watermark = new QWidget(w_button);
        w_watermark->setObjectName(QStringLiteral("w_watermark"));
        w_watermark->setMinimumSize(QSize(0, 120));
        w_watermark->setMaximumSize(QSize(16777215, 120));
        w_watermark->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"background:transparent;\n"
"}"));
        gridLayout_3 = new QGridLayout(w_watermark);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(w_watermark);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(0, 80));
        listWidget->setMaximumSize(QSize(16777214, 80));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout_3->addWidget(listWidget, 1, 0, 1, 1);

        widget_3 = new QWidget(w_watermark);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 40));
        widget_3->setMaximumSize(QSize(16777215, 40));
        widget_3->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"background:transparent;\n"
"}"));
        gridLayout_12 = new QGridLayout(widget_3);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setContentsMargins(4, 0, 0, 0);
        tb_add_size = new QToolButton(widget_3);
        tb_add_size->setObjectName(QStringLiteral("tb_add_size"));
        tb_add_size->setMinimumSize(QSize(35, 35));
        tb_add_size->setMaximumSize(QSize(35, 35));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/icon/save+icon-1320167995084087448.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_add_size->setIcon(icon3);
        tb_add_size->setIconSize(QSize(30, 30));

        gridLayout_12->addWidget(tb_add_size, 0, 1, 1, 1);

        tb_del_size = new QToolButton(widget_3);
        tb_del_size->setObjectName(QStringLiteral("tb_del_size"));
        tb_del_size->setMinimumSize(QSize(35, 35));
        tb_del_size->setMaximumSize(QSize(35, 35));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/icon/Actions-remove-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_del_size->setIcon(icon4);
        tb_del_size->setIconSize(QSize(30, 30));

        gridLayout_12->addWidget(tb_del_size, 0, 2, 1, 1);

        label = new QLabel(widget_3);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 40));
        label->setMaximumSize(QSize(16777215, 40));
        QFont font5;
        font5.setFamily(QStringLiteral("Impact"));
        font5.setPointSize(12);
        label->setFont(font5);

        gridLayout_12->addWidget(label, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget_3, 0, 0, 1, 1);


        gridLayout_6->addWidget(w_watermark, 8, 0, 1, 1);

        widget_2 = new QWidget(w_button);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 50));
        widget_2->setMaximumSize(QSize(16777215, 50));
        widget_2->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"background:#7f7f7f;\n"
"}"));
        gridLayout_13 = new QGridLayout(widget_2);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_13->setHorizontalSpacing(0);
        gridLayout_13->setVerticalSpacing(3);
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        tb_next_1 = new QToolButton(widget_2);
        tb_next_1->setObjectName(QStringLiteral("tb_next_1"));
        tb_next_1->setMinimumSize(QSize(0, 40));
        tb_next_1->setMaximumSize(QSize(25, 40));
        tb_next_1->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"background:transparent;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/icon/arrow-dropright-icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_next_1->setIcon(icon5);
        tb_next_1->setIconSize(QSize(30, 30));

        gridLayout_13->addWidget(tb_next_1, 0, 3, 1, 1);

        tb_prev_1 = new QToolButton(widget_2);
        tb_prev_1->setObjectName(QStringLiteral("tb_prev_1"));
        tb_prev_1->setMinimumSize(QSize(0, 40));
        tb_prev_1->setMaximumSize(QSize(25, 40));
        tb_prev_1->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"background:transparent;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/icon/arrow-dropleft-icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_prev_1->setIcon(icon6);
        tb_prev_1->setIconSize(QSize(30, 30));

        gridLayout_13->addWidget(tb_prev_1, 0, 0, 1, 1);

        tb_bg_2 = new QToolButton(widget_2);
        tb_bg_2->setObjectName(QStringLiteral("tb_bg_2"));
        tb_bg_2->setEnabled(true);
        tb_bg_2->setMinimumSize(QSize(40, 40));
        tb_bg_2->setMaximumSize(QSize(40, 40));
        tb_bg_2->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"background:#c3c3c3;\n"
"}"));
        tb_bg_2->setIconSize(QSize(40, 40));

        gridLayout_13->addWidget(tb_bg_2, 0, 2, 1, 1);

        tb_bg_1 = new QToolButton(widget_2);
        tb_bg_1->setObjectName(QStringLiteral("tb_bg_1"));
        tb_bg_1->setEnabled(true);
        tb_bg_1->setMinimumSize(QSize(40, 40));
        tb_bg_1->setMaximumSize(QSize(40, 40));
        tb_bg_1->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"background:#c3c3c3;\n"
"}"));
        tb_bg_1->setIconSize(QSize(40, 40));

        gridLayout_13->addWidget(tb_bg_1, 0, 1, 1, 1);

        tb_detail = new QToolButton(widget_2);
        tb_detail->setObjectName(QStringLiteral("tb_detail"));
        tb_detail->setMinimumSize(QSize(40, 40));
        tb_detail->setMaximumSize(QSize(40, 40));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/icon/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_detail->setIcon(icon7);
        tb_detail->setIconSize(QSize(40, 40));

        gridLayout_13->addWidget(tb_detail, 0, 4, 1, 1);


        gridLayout_6->addWidget(widget_2, 12, 0, 1, 1);

        widget_6 = new QWidget(w_button);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(0, 120));
        widget_6->setMaximumSize(QSize(16777215, 120));
        gridLayout_14 = new QGridLayout(widget_6);
        gridLayout_14->setSpacing(0);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_6);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(190, 0));
        label_3->setMaximumSize(QSize(190, 16777215));
        QFont font6;
        font6.setFamily(QStringLiteral("Franklin Gothic Heavy"));
        font6.setPointSize(14);
        label_3->setFont(font6);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_14->addWidget(label_3, 0, 0, 1, 1);

        tb_upload_intro = new QToolButton(widget_6);
        tb_upload_intro->setObjectName(QStringLiteral("tb_upload_intro"));
        tb_upload_intro->setMinimumSize(QSize(190, 50));
        tb_upload_intro->setMaximumSize(QSize(190, 50));
        tb_upload_intro->setFont(font6);
        tb_upload_intro->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"background:#98c253;\n"
"color:#fff200;\n"
"border-top:10px solid white;\n"
"border-bottom:10px solid white;\n"
"border-left:35px solid white;\n"
"border-right:35px solid white;\n"
"}"));

        gridLayout_14->addWidget(tb_upload_intro, 1, 0, 1, 1);

        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMinimumSize(QSize(190, 0));
        widget_7->setMaximumSize(QSize(190, 16777215));
        gridLayout_15 = new QGridLayout(widget_7);
        gridLayout_15->setSpacing(0);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        tb_library_intro = new QToolButton(widget_7);
        tb_library_intro->setObjectName(QStringLiteral("tb_library_intro"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tb_library_intro->sizePolicy().hasHeightForWidth());
        tb_library_intro->setSizePolicy(sizePolicy2);
        tb_library_intro->setMinimumSize(QSize(0, 30));
        QFont font7;
        font7.setFamily(QStringLiteral("Franklin Gothic Heavy"));
        font7.setPointSize(12);
        tb_library_intro->setFont(font7);
        tb_library_intro->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"border:none;\n"
"}\n"
"QToolButton:Hover\n"
"{\n"
"background:#c3c3c3;\n"
"border:none;\n"
"}"));

        gridLayout_15->addWidget(tb_library_intro, 0, 0, 1, 1);

        tb_play_intro = new QToolButton(widget_7);
        tb_play_intro->setObjectName(QStringLiteral("tb_play_intro"));
        tb_play_intro->setEnabled(false);
        tb_play_intro->setMinimumSize(QSize(80, 30));
        tb_play_intro->setMaximumSize(QSize(80, 16777215));
        QFont font8;
        font8.setFamily(QStringLiteral("Franklin Gothic Heavy"));
        font8.setPointSize(11);
        tb_play_intro->setFont(font8);
        tb_play_intro->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"border:1px solid black;\n"
"}"));
        tb_play_intro->setCheckable(true);

        gridLayout_15->addWidget(tb_play_intro, 0, 1, 1, 1);


        gridLayout_14->addWidget(widget_7, 2, 0, 1, 1);


        gridLayout_6->addWidget(widget_6, 0, 0, 1, 1);


        gridLayout->addWidget(w_button, 0, 1, 1, 1);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(50, 0));
        widget_4->setMaximumSize(QSize(50, 16777215));
        widget_4->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"border-right:1px solid black;\n"
"}"));
        gridLayout_17 = new QGridLayout(widget_4);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        gridLayout_17->setContentsMargins(-1, 20, -1, -1);
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(35, 35));
        label_6->setMaximumSize(QSize(35, 35));
        QFont font9;
        font9.setFamily(QStringLiteral("Franklin Gothic Heavy"));
        font9.setPointSize(18);
        label_6->setFont(font9);
        label_6->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background:#7f7f7f;\n"
"color:black;\n"
"}\n"
""));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_6, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_17->addItem(verticalSpacer_3, 0, 0, 1, 1);

        label_8 = new QLabel(widget_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(35, 35));
        label_8->setMaximumSize(QSize(35, 35));
        label_8->setFont(font9);
        label_8->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background:#7f7f7f;\n"
"color:black;\n"
"}\n"
""));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_8, 5, 0, 1, 1);

        label_7 = new QLabel(widget_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(35, 35));
        label_7->setMaximumSize(QSize(35, 35));
        label_7->setFont(font9);
        label_7->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background:#7f7f7f;\n"
"color:black;\n"
"}\n"
""));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_7, 3, 0, 1, 1);

        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(35, 35));
        label_9->setMaximumSize(QSize(35, 35));
        label_9->setFont(font9);
        label_9->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background:#7f7f7f;\n"
"color:black;\n"
"}\n"
""));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_9, 7, 0, 1, 1);

        label_10 = new QLabel(widget_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(35, 35));
        label_10->setMaximumSize(QSize(35, 35));
        label_10->setFont(font9);
        label_10->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background:#7f7f7f;\n"
"color:black;\n"
"}\n"
""));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_10, 9, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 170, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_17->addItem(verticalSpacer_8, 8, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_17->addItem(verticalSpacer_6, 4, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_17->addItem(verticalSpacer_7, 6, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_17->addItem(verticalSpacer_5, 2, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_17->addItem(verticalSpacer_4, 10, 0, 1, 1);


        gridLayout->addWidget(widget_4, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget, 1, 1, 1, 1);


        retranslateUi(Form_MainWindow);

        QMetaObject::connectSlotsByName(Form_MainWindow);
    } // setupUi

    void retranslateUi(QWidget *Form_MainWindow)
    {
        Form_MainWindow->setWindowTitle(QApplication::translate("Form_MainWindow", "GIF to MOVIE", 0));
        tb_minimize->setText(QApplication::translate("Form_MainWindow", "_", 0));
        lbl_title->setText(QApplication::translate("Form_MainWindow", " GIF TO MOVIE", 0));
        label_4->setText(QString());
        tb_close->setText(QApplication::translate("Form_MainWindow", "X", 0));
        lbl_pix->setText(QString());
        lbl_seek->setText(QString());
        label_2->setText(QApplication::translate("Form_MainWindow", "    AUDIO FILE:", 0));
        lbl_audio_path->setText(QApplication::translate("Form_MainWindow", "NO AUDIO FILE IS SELECTED.         ", 0));
        lbl_curtime->setText(QApplication::translate("Form_MainWindow", "00:00 / 00:00", 0));
        lbl_seek_intro->setText(QString());
        lbl_index->setText(QApplication::translate("Form_MainWindow", "10/10", 0));
        tb_prev->setText(QApplication::translate("Form_MainWindow", "...", 0));
        tb_next->setText(QApplication::translate("Form_MainWindow", "...", 0));
        tb_play->setText(QApplication::translate("Form_MainWindow", "PLAY", 0));
        tb_watermark->setText(QApplication::translate("Form_MainWindow", "ADD WATERMARK", 0));
        tb_create->setText(QApplication::translate("Form_MainWindow", "CREATE VIDEO", 0));
        tb_audio->setText(QApplication::translate("Form_MainWindow", "SELECT AUDIO", 0));
        tb_image->setText(QApplication::translate("Form_MainWindow", "UPLOAD  IMAGE", 0));
        tb_add_size->setText(QApplication::translate("Form_MainWindow", "...", 0));
        tb_del_size->setText(QApplication::translate("Form_MainWindow", "...", 0));
        label->setText(QApplication::translate("Form_MainWindow", "ICON SIZE", 0));
        tb_next_1->setText(QApplication::translate("Form_MainWindow", "...", 0));
        tb_prev_1->setText(QApplication::translate("Form_MainWindow", "...", 0));
        tb_bg_2->setText(QString());
        tb_bg_1->setText(QString());
        tb_detail->setText(QApplication::translate("Form_MainWindow", "...", 0));
        label_3->setText(QApplication::translate("Form_MainWindow", "ADD VIDEO-INTRO", 0));
        tb_upload_intro->setText(QApplication::translate("Form_MainWindow", "UPLOAD", 0));
        tb_library_intro->setText(QApplication::translate("Form_MainWindow", "LIBRARY", 0));
        tb_play_intro->setText(QApplication::translate("Form_MainWindow", "PLAY", 0));
        label_6->setText(QApplication::translate("Form_MainWindow", "1", 0));
        label_8->setText(QApplication::translate("Form_MainWindow", "3", 0));
        label_7->setText(QApplication::translate("Form_MainWindow", "2", 0));
        label_9->setText(QApplication::translate("Form_MainWindow", "4", 0));
        label_10->setText(QApplication::translate("Form_MainWindow", "5", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_MainWindow: public Ui_Form_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
