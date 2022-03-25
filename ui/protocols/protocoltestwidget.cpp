#include "protocoltestwidget.h"


ProtocolTestWidget::ProtocolTestWidget(ProtocolTest *test, bool canAdd, QWidget *parent)
    : QGroupBox{parent}
{
    _test = test;
    _canAdd = false;

    _angleLabel = new QLabel(tr("Angle"));

    _angleEdit = new QSpinBox();
    _angleEdit->setValue(test->angle());
    _angleEdit->setRange(10, 60);
    _angleEdit->setSingleStep(1);
    _angleEdit->setSuffix(" \u00B0");
    _angleEdit->setFixedWidth(60);
    _angleEdit->setToolTip(tr("Stimulus angle amplitude"));
    _angleEdit->setEnabled(!test->isCalibration());

    connect(_angleEdit, &QSpinBox::valueChanged,
            _test, &ProtocolTest::setAngle);

    _durationLabel = new QLabel(tr("Duration"));

    _durationEdit = new QDoubleSpinBox();
    _durationEdit->setValue(test->duration());
    _durationEdit->setSingleStep(0.01);
    _durationEdit->setSuffix(tr(" sec"));
    _durationEdit->setFixedWidth(80);
    _durationEdit->setToolTip(tr("Fixation mean duration"));
    _durationEdit->setEnabled(!test->isCalibration());

    connect(_durationEdit, &QDoubleSpinBox::valueChanged,
            _test, &ProtocolTest::setDuration);

    _variabilityLabel = new QLabel(tr("Variability"));

    _variabilityEdit = new QDoubleSpinBox();
    _variabilityEdit->setValue(test->variability());
    _variabilityEdit->setSingleStep(0.01);
    _variabilityEdit->setSuffix(" %");
    _variabilityEdit->setFixedWidth(80);
    _variabilityEdit->setToolTip(tr("Fixation duration variability"));
    _variabilityEdit->setEnabled(!test->isCalibration());

    connect(_variabilityEdit, &QDoubleSpinBox::valueChanged,
            _test, &ProtocolTest::setVariability);

    _countLabel = new QLabel(tr("Count"));

    _countEdit = new QSpinBox();
    _countEdit->setValue(test->count());
    _countEdit->setRange(5, 100);
    _countEdit->setSingleStep(1);
    _countEdit->setFixedWidth(60);
    _countEdit->setToolTip(tr("Saccades count"));
    _countEdit->setEnabled(!test->isCalibration());

    connect(_countEdit, &QSpinBox::valueChanged,
            _test, &ProtocolTest::setCount);

    _buttonsLayout = new QHBoxLayout();

    if (!test->isCalibration()) {
        _delButton = new QPushButton("-");
        _buttonsLayout->addWidget(_delButton);
    }

    if (canAdd) {
        _addButton = new QPushButton("+");
        _buttonsLayout->addWidget(_addButton);
    }

    _mainLayout = new QGridLayout();
    _mainLayout->addWidget(_angleLabel, 0, 0);
    _mainLayout->addWidget(_angleEdit, 1, 0);
    _mainLayout->addWidget(_durationLabel, 0, 1);
    _mainLayout->addWidget(_durationEdit, 1, 1);
    _mainLayout->addWidget(_variabilityLabel, 0, 2);
    _mainLayout->addWidget(_variabilityEdit, 1, 2);
    _mainLayout->addWidget(_countLabel, 0, 3);
    _mainLayout->addWidget(_countEdit, 1, 3);
    _mainLayout->setColumnStretch(4, 1);
    _mainLayout->addLayout(_buttonsLayout, 1, 5);

    setLayout(_mainLayout);
}
