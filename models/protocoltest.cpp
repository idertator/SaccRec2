#include "protocoltest.h"

#include <QStringBuilder>

ProtocolTest::ProtocolTest(int angle, float duration, float variability, int count, bool calibration, QObject *parent)
    : QObject{parent}
{
    _angle = angle;
    _duration = duration;
    _variability = variability;
    _count = count;
    _calibration = calibration;
}

int ProtocolTest::angle() const
{
    return _angle;
}

float ProtocolTest::duration() const
{
    return _duration;
}

float ProtocolTest::variability() const
{
    return _variability;
}

int ProtocolTest::count() const
{
    return _count;
}

bool ProtocolTest::isCalibration() const
{
    return _calibration;
}

QString ProtocolTest::name() const
{
    if (_calibration) {
        return QString(tr("Horizontal Calibration %d\u00B0").arg(_angle));
    }
    return QString(tr("Horizontal Saccadic %d\u00B0").arg(_angle));
}

void ProtocolTest::setAngle(int value)
{
    _angle = value;
    emit nameChanged(name());
}

void ProtocolTest::setDuration(float value)
{
    _duration = value;
}

void ProtocolTest::setVariability(float value)
{
    _variability = value;
}

void ProtocolTest::setCount(int value)
{
    _count = value;
}
void ProtocolTest::setCalibration(bool value)
{
    _calibration = value;
    emit nameChanged(name());
}
