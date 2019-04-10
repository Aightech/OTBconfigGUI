#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_filepath->setText("config/config01.cfg");

    initGUI();

    //emptied confInputs
    for(int i =0; i<12; i++)
        for(int j=0; j<7; j++)
           m_confInputs[i][j]=0;

    updateConfig();
}

void MainWindow::initGUI()
{
    //fillup comboxes
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

    for(int i=1; i < 13; i++)
        ui->comboBox_selectedIN->insertItem(i-1,m_INSEL_str[i]);
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

    //init treewidget
    ui->treeWidget->setMinimumWidth(300);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setColumnWidth(0,150);
    ui->treeWidget->setHeaderLabels(QStringList() << tr("Sources")<< tr("Infos"));
    for (int i = 0; i < 12; i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, m_INSEL_str[i+1]);

        QTreeWidgetItem *subitem_mus = new QTreeWidgetItem(item);
        subitem_mus->setText(0, "Muscle");
        subitem_mus->setText(1, m_MUS_str[0]);

        QTreeWidgetItem *subitem_sens = new QTreeWidgetItem(item);
        subitem_sens->setText(0, "Sensor");
        subitem_sens->setText(1, m_SENS_str[0]);

        QTreeWidgetItem *subitem_adapt = new QTreeWidgetItem(item);
        subitem_adapt->setText(0, "Adaptator");
        subitem_adapt->setText(1, m_ADAPT_str[0]);

        QTreeWidgetItem *subitem_side = new QTreeWidgetItem(item);
        subitem_side->setText(0, "Side");
        subitem_side->setText(1, m_SIDE_str[0]);

        QTreeWidgetItem *subitem_hpf = new QTreeWidgetItem(item);
        subitem_hpf->setText(0, "H.pass freq");
        subitem_hpf->setText(1, m_HPF_str[0]);

        QTreeWidgetItem *subitem_lpf = new QTreeWidgetItem(item);
        subitem_lpf->setText(0, "L.pass freq");
        subitem_lpf->setText(1, m_LPF_str[3]);

        QTreeWidgetItem *subitem_mode = new QTreeWidgetItem(item);
        subitem_mode->setText(0, "Mode");
        subitem_mode->setText(1, m_MODE_str[1]);
    }

    connect(ui->comboBox_FSAMP, SIGNAL (activated(int)), this, SLOT (updateConfig()));
    connect(ui->comboBox_NCH, SIGNAL (activated(int)), this, SLOT (updateConfig()));
    connect(ui->comboBox_ANOUT_GAIN, SIGNAL (activated(int)), this, SLOT (updateConfig()));
    connect(ui->comboBox_CHSEL, SIGNAL (activated(int)), this, SLOT (updateConfig()));
    connect(ui->comboBox_INSEL, SIGNAL (activated(int)), this, SLOT (updateConfig()));
    connect(ui->checkBox_DECIM, SIGNAL (clicked(bool)), this, SLOT (updateConfig()));
    connect(ui->checkBox_REC_ON, SIGNAL (clicked(bool)), this, SLOT (updateConfig()));

    connect(ui->comboBox_MUS, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_SENS, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_ADAPT, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_SIDE, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_HPF, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_LPF, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_MODE, SIGNAL (activated(int)), this, SLOT (updateConfigInput()));
    connect(ui->comboBox_selectedIN, SIGNAL (activated(int)), this, SLOT (updateGUI()));


    connect(ui->pushButton_open, SIGNAL (released()), this, SLOT (openConfig()));
    connect(ui->pushButton_save, SIGNAL (released()), this, SLOT (saveConfig()));
}

void MainWindow::updateConfig()
{//get the data from the GUI and create the resulting configuration
    m_config[0] = ACQ_SETT| ACQ_ON;
    m_config[0] |= (ui->checkBox_DECIM->checkState()==Qt::CheckState::Checked)?DECIM:0;
    m_config[0] |= (ui->checkBox_REC_ON->checkState()==Qt::CheckState::Checked)?REC_ON:0;
    m_config[0] |= static_cast<unsigned char>(3-ui->comboBox_FSAMP->currentIndex())<<3;
    m_config[0] |= static_cast<unsigned char>(3-ui->comboBox_NCH->currentIndex())<<1;

    m_config[1] = 0;
    m_config[1] |= static_cast<unsigned char>(3-ui->comboBox_ANOUT_GAIN->currentIndex())<<4;
    m_config[1] |= static_cast<unsigned char>(12-ui->comboBox_NCH->currentIndex());

    m_config[2] = static_cast<unsigned char>(63-ui->comboBox_NCH->currentIndex());

    for(unsigned i=0;i<12;i++)
    {
        m_config[i*3+3] = m_confInputs[i][0];
        m_config[i*3+4] = 0;
        m_config[i*3+4] |= (m_confInputs[i][1]<<3) | (m_confInputs[i][2]);
        m_config[i*3+5] = 0;
        m_config[i*3+5] |= (m_confInputs[i][3]<<6) | (m_confInputs[i][4]<<4) | (m_confInputs[i][5]<<2) | (m_confInputs[i][6]);
    }
    m_config[39] = crc(m_config);

}

void MainWindow::updateConfigInput()
{//get the data from the GUI and store the value in the array of the whole inputs configuration, then call updateConfig
    int i = ui->comboBox_selectedIN->currentIndex();
    m_confInputs[i][0] = static_cast<unsigned char>(ui->comboBox_MUS->currentIndex());
    m_confInputs[i][1] = static_cast<unsigned char>(ui->comboBox_SENS->currentIndex());
    m_confInputs[i][2] = static_cast<unsigned char>(ui->comboBox_ADAPT->currentIndex());
    m_confInputs[i][3] = static_cast<unsigned char>(3-ui->comboBox_SIDE->currentIndex());
    m_confInputs[i][4] = static_cast<unsigned char>(3-ui->comboBox_HPF->currentIndex());
    m_confInputs[i][5] = static_cast<unsigned char>(3-ui->comboBox_LPF->currentIndex());
    m_confInputs[i][6] = static_cast<unsigned char>(3-ui->comboBox_MODE->currentIndex());

    updateConfig();
    updateGUI();
}

unsigned char MainWindow::crc(unsigned char config[])
{//compute the crc of the config
    unsigned char crc =0;
    for(int j=0;j<CONFIG_SIZE-1;j++)
        {
            unsigned char val = config[j];
            for(int i=0;i<8;i++)
                {
                    if(crc%2 ^ val%2)
                        crc = crc/2 ^ CRC_CODE;
                    else
                        crc/=2;
                    val /= 2;
                }
        }
    return crc;
}

void MainWindow::openConfig()
{//open a config file and store it in m_config
    std::string path = ui->lineEdit_filepath->text().toStdString();
    std::ifstream file (path, std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        std::streampos size = file.tellg();
        if(size==CONFIG_SIZE)
        {
            file.seekg (0, std::ios::beg);
            file.read ((char*)m_config, size);
            file.close();
            for(unsigned i=0;i<12;i++)
            {
                m_confInputs[i][0] = m_config[i*3+3];
                m_confInputs[i][1] = m_config[i*3+4]>>3;
                m_confInputs[i][2] = m_config[i*3+4] & 0b111;
                m_confInputs[i][3] = m_config[i*3+5]>>6;
                m_confInputs[i][4] = m_config[i*3+4]>>4 & 0b11;
                m_confInputs[i][5] = m_config[i*3+4]>>2 & 0b11;
                m_confInputs[i][5] = m_config[i*3+4] & 0b11;
            }

            updateGUI();
        }
        else
            std::cout << "File not conformed" << std::endl;
    }
    else
        std::cout << "Could not open file: " << path << std::endl;
}

void MainWindow::saveConfig()
{//save m_config in a config file
    std::string path = ui->lineEdit_filepath->text().toStdString();
    std::ofstream file (path, std::ios::out| std::ios::binary | std::ios::trunc);
    if (file.is_open())
    {
        file.write((char*)m_config,CONFIG_SIZE);
        file.close();
    }
    else
        std::cout << "Could not open file: " << path << std::endl;
}

void MainWindow::updateGUI()
{//from the config array update the data to The GUI
    unsigned char c = m_config[0];
    ui->checkBox_DECIM->setCheckState(( ((m_config[0]>>6) & 0b1)==1)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    ui->checkBox_REC_ON->setCheckState((((m_config[0]>>5) & 0b1)==1)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    ui->comboBox_FSAMP->setCurrentIndex(3 - ((m_config[0]>>3) & 0b11));
    ui->comboBox_NCH->setCurrentIndex(  3 - ((m_config[0]>>1) & 0b11));
    int i = ui->comboBox_selectedIN->currentIndex();
    ui->comboBox_MUS->setCurrentIndex(m_confInputs[i][0]);
    ui->comboBox_SENS->setCurrentIndex(m_confInputs[i][1]);
    ui->comboBox_ADAPT->setCurrentIndex(m_confInputs[i][2]);
    ui->comboBox_SIDE->setCurrentIndex(3-m_confInputs[i][3]);
    ui->comboBox_HPF->setCurrentIndex(3-m_confInputs[i][4]);
    ui->comboBox_LPF->setCurrentIndex(3-m_confInputs[i][5]);
    ui->comboBox_MODE->setCurrentIndex(3-m_confInputs[i][6]);

    for (int i = 0; i < 12; i++)
    {
        ui->treeWidget->topLevelItem(i)->child(0)->setText(1,m_MUS_str[m_confInputs[i][0]]);
        ui->treeWidget->topLevelItem(i)->child(1)->setText(1,m_SENS_str[m_confInputs[i][1]]);
        ui->treeWidget->topLevelItem(i)->child(2)->setText(1,m_ADAPT_str[m_confInputs[i][2]]);
        ui->treeWidget->topLevelItem(i)->child(3)->setText(1,m_SIDE_str[3-m_confInputs[i][3]]);
        ui->treeWidget->topLevelItem(i)->child(4)->setText(1,m_HPF_str[3-m_confInputs[i][4]]);
        ui->treeWidget->topLevelItem(i)->child(5)->setText(1,m_LPF_str[3-m_confInputs[i][5]]);
        ui->treeWidget->topLevelItem(i)->child(6)->setText(1,m_MODE_str[2-m_confInputs[i][6]]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
