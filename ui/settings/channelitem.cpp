#include <QPen>
#include <QPainter>
#include <QPoint>
#include <QPointF>

#include "channelitem.h"

#define CHANNEL_PEN_WIDTH 2

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

ChannelItem::ChannelItem(const QString &label, const QString &channel, const QVector<QLine> path, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    _label = label;
    _channel = channel;
    _path = path;
}

QRectF ChannelItem::boundingRect() const
{
    int minX = 1000000, maxX = 0, minY = 1000000, maxY = 0;
    for (int i = 0; i < _path.length(); i ++) {
        QLine line = _path.at(i);
        minX = min(minX, line.x1());
        minX = min(minX, line.x2());
        maxX = min(maxX, line.x1());
        maxX = min(maxX, line.x2());

        minY = min(minY, line.y1());
        minY = min(minY, line.y2());
        maxY = min(maxY, line.y1());
        maxY = min(maxY, line.y2());
    }

    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
}

void ChannelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen;
    pen.setWidth(CHANNEL_PEN_WIDTH);

    painter->setPen(pen);
    painter->drawLines(_path);
    painter->drawText(_path.last().p2() + QPoint(5, 15), _label);
    painter->drawText(_path.last().p2() + QPoint(-20, 4), _channel);
    painter->restore();
}
