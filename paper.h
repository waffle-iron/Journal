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

	bool isModified() const { return modified; }
	QColor penColor() const { return myPenColor; }
	int penWidth() const { return myPenWidth; }

	bool getMoving() const;
	void setMoving(bool value);

	bool getPainting() const;
	void setPainting(bool value);

public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
	void drawLineTo(const QPointF &endPoint);
	void repaintPicture(const QPoint &position, QPicture* picture);

	bool modified;
	bool painting;
	bool moving;
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPainter painter;
	QPointF lastPoint;
	std::vector<QPicture*> pictures;
};

#endif
