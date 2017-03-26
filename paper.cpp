#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent)
{
	mode = InteractionMode::Selecting; // general mode is drawing
	inTheMiddleOfAStroke = false;				 // but at this very moment we're not drawing
	myPenWidth = 3;
	myPenColor = Qt::black;
	myPen = QPen(myPenColor, myPenWidth,
				 Qt::SolidLine, Qt::RoundCap,
				 Qt::RoundJoin);
	selectedItem = nullptr;
	textEdit = nullptr;
	proxyText = nullptr;
	currentStrokePath = nullptr;
	currentStrokeItem = nullptr;
}

void Paper::setPenColor(const QColor &newColor)
{
	myPenColor = newColor;
}

void Paper::setPenWidth(int newWidth)
{
	myPenWidth = newWidth;
}

void Paper::setMoving()
{
	mode = InteractionMode::Selecting;
}

void Paper::setDrawing()
{
	mode = InteractionMode::Drawing;
}

void Paper::setEditingText()
{
	mode = InteractionMode::InsertingText;
}

void Paper::setSelect()
{
	mode = InteractionMode::Selecting;
}

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{	
	if(mode != InteractionMode::EditingText)
		deselect();

	if(event->button() == Qt::LeftButton && mode == InteractionMode::EditingText)
	{
		QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
		if(!item || (item != selectedItem && item != proxyText))
		{
			deselect();
			mode = InteractionMode::Selecting;
			return;
		}
		QGraphicsScene::mousePressEvent(event);
	}

	else if (event->button() == Qt::LeftButton && mode == InteractionMode::Selecting)
	{
		QGraphicsScene::mousePressEvent(event);
		selectedItem = itemAt(event->scenePos(), QTransform());
		QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

		if(!selectedTextItem)
		{
			deselect();
			return;
		}

		textEdit = new QTextEdit();
		connect(textEdit, &QTextEdit::textChanged,
				this, &Paper::textChanged);
		textEdit->resize((int)selectedTextItem->boundingRect().size().width() + 5,
						 (int)selectedTextItem->boundingRect().size().height() + 5);
		textEdit->move((int)selectedTextItem->pos().x(), (int)selectedTextItem->pos().y());
		textEdit->setDocument(selectedTextItem->document());
		textEdit->setCursorWidth(3);
		QTextCursor tmpCursor = textEdit->textCursor();
		tmpCursor.movePosition(QTextCursor::Start);
		tmpCursor.setVisualNavigation(true);
		textEdit->setTextCursor(tmpCursor);
		textEdit->setFocus();
		proxyText = addWidget(textEdit);
		proxyText->setFocus();
		mode = InteractionMode::EditingText;
	}

	else if(mode == InteractionMode::Selecting)
		QGraphicsScene::mousePressEvent(event);

	else if (event->button() == Qt::LeftButton && mode == InteractionMode::InsertingText)
	{
		textEdit = new QTextEdit();
		textEdit->move((int)event->scenePos().x() - 10, (int)event->scenePos().y());
		proxyText = addWidget(textEdit);
		mode = InteractionMode::Selecting;
	}

	else if (event->button() == Qt::LeftButton && mode == InteractionMode::Drawing)
	{
		currentStrokePath = new QPainterPath(event->scenePos());
		currentStrokeItem = addPath(*currentStrokePath);
		currentStrokeItem->setPen(myPen);
		currentStrokeItem->setFlag(QGraphicsItem::ItemIsMovable);
		inTheMiddleOfAStroke = true;
	}
}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(mode == InteractionMode::Selecting || mode == InteractionMode::EditingText)
		QGraphicsScene::mouseMoveEvent(event);

	else if (event->buttons() == Qt::LeftButton && inTheMiddleOfAStroke && mode == InteractionMode::Drawing)
		drawLineTo(event->scenePos());
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(mode == InteractionMode::Selecting  || mode == InteractionMode::EditingText)
		QGraphicsScene::mouseReleaseEvent(event);

	else if (event->button() == Qt::LeftButton && inTheMiddleOfAStroke && mode == InteractionMode::Drawing)
	{
		drawLineTo(event->scenePos());
		inTheMiddleOfAStroke = false;
		delete currentStrokePath;
	}
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	if(mode == InteractionMode::Selecting)
		QGraphicsScene::dropEvent(event);

	QGraphicsItem* item;

	if(event->mimeData()->hasUrls()) //TODO: make sure it's a photo and add support to all file types ever
		item = new QGraphicsPixmapItem(* new QPixmap(event->mimeData()->urls()[0].toLocalFile()));

	else if (event->mimeData()->hasHtml())
	{
		item = new QGraphicsTextItem();
		((QGraphicsTextItem *)item)->setHtml(event->mimeData()->html());
	}

	else if(event->mimeData()->hasText())
			item = new QGraphicsSimpleTextItem(event->mimeData()->text());

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
	currentStrokePath->lineTo(endPoint);
	currentStrokeItem->setPath(*currentStrokePath);
}

void Paper::deselect()
{
	if (proxyText)
	{
		removeItem(proxyText);
		proxyText = nullptr;
	}

	if (textEdit)
	{
		delete textEdit;
		textEdit = nullptr;
	}

	if (selectedItem)
		selectedItem = nullptr;
}

void Paper::textChanged()
{
	QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

	if(!selectedTextItem)
		return;

	selectedTextItem->setDocument(textEdit->document());
}
