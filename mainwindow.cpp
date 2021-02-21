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
    ui->openGLWidget->setPointsByOpenGL(_lasFile->points());
    initMenu();

    qDebug()<<"Размер хедера"<<_lasFile->headerFile()->headerSize();
//    qDebug()<<"Начала байтов с точками"<<_lasFile->headerFile()->offsetToPointData();
//    qDebug()<<_lasFile->headerFile()->numberOfVariableLenghtRecords();
//    qDebug()<<_lasFile->headerFile()->poitDataRecordLength();


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
