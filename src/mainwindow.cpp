#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0; i < 4; i++)
        ui->comboBox_FSAMP->insertItem(i,m_FSAMP_str[i]);
    for(int i=0; i < 4; i++)
        ui->comboBox_NCH->insertItem(i,m_NCH_str[i]);
    for(int i=0; i < 4; i++)
        ui->comboBox_ANOUT_GAIN->insertItem(i,m_ANOUT_GAIN_str[i]);
    for(int i=0; i < 13; i++)
        ui->comboBox_INSEL->insertItem(i,m_INSEL_str[i]);
    for(int i=0; i < 64; i++)
        ui->comboBox_CHSEL->insertItem(i,QString::number(i+1));

    for(int i=0; i < 13; i++)
        ui->comboBox_selectedIN->insertItem(i,m_INSEL_str[i]);
    for(int i=0; i < 64; i++)
        ui->comboBox_MUS->insertItem(i,m_MUS_str[i]);
    for(int i=0; i < 23; i++)
        ui->comboBox_SENS->insertItem(i,m_SENS_str[i]);
    for(int i=0; i < 6; i++)
        ui->comboBox_ADAPT->insertItem(i,m_ADAPT_str[i]);
    for(int i=0; i < 4; i++)
        ui->comboBox_SIDE->insertItem(i,m_SIDE_str[i]);
    for(int i=0; i < 4; i++)
        ui->comboBox_HPF->insertItem(i,m_HPF_str[i]);
    for(int i=0; i < 4; i++)
        ui->comboBox_LPF->insertItem(i,m_LPF_str[i]);
    for(int i=0; i < 3; i++)
        ui->comboBox_MODE->insertItem(i,m_MODE_str[i]);

}

MainWindow::~MainWindow()
{
    delete ui;
}
