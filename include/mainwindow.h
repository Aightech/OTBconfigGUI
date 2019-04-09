#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString m_FSAMP_str[4]={"10240 Hz",
                            "5120 Hz",
                            "2048 Hz",
                            "512 Hz"};
    QString m_NCH_str[4]={"All",
                          "IN1-6 & MULT_IN1-3",
                          "IN1-4 & MULT_IN1-2",
                          "IN1-2 & MULT_IN1"};
    QString m_ANOUT_GAIN_str[4]={"16",
                                 "4",
                                 "2",
                                 "1"};
    QString m_INSEL_str[13]={"AUX IN",
                            "MULTIPLE IN4",
                            "MULTIPLE IN3",
                            "MULTIPLE IN2",
                            "MULTIPLE IN1",
                            "IN8",
                            "IN7",
                            "IN6",
                            "IN5",
                            "IN4",
                            "IN3",
                            "IN2",
                            "IN1"};
    QString m_MUS_str[65]={"Not_defined",
                         "Temporalis_Anterior",
                         "Superfic_Masseter",
                         "Splenius_Capitis",
                         "Upper_Trapezius",
                         "Middle_Trapezius",
                         "Lower_Trapezius",
                         "Rhomboideus_Major",
                         "Rhomboideus_Minor",
                         "Anterior_Deltoid",
                         "Posterior_Deltoid",
                         "Lateral_Deltoid",
                         "Infraspinatus",
                         "Teres_Major",
                         "Erector_Spinae",
                         "Latissimus_Dorsi",
                         "Bic_Br_Long_Head",
                         "Bic_Br_Short_Head",
                         "Tric_Br_Lat_Head",
                         "Tric_Br_Med_Head",
                         "Pronator_Teres",
                         "Flex_Carpi_Radial",
                         "Flex_Carpi_Ulnaris",
                         "Palmaris_Longus",
                         "Ext_Carpi_Radialis",
                         "Ext_Carpi_Ulnaris",
                         "Ext_Dig_Communis",
                         "Brachioradialis",
                         "Abd_Pollicis_Brev",
                         "Abd_Pollicis_Long",
                         "Opponens_Pollicis",
                         "Adductor_Pollicis",
                         "Flex_Poll_Brevis",
                         "Abd_Digiti_Minimi",
                         "Flex_Digiti_Minimi",
                         "Opp_Digiti_Minimi",
                         "Dorsal_Interossei",
                         "Palmar_Interosse",
                         "Lumbrical",
                         "Rectus_Abdominis",
                         "Ext_Abdom_Obliq",
                         "Serratus_Anterior",
                         "Pectoralis_Major",
                         "Sternoc_Ster_Head",
                         "Sternoc_Clav_Head",
                         "Anterior_Scalenus",
                         "Tensor_Fascia Latae",
                         "Gastrocn_Lateralis",
                         "Gastrocn_Medialis",
                         "Biceps_Femoris",
                         "Soleus",
                         "Semitendinosus",
                         "Gluteus_maximus",
                         "Gluteus_medius",
                         "Vastus_lateralis",
                         "Vastus_medialis",
                         "Rectus_femoris",
                         "Tibialis_anterior",
                         "Peroneus_longus",
                         "Semimembranosus",
                         "Gracilis",
                         "Ext_Anal_Sphincter",
                         "Puborectalis",
                         "Urethral_Sphincter",
                         "Not_a_Muscle"};
    QString m_SENS_str[24]={"Not defined",
                            "16 Monopolar EEG ",
                            "Mon. intram. el.",
                            "Bip. el - CoDe",
                            "8 Acceleromet.",
                            "Bipolar el. - DE1",
                            "Bipolar el. - CDE",
                            "Bip. el. - other",
                            "4 el. Array 10mm",
                            "8 el. Array 5mm",
                            "8 el. Array 10mm",
                            "64el. Gr. 2.54mm",
                            "64 el. Grid 8mm",
                            "64 el. Grid 10mm",
                            "64 el.Gr. 12.5mm",
                            "16el.Array 2.5mm",
                            "16 el. Array 5mm",
                            "16 el. Array 10mm",
                            "16 el. Array 10mm",
                            "16 el. rectal pr.",
                            "48 el. rectal pr.",
                            "12 el. Armband",
                            "16 el. Armband",
                            "Other sensor"};
    QString m_ADAPT_str[7]={"Not defined",
                             "16ch AD1x16",
                             "8ch AD2x8",
                             "4ch AD4x4",
                             "64ch AD1x64",
                             "16ch AD8x2",
                             "Other"};
    QString m_SIDE_str[4]={"None",
                          "Right",
                          "Left",
                          "Not defined"};
    QString m_HPF_str[4]={"200 Hz",
                         "100 Hz",
                         "10 Hz",
                         "0.3 Hz"};
    QString m_LPF_str[4]={"4400 Hz",
                         "900 Hz",
                         "500 Hz",
                         "130 Hz"};
    QString m_MODE_str[3]={"Bipolar",
                          "Differencial",
                          "Monopolar"};

};

#endif // MAINWINDOW_H
