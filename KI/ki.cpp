#include <string>
#include <QFileDialog>
#include <iostream>
#include "ki.h"
#include <QTimer>
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include "workthread.h"
using namespace std;
DataDealFunc *pDatafunc=NULL;
int  m_nTimerIp=0;
PCLFunc *pclfunc = NULL;
QString str_hintinfo="";//提示信息
bool f_conscan = true;//是否连续扫描标志
QByteArray zl_Getnum = NULL, zl_LMDetect = NULL;//要数指令、靶标探测指令
QByteArray zl_Brocast = NULL;//广播指令
QByteArray zl_NetParaQuery = NULL;//网络参数查询指令
QByteArray zl_BaseParaQuery = NULL;//基本参数查询指令
bool f_PointOrLine = true;//点、线标志位
bool f_NetConState_TCP = false;//TCP网络连接状态标志位
bool f_ConOrDiscon = true;
bool f_ConOrDiscon_UDP = true;
QUdpSocket * receiver = NULL;
int n_sigcountpack = 0;//单次统计包数
int n_sigcountpoint = 0;//统计点序号，要在Workthread类中用到，不能在头文件中定义
QString host;
int port;
int k_Protocal;//协议类型 0：TCP 1:UDP
workthread *workThread = NULL;
KI::KI(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	n_sigcountpack = ui.txt_sigcountpack->text().toInt();
	n_sigcountpoint = ui.txt_countpoint->text().toInt();
	ui.txt_wroprop->setText(QString::fromLocal8Bit("0"));
	ui.btn_chibiao->setVisible(false);
	ui.btn_Rotate->setToolTip(QString::fromLocal8Bit("绕Z轴顺时针旋转90°"));
	ui.btn_PointTest->setToolTip(QString::fromLocal8Bit("设置波形显示为点或线"));
	ui.btn_ZUP->setToolTip(QString::fromLocal8Bit("视角设置为Z轴正向"));
	ui.btn_ZDOWN->setToolTip(QString::fromLocal8Bit("视角设置为Z轴负向"));
	ui.btn_XUP->setToolTip(QString::fromLocal8Bit("视角设置为X轴正向"));
	ui.btn_XDown->setToolTip(QString::fromLocal8Bit("视角设置为X轴负向"));
	ui.btn_YUP->setToolTip(QString::fromLocal8Bit("视角设置为Y轴正向"));
	ui.btn_YDown->setToolTip(QString::fromLocal8Bit("视角设置为Y轴负向"));
	//连接
	pclfunc = new PCLFunc(ui.widget_Show->width(), ui.widget_Show->height());
	pclfunc->ChangePCLView(ui.widget_Show->width(), ui.widget_Show->height());
	zl_LMDetect = pDatafunc->QString2Hex("FFAA0020000000000000010100070000000000000000060400000001010600500073EEEE");
	zl_Getnum = pDatafunc->QString2Hex("FFAA001E0000000000000101000700000000000000000201000000000000001AEEEE");//要数指令
	pclfunc->initialVtkWidget(ui.widget_Show);
	LayoutDesign();
}
void setmyStyle(const QString &style) {
	QFile qss(style);
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
}
void KI::resizeEvent(QResizeEvent *event)
{
	if (pclfunc)
		pclfunc->ChangePCLView(ui.widget_Show->width(), ui.widget_Show->height());
}

#pragma region 初始化splitter
void KI::LayoutDesign()
{
	//QDesktopWidget* desktopWidget = QApplication::desktop();
	////得到客户区矩形
	//QRect clientRect = desktopWidget->availableGeometry();
	//////得到应用程序矩形
	////QRect clientRect = desktopWidget->screenGeometry();

	//int nWidth = clientRect.width();
	//int nHeight = clientRect.height();
	//QSplitter *m_splitter = new QSplitter(Qt::Horizontal, this);

	//QSplitter *splitter1 = new QSplitter(Qt::Vertical);
	//splitter1->addWidget(ui.gbx_Left);
	////splitter1->setMinimumWidth(nWidth*0.28);
	//splitter1->setFixedWidth(nWidth*0.28);
	//m_splitter->addWidget(splitter1);
	//if (ui.cbx_Protocal->currentIndex() == 1)//UDP
	//{
	//	QSplitter *splitter2 = new QSplitter(Qt::Vertical);
	//	splitter2->addWidget(ui.groupBox2);
	//	splitter2->setMinimumWidth(nWidth*0.72);
	//	splitter2->setMaximumWidth(nWidth*0.9);
	//	splitter2->setMinimumHeight(nHeight*0.2);
	//	splitter2->setMaximumHeight(nHeight*0.3);
	//	m_splitter->addWidget(splitter2);


	//	QSplitter *splitter3 = new QSplitter(Qt::Vertical, splitter2);
	//	splitter3->addWidget(pclfunc->qvtk);
	//	splitter3->setMinimumHeight(nHeight*0.85);
	//	splitter3->setMaximumHeight(nHeight*0.95);

	//	QSplitter *splitter4 = new QSplitter(Qt::Horizontal, splitter3);
	//	splitter4->addWidget(ui.gbx_Para);
	//	splitter4->setFixedHeight(0);
	//	m_splitter->addWidget(splitter2);
	//}
	//else
	//{
	//	QSplitter *splitter2 = new QSplitter(Qt::Vertical);
	//	splitter2->addWidget(ui.groupBox2);
	//	splitter2->setMinimumWidth(nWidth*0.72);
	//	splitter2->setMaximumWidth(nWidth*0.9);
	//	splitter2->setMinimumHeight(nHeight*0.2);
	//	splitter2->setMaximumHeight(nHeight*0.3);
	//	m_splitter->addWidget(splitter2);

	//	QSplitter *splitter3 = new QSplitter(Qt::Vertical, splitter2);
	//	splitter3->addWidget(pclfunc->qvtk);
	//	splitter3->setMinimumHeight(nHeight*0.85);
	//	splitter3->setMaximumHeight(nHeight*0.95);

	//	QSplitter *splitter4 = new QSplitter(Qt::Horizontal, splitter3);
	//	splitter4->addWidget(ui.gbx_Para);
	//	splitter4->setFixedHeight(nHeight*0.24);
	//	m_splitter->addWidget(splitter2);
	//}
	//QGridLayout *mainly = new QGridLayout;
	//mainly->addWidget(m_splitter);

	//this->setLayout(mainly);
	//this->setCentralWidget(m_splitter);

	setmyStyle("qss/a.qss");
	/*QString path = QCoreApplication::applicationDirPath();
	path = path + "/a.qss";*/
	//qDebug()<< path;
	/*QString qss;
	QFile qssFile(path);
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
	qss = QLatin1String(qssFile.readAll());
	qApp->setStyleSheet(qss);
	qssFile.close();
	}
	*/
}
#pragma endregion

#pragma region 定时器发送要数指令
void KI::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_nTimerIp)
	{
		if (k_Protocal == 1)//UDP
		{
			QHostAddress address(host);
			receiver->writeDatagram(zl_Getnum, zl_Getnum.length(), address, DEST_PORT);
		}
		//receiver->waitForBytesWritten(10);
		else//TCP
		{
			workThread->Sendzhiling(zl_Getnum);
			/*tcpSocket->write(zl_Getnum, zl_Getnum.length());*/

		}
	}
}
#pragma endregion

#pragma region 尺标
void KI::CBClick()//尺标
{
	/*pclfunc->Chibiao(grid_enabled_);
	grid_enabled_ = !grid_enabled_;*/
}
#pragma endregion

#pragma region 点/线模式切换
void KI::PointOrLineClick(void)//点/线切换
{
	if (f_PointOrLine)
	{
		pclfunc->PointOrPolyline(f_PointOrLine);
		ui.btn_PointTest->setText(QString::fromLocal8Bit("点"));
		f_PointOrLine = false;
	}
	else
	{
		pclfunc->PointOrPolyline(f_PointOrLine);
		ui.btn_PointTest->setText(QString::fromLocal8Bit("线"));
		f_PointOrLine = true;
	}
}
#pragma endregion

#pragma region 旋转
void KI::RotateClick()
{
	pclfunc->RotateViewTo();
}
#pragma endregion

#pragma region 变化视角
//旋转上向量，即摄像机正方向，相机的镜头朝向和位置沿着Z轴逆时针90度 主动旋转是指将向量逆时针围绕旋转轴所做出的旋转

void KI::MoveZDOWN(void)
{
	pclfunc->setViewTo(2, -1);
}
void KI::MoveZUP(void)
{
	pclfunc->setViewTo(2, 1);
}
void KI::MoveYDOWN(void)
{
	pclfunc->setViewTo(1, -1);
}
void KI::MoveYUP(void)
{
	pclfunc->setViewTo(1, 1);
}
void KI::MoveXDOWN(void)
{
	pclfunc->setViewTo(0, -1);
}
void KI::MoveXUP(void)
{
	pclfunc->setViewTo(0, 1);
}
#pragma endregion 

#pragma region 判断是否为IP地址
int isipv4str(QString ip)
{
	char*  ch;
	QByteArray ba = ip.toLatin1(); // must
	ch = ba.data();
	int i, a[4];
	if (sscanf(ch, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]) != 4)
		return 0;
	for (i = 0; i < 4; i++) if (a[i] < 0 || a[i] > 255) return 0;
	return 1;
}
#pragma endregion 

#pragma region TCP下连接到激光器
void KI::ConnTcpClick()
{
	if (f_ConOrDiscon)
	{
		host = ui.hostLineEdit->text();
		port = ui.txt_tcpPort->text().toInt();
		if (host.length() > 7 && port > 0)
		{
			if (isipv4str(host) == 1)
			{
				try
				{
					k_Protocal = 0;
					workThread = new workthread(this, pclfunc, NULL);
					workThread->start();
				}
				catch (exception& e)
				{
					str_hintinfo = e.what();
					Infoview(2, "", str_hintinfo);
				}
			}
			else
			{
				str_hintinfo = QString::fromLocal8Bit("连接失败，激光器IP填写格式错误！");
				Infoview(2, "", str_hintinfo);
			}
		}
		else
		{
			str_hintinfo = QString::fromLocal8Bit("IP地址或端口号填写错误！");
			Infoview(2, "", str_hintinfo);
		}
	}
#pragma region 网络断开
	else
	{
		if (!f_conscan)
			ContinueScanClick();
		if (workThread != NULL)
		{
			workThread->requestInterruption();
			workThread->quit();
			workThread->wait();
			//workThread->terminate();
			if (workThread->DisconnectServer())
			{
				f_NetConState_TCP = false;
				f_ConOrDiscon = true;
				ui.btn_Conn_tcp->setText(QString::fromLocal8Bit("TCP连接"));
				str_hintinfo = QString::fromLocal8Bit("网络已断开！");
				controlset(true);
			}
			else
			{
				str_hintinfo = QString::fromLocal8Bit("网络断开失败，请重新断开！");
			}
			delete workThread;
			workThread = NULL;
			Infoview(2, "", str_hintinfo);
		}
	}
#pragma endregion
}
#pragma endregion

#pragma region UDP连接
void KI::ConnUdpClick(void)
{
	if (f_ConOrDiscon_UDP)
	{
		host = ui.hostLineEdit->text();
		if (host.length() > 0)
		{
			if (host.length() > 7)
			{
				try
				{
					if (isipv4str(host) == 1)
					{
						if (receiver == NULL)
						{
							receiver = new QUdpSocket(this);
							/////绑定，第一个参数为端口号，第二表示允许其它地址链接该广播
							receiver->bind(LOCAL_PORT, QUdpSocket::ShareAddress);
						}
						k_Protocal = 1;//UDP
						workThread = new workthread(this, pclfunc, receiver);
						workThread->start();
						ui.btn_BroadCast->setEnabled(false);
						ui.btn_Continue->setEnabled(true);
						str_hintinfo = QString::fromLocal8Bit("连接成功！");
						controlset(false);
						f_ConOrDiscon_UDP = false;
						ui.btn_Conn->setText(QString::fromLocal8Bit("断开"));
						Infoview(2, "", str_hintinfo);
					}
					else
					{
						str_hintinfo = QString::fromLocal8Bit("连接失败，激光器IP填写格式错误！");
						Infoview(2, "", str_hintinfo);
					}
				}
				catch (exception&e)
				{
					str_hintinfo = e.what();
					Infoview(2, "", str_hintinfo);
				}
			}
			else
			{
				str_hintinfo = QString::fromLocal8Bit("连接失败，激光器IP填写格式错误！");
				Infoview(2, "", str_hintinfo);
			}
		}
		else
		{
			str_hintinfo = QString::fromLocal8Bit("IP地址不能为空！");
			Infoview(2, "", str_hintinfo);
		}
	}
	else
	{
		if (!f_conscan)
			ContinueScanClick();
		if (workThread != NULL)
		{
			workThread->terminate();
			workThread = NULL;
		}
		receiver = NULL;
		f_ConOrDiscon_UDP = true;
		ui.btn_Conn->setText(QString::fromLocal8Bit("UDP连接"));
		str_hintinfo = QString::fromLocal8Bit("网络已断开！");
		controlset(true);
		Infoview(2, "", str_hintinfo);
	}
}
#pragma endregion

#pragma region 断开或连接的时候控件状态控制
void KI::controlset(bool f_set)
{

	ui.cbx_Protocal->setEnabled(f_set);
	ui.hostLineEdit->setEnabled(f_set);
	ui.txt_tcpPort->setEnabled(f_set);
	ui.btn_Continue->setEnabled(!f_set);
	ui.gbx_Para->setEnabled(!f_set);
	ui.txt_mac->setEnabled(false);
}
#pragma endregion

#pragma region 广播
bool f_BrocasrStatec = false;//广播是否成功标志位 
QTimer *timer_Brocast = NULL;
void KI::Broadcast(void)
{
	if (receiver != NULL)
	{
		receiver->disconnectFromHost();
		receiver = NULL;
	}
	f_BrocasrStatec = false;
	receiver = new QUdpSocket();
	receiver->bind(LOCAL_PORT, QUdpSocket::ShareAddress);
	zl_Brocast = pDatafunc->QString2Hex("FFAA001E0000000000000101000700000000000000000406000000000000001BEEEE");
	str_hintinfo = QString::fromLocal8Bit("正在广播....");
	Infoview(2, "", str_hintinfo);
	receiver->writeDatagram(zl_Brocast, 34, QHostAddress::Broadcast, DEST_PORT);
	receiver->waitForBytesWritten(1000);
	connect(receiver, &QUdpSocket::readyRead, this, &KI::UDP_socket_Read_Data);
	timer_Brocast = new QTimer(this);
	connect(timer_Brocast, SIGNAL(timeout()), this, SLOT(timerUpDate()));
	timer_Brocast->start(2000);
	ui.btn_BroadCast->setEnabled(false);
}

void KI::timerUpDate()
{
	if (!f_BrocasrStatec)
	{
		Infoview(2, "", QString::fromLocal8Bit("广播失败,请确认激光器状态!"));
		if (timer_Brocast->isActive())
		{
			timer_Brocast->stop();
		}
		if (timer_Brocast)
		{
			delete timer_Brocast;
		}
		ui.btn_BroadCast->setEnabled(true);
	}
	else
	{
		if (timer_Brocast->isActive())
		{
			timer_Brocast->stop();
		}
		if (timer_Brocast)
		{
			delete timer_Brocast;
		}
	}
}

void KI::UDP_socket_Read_Data()
{
	QByteArray datagram = NULL;
	datagram.resize(receiver->pendingDatagramSize());
	receiver->readDatagram(datagram.data(), datagram.size());
	receiver->waitForReadyRead(100);
	QString IP_First = QString::number((unsigned char)(datagram[26]), 10);
	QString IP_Second = QString::number((unsigned char)(datagram[27]), 10);
	QString IP_Third = QString::number((unsigned char)(datagram[28]), 10);
	QString IP_Fourth = QString::number((unsigned char)(datagram[29]), 10);
	QString s_IPAdress = IP_First + "." + IP_Second + "." + IP_Third + "." + IP_Fourth;
	int port = ((unsigned char)datagram[38] << 8) + ((unsigned char)datagram[39]);
	QString s_Port = QString::number(port, 10);
	if (s_IPAdress.length() >= 7 && s_Port.length() > 1)
	{
		Infoview(2, "", QString::fromLocal8Bit("广播成功!"));
		f_BrocasrStatec = true;
		ui.hostLineEdit->setText(s_IPAdress);
		ui.txt_tcpPort->setText(s_Port);
	}
}

#pragma endregion

#pragma region 窗口关闭事件
void KI::closeEvent(QCloseEvent *event)
{
	//TODO: 在退出窗口之前，实现希望做的操作 
	if (QMessageBox::question(this,
		QString::fromLocal8Bit("退出"),
		QString::fromLocal8Bit("确定关闭此应用？"),
		QMessageBox::Yes, QMessageBox::No)
		== QMessageBox::Yes)
	{
		if (workThread != NULL)
		{
			/*workThread->terminate();*/
			workThread->requestInterruption();
			//workThread->quit();*/
			/*workThread->wait();*/
			workThread->DisconnectServer();
			/*workThread = NULL;*/
		}
		if (receiver != NULL)
		{
			receiver->disconnectFromHost();
			receiver = NULL;
		}
		event->accept();//不会将事件传递给组件的父组件
		//exit(0);
	}
	else
		event->ignore();
}
#pragma endregion

#pragma region 连续扫描
void KI::ContinueScanClick()
{
	if (f_conscan)
	{
		workThread->Sendzhiling(zl_LMDetect);//设置靶标探测模式
		Sleep(30);
		m_nTimerIp = startTimer(160);
		ui.btn_Continue->setText(QString::fromLocal8Bit("停止获取波形"));
		f_conscan = false;
		QString qstr = QString::fromLocal8Bit("获取连续波形！");
		Infoview(2, "", qstr);
	}
	else
	{
		killTimer(m_nTimerIp);
		ui.btn_Continue->setText(QString::fromLocal8Bit("获取连续波形"));
		f_conscan = true;
		QString qstr = QString::fromLocal8Bit("停止获取波形！");
		Infoview(2, "", qstr);

	}
}
#pragma endregion

#pragma region 提示信息
void KI::Infoview(int info_Kind, QString slotinfo, QString qstr)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("hh:mm:ss.zzz") + tr(":");
	ui.tbr_Info->append(current_date + qstr);
}
#pragma endregion

#pragma region 错误帧数数据显示
void KI::showwrong(int wrongnum, int allnum, float wro_prop)
{
	ui.txt_wrozs->setText(QString::number(wrongnum, 10));
	ui.txt_zzs->setText(QString::number(allnum, 10));
	ui.txt_wroprop->setText(QString::number(wro_prop, 'f', 4));
}
#pragma endregion 

#pragma region 网络参数查询
void KI::NetParaQueryClick()
{
	zl_NetParaQuery = pDatafunc->QString2Hex("FFAA001E0000000000000101000700000000000000000502000000000000001EEEEE");
	workThread->Sendzhiling(zl_NetParaQuery);
}
void KI::NetParaInfoView(QString ip, QString port, QString Mask, QString getway, QString mac)
{
	ui.txt_IP->setText(ip);
	ui.txt_port->setText(port);
	ui.txt_mask->setText(Mask);
	ui.txt_getway->setText(getway);
	ui.txt_mac->setText(mac);
	str_hintinfo = QString::fromLocal8Bit("网络参数查询成功！");
	Infoview(2, "", str_hintinfo);
}
#pragma endregion

#pragma region 网络参数设置
void KI::NetParaSettingClick()
{
	QString str_host = ui.txt_IP->text();
	if (f_NetConState_TCP)//网络已连接
	{
		if (host.length() > 7)
		{
			if (isipv4str(host) == 1 && isipv4str(ui.txt_mask->text()) == 1 && isipv4str(ui.txt_getway->text()) == 1)
			{
				if (ui.txt_port->text().toInt() > 0)
				{
					QString IPinfo = pDatafunc->GetInforFromMark(host, '.');
					QString Maskinfo = pDatafunc->GetInforFromMark(ui.txt_mask->text(), '.');
					QString Getwayinfo = pDatafunc->GetInforFromMark(ui.txt_getway->text(), '.');
					QString Portinfo = QString("%1").arg(ui.txt_port->text().toInt(), 4, 16, QLatin1Char('0'));
					QString Macinfo = ui.txt_mac->text().trimmed().replace(QString("-"), QString(""));
					QString NetParaSet_Ord = "002F0000000A140901010007000000000000000005030000" + IPinfo + Maskinfo + Getwayinfo + Portinfo + Macinfo + "00";
					QString BCC = pDatafunc->GetBCCXorCode(NetParaSet_Ord);
					NetParaSet_Ord = "FFAA" + NetParaSet_Ord + BCC + "EEEE";
					QByteArray NetPara_Ord = pDatafunc->QString2Hex(NetParaSet_Ord);
					workThread->Sendzhiling(NetPara_Ord);
				}
				else
				{
					str_hintinfo = QString::fromLocal8Bit("端口格式错误！");
					Infoview(2, "", str_hintinfo);
				}
			}
			else
			{
				str_hintinfo = QString::fromLocal8Bit("IP地址格式错误！");
				Infoview(2, "", str_hintinfo);
			}
		}
		else
		{
			str_hintinfo = QString::fromLocal8Bit("IP地址格式错误！");
			Infoview(2, "", str_hintinfo);
		}
	}
	else
	{
		str_hintinfo = QString::fromLocal8Bit("网络未连接或已断开！");
		Infoview(2, "", str_hintinfo);
	}
}
#pragma endregion

#pragma region 通信协议发生变化
void KI::ProtocalChanged()
{
	if (ui.cbx_Protocal->currentIndex() == 0)//tcp
	{
		ui.btn_Conn_tcp->setVisible(true);
		ui.btn_Conn->setVisible(false);
		ui.gbx_Para->setVisible(true);
		//ui.widget_PCL->setFixedHeight(ui.widget_Show->height());
		//pclfunc->ChangePCLView(ui.widget_Show->width(), ui.widget_Show->height());
		//LayoutDesign();
	}
	else
	{
		ui.btn_Conn_tcp->setVisible(false);
		ui.btn_Conn->setVisible(true);
		ui.gbx_Para->setVisible(false);
	/*	int y = ui.widget_Show->height() + ui.widget_LaserPara->height();
		ui.widget_PCL->setFixedHeight(y);
		pclfunc->ChangePCLView(ui.widget_Show->width(), y);*/
		//LayoutDesign();
	}
}
#pragma endregion 

#pragma region 统计数据显示
void KI::Countdataview(int max, int min, int avg)
{
	ui.txt_countmax->setText(QString::number(max, 10));
	ui.txt_countmin->setText(QString::number(min, 10));
	ui.txt_countavg->setText(QString::number(avg, 10));
}
#pragma endregion

#pragma region 统计信息参数变化
void KI::CountPackChanged()
{
	n_sigcountpack = ui.txt_sigcountpack->text().toInt();
}

void KI::CountPointChanged()
{
	n_sigcountpoint = ui.txt_countpoint->text().toInt();
}
#pragma endregion

#pragma region TCP网络连接反馈
void KI::TcpConnInfo(bool b_conn)
{
	if (b_conn)
	{
		ui.btn_Conn_tcp->setText(QString::fromLocal8Bit("断开"));
		str_hintinfo = QString::fromLocal8Bit("网络连接成功！");
		controlset(false);
		Infoview(2, "", str_hintinfo);
		f_ConOrDiscon = false;
		f_NetConState_TCP = true;//表示TCP网络已连接
		ui.btn_Continue->setEnabled(true);
	}
	else
	{
		str_hintinfo = QString::fromLocal8Bit("网络连接失败！");
		Infoview(2, "", str_hintinfo);
	}
}
#pragma endregion

#pragma region 基本参数查询
void KI::BaseParaQueryClick()
{
	zl_BaseParaQuery = pDatafunc->QString2Hex("FFAA001E0000000000000101000700000000000000000601000000000000001EEEEE");
	workThread->Sendzhiling(zl_BaseParaQuery);
}
void KI::BaseParaInfoView(int heart, int ratio)
{
	if (heart == 1)//心跳开启
	{
		ui.cbx_heart->setCurrentIndex(1);
	}
	else
	{
		ui.cbx_heart->setCurrentIndex(0);
	}
	if (ratio == 1)//分辨率0.1
	{
		ui.cbx_ratio->setCurrentIndex(1);
	}
	else
	{
		ui.cbx_ratio->setCurrentIndex(0);
	}
	str_hintinfo = QString::fromLocal8Bit("基本参数查询成功！");
	Infoview(2, "", str_hintinfo);
}
#pragma endregion

#pragma region 基本参数设置
void KI::BaseParaSetClick()
{
	QString heart, ratio;
	if (ui.cbx_heart->currentIndex() == 0)
	{
		heart = "00";
	}
	else
	{
		heart = "01";
	}
	if (ui.cbx_ratio->currentIndex() == 0)
	{
		ratio = "02";
	}
	else
	{
		ratio = "01";
	}
	QString BaseParaSet_ord = "001E00000000000001010007000000000000000006020000" + heart + ratio + "0000";
	QString BCC = pDatafunc->GetBCCXorCode(BaseParaSet_ord);
	BaseParaSet_ord = "FFAA" + BaseParaSet_ord + BCC + "EEEE";
	QByteArray zl_BaseParaSet = pDatafunc->QString2Hex(BaseParaSet_ord);
	workThread->Sendzhiling(zl_BaseParaSet);
	sum_framenum = 0;
	wrong_framenum = 0;
}
#pragma endregion

KI::~KI()
{
	disconnect(receiver, &QUdpSocket::readyRead, this, &KI::UDP_socket_Read_Data);
	disconnect(timer_Brocast, SIGNAL(timeout()), this, SLOT(timerUpDate()));
	if (workThread)
	{
		if (workThread->isRunning())
		{
			workThread->requestInterruption();
			workThread->quit();
			workThread->wait();
		}
		delete workThread;
		workThread = NULL;
	}
}