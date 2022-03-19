#include "electrodespage.h"

ElectrodesPage::ElectrodesPage(QWidget *parent)
    : QWidget{parent}
{
    _scene = new QGraphicsScene();

    _face = new QGraphicsSvgItem(":/settings/face.svg");
    _leftElectrode = new ElectrodeItem("");
    _rightElectrode = new ElectrodeItem("");
    _topElectrode = new ElectrodeItem("");
    _bottomElectrode = new ElectrodeItem("");

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

    _diagramLayout = new QVBoxLayout();
    _diagramLayout->addWidget(_schema);

    _horizontalGroup = new ChannelGroup(tr("Horizontal Channel"), tr("Left"), tr("Right"));
    _verticalGroup = new ChannelGroup(tr("Vertical Channel"), tr("Top"), tr("Bottom"));

    _parametersLayout = new QVBoxLayout();
    _parametersLayout->addWidget(_horizontalGroup);
    _parametersLayout->addWidget(_verticalGroup);

    _mainLayout = new QHBoxLayout();
    _mainLayout->addLayout(_diagramLayout);
    _mainLayout->addLayout(_parametersLayout);

    setLayout(_mainLayout);

    connect(_horizontalGroup, &ChannelGroup::useChannelChanged,
            this, &ElectrodesPage::setHorizontalChannelVisible);

    connect(_horizontalGroup, &ChannelGroup::inputChannelChanged,
            this, &ElectrodesPage::setHorizontalChannelInput);

    connect(_horizontalGroup, &ChannelGroup::eye1MarkChanged,
            this, &ElectrodesPage::setLeftElectrodeMark);

    connect(_horizontalGroup, &ChannelGroup::eye2MarkChanged,
            this, &ElectrodesPage::setRightElectrodeMark);

    connect(_verticalGroup, &ChannelGroup::useChannelChanged,
            this, &ElectrodesPage::setVerticalChannelVisible);

    connect(_verticalGroup, &ChannelGroup::inputChannelChanged,
            this, &ElectrodesPage::setVerticalChannelInput);

    connect(_verticalGroup, &ChannelGroup::eye1MarkChanged,
            this, &ElectrodesPage::setTopElectrodeMark);

    connect(_verticalGroup, &ChannelGroup::eye2MarkChanged,
            this, &ElectrodesPage::setBottomElectodeMark);
}

void ElectrodesPage::setHorizontalChannelVisible(bool visible)
{
    _horizontalChannel->setVisible(visible);
    _leftElectrode->setVisible(visible);
    _rightElectrode->setVisible(visible);
    _scene->update();

}

void ElectrodesPage::setHorizontalChannelInput(const QString &channel)
{
    _horizontalChannel->setInputChannel(channel);
    _scene->update();
}

void ElectrodesPage::setLeftElectrodeMark(const QString &mark)
{
    _leftElectrode->setMark(mark);
}

void ElectrodesPage::setRightElectrodeMark(const QString &mark)
{
    _rightElectrode->setMark(mark);
}

void ElectrodesPage::setVerticalChannelVisible(bool visible)
{
    _verticalChannel->setVisible(visible);
    _topElectrode->setVisible(visible);
    _bottomElectrode->setVisible(visible);
    _scene->update();
}

void ElectrodesPage::setVerticalChannelInput(const QString &channel)
{
    _verticalChannel->setInputChannel(channel);
    _scene->update();
}

void ElectrodesPage::setTopElectrodeMark(const QString &mark)
{
    _topElectrode->setMark(mark);
}

void ElectrodesPage::setBottomElectodeMark(const QString &mark)
{
    _bottomElectrode->setMark(mark, false);
}
