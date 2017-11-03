#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>

// AddCommand
class AddCommand : public QUndoCommand
{
	QAbstractGraphicsShapeItem *_ptr_item;
	QGraphicsScene *_ptr_scene;

public:
	explicit AddCommand(QAbstractGraphicsShapeItem *item, QGraphicsScene *scene,
			   QUndoCommand *parent = nullptr);
	~AddCommand();

	void undo() override;
	void redo() override;
};

// DeleteCommand
class DeleteCommand : public QUndoCommand
{
	QAbstractGraphicsShapeItem *_ptr_item;
	QGraphicsScene *_ptr_scene;

public:
	explicit DeleteCommand(QGraphicsScene *scene,
						   QUndoCommand *parent = nullptr);
	~DeleteCommand();

	void undo() override;
	void redo() override;
};

// MoveCommand
class MoveCommand : public QUndoCommand
{
	QAbstractGraphicsShapeItem *_ptr_item;
	QPointF _old_pos;
	QPointF _new_pos;

public:
	enum {Id = 1234};

	explicit MoveCommand(QAbstractGraphicsShapeItem *item,
						const QPointF &old_pos, QUndoCommand *parent = nullptr);
	~MoveCommand();

	void undo() override;
	void redo() override;
	bool mergeWith(const QUndoCommand *command) override;
	int id() const override { return Id; }
};

#endif // MYCOMMAND_H
