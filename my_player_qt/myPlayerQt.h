///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     myPlayerQt.h                                                       
///  @brief    Qt������������࣬�����������пؼ��Ϳؼ������������Ʋ�����������                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
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
	@brief ָʾ��ǰ��Ƶ����
*/
enum videoType { 
	url,   
	local 
};
/**
	@brief Qt�������������
	
	�����������пؼ��Ϳؼ������������Ʋ�����������
*/
class myPlayerQt : public QMainWindow
{
	Q_OBJECT

public:
	myPlayerQt(QWidget *parent = Q_NULLPTR);
	/** 
		@brief ����Ƶ��
		
		@param name     ��Ƶ·�������ص�ַ����������
		@param type     ��Ƶ����
	*/
	void openVideo(QString name, int type);

	void timerEvent(QTimerEvent *pEvent);
	void resizeEvent(QResizeEvent *pEvent);
	void closeEvent(QCloseEvent *pEvent);
	void keyPressEvent(QKeyEvent *pEvent);
	void mouseDoubleClickEvent(QMouseEvent * pEvent);
	void contextMenuEvent(QContextMenuEvent *pEvent);
	/**
		@brief ����϶�������Ƶ���벥���б�
	*/
	void dragEnterEvent(QDragEnterEvent *pEvent);
	void dropEvent(QDropEvent *pEvent);

	void showVideoInfo(playerMedia *media);
	/** @brief ���õ�ǰ����ʱ��
		
		�������ڵ�timerEvent�е��ã�
		������Ƶ��pts���õ�ǰ����ʱ��
	*/
	void setPlayTime(double pts, double rate);
	/** @brief ���������س�ʱȷ��
		
		�������ڵ�timerEvent�е��ã�
		�õ�ǰvideo packet���д�С�жϵ�ǰ����Ƶ�Ļ���״̬��
		����Ϊ��ʱ�Զ���ͣ�����д�С����һ��ֵ������Ƶ��
		���س�ʱʱ�ر���Ƶ����
		
		@bug	�˴���ʱ��ᵼ�³������
	*/
	void urlTimeoutCheck(double rate);

	/** @brief ������Ƶ���ƺ������ж��ļ��Ƿ�ɲ���

		@param name     ��Ƶ����
        @param type     ��Ƶ����
        @return         true��ʾ�ɲ���
	*/
	bool formatCheck(QString name, int type);
	/** @brief �����Ƿ���ʾloadingͼ�������loading����

		@param isShow   �Ƿ���ʾͼ��
		@param text     ��ʾ������
	*/
	void loadingShow(bool isShow, QString text);
	/** @brief ���ļ�map�Ͳ����б�������ļ�*/
	void addVideoItem(QString name, int type);

public slots:
	/** 
		@brief �򿪱�����Ƶ
	*/
	void open();
	/** 
		@brief ����������Ƶ
	*/
	void netAddressInput();

	/** 
		@brief ������Ƶ����ͣ�Ͳ���
	*/
	void play();
	/**
		@brief ����������¼�������
	*/
	void sliderPressed();
	void sliderRelease();
	/**
		@brief ���þ���
	*/
	void setMute();
	void setVolume();
	/**
		@brief ����ȫ��
	*/
	void fullScreen();
	void showVideoList();
	/**
		@brief ˫�������б�item������Ƶ
	*/
	void clickedVideoList(QListWidgetItem* item);
	/**
		@brief ��ת�������б��е�ǰһ����Ƶ
	*/
	void skipPrevious();
	void skipNext();
	void seekBack();
	void seekForward();
	/**
		@brief ������ʾ�������Ͳ��Ű�ť
	*/
	void showPlayGroup(bool isShow);

signals:
	void sendPos(float pos);
private:
	Ui::myPlayerQtClass ui;
	QMenu *popMenu; ///< ����Ҽ������˵�
	int windowWidth; ///< ��Ƶ��ʾ���ڿ�ȣ��沥���б����ʾ�仯��
	QMovie* movie; ///< ����gif��ʽ��loadingͼ��
};
