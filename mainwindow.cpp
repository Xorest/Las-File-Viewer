#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QList>
#include "mainwindow.h"
#include "ui_mainwindow.h"
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

void MainWindow::savePCD()
{
//    PointCloud<PointXYZRGBA> cloud;

//    cloud.width = _lasFile->points().size();
//    cloud.height = 1;
//    cloud.is_dense = false;
//    cloud.points.resize(cloud.width * cloud.width);

//    int indexLasPoint = 0;

//    for (PointXYZRGBA& p : cloud)
//    {
//        PointDataRecords* lasPoint = _lasFile->points()[indexLasPoint];
//        p._PointXYZRGBA::x = lasPoint->x();
//        p._PointXYZRGBA::y = lasPoint->y();
//        p._PointXYZRGBA::z = lasPoint->z();
//        p._PointXYZRGBA::r = lasPoint->red();
//        p._PointXYZRGBA::g = lasPoint->green();
//        p._PointXYZRGBA::b = lasPoint->blue();
//        p._PointXYZRGBA::a = 255;

//        indexLasPoint++;
//    }

//    io::savePCDFileASCII("test_pcd.pcd", cloud);
}

