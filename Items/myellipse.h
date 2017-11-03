#ifndef MYELLIPSE_H
#define MYELLIPSE_H

#include <QObject>
#include <QBrush>
#include <QGraphicsEllipseItem>

class MyEllipse : public QGraphicsEllipseItem
{

public:
	explicit MyEllipse(qreal x, qreal y,
					   QGraphicsEllipseItem *parent = nullptr);
	~MyEllipse();
};

#endif // MYELLIPSE_H
