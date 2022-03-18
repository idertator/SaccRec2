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

    QVector<QLine> horizontalPath(3);
    horizontalPath[0] = QLine(115, 315, 115, 500);
    horizontalPath[1] = QLine(350, 315, 350, 500);
    horizontalPath[2] = QLine(350, 500, 30, 500);

    _horizontalChannel = new ChannelItem(tr("Horizontal Channel"), "A0", horizontalPath);

    QVector<QLine> verticalPath(4);
    verticalPath[0] = QLine(295, 285, 240, 285);
    verticalPath[1] = QLine(295, 350, 240, 350);
    verticalPath[2] = QLine(240, 285, 240, 525);
    verticalPath[3] = QLine(240, 525, 30, 525);

    _verticalChannel = new ChannelItem(tr("Vertical Channel"), "A1", verticalPath);

    _scene->addItem(_face);
    _scene->addItem(_leftElectrode);
    _scene->addItem(_rightElectrode);
    _scene->addItem(_topElectrode);
    _scene->addItem(_bottomElectrode);

    _scene->addItem(_horizontalChannel);
    _scene->addItem(_verticalChannel);

    _leftElectrode->moveBy(105, 305);
    _rightElectrode->moveBy(340, 305);
    _topElectrode->moveBy(285, 275);
    _bottomElectrode->moveBy(285, 340);

    _schema = new QGraphicsView(_scene);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_schema);

    setLayout(_mainLayout);
}
