#include "videoWidget.h"
#include "readPacketsThread.h"
#include "playerMediaTimer.h"
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QMouseEvent>

static QImage* image = nullptr;

videoWidget::videoWidget(QWidget * p): QOpenGLWidget(p)
{
	startTimer(10);
	setFocusPolicy(Qt::StrongFocus);
	this->setMouseTracking(true);
	mouseTimer = new QTimer(this);

	QObject::connect(mouseTimer,
		SIGNAL(timeout()),
		this,
		SLOT(hideMouse())
	);

	QObject::connect(playerMediaTimer::getInstance(),
		SIGNAL(updateFrame(QImage*)),
		this,
		SLOT(setVideoImage(QImage*))
	);
	mouseTimer->start(6000);
}
void videoWidget::setVideoImage(QImage* img) {
	if (readPacketsThread::getInstance()->getIsPlaying()) {
		image = img;
		this->update();
	}
}
void videoWidget::hideMouse()
{
	this->setCursor(Qt::BlankCursor);
	emit showSlider(false);
}

void videoWidget::paintEvent(QPaintEvent * pEvent)
{
	QPainter painter;
	painter.begin(this);
	if (image == nullptr)
	{
		return;
	}
	else
	{
		painter.drawImage(QPoint(0, 0), *image);
	}
	painter.end();
}
void videoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}
void videoWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
	this->setCursor(Qt::ArrowCursor);
	if (pEvent->pos().y() > this->height()-100)
	{
		emit showSlider(true);
	}
}

videoWidget::videoWidget()
{
}
videoWidget::~videoWidget()
{
	
}
