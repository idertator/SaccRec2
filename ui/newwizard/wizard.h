#ifndef NEWRECORDINGWIZARD_H
#define NEWRECORDINGWIZARD_H

#include <QWidget>
#include <QWizard>

#include "welcomepage.h"
#include "subjectpage.h"

class NewRecordingWizard : public QWizard
{
    Q_OBJECT
public:
    explicit NewRecordingWizard(QWidget *parent = nullptr);

private:
    NewRecordingWizardWelcomePage *_welcomePage = nullptr;
    NewRecordingWizardSubjectPage *_subjectPage = nullptr;
};

#endif // NEWRECORDINGWIZARD_H
