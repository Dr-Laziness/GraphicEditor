#include "myellipse.h"

MyEllipse::MyEllipse(qreal x, qreal y, QGraphicsEllipseItem *parent) :
	QGraphicsEllipseItem(parent)
{
	setRect(x - 25, y - 25, 50, 50);
	setBrush(QBrush(QColor(Qt::red)));
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

MyEllipse::~MyEllipse()
{

}
