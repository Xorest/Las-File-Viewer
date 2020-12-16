#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = "D:/art/las/lasfile1.las";
    _lasFile = new File(path);
}

MainWindow::~MainWindow()
{
    delete ui;
}

