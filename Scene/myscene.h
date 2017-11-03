#ifndef MYSCENE_H
#define MYSCENE_H

#include "./Items/myellipse.h"
#include "./Items/myrectangle.h"

#include "./Command/mycommand.h"

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>

#include <QUndoStack>

enum class ToolType
{
	Selector,
	Rectangle,
	Ellipse
};

class MyScene : public QGraphicsScene
{
	Q_OBJECT

	QGraphicsItem *_ptr_moving_item;
	QPointF _old_pos;

	ToolType _tool_type{ToolType::Selector};

	QUndoStack *_ptr_undo_stack;

public:
	explicit MyScene(QGraphicsScene *parent = nullptr);
	~MyScene();

	ToolType tool_type() const;
	void set_tool_type(const ToolType &tool_type);

	void delete_selection();

	void undo();
	void redo();

	bool can_undo();
	bool can_redo();

signals:
	void scene_changes();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYSCENE_H
