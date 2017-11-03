#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./Scene/myscene.h"

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainWindow *ui;

	MyScene *_ptr_scene;

	void configure_widget();

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void check_command();

	void on_action_new_file_triggered();
	void on_action_undo_triggered();
	void on_action_redo_triggered();
	void on_action_rectangle_triggered();
	void on_action_ellipse_triggered();
	void on_action_select_triggered();
	void on_action_delete_selected_triggered();
};

#endif // MAINWINDOW_H
