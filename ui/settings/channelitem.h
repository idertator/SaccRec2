#ifndef CHANNELITEM_H
#define CHANNELITEM_H

#include <QGraphicsItem>
#include <QWidget>
#include <QVector>
#include <QLine>

class ChannelItem : public QGraphicsItem
{
public:
    explicit ChannelItem(const QString &label, const QString &channel, const QVector<QLine> path, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setInputChannel(const QString &channel);

private:
    QString _label;
    QString _channel;
    QVector<QLine> _path;
};

#endif // CHANNELITEM_H
