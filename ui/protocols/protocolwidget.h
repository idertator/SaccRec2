#ifndef PROTOCOLWIDGET_H
#define PROTOCOLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "models/protocol.h"

class ProtocolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProtocolWidget(Protocol *protocol, QWidget *parent = nullptr);

private:
    Protocol *_protocol = nullptr;

    QLabel *_nameLabel = nullptr;
    QLineEdit *_nameEdit = nullptr;
    QPushButton *_openButton = nullptr;
    QPushButton *_saveButton = nullptr;
    QHBoxLayout *_topLayout = nullptr;

    QVBoxLayout *_mainLayout = nullptr;
};

#endif // PROTOCOLWIDGET_H
