#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <ui/deviceselector.h>
#include <ui/newwizard/wizard.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QToolBar *_mainToolbar = nullptr;

    QAction *_newRecordingAction = nullptr;
    QAction *_showSelectRecordingDeviceAction = nullptr;
    QAction *_quitAction = nullptr;

    NewRecordingWizard *_newRecordingWizard = nullptr;
    DeviceSelectorDialog *_deviceSelectionDialog = nullptr;
};
#endif // MAINWINDOW_H
