#ifndef CHANNELGROUP_H
#define CHANNELGROUP_H

#include <QWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

class ChannelGroup : public QGroupBox
{
    Q_OBJECT

public:
    explicit ChannelGroup(const QString &label, const QString &eye1, const QString &eye2, QWidget *parent = nullptr);

    bool isUsed();
    void setUsed(bool value = true);

    QString inputChannel() const;
    void setInputChannel(const QString &value);

    QString eye1Mark() const;
    void setEye1Mark(const QString &value);

    QString eye2Mark() const;
    void setEye2Mark(const QString &value);

signals:
    void useChannelChanged(bool use);
    void inputChannelChanged(const QString &channel);
    void eye1MarkChanged(const QString &mark);
    void eye2MarkChanged(const QString &mark);

private slots:
    void onUseChannelStateChanged(int state);
    void onInputChannelTextChanged(const QString &text);
    void onEye1TextChanged(const QString &text);
    void onEye2TextChanged(const QString &text);

private:
    QFormLayout *_mainLayout = nullptr;

    QCheckBox *_useChannel = nullptr;
    QComboBox *_channelInput = nullptr;
    QLineEdit *_eye1Mark = nullptr;
    QLineEdit *_eye2Mark = nullptr;
};

#endif // CHANNELGROUP_H
