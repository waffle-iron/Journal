#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Paper;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:

private slots:
	void penColor();
	void penWidth();
	void about();

	void on_actionDraw_triggered();
	void on_actionMove_triggered();
	void on_actionText_triggered();
	void on_actionSelect_triggered();

private:
	Paper *paper;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
