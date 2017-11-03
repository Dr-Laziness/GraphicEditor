#include "myrectangle.h"

MyRectangle::MyRectangle(qreal x, qreal y, QGraphicsRectItem *parent) :
	QGraphicsRectItem(parent)
{
	setRect(x - 25, y - 25, 50, 50);
	setBrush(QBrush(QColor(Qt::green)));
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

MyRectangle::~MyRectangle()
{

}
