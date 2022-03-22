#ifndef ELECTRODESPAGE_H
#define ELECTRODESPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "electrodeitem.h"
#include "channelitem.h"
#include "channelgroup.h"

class ElectrodesPage : public QWidget
{
    Q_OBJECT
public:
    explicit ElectrodesPage(QWidget *parent = nullptr);

     void loadSettings();
     void saveSettings();

private:
    QGraphicsView *_schema = nullptr;
    QGraphicsScene *_scene = nullptr;

    QGraphicsSvgItem *_face = nullptr;
    ElectrodeItem *_leftElectrode = nullptr;
    ElectrodeItem *_rightElectrode = nullptr;
    ElectrodeItem *_topElectrode = nullptr;
    ElectrodeItem *_bottomElectrode = nullptr;
    ChannelItem *_horizontalChannel = nullptr;
    ChannelItem *_verticalChannel = nullptr;

    ChannelGroup *_horizontalGroup = nullptr;
    ChannelGroup *_verticalGroup = nullptr;

    QVBoxLayout *_diagramLayout = nullptr;
    QVBoxLayout *_parametersLayout = nullptr;
    QHBoxLayout *_mainLayout = nullptr;

private slots:
    void setHorizontalChannelVisible(bool visible);
    void setHorizontalChannelInput(const QString &channel);
    void setLeftElectrodeMark(const QString &mark);
    void setRightElectrodeMark(const QString &mark);

    void setVerticalChannelVisible(bool visible);
    void setVerticalChannelInput(const QString &channel);
    void setTopElectrodeMark(const QString &mark);
    void setBottomElectodeMark(const QString &mark);
};

#endif // ELECTRODESPAGE_H
