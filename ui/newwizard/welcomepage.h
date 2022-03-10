#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>

class NewRecordingWizardWelcomePage : public QWizardPage
{
    Q_OBJECT
public:
    explicit NewRecordingWizardWelcomePage(QWidget *parent = nullptr);

private:
    QVBoxLayout *_mainLayout = nullptr;
    QLabel *_purposeLabel = nullptr;
};

#endif // WELCOMEPAGE_H
