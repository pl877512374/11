#pragma once
#include <QThread>
#include <QtNetwork/QtNetwork>
#include "ki.h"
#include "PCLFunc.h"
#include "datadealfunc.h"
#include <vector>
using namespace std;
#define PI  3.14159265358979323846
class workthread:public QThread
{
	Q_OBJECT
public:
	workthread(KI *Ck, PCLFunc *pclfun, QUdpSocket * UDPClient);
	~workthread();
	void Sendzhiling(QByteArray send);
	bool DisconnectServer();
private:
	KI *Cki;
	PCLFunc *pclfun;
	DataDealFunc *pDfunc;
	QByteArray heart_zl;
	float wrong_prop;//������
	int k_protocal;//Э������ 0:TCP 1:UDP
	void getMaxOrMin(vector<int> arr, int count,int *rval);
signals:
	void Draw_sig(int);
	void CountDataView_sig(int,int,int);
	void InfoView_sig(QString);
	void Enablebtn();//ʹ�����水ť�ָ�����
	void wrong_info(int,int,float );//����֡����ʾ
	void TcpConnInfo_sig(bool);
	void sig_NetParaview(QString, QString, QString, QString,QString);//���������ѯ
	void sig_BaseParaView(int,int);//����������ѯ
public slots:
	void Draw_slot(int);
	void CountDataView_slot(int,int,int);
	void InfoView_slot(QString);
	void wronginfo_slot(int,int,float);
	void connect_false(QAbstractSocket::SocketError);
	void TcpConnInfo_slot(bool);
	void slot_NetParaview(QString, QString, QString, QString, QString);
	void slot_BaseParaView(int, int);
protected:
	void run();
	void OnNetRecv(char *pDataBuf, int nDataBufSize);

};

