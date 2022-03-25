#include "wizard.h"

NewRecordingWizard::NewRecordingWizard(QWidget *parent)
    : QWizard{parent}
{
    _welcomePage = new NewRecordingWizardWelcomePage(this);
    _subjectPage = new NewRecordingWizardSubjectPage(this);

    addPage(_welcomePage);
    addPage(_subjectPage);
}
