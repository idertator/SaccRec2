#ifndef PROTOCOLTEST_H
#define PROTOCOLTEST_H

#include <QObject>

class ProtocolTest : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolTest(
            int angle, float duration, float variability, int count,
            bool calibration,
            QObject *parent = nullptr);

    int angle() const;
    float duration() const;
    float variability() const;
    int count() const;
    bool isCalibration() const;

    QString name() const;

public slots:
    void setAngle(int value);
    void setDuration(float value);
    void setVariability(float value);
    void setCount(int value);
    void setCalibration(bool value);

signals:
    void nameChanged(const QString&);

private:
    int _angle = 0;
    float _duration = 0.0;
    float _variability = 0.0;
    int _count = 0;
    bool _calibration = false;
};

#endif // PROTOCOLTEST_H
