/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDletePoints;
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionRemoveOutliers;
    QAction *actionJetSmooth;
    QAction *actionRandomSimplify;
    QAction *actionGridSimplify;
    QAction *actionHierarchySmiplfy;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    OpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuSimplify;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1285, 791);
        MainWindow->setFocusPolicy(Qt::ClickFocus);
        actionDletePoints = new QAction(MainWindow);
        actionDletePoints->setObjectName(QString::fromUtf8("actionDletePoints"));
        actionDletePoints->setEnabled(false);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionRemoveOutliers = new QAction(MainWindow);
        actionRemoveOutliers->setObjectName(QString::fromUtf8("actionRemoveOutliers"));
        actionRemoveOutliers->setEnabled(false);
        actionJetSmooth = new QAction(MainWindow);
        actionJetSmooth->setObjectName(QString::fromUtf8("actionJetSmooth"));
        actionJetSmooth->setEnabled(false);
        actionRandomSimplify = new QAction(MainWindow);
        actionRandomSimplify->setObjectName(QString::fromUtf8("actionRandomSimplify"));
        actionRandomSimplify->setEnabled(false);
        actionGridSimplify = new QAction(MainWindow);
        actionGridSimplify->setObjectName(QString::fromUtf8("actionGridSimplify"));
        actionGridSimplify->setEnabled(false);
        actionHierarchySmiplfy = new QAction(MainWindow);
        actionHierarchySmiplfy->setObjectName(QString::fromUtf8("actionHierarchySmiplfy"));
        actionHierarchySmiplfy->setEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        openGLWidget = new OpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(openGLWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1285, 20));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuSimplify = new QMenu(menu);
        menuSimplify->setObjectName(QString::fromUtf8("menuSimplify"));
        menuSimplify->setEnabled(false);
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu->menuAction());
        menu->addAction(actionDletePoints);
        menu->addAction(actionRemoveOutliers);
        menu->addAction(menuSimplify->menuAction());
        menu->addAction(actionJetSmooth);
        menuSimplify->addAction(actionRandomSimplify);
        menuSimplify->addAction(actionGridSimplify);
        menuSimplify->addAction(actionHierarchySmiplfy);
        menu_2->addAction(actionSave);
        menu_2->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Las File Viewer", nullptr));
        actionDletePoints->setText(QCoreApplication::translate("MainWindow", "\320\233\320\260\321\201\321\202\320\270\320\272", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        actionRemoveOutliers->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\265\320\275\320\270\320\265 \321\210\321\203\320\274\320\276\320\262", nullptr));
        actionJetSmooth->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\273\320\260\320\266\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        actionRandomSimplify->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\275\320\264\320\276\320\274\320\275\320\276\320\265", nullptr));
        actionGridSimplify->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\202\320\272\320\260", nullptr));
        actionHierarchySmiplfy->setText(QCoreApplication::translate("MainWindow", "\320\230\320\265\321\200\320\260\321\200\321\205\320\270\321\207\320\265\321\201\320\272\320\260\321\217", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213", nullptr));
        menuSimplify->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\265\320\275\320\270\320\265 \320\273\320\270\321\210\320\275\320\270\321\205 \321\202\320\276\321\207\320\265\320\272", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
