#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actioncharger, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionICP, SIGNAL(triggered()), this, SLOT(loadICP()));
    connect(ui->actionsauvegarder, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionrepeter_icp, SIGNAL(triggered()), this, SLOT(repeatIcp()));
    ui->actionsauvegarder->setVisible(false);
    ui->actionrepeter_icp->setVisible(false);
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
        buffer.clear();
        ui->statusbar->showMessage("load "+ file1 + file2+"...");
        this->pointcloud2 = new Pointcloud(file2,QVector4D(0.0,0.0,1.0,0.5));
        this->pointcloud1 = new Pointcloud(file1,this->pointcloud2->getDecimation());

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
        //std::vector<Vertex> v1 = this->pointcloud1->getPoints().toStdVector();
        std::vector<Vertex *> v1;
        for(int i =0; i<pointcloud1->getPoints().size();i++)
        {
            Vertex * v = new Vertex(0.08,pointcloud1->at(i).getX(),pointcloud1->at(i).getY(),pointcloud1->at(i).getZ());
            v1.push_back(v);
        }
        std::vector<Vertex *> v2;
        for(int i =0; i<pointcloud2->getPoints().size();i++)
        {
            Vertex * v = new Vertex(0.08,pointcloud2->at(i).getX(),pointcloud2->at(i).getY(),pointcloud2->at(i).getZ());
            v->setColor(QVector4D(1.0,1.0,1.0,0.5));
            v2.push_back(v);
        }
        //std::vector<Vertex> v2 = this->pointcloud2->getPoints().toStdVector();
        //for(int i = 0 ; i< 2; i++)
        {
            icp.icp(v1,v2);
        }
        this->v_icp1 = v1;
        this->v_icp2 = v2;
        this->dist = dist;
        this->isIcp = true;
        ui->glarea->set_particle(v1,dist);
        ui->glarea->set_particle(v2,dist);
        //QVector <Vertex> vp1 = QVector<Vertex>::fromStdVector(v1);
        /*QVector <Vertex> vp1;
        for(int i =0; i<v1.size();i++)
        {
            Vertex v(0.04,v1.at(i)->getX(),v1.at(i)->getY(),v1.at(i)->getZ());
            vp1.push_back(v);
        }
        //QVector <Vertex> vp2 = QVector<Vertex>::fromStdVector(v2);
        QVector <Vertex> vp2;
        for(int i =0; i<v2.size();i++)
        {
            Vertex v(0.04,v2.at(i)->getX(),v2.at(i)->getY(),v2.at(i)->getZ());
            v.setColor(QVector4D(0.0,0.0,1.0,0.5));
            vp2.push_back(v);
        }
        qDebug()<<"VP2 SIZE :"<<vp2.size();
        //v = this->pointcloud1->getPoints() + this->pointcloud2->getPoints();
        this->buffer = vp1+vp2;
        ui->glarea->set_particle(buffer,dist);*/
        ui->actionsauvegarder->setVisible(true);
        ui->actionrepeter_icp->setVisible(true);
    }
}

void MainWindow::save()
{
    ui->glarea->clear_particle();
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save PLY file"), "",
            tr("PLY file (*.ply);;All Files (*)"));
    Pointcloud p;
    p.setPoints(this->buffer);
    p.save(fileName.toStdString());
}

void MainWindow::repeatIcp()
{
    if(this->isIcp)
    {
        ui->glarea->clear_particle();
        ICP icp;
        icp.icp(this->v_icp1,this->v_icp2);
        ui->glarea->set_particle(this->v_icp1,dist);
        ui->glarea->set_particle(this->v_icp2,dist);
    }
}
