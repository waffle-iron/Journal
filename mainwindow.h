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
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void open();
	void save();
	void penColor();
	void penWidth();
	void about();

private:
	Paper *paper;

	bool maybeSave();
	bool saveFile(const QByteArray &fileFormat);

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
