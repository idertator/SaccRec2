#include "subjectpage.h"

NewRecordingWizardSubjectPage::NewRecordingWizardSubjectPage(QWidget *parent)
    : QWizardPage{parent}
{
    setTitle(tr("Subject Info"));

    _nameEdit = new QLineEdit();

    _genderCombo = new QComboBox();
    _genderCombo->addItem(tr("Unknowwn"), "unknown");
    _genderCombo->addItem(tr("Male"), "male");
    _genderCombo->addItem(tr("Female"), "female");

    _bornDate = new QDateEdit();
    _bornDate->setCalendarPopup(true);

    _statusCombo = new QComboBox();
    _statusCombo->addItem(tr("Unknown"), "unknown");
    _statusCombo->addItem(tr("Control"), "control");
    _statusCombo->addItem(tr("Presymptomatic"), "presymptomatic");
    _statusCombo->addItem(tr("Sick"), "sick");

    _mainLayout = new QFormLayout();
    _mainLayout->addRow(tr("Name"), _nameEdit);
    _mainLayout->addRow(tr("Gender"), _genderCombo);
    _mainLayout->addRow(tr("Borndate"), _bornDate);
    _mainLayout->addRow(tr("Status"), _statusCombo);

    setLayout(_mainLayout);

    registerField("name", _nameEdit);
    registerField("gender", _genderCombo);
    registerField("borndate", _bornDate);
    registerField("status", _statusCombo);

    connect(_nameEdit, &QLineEdit::textChanged,
            this, &NewRecordingWizardSubjectPage::onNameChanged);
}

bool NewRecordingWizardSubjectPage::isComplete() const
{
    return !_nameEdit->text().trimmed().isEmpty();
}

void NewRecordingWizardSubjectPage::onNameChanged()
{
    emit completeChanged();
}
