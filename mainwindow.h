#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include "file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();
    protected:
        void contextMenuEvent(QContextMenuEvent* event) override;
    private:
        Ui::MainWindow* ui;
        File* _lasFile;
        QAction* _actionCut;
        QMenu* _menu;
        void initMenu();
    private slots:
            void trigger();
            void open();
            void pushButtonBreakClic();
            void deletePoints();
            void save();
            void savePCD();
};
#endif // MAINWINDOW_H
