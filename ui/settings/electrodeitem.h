#ifndef ELECTRODEITEM_H
#define ELECTRODEITEM_H

#include <QGraphicsItem>

class ElectrodeItem : public QGraphicsItem
{
public:
    explicit ElectrodeItem(const QString &mark = "", QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void setMark(const QString &mark, bool upwards = true);

private:
    QString _mark = "";
    bool _upwards = true;
};

#endif // ELECTRODEITEM_H
