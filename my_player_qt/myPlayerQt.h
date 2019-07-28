///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     myPlayerQt.h                                                       
///  @brief    Qt界面的主窗口类，定义界面的所有控件和控件处理函数，绘制播放器主窗口                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <map>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QElapsedTimer>
#include <QLabel>
#include <QMovie>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#define PAUSE "QPushButton\
{border-image:url\
(:/my_player_qt/Resources/CIRCLE_PAUSE.png);}"
#define PLAY "QPushButton\
{border-image:url\
(:/my_player_qt/Resources/CIRCLE_PLAY.png);}"
#define VOLUME "QPushButton\
{border-image:url\
(:/my_player_qt/Resources/VOLUME.png);}"
#define VOLUME_MUTE "QPushButton\
{border-image:url\
(:/my_player_qt/Resources/VOLUME_MUTE.png);}"

#include "ui_my_player_qt.h"
#include "playerMedia.h"

/** 
	@brief 指示当前视频类型
*/
enum videoType { 
	url,   
	local 
};
/**
	@brief Qt界面的主窗口类
	
	定义界面的所有控件和控件处理函数，绘制播放器主窗口
*/
class myPlayerQt : public QMainWindow
{
	Q_OBJECT

public:
	myPlayerQt(QWidget *parent = Q_NULLPTR);
	/** 
		@brief 打开视频流
		
		@param name     视频路径，本地地址或网络链接
		@param type     视频类型
	*/
	void openVideo(QString name, int type);

	void timerEvent(QTimerEvent *pEvent);
	void resizeEvent(QResizeEvent *pEvent);
	void closeEvent(QCloseEvent *pEvent);
	void keyPressEvent(QKeyEvent *pEvent);
	void mouseDoubleClickEvent(QMouseEvent * pEvent);
	void contextMenuEvent(QContextMenuEvent *pEvent);
	/**
		@brief 鼠标拖动本地视频加入播放列表
	*/
	void dragEnterEvent(QDragEnterEvent *pEvent);
	void dropEvent(QDropEvent *pEvent);

	void showVideoInfo(playerMedia *media);
	/** @brief 设置当前播放时间
		
		在主窗口的timerEvent中调用，
		根据音频的pts设置当前播放时间
	*/
	void setPlayTime(double pts, double rate);
	/** @brief 网络流加载超时确认
		
		在主窗口的timerEvent中调用，
		用当前video packet队列大小判断当前流视频的缓冲状态，
		队列为空时自动暂停，队列大小超过一定值加载视频，
		加载超时时关闭视频流。
		
		@bug	此处有时候会导致程序崩溃
	*/
	void urlTimeoutCheck(double rate);

	/** @brief 根据视频名称和类型判断文件是否可播放

		@param name     视频名称
        @param type     视频类型
        @return         true表示可播放
	*/
	bool formatCheck(QString name, int type);
	/** @brief 控制是否显示loading图标和设置loading文字

		@param isShow   是否显示图标
		@param text     显示的文字
	*/
	void loadingShow(bool isShow, QString text);
	/** @brief 向文件map和播放列表中添加文件*/
	void addVideoItem(QString name, int type);

public slots:
	/** 
		@brief 打开本地视频
	*/
	void open();
	/** 
		@brief 打开网络流视频
	*/
	void netAddressInput();

	/** 
		@brief 控制视频的暂停和播放
	*/
	void play();
	/**
		@brief 进度条点击事件处理函数
	*/
	void sliderPressed();
	void sliderRelease();
	/**
		@brief 设置静音
	*/
	void setMute();
	void setVolume();
	/**
		@brief 设置全屏
	*/
	void fullScreen();
	void showVideoList();
	/**
		@brief 双击播放列表item播放视频
	*/
	void clickedVideoList(QListWidgetItem* item);
	/**
		@brief 跳转到播放列表中的前一个视频
	*/
	void skipPrevious();
	void skipNext();
	void seekBack();
	void seekForward();
	/**
		@brief 控制显示进度条和播放按钮
	*/
	void showPlayGroup(bool isShow);

signals:
	void sendPos(float pos);
private:
	Ui::myPlayerQtClass ui;
	QMenu *popMenu; ///< 鼠标右键弹出菜单
	int windowWidth; ///< 视频显示窗口宽度（随播放列表的显示变化）
	QMovie* movie; ///< 加载gif格式的loading图标
};
