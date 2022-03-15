#ifndef ELECTRODESPAGE_H
#define ELECTRODESPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "electrodeitem.h"

class ElectrodesPage : public QWidget
{
    Q_OBJECT
public:
    explicit ElectrodesPage(QWidget *parent = nullptr);

private:
    QGraphicsView *_schema = nullptr;
    QGraphicsScene *_scene = nullptr;

    QGraphicsSvgItem *_face = nullptr;
    ElectrodeItem *_leftElectrode = nullptr;
    ElectrodeItem *_rightElectrode = nullptr;
    ElectrodeItem *_topElectrode = nullptr;
    ElectrodeItem *_bottomElectrode = nullptr;

    QVBoxLayout *_mainLayout = nullptr;
};

#endif // ELECTRODESPAGE_H
