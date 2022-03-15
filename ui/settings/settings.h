#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ui/settings/electrodespage.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private:
    QTabWidget *_tabWidget = nullptr;

    ElectrodesPage *_electrodesPage = nullptr;

    QPushButton *_saveButton = nullptr;
    QPushButton *_cancelButton = nullptr;

    QVBoxLayout *_mainLayout = nullptr;
    QHBoxLayout *_buttonsLayout = nullptr;
};

#endif // SETTINGSDIALOG_H
