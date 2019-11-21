#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpropertyanimation.h"
#include "qlabel.h"
#include <QGraphicsBlurEffect>
#include "blurredsidebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void collapseExpand();

private:
    Ui::MainWindow *ui;
    BlurredSidebar* sidebar;
    QPropertyAnimation* sidebarClose;
    QPropertyAnimation* sidebarOpen;
    QPropertyAnimation* buttonClose;
    QPropertyAnimation* buttonOpen;
    bool sidebarVisible;
    QGraphicsBlurEffect* effect;
};
#endif // MAINWINDOW_H
