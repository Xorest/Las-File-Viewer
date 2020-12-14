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

    qDebug()<<_lasFile->variableLengthRecordsFile()->description();
    qDebug()<<_lasFile->variableLengthRecordsFile()->recordId();
    qDebug()<<_lasFile->variableLengthRecordsFile()->recordLengthAfterHeader();
    qDebug()<<_lasFile->variableLengthRecordsFile()->reserved();
    qDebug()<<_lasFile->variableLengthRecordsFile()->userId();
    qDebug()<<_lasFile->headerFile()->pointDataFormatId();


}

MainWindow::~MainWindow()
{
    delete ui;
}

