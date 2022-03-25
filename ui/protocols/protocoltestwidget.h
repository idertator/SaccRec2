#ifndef PROTOCOLTESTWIDGET_H
#define PROTOCOLTESTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>

#include "models/protocoltest.h"

class ProtocolTestWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit ProtocolTestWidget(ProtocolTest *test, bool canAdd = true, QWidget *parent = nullptr);

private:
    ProtocolTest *_test = nullptr;
    bool _canAdd = false;

    QLabel *_angleLabel = nullptr;
    QSpinBox *_angleEdit = nullptr;
    QLabel *_durationLabel = nullptr;
    QDoubleSpinBox *_durationEdit = nullptr;
    QLabel *_variabilityLabel = nullptr;
    QDoubleSpinBox *_variabilityEdit = nullptr;
    QLabel *_countLabel = nullptr;
    QSpinBox *_countEdit = nullptr;

    QPushButton *_delButton = nullptr;
    QPushButton *_addButton = nullptr;

    QHBoxLayout *_buttonsLayout = nullptr;
    QGridLayout *_mainLayout = nullptr;
};

#endif // PROTOCOLTESTWIDGET_H
