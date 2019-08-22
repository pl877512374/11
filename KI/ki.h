#ifndef KI_H
#define KI_H
#include <QtWidgets/QMainWindow>
#include "ui_ki.h"
#include "5.7.0\QtCore\private\cp949codetbl_p.h"
#include <QtNetwork/QtNetwork>
#include <QCloseEvent>
#include <QResizeEvent>
#include<QMessageBox>
#include <QTextStream>
#include <QStandardItemModel>
#include<QSplitter>
#include<QGridLayout>
#include "PCLFunc.h"
#include "datadealfunc.h"
#include <QDesktopWidget>
#define LOCAL_PORT 7000
#define DEST_PORT 6060
extern int sum_framenum;
extern int wrong_framenum;
class KI : public QMainWindow
{
	Q_OBJECT

public:
	KI(QWidget *parent = 0);
	~KI();
	void Infoview(int info_Kind,QString slotinfo, QString qstr = "");//slotinfo为槽函数中返回的信息，qstr为操作提示信息或错误信息
	void showwrong(int wrongnum,int allnum, float wro_prop);//错误帧统计显示
	void NetParaInfoView(QString ip,QString port,QString Mask,QString getway,QString mac);//网络参数数据显示
	void BaseParaInfoView(int heart, int ratio);//基本参数数据显示
	void Countdataview(int max, int min, int avg);//统计数据显示
	void TcpConnInfo(bool b_conn);//TCP连接信息显示
private:
	Ui::KIClass ui;
	void timerEvent(QTimerEvent* event);
	void LayoutDesign();
	void controlset(bool f_set);//控制网络部分控件
	//创建连接槽
private slots:
	void MoveZUP(void);
	void MoveZDOWN(void);
	void MoveYUP(void);
	void MoveYDOWN(void);
	void MoveXUP(void);
	void MoveXDOWN(void);
	void RotateClick();
	void PointOrLineClick();
	void ConnUdpClick(void);
	void Broadcast(void);
	void CBClick();
	void ContinueScanClick();//连续扫描
	void ConnTcpClick();
	void NetParaQueryClick();
	void NetParaSettingClick();
	void ProtocalChanged();
	void CountPackChanged();
	void CountPointChanged();
	void BaseParaQueryClick();
	void BaseParaSetClick();
	void timerUpDate();
	void UDP_socket_Read_Data();
protected:
	void closeEvent(QCloseEvent *event);
	virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // PCLVISUALIZER_H