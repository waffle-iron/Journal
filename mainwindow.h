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

private:
	Paper *paper;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
