#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paper.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	paper = new Paper;
	setCentralWidget(paper);

	setWindowTitle(tr("Journal"));
	resize(500, 500);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) event->accept();
	else event->ignore();
}

void MainWindow::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this,
								   tr("Open File"), QDir::currentPath());
		if (!fileName.isEmpty())
			paper->openImage(fileName);
	}
}

void MainWindow::save()
{
	QAction *action = qobject_cast<QAction *>(sender());
	QByteArray fileFormat = action->data().toByteArray();
	saveFile(fileFormat);
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

bool MainWindow::maybeSave()
{
	if (paper->isModified())
		return saveFile("png");
	return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
	QString fileName = QDir::currentPath() + "/untitled." + fileFormat;
	return paper->saveImage(fileName, fileFormat.constData());
}
