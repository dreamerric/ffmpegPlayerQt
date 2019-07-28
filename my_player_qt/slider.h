///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     slider.h                                                       
///  @brief    qt进度条控制类                                                                        
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <qslider.h>
/**
	@brief qt进度条控制类
*/
class slider :
	public QSlider
{
	Q_OBJECT
public:
	slider(QWidget*p = NULL);
	void mousePressEvent(QMouseEvent *e);

	virtual ~slider();
};

