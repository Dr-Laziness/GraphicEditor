#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./Command/mycommand.h"

void MainWindow::configure_widget()
{
	connect(_ptr_scene, SIGNAL(scene_changes()), this, SLOT(check_command()));
	ui->graphicsView->setScene(_ptr_scene);

	ui->action_select->setChecked(true);
	ui->action_rectangle->setChecked(false);
	ui->action_ellipse->setChecked(false);
	ui->graphicsView->setCursor(QCursor(Qt::PointingHandCursor));

	ui->action_delete_selected->setEnabled(false);
	ui->action_redo->setEnabled(false);
	ui->action_undo->setEnabled(false);
}

void MainWindow::check_command()
{
	if(_ptr_scene->selectedItems().isEmpty())
		ui->action_delete_selected->setEnabled(false);
	else
		ui->action_delete_selected->setEnabled(true);

	if(_ptr_scene->can_undo())
		ui->action_undo->setEnabled(true);
	else
		ui->action_undo->setEnabled(false);

	if(_ptr_scene->can_redo())
		ui->action_redo->setEnabled(true);
	else
		ui->action_redo->setEnabled(false);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	_ptr_scene = new MyScene();

	configure_widget();
}

MainWindow::~MainWindow()
{
	delete _ptr_scene;
	delete ui;
}

void MainWindow::on_action_new_file_triggered()
{
	delete _ptr_scene;
	_ptr_scene = new MyScene();

	configure_widget();
}

void MainWindow::on_action_undo_triggered()
{
	_ptr_scene->undo();
}

void MainWindow::on_action_redo_triggered()
{
	_ptr_scene->redo();
}

void MainWindow::on_action_rectangle_triggered()
{
	ui->action_select->setChecked(false);
	ui->action_rectangle->setChecked(true);
	ui->action_ellipse->setChecked(false);
	_ptr_scene->set_tool_type(ToolType::Rectangle);
	ui->graphicsView->setCursor(QCursor(Qt::CrossCursor));
}

void MainWindow::on_action_ellipse_triggered()
{
	ui->action_select->setChecked(false);
	ui->action_rectangle->setChecked(false);
	ui->action_ellipse->setChecked(true);
	_ptr_scene->set_tool_type(ToolType::Ellipse);
	ui->graphicsView->setCursor(QCursor(Qt::CrossCursor));
}

void MainWindow::on_action_select_triggered()
{
	ui->action_select->setChecked(true);
	ui->action_rectangle->setChecked(false);
	ui->action_ellipse->setChecked(false);
	_ptr_scene->set_tool_type(ToolType::Selector);
	ui->graphicsView->setCursor(QCursor(Qt::PointingHandCursor));
}

void MainWindow::on_action_delete_selected_triggered()
{
	_ptr_scene->delete_selection();
}
