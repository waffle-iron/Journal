#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent)
{
	drawing = false;
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

void Paper::setMoving(bool isMoving)
{
	moving = isMoving;
}

void Paper::setDrawing(bool isDrawing)
{
	moving = !isDrawing;
}

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving)
	{
		QGraphicsScene::mousePressEvent(event);
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		drawing = true;
		lastPoint = event->scenePos();
	}

}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving)
	{
		QGraphicsScene::mouseMoveEvent(event);
		return;
	}
	if (event->buttons() == Qt::LeftButton && drawing)
		drawLineTo(event->scenePos());
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(moving)
	{
		QGraphicsScene::mouseReleaseEvent(event);
		return;
	}
	if (event->button() == Qt::LeftButton && drawing)
	{
		drawLineTo(event->scenePos());
		drawing = false;
	}
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event)
{
//	for (QString mime : event->mimeData()->formats())
//		std::cout << mime.toStdString() << std::endl;

	if(moving)
	{
		QGraphicsScene::dropEvent(event);
		return;
	}

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
	item->setFlag(QGraphicsItem::ItemIsMovable);
	addItem(item);
}

void Paper::drawLineTo(const QPointF &endPoint)
{
	addLine(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y(), QPen(myPenColor, myPenWidth,
																		   Qt::SolidLine, Qt::RoundCap,
																		   Qt::RoundJoin));
	lastPoint = endPoint;
}
