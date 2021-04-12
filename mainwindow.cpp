#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QList>
#include <QtConcurrent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treatmentcgal.h"
#include <QDebug>
//#include <pcl/pcl_base.h>
//#include <pcl/impl/point_types.hpp>
//#include <pcl/io/io.h>
//#include <pcl/io/pcd_io.h>

//using namespace pcl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    _menu->exec(event->globalPos());
}

void MainWindow::initMenu()
{
    _actionCut = new QAction("Вырезать");
    _menu = new QMenu();
    _menu->addAction(_actionCut);
    connect(_actionCut, &QAction::triggered, this, &MainWindow::trigger);
    connect(ui->actionDletePoints, &QAction::triggered, this, &MainWindow::deletePoints);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionRemoveOutliers, &QAction::triggered, this, &MainWindow::removeOutliers);
    connect(ui->actionGridSimplify, &QAction::triggered, this, &MainWindow::gridSimplify);
    connect(ui->actionHierarchySmiplfy, &QAction::triggered, this, &MainWindow::hierarchySimplify);
    connect(ui->actionRandomSimplify, &QAction::triggered, this, &MainWindow::randomSimplify);
    connect(ui->actionJetSmooth, &QAction::triggered, this, &MainWindow::jetSmooth);
}

void MainWindow::treatmentText()
{
    ui->menubar->setEnabled(false);
    _menu->setEnabled(false);
    ui->statusbar->showMessage("Обработка...");
}

void MainWindow::trigger()
{
    _lasFile->cutPoints(ui->openGLWidget->cutPosBegin(),ui->openGLWidget->cutPosEnd());
}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName();
    if (path.isEmpty())
    {
        return;
    }

    _lasFile = new File(path);
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
    ui->actionSave->setEnabled(true);
    ui->actionDletePoints->setEnabled(true);
    ui->actionRemoveOutliers->setEnabled(true);
    ui->actionGridSimplify->setEnabled(true);
    ui->actionHierarchySmiplfy->setEnabled(true);
    ui->actionRandomSimplify->setEnabled(true);
    ui->actionJetSmooth->setEnabled(true);
    ui->menuSimplify->setEnabled(true);
}

void MainWindow::pushButtonBreakClic()
{
    QString path = QFileDialog::getOpenFileName();
    _lasFile = new File(path);
    _lasFile->cutPoints();

}

void MainWindow::deletePoints()
{
    ui->openGLWidget->deletePoints();
}

void MainWindow::save()
{
    _lasFile->save(ui->openGLWidget->points());
}

void MainWindow::removeOutliers()
{
    connect(&_watcher, &QFutureWatcher<QList<PointDataRecords*>>::finished, this, &MainWindow::watcherFinshed);
    _watcher.setFuture(QtConcurrent::run(TreatmentCGAL::removeOutliers, ui->openGLWidget->points(), 100));
    treatmentText();
}

void MainWindow::gridSimplify()
{
    connect(&_watcher, &QFutureWatcher<QList<PointDataRecords*>>::finished, this, &MainWindow::watcherFinshed);
    _watcher.setFuture(QtConcurrent::run(TreatmentCGAL::gridSimplify, ui->openGLWidget->points(), 20));
    treatmentText();
}

void MainWindow::hierarchySimplify()
{
    connect(&_watcher, &QFutureWatcher<QList<PointDataRecords*>>::finished, this, &MainWindow::watcherFinshed);
    _watcher.setFuture(QtConcurrent::run(TreatmentCGAL::hierarchySimplify, ui->openGLWidget->points(), 20));
    treatmentText();
}

void MainWindow::randomSimplify()
{
    connect(&_watcher, &QFutureWatcher<QList<PointDataRecords*>>::finished, this, &MainWindow::watcherFinshed);
    _watcher.setFuture(QtConcurrent::run(TreatmentCGAL::randomSimplify, ui->openGLWidget->points(), 100));
    treatmentText();
}

void MainWindow::jetSmooth()
{
    connect(&_watcher, &QFutureWatcher<QList<PointDataRecords*>>::finished, this, &MainWindow::watcherFinshed);
    _watcher.setFuture(QtConcurrent::run(TreatmentCGAL::jetSmooth, ui->openGLWidget->points(), 8));
    treatmentText();
}

void MainWindow::watcherFinshed()
{
    _lasFile->setPoints(_watcher.result());
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
    ui->menubar->setEnabled(true);
    _menu->setEnabled(true);
    ui->statusbar->showMessage("OK", 300);
    qDebug()<<_lasFile->points().size();
}

