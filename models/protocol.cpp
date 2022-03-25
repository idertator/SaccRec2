#include "protocol.h"

Protocol::Protocol(const QString &name, QList<ProtocolTest *> *tests, QObject *parent)
    : QObject{parent}
{
    _name = name;
    if (tests == nullptr) {
        _tests = Protocol::defaultTests();
    } else {
        _tests = tests;
    }
}

QList<ProtocolTest *> *Protocol::defaultTests()
{
    QList<ProtocolTest *> *result = new QList<ProtocolTest *>();

    result->append(new ProtocolTest(30, 3.0, 50.0, 10, true));
    result->append(new ProtocolTest(30, 3.0, 50.0, 20, false));
    result->append(new ProtocolTest(30, 3.0, 50.0, 10, true));

    return result;
}
