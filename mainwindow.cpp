#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QList>
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
    connect(ui->actionGridSimplifyPoint, &QAction::triggered, this, &MainWindow::gridSimplify);
    connect(ui->actionBilateralSmooth, &QAction::triggered, this, &MainWindow::bilateralSmooth);
    connect(ui->actionJetSmooth, &QAction::triggered, this, &MainWindow::jetSmooth);
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
    ui->actionGridSimplifyPoint->setEnabled(true);
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
    _lasFile->setPoints(TreatmentCGAL::removeOutliers(ui->openGLWidget->points(), 100));
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
    qDebug()<<_lasFile->points().size();
}

void MainWindow::gridSimplify()
{
    _lasFile->setPoints(TreatmentCGAL::removeOutliers(ui->openGLWidget->points(), 6));
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
    qDebug()<<_lasFile->points().size();
}

void MainWindow::bilateralSmooth()
{
    //todo доделать
}

void MainWindow::jetSmooth()
{
    //todo доделать
}

