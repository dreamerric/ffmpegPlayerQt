#include "slider.h"
#include <QMouseEvent>

slider::slider(QWidget *p) :QSlider(p)
{
}

void slider::mousePressEvent(QMouseEvent *e)
{
	int value = ((float)e->pos().x() / (float)this->width())*(this->maximum() + 1);
	this->setValue(value);
	QSlider::mousePressEvent(e);
}

slider::~slider()
{
}
