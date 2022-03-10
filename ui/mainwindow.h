#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <ui/newwizard/wizard.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();

    QToolBar *_mainToolbar = nullptr;

    QAction *_newRecordingAction = nullptr;
    QAction *_showSelectRecordingDeviceAction = nullptr;
    QAction *_quitAction = nullptr;

    NewRecordingWizard *_newRecordingWizard = nullptr;

private slots:
    void showSelectRecordingDevice();
};
#endif // MAINWINDOW_H
