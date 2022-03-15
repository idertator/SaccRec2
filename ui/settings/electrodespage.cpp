#include "electrodespage.h"

ElectrodesPage::ElectrodesPage(QWidget *parent)
    : QWidget{parent}
{
    _scene = new QGraphicsScene();

    _face = new QGraphicsSvgItem(":/settings/face.svg");
    _leftElectrode = new ElectrodeItem();
    _rightElectrode = new ElectrodeItem();
    _topElectrode = new ElectrodeItem();
    _bottomElectrode = new ElectrodeItem();

    _scene->addItem(_face);
    _scene->addItem(_leftElectrode);
    _scene->addItem(_rightElectrode);
    _scene->addItem(_topElectrode);
    _scene->addItem(_bottomElectrode);

    _leftElectrode->moveBy(105, 305);
    _rightElectrode->moveBy(340, 305);
    _topElectrode->moveBy(285, 275);
    _bottomElectrode->moveBy(285, 340);

    _schema = new QGraphicsView(_scene);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_schema);

    setLayout(_mainLayout);
}
