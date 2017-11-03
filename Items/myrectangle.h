#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include <QObject>
#include <QBrush>
#include <QGraphicsRectItem>

class MyRectangle : public QGraphicsRectItem
{

public:
	explicit MyRectangle(qreal x, qreal y,
						 QGraphicsRectItem *parent = nullptr);
	~MyRectangle();
};

#endif // MYRECTANGLE_H
