#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

#include "paper.h"

Paper::Paper(QWidget *parent)
	: QGraphicsScene(parent)
{
	modified = false;
	painting = false;
	moving = false;
	myPenWidth = 3;
	myPenColor = Qt::black;
}

void Paper::setPenColor(const QColor &newColor)
{
	myPenColor = newColor;
}

void Paper::setPenWidth(int newWidth)
{
	myPenWidth = newWidth;
}

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving)
	{
		return;
	}
	if (event->button() == Qt::LeftButton) {
		painting = true;
		lastPoint = event->scenePos();
	}
}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving)
	{
		return;
	}

	if ((event->buttons() & Qt::LeftButton) && painting)
		drawLineTo(event->scenePos());
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving) return;

	if (event->button() == Qt::LeftButton && painting) {
		drawLineTo(event->scenePos());
		painting = false;
	}
}

void Paper::drawLineTo(const QPointF &endPoint)
{
	addLine(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y(), QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
																				  Qt::RoundJoin));
	lastPoint = endPoint;
}

bool Paper::getPainting() const
{
	return painting;
}

void Paper::setPainting(bool value)
{
	painting = value;
}

bool Paper::getMoving() const
{
	return moving;
}

void Paper::setMoving(bool value)
{
	moving = value;
}
