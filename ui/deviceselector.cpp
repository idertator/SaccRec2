#include "deviceselector.h"
#include "adq/bitalino.h"


DeviceSelectorDialog::DeviceSelectorDialog(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle(tr("Select the recording device ..."));

    _devicesList = new QListWidget();

    _scanButton = new QPushButton(tr("Scan"));
    _selectButton = new QPushButton(tr("Select"));
    _cancelButton = new QPushButton(tr("Cancel"));

    _buttonsLayout = new QHBoxLayout();
    _buttonsLayout->addWidget(_scanButton);
    _buttonsLayout->addStretch();
    _buttonsLayout->addWidget(_selectButton);
    _buttonsLayout->addWidget(_cancelButton);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_devicesList);
    _mainLayout->addLayout(_buttonsLayout);

    setLayout(_mainLayout);

    connect(_scanButton, &QPushButton::pressed,
            this, &DeviceSelectorDialog::scanDevices);

    connect(_cancelButton, &QPushButton::pressed,
            this, &QDialog::hide);
}

void DeviceSelectorDialog::scanDevices() {
    BITalino::VDevInfo info = BITalino::find();
    for (const auto &device: info) {
        qDebug() << QString::fromUtf8(device.macAddr) << QString::fromUtf8(device.name) << "\n";
    }
}
