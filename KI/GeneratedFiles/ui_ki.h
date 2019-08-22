/********************************************************************************
** Form generated from reading UI file 'ki.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KI_H
#define UI_KI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KIClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_Left;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *gbx_Left;
    QComboBox *cbx_Protocal;
    QLabel *label_5;
    QLineEdit *txt_tcpPort;
    QLabel *label;
    QLineEdit *hostLineEdit;
    QLabel *label_4;
    QPushButton *btn_Conn;
    QPushButton *btn_BroadCast;
    QPushButton *btn_Conn_tcp;
    QGroupBox *groupBox_9;
    QLineEdit *txt_wrozs;
    QLabel *label_2;
    QLineEdit *txt_zzs;
    QLabel *label_10;
    QLineEdit *txt_wroprop;
    QLabel *label_9;
    QTextBrowser *tbr_Info;
    QGroupBox *groupBox_10;
    QLineEdit *txt_sigcountpack;
    QLabel *label_6;
    QLineEdit *txt_countpoint;
    QLabel *label_17;
    QLineEdit *txt_countmax;
    QLabel *label_18;
    QLineEdit *txt_countmin;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *txt_countavg;
    QWidget *widget_Right;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget_ShowSet;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox2;
    QPushButton *btn_chibiao;
    QPushButton *btn_XDown;
    QPushButton *btn_Rotate;
    QPushButton *btn_YUP;
    QPushButton *btn_ZUP;
    QPushButton *btn_PointTest;
    QPushButton *btn_ZDOWN;
    QPushButton *btn_YDown;
    QPushButton *btn_XUP;
    QPushButton *btn_Continue;
    QWidget *widget_PCL;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_Show;
    QWidget *widget_LaserPara;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gbx_Para;
    QGroupBox *gbox_netpara_3;
    QLabel *label_16;
    QLineEdit *txt_IP;
    QLabel *label_21;
    QLineEdit *txt_port;
    QLabel *label_22;
    QLineEdit *txt_mask;
    QLabel *label_23;
    QLineEdit *txt_getway;
    QPushButton *btn_netquery;
    QPushButton *btn_netsetting;
    QLabel *label_24;
    QLineEdit *txt_mac;
    QGroupBox *gbox_basepara_2;
    QLabel *label_25;
    QLabel *label_26;
    QPushButton *btn_baseparasetting;
    QPushButton *btn_baseparaquery;
    QComboBox *cbx_ratio;
    QComboBox *cbx_heart;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KIClass)
    {
        if (KIClass->objectName().isEmpty())
            KIClass->setObjectName(QStringLiteral("KIClass"));
        KIClass->setWindowModality(Qt::ApplicationModal);
        KIClass->resize(1155, 705);
        actionOpen = new QAction(KIClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(KIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_Left = new QWidget(centralWidget);
        widget_Left->setObjectName(QStringLiteral("widget_Left"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_Left->sizePolicy().hasHeightForWidth());
        widget_Left->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget_Left);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gbx_Left = new QGroupBox(widget_Left);
        gbx_Left->setObjectName(QStringLiteral("gbx_Left"));
        cbx_Protocal = new QComboBox(gbx_Left);
        cbx_Protocal->setObjectName(QStringLiteral("cbx_Protocal"));
        cbx_Protocal->setGeometry(QRect(120, 30, 111, 22));
        cbx_Protocal->setEditable(false);
        label_5 = new QLabel(gbx_Left);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 30, 71, 16));
        txt_tcpPort = new QLineEdit(gbx_Left);
        txt_tcpPort->setObjectName(QStringLiteral("txt_tcpPort"));
        txt_tcpPort->setGeometry(QRect(120, 110, 113, 20));
        label = new QLabel(gbx_Left);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 70, 54, 16));
        hostLineEdit = new QLineEdit(gbx_Left);
        hostLineEdit->setObjectName(QStringLiteral("hostLineEdit"));
        hostLineEdit->setGeometry(QRect(120, 70, 113, 20));
        label_4 = new QLabel(gbx_Left);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 110, 54, 16));
        btn_Conn = new QPushButton(gbx_Left);
        btn_Conn->setObjectName(QStringLiteral("btn_Conn"));
        btn_Conn->setGeometry(QRect(130, 140, 81, 23));
        btn_BroadCast = new QPushButton(gbx_Left);
        btn_BroadCast->setObjectName(QStringLiteral("btn_BroadCast"));
        btn_BroadCast->setGeometry(QRect(20, 140, 75, 23));
        btn_Conn_tcp = new QPushButton(gbx_Left);
        btn_Conn_tcp->setObjectName(QStringLiteral("btn_Conn_tcp"));
        btn_Conn_tcp->setGeometry(QRect(130, 140, 81, 23));
        groupBox_9 = new QGroupBox(gbx_Left);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(10, 440, 171, 191));
        txt_wrozs = new QLineEdit(groupBox_9);
        txt_wrozs->setObjectName(QStringLiteral("txt_wrozs"));
        txt_wrozs->setGeometry(QRect(80, 30, 81, 20));
        label_2 = new QLabel(groupBox_9);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 71, 16));
        txt_zzs = new QLineEdit(groupBox_9);
        txt_zzs->setObjectName(QStringLiteral("txt_zzs"));
        txt_zzs->setGeometry(QRect(80, 70, 81, 20));
        label_10 = new QLabel(groupBox_9);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 70, 61, 16));
        txt_wroprop = new QLineEdit(groupBox_9);
        txt_wroprop->setObjectName(QStringLiteral("txt_wroprop"));
        txt_wroprop->setGeometry(QRect(80, 110, 81, 20));
        label_9 = new QLabel(groupBox_9);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 110, 61, 16));
        tbr_Info = new QTextBrowser(gbx_Left);
        tbr_Info->setObjectName(QStringLiteral("tbr_Info"));
        tbr_Info->setGeometry(QRect(20, 170, 221, 261));
        groupBox_10 = new QGroupBox(gbx_Left);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(190, 440, 171, 191));
        txt_sigcountpack = new QLineEdit(groupBox_10);
        txt_sigcountpack->setObjectName(QStringLiteral("txt_sigcountpack"));
        txt_sigcountpack->setGeometry(QRect(110, 30, 51, 20));
        label_6 = new QLabel(groupBox_10);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 25, 91, 31));
        txt_countpoint = new QLineEdit(groupBox_10);
        txt_countpoint->setObjectName(QStringLiteral("txt_countpoint"));
        txt_countpoint->setGeometry(QRect(110, 60, 51, 20));
        label_17 = new QLabel(groupBox_10);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 60, 91, 16));
        txt_countmax = new QLineEdit(groupBox_10);
        txt_countmax->setObjectName(QStringLiteral("txt_countmax"));
        txt_countmax->setGeometry(QRect(110, 90, 51, 20));
        label_18 = new QLabel(groupBox_10);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 90, 91, 16));
        txt_countmin = new QLineEdit(groupBox_10);
        txt_countmin->setObjectName(QStringLiteral("txt_countmin"));
        txt_countmin->setGeometry(QRect(110, 120, 51, 20));
        label_19 = new QLabel(groupBox_10);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 120, 91, 16));
        label_20 = new QLabel(groupBox_10);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 150, 91, 16));
        txt_countavg = new QLineEdit(groupBox_10);
        txt_countavg->setObjectName(QStringLiteral("txt_countavg"));
        txt_countavg->setGeometry(QRect(110, 150, 51, 20));

        horizontalLayout_2->addWidget(gbx_Left);


        horizontalLayout->addWidget(widget_Left);

        widget_Right = new QWidget(centralWidget);
        widget_Right->setObjectName(QStringLiteral("widget_Right"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(7);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_Right->sizePolicy().hasHeightForWidth());
        widget_Right->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(widget_Right);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_ShowSet = new QWidget(widget_Right);
        widget_ShowSet->setObjectName(QStringLiteral("widget_ShowSet"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(widget_ShowSet->sizePolicy().hasHeightForWidth());
        widget_ShowSet->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(widget_ShowSet);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox2 = new QGroupBox(widget_ShowSet);
        groupBox2->setObjectName(QStringLiteral("groupBox2"));
        btn_chibiao = new QPushButton(groupBox2);
        btn_chibiao->setObjectName(QStringLiteral("btn_chibiao"));
        btn_chibiao->setGeometry(QRect(530, 10, 41, 23));
        btn_XDown = new QPushButton(groupBox2);
        btn_XDown->setObjectName(QStringLiteral("btn_XDown"));
        btn_XDown->setGeometry(QRect(330, 10, 41, 23));
        btn_Rotate = new QPushButton(groupBox2);
        btn_Rotate->setObjectName(QStringLiteral("btn_Rotate"));
        btn_Rotate->setGeometry(QRect(450, 10, 41, 23));
        btn_YUP = new QPushButton(groupBox2);
        btn_YUP->setObjectName(QStringLiteral("btn_YUP"));
        btn_YUP->setGeometry(QRect(370, 10, 41, 23));
        btn_ZUP = new QPushButton(groupBox2);
        btn_ZUP->setObjectName(QStringLiteral("btn_ZUP"));
        btn_ZUP->setGeometry(QRect(210, 10, 41, 23));
        btn_PointTest = new QPushButton(groupBox2);
        btn_PointTest->setObjectName(QStringLiteral("btn_PointTest"));
        btn_PointTest->setGeometry(QRect(490, 10, 41, 23));
        btn_ZDOWN = new QPushButton(groupBox2);
        btn_ZDOWN->setObjectName(QStringLiteral("btn_ZDOWN"));
        btn_ZDOWN->setGeometry(QRect(250, 10, 41, 23));
        btn_YDown = new QPushButton(groupBox2);
        btn_YDown->setObjectName(QStringLiteral("btn_YDown"));
        btn_YDown->setGeometry(QRect(410, 10, 41, 23));
        btn_XUP = new QPushButton(groupBox2);
        btn_XUP->setObjectName(QStringLiteral("btn_XUP"));
        btn_XUP->setGeometry(QRect(290, 10, 41, 23));
        btn_Continue = new QPushButton(groupBox2);
        btn_Continue->setObjectName(QStringLiteral("btn_Continue"));
        btn_Continue->setEnabled(false);
        btn_Continue->setGeometry(QRect(60, 10, 131, 21));

        verticalLayout_4->addWidget(groupBox2);


        verticalLayout->addWidget(widget_ShowSet);

        widget_PCL = new QWidget(widget_Right);
        widget_PCL->setObjectName(QStringLiteral("widget_PCL"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(6);
        sizePolicy3.setHeightForWidth(widget_PCL->sizePolicy().hasHeightForWidth());
        widget_PCL->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(widget_PCL);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_Show = new QWidget(widget_PCL);
        widget_Show->setObjectName(QStringLiteral("widget_Show"));

        verticalLayout_3->addWidget(widget_Show);


        verticalLayout->addWidget(widget_PCL);

        widget_LaserPara = new QWidget(widget_Right);
        widget_LaserPara->setObjectName(QStringLiteral("widget_LaserPara"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(3);
        sizePolicy4.setHeightForWidth(widget_LaserPara->sizePolicy().hasHeightForWidth());
        widget_LaserPara->setSizePolicy(sizePolicy4);
        verticalLayout_2 = new QVBoxLayout(widget_LaserPara);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gbx_Para = new QGroupBox(widget_LaserPara);
        gbx_Para->setObjectName(QStringLiteral("gbx_Para"));
        gbx_Para->setEnabled(false);
        gbox_netpara_3 = new QGroupBox(gbx_Para);
        gbox_netpara_3->setObjectName(QStringLiteral("gbox_netpara_3"));
        gbox_netpara_3->setGeometry(QRect(0, 10, 461, 171));
        label_16 = new QLabel(gbox_netpara_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 20, 61, 21));
        txt_IP = new QLineEdit(gbox_netpara_3);
        txt_IP->setObjectName(QStringLiteral("txt_IP"));
        txt_IP->setGeometry(QRect(80, 20, 161, 20));
        label_21 = new QLabel(gbox_netpara_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(253, 20, 71, 20));
        txt_port = new QLineEdit(gbox_netpara_3);
        txt_port->setObjectName(QStringLiteral("txt_port"));
        txt_port->setGeometry(QRect(330, 20, 111, 20));
        label_22 = new QLabel(gbox_netpara_3);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 60, 71, 20));
        txt_mask = new QLineEdit(gbox_netpara_3);
        txt_mask->setObjectName(QStringLiteral("txt_mask"));
        txt_mask->setGeometry(QRect(80, 60, 161, 20));
        label_23 = new QLabel(gbox_netpara_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(250, 60, 51, 21));
        txt_getway = new QLineEdit(gbox_netpara_3);
        txt_getway->setObjectName(QStringLiteral("txt_getway"));
        txt_getway->setGeometry(QRect(310, 60, 131, 20));
        btn_netquery = new QPushButton(gbox_netpara_3);
        btn_netquery->setObjectName(QStringLiteral("btn_netquery"));
        btn_netquery->setGeometry(QRect(80, 130, 75, 23));
        btn_netsetting = new QPushButton(gbox_netpara_3);
        btn_netsetting->setObjectName(QStringLiteral("btn_netsetting"));
        btn_netsetting->setGeometry(QRect(260, 130, 75, 23));
        label_24 = new QLabel(gbox_netpara_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 100, 41, 20));
        txt_mac = new QLineEdit(gbox_netpara_3);
        txt_mac->setObjectName(QStringLiteral("txt_mac"));
        txt_mac->setGeometry(QRect(70, 100, 341, 20));
        gbox_basepara_2 = new QGroupBox(gbx_Para);
        gbox_basepara_2->setObjectName(QStringLiteral("gbox_basepara_2"));
        gbox_basepara_2->setGeometry(QRect(470, 10, 181, 161));
        label_25 = new QLabel(gbox_basepara_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 30, 54, 21));
        label_26 = new QLabel(gbox_basepara_2);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 80, 41, 16));
        btn_baseparasetting = new QPushButton(gbox_basepara_2);
        btn_baseparasetting->setObjectName(QStringLiteral("btn_baseparasetting"));
        btn_baseparasetting->setGeometry(QRect(100, 130, 75, 23));
        btn_baseparaquery = new QPushButton(gbox_basepara_2);
        btn_baseparaquery->setObjectName(QStringLiteral("btn_baseparaquery"));
        btn_baseparaquery->setGeometry(QRect(10, 130, 75, 23));
        cbx_ratio = new QComboBox(gbox_basepara_2);
        cbx_ratio->setObjectName(QStringLiteral("cbx_ratio"));
        cbx_ratio->setGeometry(QRect(70, 30, 91, 22));
        cbx_heart = new QComboBox(gbox_basepara_2);
        cbx_heart->setObjectName(QStringLiteral("cbx_heart"));
        cbx_heart->setGeometry(QRect(70, 80, 91, 22));

        verticalLayout_2->addWidget(gbx_Para);


        verticalLayout->addWidget(widget_LaserPara);


        horizontalLayout_3->addLayout(verticalLayout);


        horizontalLayout->addWidget(widget_Right);


        horizontalLayout_4->addLayout(horizontalLayout);

        KIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(KIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        KIClass->setStatusBar(statusBar);

        retranslateUi(KIClass);
        QObject::connect(btn_Conn_tcp, SIGNAL(clicked()), KIClass, SLOT(ConnTcpClick()));
        QObject::connect(btn_BroadCast, SIGNAL(clicked()), KIClass, SLOT(Broadcast()));
        QObject::connect(cbx_Protocal, SIGNAL(currentIndexChanged(int)), KIClass, SLOT(ProtocalChanged()));
        QObject::connect(btn_Conn, SIGNAL(clicked()), KIClass, SLOT(ConnUdpClick()));
        QObject::connect(btn_Continue, SIGNAL(clicked()), KIClass, SLOT(ContinueScanClick()));
        QObject::connect(btn_ZUP, SIGNAL(clicked()), KIClass, SLOT(MoveZUP()));
        QObject::connect(btn_ZDOWN, SIGNAL(clicked()), KIClass, SLOT(MoveZDOWN()));
        QObject::connect(btn_XUP, SIGNAL(clicked()), KIClass, SLOT(MoveXUP()));
        QObject::connect(btn_XDown, SIGNAL(clicked()), KIClass, SLOT(MoveXDOWN()));
        QObject::connect(btn_YUP, SIGNAL(clicked()), KIClass, SLOT(MoveYUP()));
        QObject::connect(btn_YDown, SIGNAL(clicked()), KIClass, SLOT(MoveYDOWN()));
        QObject::connect(btn_Rotate, SIGNAL(clicked()), KIClass, SLOT(RotateClick()));
        QObject::connect(btn_PointTest, SIGNAL(clicked()), KIClass, SLOT(PointOrLineClick()));
        QObject::connect(btn_chibiao, SIGNAL(clicked()), KIClass, SLOT(CBClick()));
        QObject::connect(btn_netquery, SIGNAL(clicked()), KIClass, SLOT(NetParaQueryClick()));
        QObject::connect(btn_netsetting, SIGNAL(clicked()), KIClass, SLOT(NetParaSettingClick()));
        QObject::connect(btn_baseparaquery, SIGNAL(clicked()), KIClass, SLOT(BaseParaQueryClick()));
        QObject::connect(btn_baseparasetting, SIGNAL(clicked()), KIClass, SLOT(BaseParaSetClick()));

        QMetaObject::connectSlotsByName(KIClass);
    } // setupUi

    void retranslateUi(QMainWindow *KIClass)
    {
        KIClass->setWindowTitle(QApplication::translate("KIClass", "\344\270\207\351\233\206Laser(712C)_V1.0", 0));
        actionOpen->setText(QApplication::translate("KIClass", "Open", 0));
        gbx_Left->setTitle(QString());
        cbx_Protocal->clear();
        cbx_Protocal->insertItems(0, QStringList()
         << QApplication::translate("KIClass", "TCP", 0)
         << QApplication::translate("KIClass", "UDP", 0)
        );
        label_5->setText(QApplication::translate("KIClass", "\345\215\217\350\256\256\347\261\273\345\236\213\357\274\232", 0));
        txt_tcpPort->setText(QApplication::translate("KIClass", "2110", 0));
        label->setText(QApplication::translate("KIClass", "IP\345\234\260\345\235\200\357\274\232", 0));
        hostLineEdit->setText(QApplication::translate("KIClass", "192.168.0.106", 0));
        label_4->setText(QApplication::translate("KIClass", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        btn_Conn->setText(QApplication::translate("KIClass", "UDP\350\277\236\346\216\245", 0));
        btn_BroadCast->setText(QApplication::translate("KIClass", "\345\271\277\346\222\255", 0));
        btn_Conn_tcp->setText(QApplication::translate("KIClass", "TCP\350\277\236\346\216\245", 0));
        groupBox_9->setTitle(QApplication::translate("KIClass", "\346\225\260\346\215\256\347\273\237\350\256\241", 0));
        label_2->setText(QApplication::translate("KIClass", "\351\224\231\350\257\257\345\270\247\346\225\260\357\274\232", 0));
        label_10->setText(QApplication::translate("KIClass", "\346\200\273\345\270\247\346\225\260\357\274\232", 0));
        label_9->setText(QApplication::translate("KIClass", "\351\224\231\350\257\257\347\216\207\357\274\232", 0));
        groupBox_10->setTitle(QApplication::translate("KIClass", "\346\211\253\346\217\217\346\225\260\346\215\256\344\277\241\346\201\257", 0));
        txt_sigcountpack->setText(QApplication::translate("KIClass", "100", 0));
        label_6->setText(QApplication::translate("KIClass", "\345\215\225\346\254\241\347\273\237\350\256\241\345\214\205\346\225\260\357\274\232", 0));
        txt_countpoint->setText(QApplication::translate("KIClass", "1", 0));
        label_17->setText(QApplication::translate("KIClass", "\347\273\237\350\256\241\347\202\271\345\272\217\345\217\267\357\274\232", 0));
        txt_countmax->setText(QApplication::translate("KIClass", "0", 0));
        label_18->setText(QApplication::translate("KIClass", "\346\234\200\345\244\247\345\200\274(mm)\357\274\232", 0));
        txt_countmin->setText(QApplication::translate("KIClass", "0", 0));
        label_19->setText(QApplication::translate("KIClass", "\346\234\200\345\260\217\345\200\274(mm)\357\274\232", 0));
        label_20->setText(QApplication::translate("KIClass", "\345\271\263\345\235\207\345\200\274(mm)\357\274\232", 0));
        txt_countavg->setText(QApplication::translate("KIClass", "0", 0));
        groupBox2->setTitle(QApplication::translate("KIClass", "\346\230\276\347\244\272\350\256\276\347\275\256", 0));
        btn_chibiao->setText(QApplication::translate("KIClass", "\345\260\272\346\240\207", 0));
        btn_XDown->setText(QApplication::translate("KIClass", "X-", 0));
        btn_Rotate->setText(QApplication::translate("KIClass", "90Z", 0));
        btn_YUP->setText(QApplication::translate("KIClass", "Y+", 0));
        btn_ZUP->setText(QApplication::translate("KIClass", "Z+", 0));
        btn_PointTest->setText(QApplication::translate("KIClass", "\347\272\277", 0));
        btn_ZDOWN->setText(QApplication::translate("KIClass", "Z-", 0));
        btn_YDown->setText(QApplication::translate("KIClass", "Y-", 0));
        btn_XUP->setText(QApplication::translate("KIClass", "X+", 0));
        btn_Continue->setText(QApplication::translate("KIClass", "\350\216\267\345\217\226\350\277\236\347\273\255\346\263\242\345\275\242", 0));
        gbx_Para->setTitle(QString());
        gbox_netpara_3->setTitle(QApplication::translate("KIClass", "\347\275\221\347\273\234\345\217\202\346\225\260", 0));
        label_16->setText(QApplication::translate("KIClass", "IP\345\234\260\345\235\200\357\274\232", 0));
        label_21->setText(QApplication::translate("KIClass", "\346\234\254\345\234\260\347\253\257\345\217\243\357\274\232", 0));
        label_22->setText(QApplication::translate("KIClass", "\345\255\220\347\275\221\346\216\251\347\240\201\357\274\232", 0));
        label_23->setText(QApplication::translate("KIClass", "\347\275\221\345\205\263\357\274\232", 0));
        btn_netquery->setText(QApplication::translate("KIClass", "\346\237\245\350\257\242", 0));
        btn_netsetting->setText(QApplication::translate("KIClass", "\350\256\276\347\275\256", 0));
        label_24->setText(QApplication::translate("KIClass", "MAC\357\274\232", 0));
        gbox_basepara_2->setTitle(QApplication::translate("KIClass", "\345\237\272\346\234\254\345\217\202\346\225\260", 0));
        label_25->setText(QApplication::translate("KIClass", "\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_26->setText(QApplication::translate("KIClass", "\345\277\203\350\267\263:", 0));
        btn_baseparasetting->setText(QApplication::translate("KIClass", "\350\256\276\347\275\256", 0));
        btn_baseparaquery->setText(QApplication::translate("KIClass", "\346\237\245\350\257\242", 0));
        cbx_ratio->clear();
        cbx_ratio->insertItems(0, QStringList()
         << QApplication::translate("KIClass", "0.05", 0)
         << QApplication::translate("KIClass", "0.1", 0)
        );
        cbx_heart->clear();
        cbx_heart->insertItems(0, QStringList()
         << QApplication::translate("KIClass", "\345\205\263\351\227\255", 0)
         << QApplication::translate("KIClass", "\345\274\200\345\220\257", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class KIClass: public Ui_KIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KI_H
