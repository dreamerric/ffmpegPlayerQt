///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     slider.h                                                       
///  @brief    qt������������                                                                        
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <qslider.h>
/**
	@brief qt������������
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

