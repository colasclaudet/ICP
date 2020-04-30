#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "pointcloud.h"
#include "icp.h"

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
    void load();
    void loadICP();
    void save();

private:
    Ui::MainWindow *ui;
    QVector<Vertex> buffer;
    Pointcloud * pointcloud1;
    Pointcloud * pointcloud2;

};
#endif // MAINWINDOW_H
