#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog{parent}
{
    _electrodesPage = new ElectrodesPage(this);

    _tabWidget = new QTabWidget();
    _tabWidget->addTab(_electrodesPage, tr("Electrodes"));

    _saveButton = new QPushButton(tr("Save"));
    _cancelButton = new QPushButton(tr("Cancel"));

    _buttonsLayout = new QHBoxLayout();
    _buttonsLayout->addStretch();
    _buttonsLayout->addWidget(_saveButton);
    _buttonsLayout->addWidget(_cancelButton);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_tabWidget);
    _mainLayout->addLayout(_buttonsLayout);

    setLayout(_mainLayout);

    connect(_cancelButton, &QPushButton::pressed,
            this, &QDialog::hide);
}
