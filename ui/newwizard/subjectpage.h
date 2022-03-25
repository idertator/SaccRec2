#ifndef SUBJECTPAGE_H
#define SUBJECTPAGE_H

#include <QWizardPage>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>

class NewRecordingWizardSubjectPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit NewRecordingWizardSubjectPage(QWidget *parent = nullptr);

    bool isComplete() const override;

private slots:
    void onNameChanged();

private:
    QLineEdit *_nameEdit = nullptr;
    QComboBox *_genderCombo = nullptr;
    QDateEdit *_bornDate = nullptr;
    QComboBox *_statusCombo = nullptr;

    QFormLayout *_mainLayout;
};

#endif // SUBJECTPAGE_H
