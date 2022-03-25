#ifndef PROTOCOLPAGE_H
#define PROTOCOLPAGE_H

#include <QWizardPage>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include "ui/protocols/protocolwidget.h"


class NewRecordingWizardProtocolPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit NewRecordingWizardProtocolPage(QWidget *parent = nullptr);

private:
    ProtocolWidget *_protocolWidget = nullptr;

    QVBoxLayout *_mainLayout = nullptr;
};

#endif // PROTOCOLPAGE_H
