#include "mainwindow.h"

#include <QMenuBar>
#include <QIcon>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Saccade Recorder 2");

    _mainToolbar = this->addToolBar(tr("Main Toolbar"));

    _newRecordingAction = _mainToolbar->addAction(QIcon(":/icons/new.svg"), tr("&New Recording"));
    _mainToolbar->addSeparator();
    _showSelectRecordingDeviceAction = _mainToolbar->addAction(QIcon(":/icons/bluetooth.svg"), tr("&Select Recording Device"));
    _showSettingsAction = _mainToolbar->addAction(QIcon(":/icons/settings.svg"), tr("Show &Settings"));
    _mainToolbar->addSeparator();
    _quitAction = _mainToolbar->addAction(QIcon(":/icons/exit.svg"), tr("&Quit"));

    _newRecordingWizard = new NewRecordingWizard(this);
    _deviceSelectionDialog = new DeviceSelectorDialog(this);
    _settingsDialog = new SettingsDialog(this);

    connect(_newRecordingAction, &QAction::triggered,
            _newRecordingWizard, &NewRecordingWizard::exec);

    connect(_showSelectRecordingDeviceAction, &QAction::triggered,
            _deviceSelectionDialog, &DeviceSelectorDialog::exec);

    connect(_showSettingsAction, &QAction::triggered,
            _settingsDialog, &SettingsDialog::exec);

    connect(_quitAction, &QAction::triggered,
            QCoreApplication::instance(), &QCoreApplication::quit,
            Qt::QueuedConnection);
}
