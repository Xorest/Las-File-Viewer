#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = "D:/art/las/lasfileTree3.las";
    _lasFile = new File(path);
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
}

MainWindow::~MainWindow()
{
    delete ui;
}

