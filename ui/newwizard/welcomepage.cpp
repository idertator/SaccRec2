#include "welcomepage.h"

NewRecordingWizardWelcomePage::NewRecordingWizardWelcomePage(QWidget *parent)
    : QWizardPage{parent}
{
    setTitle(tr("Create New Recording"));

    _purposeLabel = new QLabel(tr("This wizard will guide you into the process of creating a new saccade recording"));

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_purposeLabel);

    setLayout(_mainLayout);
}
