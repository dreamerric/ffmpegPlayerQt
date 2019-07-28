///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     readPacketsThread.h                                                       
///  @brief    ��ȡ��Ƶ��Ƶ����Ƶpacket���߳���                                                                        
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QThread>
#include <QMutex>

/**
	@brief ��ȡ��Ƶ��Ƶ����Ƶpacket���߳���
*/
class readPacketsThread :public QThread
{
	Q_OBJECT
public:
	static readPacketsThread * getInstance() {
		static readPacketsThread rpt;
		return &rpt;
	}
	/**
		@brief ����Ƶpacket����߳�

		����packet�е�stream_index����Ƶ����Ƶpacket�ֱ������Զ�����У�
		��������ڽ���������isSeek��־����av_seek_frame()��ת����Ƶָ��λ�ã�
	*/
	void run();
	bool getIsPlaying();
	/**
		@brief ������ת��־
	*/
	bool getIsSeeking();
	void setPlaying(bool isPlaying);
	virtual ~readPacketsThread();

public slots:
	/**
		@brief	������������Ƶ��תλ��
		@param pos	��Ƶ��ת���ڽ������е�λ��
	*/
	void receivePos(float pos);
private:
	readPacketsThread();
	bool isSeek = false;
	float currentPos = 0;
	
	bool isPlay = false;
	QMutex mutex;
};

