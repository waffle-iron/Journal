#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paper.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	paper = new Paper();
	ui->graphicsView->setScene(paper);
	ui->graphicsView->setSceneRect(QRectF(0, 0, 800, 600));

	setWindowTitle(tr("Journal"));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::penColor()
{
	QColor newColor = QColorDialog::getColor(paper->penColor());
	if (newColor.isValid())
		paper->setPenColor(newColor);
}

void MainWindow::penWidth()
{
	bool ok;
	int newWidth = QInputDialog::getInt(this, tr("Scribble"),
										tr("Select pen width:"),
										paper->penWidth(),
										1, 50, 1, &ok);
	if (ok)
		paper->setPenWidth(newWidth);
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Scribble"),
			tr("<p>The <b>Journal</b> app is a notes taking app inspired heavily by Microsoft OneNote.</p>"));
}

void MainWindow::on_actionMove_triggered()
{
	paper->setMoving(true);
}

void MainWindow::on_actionPaint_triggered()
{
	paper->setMoving(false);
}
