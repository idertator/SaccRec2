#include "mainwindow.h"

#include <QMenuBar>
#include <QIcon>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    setWindowTitle("Saccade Recorder 2");

    QMenuBar *bar = this->menuBar();

    _fileMenu = bar->addMenu(tr("&File"));

    _newRecordingAction = _fileMenu->addAction(QIcon(":/icons/new.svg"), tr("&New Recording"));
    _fileMenu->addSeparator();
    _quitAction = _fileMenu->addAction(QIcon(":/icons/exit.svg"), tr("&Quit"));

    _newRecordingWizard = new NewRecordingWizard(this);

    connect(_newRecordingAction, &QAction::triggered,
            _newRecordingWizard, &NewRecordingWizard::exec);

    connect(_quitAction, &QAction::triggered,
            QCoreApplication::instance(), &QCoreApplication::quit,
            Qt::QueuedConnection);
}

