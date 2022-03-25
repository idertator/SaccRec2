#ifndef NEWRECORDINGWIZARD_H
#define NEWRECORDINGWIZARD_H

#include <QWidget>
#include <QWizard>

#include "welcomepage.h"
#include "subjectpage.h"
#include "protocolpage.h"

class NewRecordingWizard : public QWizard
{
    Q_OBJECT
public:
    explicit NewRecordingWizard(QWidget *parent = nullptr);

private:
    NewRecordingWizardWelcomePage *_welcomePage = nullptr;
    NewRecordingWizardSubjectPage *_subjectPage = nullptr;
    NewRecordingWizardProtocolPage *_protocolPage = nullptr;
};

#endif // NEWRECORDINGWIZARD_H
