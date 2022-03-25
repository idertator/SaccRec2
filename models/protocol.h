#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QString>
#include <QList>

#include "protocoltest.h"

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(const QString &name, QList<ProtocolTest *> *tests = nullptr, QObject *parent = nullptr);
    static QList<ProtocolTest *> *defaultTests();

private:
    QString _name = "";
    QList<ProtocolTest *> *_tests = nullptr;
};

#endif // PROTOCOL_H
