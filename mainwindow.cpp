#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QList>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//#include <pcl/2d/convolution.h>
//#include <pcl/2d/edge.h>
//#include <pcl/2d/kernel.h>
//#include <pcl/2d/morphology.h>
//#include <pcl/pcl_base.h>
//#include <pcl/point_types.h>

//using namespace pcl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();

//    Edge<pcl::PointXYZRGB> edge;
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
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
    _actionCut = new QAction("Cut");
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
