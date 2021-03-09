#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <pcl/2d/convolution.h>
#include <pcl/2d/edge.h>
#include <pcl/2d/kernel.h>
#include <pcl/2d/morphology.h>
#include <pcl/pcl_base.h>
#include <pcl/point_types.h>

using namespace pcl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
    connect(ui->pushButtonOpen, &QPushButton::clicked, this, &MainWindow::PushButtonOpenClic);
    connect(ui->pushButtonBreak, &QPushButton::clicked, this, &MainWindow::PushButtonBreakClic);

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
    _menu = new QMenu();
    _actionCut = new QAction("Cut");
    _menu->addAction(_actionCut);
    connect(_actionCut, &QAction::triggered, this, &MainWindow::trigger);
}
void MainWindow::trigger()
{
    _lasFile->cutPoints(ui->openGLWidget->cutPosBegin(),ui->openGLWidget->cutPosEnd());
}

void MainWindow::PushButtonOpenClic()
{
    QString path = QFileDialog::getOpenFileName();
    _lasFile = new File(path);
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
}

void MainWindow::PushButtonBreakClic()
{
    QString path = QFileDialog::getOpenFileName();
    _lasFile = new File(path);
    _lasFile->cutPoints();

}
