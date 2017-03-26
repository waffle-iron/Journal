#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent)
{
	painting = false;
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
	if (event->button() == Qt::LeftButton)
	{
		painting = true;
		lastPoint = event->scenePos();
	}

}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton && painting)
		drawLineTo(event->scenePos());
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && painting)
	{
		drawLineTo(event->scenePos());
		painting = false;
	}
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event)
{
//	for (QString mime : event->mimeData()->formats())
//		std::cout << mime.toStdString() << std::endl;
	QGraphicsItem* item;
	if(event->mimeData()->hasUrls()) //TODO: make sure it's a photo and add support to all file types ever
		item = new QGraphicsPixmapItem(* new QPixmap(event->mimeData()->urls()[0].toLocalFile()));
	else if(event->mimeData()->hasText())
		item = new QGraphicsTextItem(event->mimeData()->text());
	else if(event->mimeData()->hasImage())
	{
		QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
		item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	}
	else return;
	item->setPos(event->scenePos());
	addItem(item);
}

void Paper::drawLineTo(const QPointF &endPoint)
{
	addLine(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y(), QPen(myPenColor, myPenWidth,
																		   Qt::SolidLine, Qt::RoundCap,
																		   Qt::RoundJoin));
	lastPoint = endPoint;
}
