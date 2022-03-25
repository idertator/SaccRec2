#include "wizard.h"

NewRecordingWizard::NewRecordingWizard(QWidget *parent)
    : QWizard{parent}
{
    _welcomePage = new NewRecordingWizardWelcomePage(this);
    _subjectPage = new NewRecordingWizardSubjectPage(this);
    _protocolPage = new NewRecordingWizardProtocolPage(this);

    addPage(_welcomePage);
    addPage(_subjectPage);
    addPage(_protocolPage);
}
