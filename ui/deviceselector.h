#ifndef DEVICESELECTOR_H
#define DEVICESELECTOR_H

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DeviceSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceSelectorDialog(QWidget *parent = nullptr);

private slots:
    void scanDevices();

private:
    QPushButton *_scanButton = nullptr;
    QPushButton *_selectButton = nullptr;
    QPushButton *_cancelButton = nullptr;
    QListWidget *_devicesList = nullptr;

    QVBoxLayout *_mainLayout = nullptr;
    QHBoxLayout *_buttonsLayout = nullptr;
};

#endif // DEVICESELECTOR_H
