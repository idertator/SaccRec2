#include "channelgroup.h"

ChannelGroup::ChannelGroup(const QString &label, const QString &eye1, const QString &eye2, QWidget *parent)
    : QGroupBox{parent}
{
    setTitle(label);

    _useChannel = new QCheckBox(tr("Use Channel"));
    _useChannel->setChecked(true);

    _channelInput = new QComboBox();
    _channelInput->addItems({"A1", "A2", "A3", "A4", "A5", "A6"});

    _eye1Mark = new QLineEdit();
    _eye1Mark->setMaxLength(3);

    _eye2Mark = new QLineEdit();
    _eye2Mark->setMaxLength(3);

    _mainLayout = new QFormLayout();
    _mainLayout->addWidget(_useChannel);
    _mainLayout->addRow(tr("Input"), _channelInput);
    _mainLayout->addRow(eye1, _eye1Mark);
    _mainLayout->addRow(eye2, _eye2Mark);

    setLayout(_mainLayout);

    connect(_useChannel, &QCheckBox::stateChanged,
            this, &ChannelGroup::onUseChannelStateChanged);

    connect(_channelInput, &QComboBox::currentTextChanged,
            this, &ChannelGroup::onInputChannelTextChanged);

    connect(_eye1Mark, &QLineEdit::textChanged,
            this, &ChannelGroup::onEye1TextChanged);

    connect(_eye2Mark, &QLineEdit::textChanged,
            this, &ChannelGroup::onEye2TextChanged);
}

bool ChannelGroup::isUsed()
{
    return _useChannel->isChecked();
}

void ChannelGroup::setUsed(bool value)
{
    _useChannel->setChecked(value);
}

QString ChannelGroup::inputChannel() const
{
    return _channelInput->currentText();
}

void ChannelGroup::setInputChannel(const QString &value)
{
    _channelInput->setCurrentText(value);
}

QString ChannelGroup::eye1Mark() const
{
    return _eye1Mark->text();
}

void ChannelGroup::setEye1Mark(const QString &value)
{
    _eye1Mark->setText(value);
}

QString ChannelGroup::eye2Mark() const
{
    return _eye2Mark->text();
}

void ChannelGroup::setEye2Mark(const QString &value)
{
    _eye2Mark->setText(value);
}

void ChannelGroup::onUseChannelStateChanged(int state)
{
    bool checked = state == Qt::Checked;
    _channelInput->setEnabled(checked);
    _eye1Mark->setEnabled(checked);
    _eye2Mark->setEnabled(checked);
    emit useChannelChanged(checked);
}

void ChannelGroup::onInputChannelTextChanged(const QString &text)
{
    emit inputChannelChanged(text);
}

void ChannelGroup::onEye1TextChanged(const QString &text)
{
    emit eye1MarkChanged(text);
}

void ChannelGroup::onEye2TextChanged(const QString &text)
{
    emit eye2MarkChanged(text);
}
