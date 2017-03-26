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

class Paper : public QGraphicsScene
{
	Q_OBJECT

public:
	Paper(QWidget *parent = 0);

	void setPenColor(const QColor &newColor);
	void setPenWidth(int newWidth);

	QColor penColor() const { return myPenColor; }
	int penWidth() const { return myPenWidth; }
	void setMoving(bool isMoving);
	void setDrawing(bool isDrawing);

public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

private:
	void drawLineTo(const QPointF &endPoint);

	bool drawing;
	bool moving;
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPointF lastPoint;
	QPen myPen;
	QPainterPath* currentStrokePath;
	QGraphicsPathItem* currentStrokeItem;
};

#endif
