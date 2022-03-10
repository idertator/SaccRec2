#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <ui/newwizard/wizard.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();

    QMenu *_fileMenu = nullptr;

    QAction *_newRecordingAction = nullptr;
    QAction *_quitAction = nullptr;

    NewRecordingWizard *_newRecordingWizard = nullptr;
};
#endif // MAINWINDOW_H
