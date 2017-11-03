#include "myscene.h"

MyScene::MyScene(QGraphicsScene *parent) :
	QGraphicsScene(parent),
	_ptr_moving_item(nullptr)
{
	_ptr_undo_stack = new QUndoStack(this);
	setSceneRect(100, 100, 800, 600);
}

MyScene::~MyScene()
{
	delete _ptr_undo_stack;
	delete _ptr_moving_item;
}

ToolType MyScene::tool_type() const
{
	return _tool_type;
}

void MyScene::set_tool_type(const ToolType &tool_type)
{
	_tool_type = tool_type;
}

void MyScene::delete_selection()
{
	if (selectedItems().isEmpty())
		return;

	_ptr_undo_stack->push(new DeleteCommand(this));
	emit scene_changes();
}

void MyScene::undo()
{
	_ptr_undo_stack->undo();
	emit scene_changes();
}

void MyScene::redo()
{
	_ptr_undo_stack->redo();
	emit scene_changes();
}

bool MyScene::can_undo()
{
	return _ptr_undo_stack->canUndo();
}

bool MyScene::can_redo()
{
	return _ptr_undo_stack->canRedo();
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF mouse_pos(event->buttonDownScenePos(Qt::LeftButton).x(),
					  event->buttonDownScenePos(Qt::LeftButton).y());
	switch (_tool_type)
	{
		case ToolType::Selector:
		{
			const QList<QGraphicsItem *> item_list = items(mouse_pos);
			_ptr_moving_item = item_list.isEmpty() ?nullptr : item_list.first();

			if(_ptr_moving_item != nullptr && event->button() == Qt::LeftButton)
				_old_pos = _ptr_moving_item->pos();
			break;
		}
		case ToolType::Rectangle:
		{
			MyRectangle *new_rect = new MyRectangle(mouse_pos.x(),
													mouse_pos.y());
			_ptr_undo_stack->push(new AddCommand(new_rect, this));
			clearSelection();
			break;
		}
		case ToolType::Ellipse:
		{
			MyEllipse *new_Ellipse = new MyEllipse(mouse_pos.x(),
												   mouse_pos.y());
			_ptr_undo_stack->push(new AddCommand(new_Ellipse, this));
			clearSelection();
			break;
		}
		default:
			break;
	}
	emit scene_changes();
	QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(_tool_type == ToolType::Selector && _ptr_moving_item != nullptr &&
			event->button() == Qt::LeftButton)
	{
		if(_old_pos != _ptr_moving_item->pos())
			_ptr_undo_stack->push(new MoveCommand(
				qgraphicsitem_cast<QAbstractGraphicsShapeItem *>(_ptr_moving_item),
				 _old_pos));

		_ptr_moving_item = nullptr;
	}
	emit scene_changes();
	QGraphicsScene::mouseReleaseEvent(event);
}
