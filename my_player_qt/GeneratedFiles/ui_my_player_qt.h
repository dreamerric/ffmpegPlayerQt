/********************************************************************************
** Form generated from reading UI file 'my_player_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_PLAYER_QT_H
#define UI_MY_PLAYER_QT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "slider.h"
#include "videoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_myPlayerQtClass
{
public:
    QAction *openLocalFile;
    QAction *openWebFile;
    QAction *openVideoList;
    QAction *pauseAction;
    QAction *fullScreenAction;
    QAction *volumeMute;
    QAction *nextVideo;
    QAction *previousVideo;
    QAction *screenshotAction;
    QWidget *centralWidget;
    videoWidget *openGL_widget;
    QTabWidget *videoInfoWidget;
    QWidget *tab;
    QListWidget *videoListWidget;
    QWidget *tab_2;
    QTextEdit *videoInfo;
    QLabel *loadingLabel;
    QPushButton *iconBackground;
    QGroupBox *groupBox;
    QPushButton *nextButton;
    QPushButton *forwardButton;
    QPushButton *playButton;
    QPushButton *rewinButton;
    QPushButton *previousButton;
    slider *playSlider;
    QLabel *curTime;
    QLabel *totalTime;
    QSlider *volumeSlider;
    QPushButton *volumeButton;
    QLabel *textLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTool;
    QMenu *menuWindow;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myPlayerQtClass)
    {
        if (myPlayerQtClass->objectName().isEmpty())
            myPlayerQtClass->setObjectName(QString::fromUtf8("myPlayerQtClass"));
        myPlayerQtClass->setEnabled(true);
        myPlayerQtClass->resize(800, 505);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/my_player_qt/Resources/playerIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        myPlayerQtClass->setWindowIcon(icon);
        myPlayerQtClass->setAutoFillBackground(false);
        myPlayerQtClass->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"\n"
""));
        openLocalFile = new QAction(myPlayerQtClass);
        openLocalFile->setObjectName(QString::fromUtf8("openLocalFile"));
        openLocalFile->setCheckable(false);
        openWebFile = new QAction(myPlayerQtClass);
        openWebFile->setObjectName(QString::fromUtf8("openWebFile"));
        openVideoList = new QAction(myPlayerQtClass);
        openVideoList->setObjectName(QString::fromUtf8("openVideoList"));
        pauseAction = new QAction(myPlayerQtClass);
        pauseAction->setObjectName(QString::fromUtf8("pauseAction"));
        fullScreenAction = new QAction(myPlayerQtClass);
        fullScreenAction->setObjectName(QString::fromUtf8("fullScreenAction"));
        volumeMute = new QAction(myPlayerQtClass);
        volumeMute->setObjectName(QString::fromUtf8("volumeMute"));
        nextVideo = new QAction(myPlayerQtClass);
        nextVideo->setObjectName(QString::fromUtf8("nextVideo"));
        previousVideo = new QAction(myPlayerQtClass);
        previousVideo->setObjectName(QString::fromUtf8("previousVideo"));
        screenshotAction = new QAction(myPlayerQtClass);
        screenshotAction->setObjectName(QString::fromUtf8("screenshotAction"));
        centralWidget = new QWidget(myPlayerQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 0, 0);\n"
"color:rgb(0, 0, 0)"));
        openGL_widget = new videoWidget(centralWidget);
        openGL_widget->setObjectName(QString::fromUtf8("openGL_widget"));
        openGL_widget->setGeometry(QRect(0, 0, 600, 380));
        openGL_widget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0)"));
        videoInfoWidget = new QTabWidget(centralWidget);
        videoInfoWidget->setObjectName(QString::fromUtf8("videoInfoWidget"));
        videoInfoWidget->setGeometry(QRect(600, 0, 210, 450));
        videoInfoWidget->setMinimumSize(QSize(200, 10));
        videoInfoWidget->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        videoInfoWidget->setFont(font);
        videoInfoWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(89,87,87);\n"
"border:1px"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setStyleSheet(QString::fromUtf8("background-color:rgb(89,87,87);\n"
"border-color:rgb(35, 35, 35)"));
        videoListWidget = new QListWidget(tab);
        videoListWidget->setObjectName(QString::fromUtf8("videoListWidget"));
        videoListWidget->setGeometry(QRect(0, 0, 200, 440));
        videoListWidget->setMinimumSize(QSize(200, 400));
        QFont font1;
        font1.setPointSize(9);
        videoListWidget->setFont(font1);
        videoListWidget->setAutoFillBackground(false);
        videoListWidget->setStyleSheet(QString::fromUtf8(""));
        videoInfoWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setStyleSheet(QString::fromUtf8("background-color:rgb(35, 35, 35);"));
        videoInfo = new QTextEdit(tab_2);
        videoInfo->setObjectName(QString::fromUtf8("videoInfo"));
        videoInfo->setGeometry(QRect(0, 0, 200, 440));
        videoInfoWidget->addTab(tab_2, QString());
        loadingLabel = new QLabel(centralWidget);
        loadingLabel->setObjectName(QString::fromUtf8("loadingLabel"));
        loadingLabel->setGeometry(QRect(250, 160, 91, 51));
        iconBackground = new QPushButton(centralWidget);
        iconBackground->setObjectName(QString::fromUtf8("iconBackground"));
        iconBackground->setGeometry(QRect(260, 160, 81, 81));
        iconBackground->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/playerIcon.png)"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 360, 601, 91));
        groupBox->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"border: 0px"));
        nextButton = new QPushButton(groupBox);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(430, 22, 44, 44));
        nextButton->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/CIRCLE_SKIP_NEXT.png)"));
        forwardButton = new QPushButton(groupBox);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setGeometry(QRect(370, 22, 44, 44));
        forwardButton->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/CIRCLE_FAST_FORWARD.png)"));
        playButton = new QPushButton(groupBox);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(300, 20, 51, 51));
        playButton->setStyleSheet(QString::fromUtf8("QPushButton:!hover{border-image:url(:/my_player_qt/Resources/CIRCLE_PLAY.png);}\n"
"QPushButton:hover{border-image: url(:/my_player_qt/Resources/CIRCLE_PLAY.png);}	"));
        rewinButton = new QPushButton(groupBox);
        rewinButton->setObjectName(QString::fromUtf8("rewinButton"));
        rewinButton->setGeometry(QRect(240, 22, 44, 44));
        rewinButton->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/CIRCLE_REWIND.png)"));
        previousButton = new QPushButton(groupBox);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        previousButton->setGeometry(QRect(180, 22, 44, 44));
        previousButton->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/CIRCLE_SKIP_PREVIOUS.png)"));
        playSlider = new slider(groupBox);
        playSlider->setObjectName(QString::fromUtf8("playSlider"));
        playSlider->setGeometry(QRect(0, 0, 600, 20));
        playSlider->setMaximum(999);
        playSlider->setSingleStep(1);
        playSlider->setPageStep(100);
        playSlider->setOrientation(Qt::Horizontal);
        curTime = new QLabel(groupBox);
        curTime->setObjectName(QString::fromUtf8("curTime"));
        curTime->setGeometry(QRect(10, 20, 61, 21));
        curTime->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255)"));
        totalTime = new QLabel(groupBox);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(530, 20, 61, 21));
        totalTime->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255)"));
        volumeSlider = new QSlider(groupBox);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setGeometry(QRect(530, 50, 51, 22));
        volumeSlider->setOrientation(Qt::Horizontal);
        volumeButton = new QPushButton(groupBox);
        volumeButton->setObjectName(QString::fromUtf8("volumeButton"));
        volumeButton->setGeometry(QRect(500, 50, 20, 20));
        volumeButton->setStyleSheet(QString::fromUtf8("border-image:url(:/my_player_qt/Resources/VOLUME.png)"));
        textLabel = new QLabel(centralWidget);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));
        textLabel->setGeometry(QRect(240, 250, 141, 21));
        textLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 14px;\n"
"background-color: transparent;"));
        textLabel->setAlignment(Qt::AlignCenter);
        myPlayerQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myPlayerQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QString::fromUtf8("menuTool"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        myPlayerQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myPlayerQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myPlayerQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myPlayerQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myPlayerQtClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuFile->addAction(openLocalFile);
        menuFile->addAction(openWebFile);
        menuTool->addAction(previousVideo);
        menuTool->addAction(nextVideo);
        menuTool->addAction(volumeMute);
        menuTool->addAction(pauseAction);
        menuWindow->addAction(openVideoList);
        menuWindow->addAction(fullScreenAction);

        retranslateUi(myPlayerQtClass);
        QObject::connect(playSlider, SIGNAL(sliderPressed()), myPlayerQtClass, SLOT(sliderPressed()));
        QObject::connect(playSlider, SIGNAL(sliderReleased()), myPlayerQtClass, SLOT(sliderRelease()));
        QObject::connect(playButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(play()));
        QObject::connect(videoListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), myPlayerQtClass, SLOT(clickedVideoList(QListWidgetItem*)));
        QObject::connect(volumeButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(setMute()));
        QObject::connect(volumeSlider, SIGNAL(sliderReleased()), myPlayerQtClass, SLOT(setVolume()));
        QObject::connect(previousButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(skipPrevious()));
        QObject::connect(nextButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(skipNext()));
        QObject::connect(pauseAction, SIGNAL(triggered()), myPlayerQtClass, SLOT(play()));
        QObject::connect(fullScreenAction, SIGNAL(triggered()), myPlayerQtClass, SLOT(fullScreen()));
        QObject::connect(openWebFile, SIGNAL(triggered()), myPlayerQtClass, SLOT(netAddressInput()));
        QObject::connect(openLocalFile, SIGNAL(triggered()), myPlayerQtClass, SLOT(open()));
        QObject::connect(volumeMute, SIGNAL(triggered()), myPlayerQtClass, SLOT(setMute()));
        QObject::connect(openVideoList, SIGNAL(triggered()), myPlayerQtClass, SLOT(showVideoList()));
        QObject::connect(previousVideo, SIGNAL(triggered()), myPlayerQtClass, SLOT(skipPrevious()));
        QObject::connect(nextVideo, SIGNAL(triggered()), myPlayerQtClass, SLOT(skipNext()));
        QObject::connect(rewinButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(seekBack()));
        QObject::connect(forwardButton, SIGNAL(clicked()), myPlayerQtClass, SLOT(seekForward()));

        videoInfoWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(myPlayerQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *myPlayerQtClass)
    {
        myPlayerQtClass->setWindowTitle(QApplication::translate("myPlayerQtClass", "\346\210\221\347\232\204\346\222\255\346\224\276\345\231\250", nullptr));
        openLocalFile->setText(QApplication::translate("myPlayerQtClass", "\346\211\223\345\274\200\346\234\254\345\234\260\350\247\206\351\242\221", nullptr));
        openWebFile->setText(QApplication::translate("myPlayerQtClass", "\346\211\223\345\274\200\347\275\221\347\273\234\350\247\206\351\242\221", nullptr));
        openVideoList->setText(QApplication::translate("myPlayerQtClass", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
#ifndef QT_NO_TOOLTIP
        openVideoList->setToolTip(QApplication::translate("myPlayerQtClass", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
#endif // QT_NO_TOOLTIP
        pauseAction->setText(QApplication::translate("myPlayerQtClass", "\346\232\202\345\201\234", nullptr));
        fullScreenAction->setText(QApplication::translate("myPlayerQtClass", "\345\205\250\345\261\217", nullptr));
        volumeMute->setText(QApplication::translate("myPlayerQtClass", "\351\235\231\351\237\263", nullptr));
        nextVideo->setText(QApplication::translate("myPlayerQtClass", "\344\270\213\344\270\200\344\270\252\350\247\206\351\242\221", nullptr));
        previousVideo->setText(QApplication::translate("myPlayerQtClass", "\344\270\212\344\270\200\344\270\252\350\247\206\351\242\221", nullptr));
        screenshotAction->setText(QApplication::translate("myPlayerQtClass", "\346\210\252\345\233\276", nullptr));
        videoInfoWidget->setTabText(videoInfoWidget->indexOf(tab), QApplication::translate("myPlayerQtClass", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        videoInfoWidget->setTabText(videoInfoWidget->indexOf(tab_2), QApplication::translate("myPlayerQtClass", "\350\247\206\351\242\221\344\277\241\346\201\257", nullptr));
        loadingLabel->setText(QApplication::translate("myPlayerQtClass", "TextLabel", nullptr));
        iconBackground->setText(QString());
        groupBox->setTitle(QString());
        nextButton->setText(QString());
        forwardButton->setText(QString());
        playButton->setText(QString());
        rewinButton->setText(QString());
        previousButton->setText(QString());
        curTime->setText(QApplication::translate("myPlayerQtClass", "<html><head/><body><p>00:00:00</p></body></html>", nullptr));
        totalTime->setText(QApplication::translate("myPlayerQtClass", "<html><head/><body><p>00:00:00</p></body></html>", nullptr));
        volumeButton->setText(QString());
        textLabel->setText(QApplication::translate("myPlayerQtClass", "\346\255\243\345\234\250\345\212\240\350\275\275...", nullptr));
        menuFile->setTitle(QApplication::translate("myPlayerQtClass", "\346\226\207\344\273\266", nullptr));
        menuTool->setTitle(QApplication::translate("myPlayerQtClass", "\345\267\245\345\205\267", nullptr));
        menuWindow->setTitle(QApplication::translate("myPlayerQtClass", "\347\252\227\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myPlayerQtClass: public Ui_myPlayerQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_PLAYER_QT_H
