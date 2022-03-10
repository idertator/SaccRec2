#include "wizard.h"

NewRecordingWizard::NewRecordingWizard(QWidget *parent)
    : QWizard{parent}
{
    _welcomePage = new NewRecordingWizardWelcomePage(this);

    addPage(_welcomePage);
}
