#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>

enum InteractionMode
{
	Drawing,
	Selecting,
	InsertingText,
	EditingText
};

class Paper : public QGraphicsScene
{
	Q_OBJECT

public:

	InteractionMode mode;

	Paper(QWidget *parent = 0);

	void setPenColor(const QColor &newColor);
	void setPenWidth(int newWidth);

	QColor penColor() const { return myPenColor; }
	int penWidth() const { return myPenWidth; }
	void setMoving();
	void setDrawing();
	void setEditingText();
	void setSelect();

public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

private:
	void drawLineTo(const QPointF &endPoint);
	void deselect();
	void textChanged();

	bool inTheMiddleOfAStroke;
	int myPenWidth;
	QGraphicsItem* selectedItem;
	QTextEdit* textEdit;
	QGraphicsProxyWidget *proxyText;
	QColor myPenColor;
	QPointF lastPoint;
	QPen myPen;
	QPainterPath* currentStrokePath;
	QGraphicsPathItem* currentStrokeItem;
};

#endif
