#include "protocolpage.h"
#include "models/protocol.h"

NewRecordingWizardProtocolPage::NewRecordingWizardProtocolPage(QWidget *parent)
        : QWizardPage{parent}
{
        setTitle(tr("Stimuli Setup"));

    _protocolWidget = new ProtocolWidget(new Protocol(tr("Default")));

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_protocolWidget);

    setLayout(_mainLayout);
}
