﻿#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
#include <QCloseEvent>
#include <QTableView>
#include <QStandardItemModel>
#include <QFileSystemWatcher>
#include <QStringListModel>
#include "hookanalysis.h"
#include "colorfulmodel.h"
#include "filewidget.h"
#include "memorywidget.h"
#include "regwidget.h"
#include "heapwidget.h"
#include "netwidget.h"
#include "historytracer.h"
#include "modulewidget.h"
#include "exceptionwidget.h"
#include "logwidget.h"
#include "injectthread.h"

#define FILEACCESS_COUNT 3
#define FILESHAREMODE_COUNT 3
#define FILECREATEDISP_COUNT 5
#define FILEFLAGATTR 12

namespace Ui {
class Output;
}

class Output : public QWidget
{
    Q_OBJECT

public:
    QFileSystemWatcher* watcher = new QFileSystemWatcher(this);

    QStandardItemModel* heapViewModel = new QStandardItemModel(this);
    QStandardItemModel* fileViewModel = new QStandardItemModel(this);
    QStandardItemModel* exceptionModel = new QStandardItemModel(this);
    QStandardItemModel* regeditModel = new QStandardItemModel(this);
    QStandardItemModel* netModel = new QStandardItemModel(this);
    QStandardItemModel* logWidgetModel = new QStandardItemModel(this);
    QStandardItemModel* memoryModel = new QStandardItemModel(this);
    QStandardItemModel* moduleModel = new QStandardItemModel(this);
    colorfulModel* fileAccessModel = nullptr;
    colorfulModel* fileShareModeModel = nullptr;
    colorfulModel* fileCreateDispModel = nullptr;
    colorfulModel* fileFlagAttrModel = nullptr;
    hookAnalysis* analyser = new hookAnalysis(heapViewModel, fileViewModel, exceptionModel,
                                              regeditModel, logWidgetModel, netModel,
                                              memoryModel, moduleModel);
    historyTracer* tracer = new historyTracer(analyser, this);
    std::vector<bool> injectionOptions;

    explicit Output(std::vector<bool> choices = {}, QWidget *parent = nullptr);
    void initialize(std::vector<bool> choices);
    void updateLog();
    void showExeInfo();
    void closeEvent(QCloseEvent * event);
    void trimExeInfo(QString& fullInfo, bool firstLog = false);
    void saveFullLog();
    void appendLog(QString log);
    void changeStep(int changedValue);
    void updateLogCount();
    void allClear();

    QString getInjOptions();
    ~Output();

    fileWidget* fWdg;
    regWidget* rWdg;
    heapWidget* hWdg;
    exceptionWidget* eWdg;
    logWidget* lWdg;
    memoryWidget* mWdg;
    netWidget* nWdg;
    moduleWidget* moWdg;
    bool loadHistory = false;
    bool executing = true;

    injectThread* injThread;
    bool uselessFlag = false;

private slots:
    void on_fileView_clicked(const QModelIndex &index);

    void on_showFileWidget_clicked();

    void on_showRegWidget_clicked();

    void on_showHeapWidget_clicked();

    void on_showExceptionWidget_clicked();

    void on_showLogWidget_clicked();

    void on_showMemoryWidget_clicked();

    void on_showNetWidget_clicked();

    void on_showModulesWidget_clicked();

    void on_prevStep_clicked();

    void on_nextStep_clicked();

private:
    Ui::Output *ui;
    QStandardItemModel* model = new QStandardItemModel();
};

#endif // OUTPUT_H
