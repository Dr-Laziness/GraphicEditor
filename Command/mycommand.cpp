#include "mycommand.h"

// AddCommand
AddCommand::AddCommand(QAbstractGraphicsShapeItem *item, QGraphicsScene *scene,
					   QUndoCommand *parent) :
	QUndoCommand(parent),
	_ptr_item(item),
	_ptr_scene(scene)
{
	_ptr_scene->update();
}

AddCommand::~AddCommand()
{
	if (!_ptr_item->scene())
		delete _ptr_item;
}

void AddCommand::undo()
{
	_ptr_scene->removeItem(_ptr_item);
	_ptr_scene->update();
}

void AddCommand::redo()
{
	_ptr_scene->addItem(_ptr_item);
	_ptr_scene->update();
}

// DeleteCommand
DeleteCommand::DeleteCommand(QGraphicsScene *scene, QUndoCommand *parent) :
QUndoCommand(parent),
_ptr_scene(scene)
{
QList<QGraphicsItem *> list = scene->selectedItems();
list.first()->setSelected(false);
_ptr_item = static_cast<QAbstractGraphicsShapeItem *>(list.first());
}

DeleteCommand::~DeleteCommand()
{

}

void DeleteCommand::undo()
{
_ptr_scene->addItem(_ptr_item);
_ptr_scene->update();
}

void DeleteCommand::redo()
{
_ptr_scene->removeItem(_ptr_item);
}

// MoveCommand
MoveCommand::MoveCommand(QAbstractGraphicsShapeItem *item,
						 const QPointF &old_pos, QUndoCommand *parent) :
	QUndoCommand(parent),
	_ptr_item(item),
	_old_pos(old_pos),
	_new_pos(item->pos())
{

}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::undo()
{
	_ptr_item->setPos(_old_pos);
	_ptr_item->scene()->update();
}

void MoveCommand::redo()
{
	_ptr_item->setPos(_new_pos);
}

bool MoveCommand::mergeWith(const QUndoCommand *command)
{
	const MoveCommand *move_command = static_cast<const MoveCommand *>(command);
	QAbstractGraphicsShapeItem *item = move_command->_ptr_item;

	if (_ptr_item != item)
		return false;

	_new_pos = item->pos();
	return true;
}
