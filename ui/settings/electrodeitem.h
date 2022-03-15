#ifndef ELECTRODEITEM_H
#define ELECTRODEITEM_H

#include <QGraphicsItem>

class ElectrodeItem : public QGraphicsItem
{
public:
    explicit ElectrodeItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ELECTRODEITEM_H
