#include "protocolwidget.h"

ProtocolWidget::ProtocolWidget(Protocol *protocol, QWidget *parent)
    : QWidget{parent}
{
    _protocol = protocol;

    _nameLabel = new QLabel(tr("Protocol Name"));
    _nameEdit = new QLineEdit();
    _openButton = new QPushButton(tr("Open"));
    _saveButton = new QPushButton(tr("Save"));

    _topLayout = new QHBoxLayout();
    _topLayout->addWidget(_nameLabel);
    _topLayout->addWidget(_nameEdit);
    _topLayout->addWidget(_openButton);
    _topLayout->addWidget(_saveButton);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addLayout(_topLayout);
    _mainLayout->addStretch();

    setLayout(_mainLayout);
}
