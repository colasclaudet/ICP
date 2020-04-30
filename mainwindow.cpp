#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actioncharger, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionICP, SIGNAL(triggered()), this, SLOT(loadICP()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    ui->glarea->clear_particle();
    QString file = QFileDialog::getOpenFileName(this,
        tr("Ouvrir fichier"), "",
        tr("ply format(*.ply);;"
        "Tous les fichiers(*)"));

    if (file == "")
    {
        ui->statusbar->showMessage("Pas de fichier choisi");
        return;
    }
    else
    {

        this->pointcloud1 = new Pointcloud(file);
        ui->glarea->set_particle(this->pointcloud1->getPoints(),this->pointcloud1->getDistmax());
    }
}

void MainWindow::loadICP()
{
    ui->glarea->clear_particle();
    QString file1 = QFileDialog::getOpenFileName(this,
        tr("Ouvrir le fichier 1"), "",
        tr("ply format(*.ply);;"
        "Tous les fichiers(*)"));
    QString file2 = QFileDialog::getOpenFileName(this,
        tr("Ouvrir le fichier 2"), "",
        tr("ply format(*.ply);;"
        "Tous les fichiers(*)"));

    if (file1 == "" || file2 == "")
    {
        ui->statusbar->showMessage("Pas assez de fichier choisi");
        return;
    }
    else
    {

        this->pointcloud1 = new Pointcloud(file1);
        this->pointcloud2 = new Pointcloud(file2,QVector4D(0.0,0.0,1.0,0.5));
        QVector<Vertex> v;
        float dist = 0.0;
        if(this->pointcloud1->getDistmax() >= this->pointcloud2->getDistmax())
        {
            dist = this->pointcloud1->getDistmax();
        }
        else
        {
            dist = this->pointcloud2->getDistmax();
        }
        ICP icp;
        std::vector<Vertex> v1 = this->pointcloud1->getPoints().toStdVector();
        std::vector<Vertex> v2 = this->pointcloud2->getPoints().toStdVector();
        icp.icp(&v1,&v2);
        QVector <Vertex> vp1 = QVector<Vertex>::fromStdVector(v1);
        QVector <Vertex> vp2 = QVector<Vertex>::fromStdVector(v2);
        //v = this->pointcloud1->getPoints() + this->pointcloud2->getPoints();
        v = vp1+vp2;
        ui->glarea->set_particle(v,dist);
    }
}
