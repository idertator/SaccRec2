#include "electrodeitem.h"

#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>

#define ELECTRODE_PEN_WIDTH 2
#define ELECTRODE_ITEM_WIDTH 20
#define ELECTRODE_OUTER_RADIUS ELECTRODE_ITEM_WIDTH / 2 - 1
#define ELECTRODE_INNER_RADIUS ELECTRODE_ITEM_WIDTH / 4
#define ELECTRODE_CENTER ELECTRODE_ITEM_WIDTH / 2

ElectrodeItem::ElectrodeItem(const QString &mark, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    _mark = mark;
}

QRectF ElectrodeItem::boundingRect() const
{
    const float side = ELECTRODE_ITEM_WIDTH + ELECTRODE_PEN_WIDTH;
    return QRectF(0, _upwards ? -30 : 30, side, side + 30);
}

void ElectrodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen;
    pen.setWidth(ELECTRODE_PEN_WIDTH);

    painter->drawText(
        ELECTRODE_CENTER - ELECTRODE_ITEM_WIDTH, ELECTRODE_CENTER + (_upwards ? - 30 : 15),
        ELECTRODE_ITEM_WIDTH * 2, 30,
        Qt::AlignHCenter, _mark
    );

    painter->setPen(pen);
    painter->drawEllipse(QPointF(ELECTRODE_CENTER, ELECTRODE_CENTER), ELECTRODE_OUTER_RADIUS, ELECTRODE_OUTER_RADIUS);

    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(ELECTRODE_CENTER, ELECTRODE_CENTER), ELECTRODE_INNER_RADIUS, ELECTRODE_INNER_RADIUS);
    painter->restore();
}

void ElectrodeItem::setMark(const QString &mark, bool upwards)
{
    _mark = mark;
    _upwards = upwards;
    update();
}
