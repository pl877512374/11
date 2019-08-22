#include "workthread.h"
#include "resource.h"
const int MAX_BLOCK = 10000;
const int NET_BUF_NUM = 100;
const int NET_BUFCOL_NUM = 5000;
int xorflag = 0;//У����
int count_framenum = 0;//ͳ��֡��(ͳ��ĳ����ľ���)
bool f_tcpNetConn = false;//TCP�����Ƿ����ӱ�־
bool f_addAngEnergy = false;//�Ƿ���Ҫ�ǶȲ�����־λ
int g_n32MaxDis = 50000;//�����ֵ
int g_n32NetRcvdPkgs = 0;
QTcpSocket *TCPRecSocket = NULL;
QUdpSocket * UDPClient = NULL;
float m_LaserPose[4] = { 0 };//������λ��
int g_n32CircleNo = 0;//Ȧ�ű������仯��Ȧ��ֵ��
int SZ_Serial = 0;//ÿһȦ��ÿһ�����к�
bool b_readfinish = false;//һ֡������û�ж������һ���ı�־
int g_n32NetRecvID = 0;//ÿһ֡���ݵ�ID
int *countval = NULL;//����ͳ��ֵ
int sum_framenum = 0, wrong_framenum = 0;//��֡��������֡�� Ҫ�ڱ������ʹ�ã����Բ�Ҫ�ŵ�ͷ�ļ���ȥ
char g_cNetRecvBuf[NET_BUF_NUM][NET_BUFCOL_NUM];
float g_n64ArrayZhiX[7200] = { 0 };
float g_n64ArrayZhiY[7200] = { 0 };
float g_n64ArrayZhiZ[7200] = { 0 };
float g_n64ArrayCompenAngle[7200] = { 0 }, g_n64ArrayEnergy[7200] = { 0 };//�ǶȲ������������ֵ����
extern int n_sigcountpoint;//ͳ�Ƶ����
extern int n_sigcountpack;//����ͳ�ư���
extern int k_Protocal;//Э������
extern QString host;//�豸��IP��ַ
extern int port;//�豸�Ķ˿ں�
typedef struct TagNetDataStruct
{
	char m_pcData[20000];
	int  m_n32Len;
	int m_n32BufCnt;
	int m_n32Channel;
}NetDataStruct;
NetDataStruct g_sNetData;
typedef struct TagStructNetBuf
{
	char m_acbuf[MAX_BLOCK * 10];
	unsigned int m_u32in;
	unsigned int m_u32out;
	unsigned int m_u32size;
}
StructNetBuf;
StructNetBuf g_sNetBuf;
typedef struct TagStructNetTemBuf
{
	char g_byteLstDistancePkgsScanDat[14400];
	char g_byteLstAnglePkgsScanDat[7200];
	char g_byteLstEnergyPkgsScanDat[7200];
	int g_32ScanPackNo[25];//��¼ÿһȦ�е�ÿһ���Ķ�Ӧ�İ���
	int g_n32ScanDatID[25];//��¼ÿһȦ��ÿһ����Ӧ��ID
	unsigned int m_u32in;
}StructNetTemBuf;
StructNetTemBuf g_sNetTemBuf;
workthread::workthread(KI *Ck, PCLFunc *pclfun, QUdpSocket * UDPclient)
{
	this->Cki = Ck;
	this->pclfun = pclfun;
	if (k_Protocal == 1)
	{
		UDPClient = new QUdpSocket;
		UDPClient = UDPclient;
	}
	connect(this, SIGNAL(Draw_sig(int)), this, SLOT(Draw_slot(int)));
	connect(this, SIGNAL(InfoView_sig(QString)), this, SLOT(InfoView_slot(QString)));
	connect(this, SIGNAL(wrong_info(int, int, float)), this, SLOT(wronginfo_slot(int, int, float)));
	connect(this, SIGNAL(CountDataView_sig(int, int, int)), this, SLOT(CountDataView_slot(int, int, int)));
}
workthread::~workthread()
{
	disconnect(this, SIGNAL(Draw_sig(int)), this, SLOT(Draw_slot(int)));
	disconnect(this, SIGNAL(InfoView_sig(QString)), this, SLOT(InfoView_slot(QString)));
	disconnect(this, SIGNAL(wrong_info(int, int, float)), this, SLOT(wronginfo_slot(int, int, float)));
	disconnect(this, SIGNAL(CountDataView_sig(int, int, int)), this, SLOT(CountDataView_slot(int, int, int)));
	disconnect(TCPRecSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connect_false(QAbstractSocket::SocketError)));
	disconnect(this, SIGNAL(TcpConnInfo_sig(bool)), this, SLOT(TcpConnInfo_slot(bool)));
	disconnect(this, SIGNAL(sig_NetParaview(QString, QString, QString, QString, QString)), this, SLOT(slot_NetParaview(QString, QString, QString, QString, QString)));
	disconnect(this, SIGNAL(sig_BaseParaView(int, int)), this, SLOT(slot_BaseParaView(int, int)));
	if (TCPRecSocket)
	{
		if (f_tcpNetConn)
		{
			TCPRecSocket->disconnectFromHost();
		}
		delete TCPRecSocket;
		TCPRecSocket = NULL;
	}
	if (UDPClient)
	{
		delete UDPClient;
		UDPClient = NULL;
	}

}
void workthread::run()
{
	if (k_Protocal == 0)//TCPЭ��
	{
		TCPRecSocket = new QTcpSocket;
		connect(TCPRecSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connect_false(QAbstractSocket::SocketError)));
		connect(this, SIGNAL(TcpConnInfo_sig(bool)), this, SLOT(TcpConnInfo_slot(bool)));
		connect(this, SIGNAL(sig_NetParaview(QString, QString, QString, QString, QString)), this, SLOT(slot_NetParaview(QString, QString, QString, QString, QString)));
		connect(this, SIGNAL(sig_BaseParaView(int, int)), this, SLOT(slot_BaseParaView(int, int)));
		TCPRecSocket->connectToHost(host, port, QTcpSocket::ReadWrite); //��������
		if (TCPRecSocket->waitForConnected(100))//�����٣�������Ҫһ����ʱ��
		{
			f_tcpNetConn = true;
		}
		else
		{
			f_tcpNetConn = false;
		}
		//Sleep(500);
		emit TcpConnInfo_sig(f_tcpNetConn);
	}
	int nRecvSize = 0;
	while (!isInterruptionRequested())
	{
		QByteArray arr = "";
		if (k_Protocal == 1)
		{
			while (UDPClient->hasPendingDatagrams())//��������жϾͻ�����еİ�����û�н���
			{
				arr.resize(UDPClient->pendingDatagramSize());
				UDPClient->readDatagram(arr.data(), arr.size());
			}
			nRecvSize = arr.size();
		}
		else
		{
			if (f_tcpNetConn)//TCP����������
			{
				if (TCPRecSocket->waitForReadyRead(100))
				{
					arr = TCPRecSocket->readAll();
					nRecvSize = arr.size();
				}
				else
				{
					qDebug() << TCPRecSocket->errorString();
				}
			}
		}
		if (nRecvSize <0)
		{
			continue;
		}
#pragma region ��һ���������
		if ((g_sNetBuf.m_u32in + nRecvSize) >= MAX_BLOCK * 10)
		{
			memset(&g_sNetBuf, 0, sizeof(g_sNetBuf));//������󻺴棬ԭ������ȫ��0
			continue;
		}
#pragma endregion
		memcpy(&g_sNetBuf.m_acbuf[g_sNetBuf.m_u32in], arr, nRecvSize*sizeof(char));
		g_sNetBuf.m_u32in += nRecvSize;
#pragma region �ڶ����������
		if (g_sNetBuf.m_u32in >= MAX_BLOCK * 10)
		{
			memset(&g_sNetBuf, 0, sizeof(g_sNetBuf));
			break;
		}
#pragma endregion
		while (g_sNetBuf.m_u32out < g_sNetBuf.m_u32in)
		{
			int l_u32reallen = 0;
			if ((((unsigned char)g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out] == 0xff &&
				(unsigned char)g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + 1] == 0xaa)))
			{
				l_u32reallen = ((unsigned char)g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + 3] << 0) |
					((unsigned char)g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + 2] << 8);
				l_u32reallen += 4;                                             //һ֡���ݵ�ʵ�ʳ���Ӧ����֡ͷ֡β4���ֽ�
			}
			else
			{
				g_sNetBuf.m_u32out++;  //�Ұ�ͷ
			}
#pragma region �жϰ�������ʵ�ʻ��泤��֮��Ĺ�ϵ
			if (l_u32reallen <= (g_sNetBuf.m_u32in - g_sNetBuf.m_u32out + 1))
			{
				//���ݷ�֡����
				OnNetRecv(&g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out], l_u32reallen);//����һ֡����
				//1.У�鴦��
#pragma region ���У�����
				if (xorflag == 1)
				{
					int i;
					for (i = 1; i < l_u32reallen; i++)
					{
						if ((g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i] == 0x02 && g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i + 1] == 0x02 && g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i + 2] == 0x02 && g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i + 3] == 0x02)
							|| (g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i] == 0xff && g_sNetBuf.m_acbuf[g_sNetBuf.m_u32out + i + 1] == 0xff))
						{
							g_sNetBuf.m_u32out += i;
							xorflag = 0;
							break;
						}

					}
					if (i == l_u32reallen && xorflag == 1)
					{
						g_sNetBuf.m_u32out += l_u32reallen;
					}
					xorflag = 0;
				}
#pragma endregion
				else
					g_sNetBuf.m_u32out += l_u32reallen;
			}
#pragma endregion
#pragma region �������������
			else if (l_u32reallen >= MAX_BLOCK)
			{
				memset(&g_sNetBuf, 0, sizeof(g_sNetBuf));//������󻺴棬ԭ������ȫ��0
				continue;
			}
#pragma endregion
			else
			{
				break;
			}
		}
#pragma region ���Ĵ��������
		if ((g_sNetBuf.m_u32in + nRecvSize) >= MAX_BLOCK * 10)
		{
			//������󻺴棬ԭ������ȫ��0
			memset(&g_sNetBuf, 0, sizeof(g_sNetBuf));//������󻺴棬ԭ������ȫ��0
			continue;
		}
#pragma endregion
#pragma region ������������
		if (g_sNetBuf.m_u32out >= g_sNetBuf.m_u32in)//��ʱ֤��������������ݶ��Ѿ�������ɣ��������
		{
			//��ʱ֤��������������ݶ��Ѿ�������ɣ��������");
			memset(&g_sNetBuf, 0, sizeof(g_sNetBuf));//������󻺴棬ԭ������ȫ��0
		}
#pragma endregion
	}
}

int temp_Packnum;
int PackSum = 0;
int RecNum;
void workthread::OnNetRecv(char *pDataBuf, int nDataBufSize)
{
	if (nDataBufSize > 0)
	{
		if (pDfunc->checkXor(pDataBuf, nDataBufSize))
		{
			memcpy(g_cNetRecvBuf[g_n32NetRecvID], pDataBuf, nDataBufSize);
			switch ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][22])
			{
#pragma region 0x02
			case 0x02:
			{
						 g_n32NetRcvdPkgs++;
						 int CirclNo = (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][81];   //Ȧ��
						 if (g_n32NetRcvdPkgs == 1)//����ǵ�һ������
						 {
							 g_n32CircleNo = CirclNo;               //��¼��һ�����ݵ�Ȧ��
						 }
						 int PackNo = (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][82];  //��Ȧ����
						 int RatioMark = (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][80];
						 if (RatioMark == 0) //12��
						 {
							 switch (PackNo)
							 {
							 case 1:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[0], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 2:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[1200], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 3:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[2400], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 4:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[3600], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 5:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[4800], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 6:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[6000], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 7:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[7200], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 8:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[8400], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 9:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[9600], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 10:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[10800], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 11:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[12000], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 12:
								 PackSum += PackNo;
								 temp_Packnum = PackSum;
								 if (temp_Packnum != 78)
								 {
									 RecNum = temp_Packnum;
								 }
								 memcpy(&g_sNetData.m_pcData[13200], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 b_readfinish = true;
								 break;
							 default:
								 break;
							 }
						 }
						 else if (RatioMark == 1)
						 {
							 switch (PackNo)
							 {
							 case 1:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[0], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 2:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[1200], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 3:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[2400], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 4:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[3600], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 5:
								 PackSum += PackNo;
								 memcpy(&g_sNetData.m_pcData[4800], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 break;
							 case 6:
								 PackSum += PackNo;
								 temp_Packnum = PackSum;
								 if (temp_Packnum != 21)
								 {
									 RecNum = temp_Packnum;
								 }
								 memcpy(&g_sNetData.m_pcData[6000], &g_cNetRecvBuf[g_n32NetRecvID][86], 1200);
								 b_readfinish = true;
								 break;
							 default:
								 break;
							 }
						 }
						 if (g_n32CircleNo != CirclNo)
						 {
							 if (count_framenum == 0)
							 {
								 countval = new int[n_sigcountpack];
							 }
							 int RightPackNum, BufLength;
							 float AngRatio;
							 if (RatioMark == 0)
							 {
								 RightPackNum = 78;
								 BufLength = 14400;
								 AngRatio = 0.05;
							 }
							 else if (RatioMark == 1)
							 {
								 RightPackNum = 21;
								 BufLength = 7200;
								 AngRatio = 0.1;
							 }
							 if (b_readfinish&&temp_Packnum == RightPackNum)
							 {
								 sum_framenum++;
								 PackSum = 0;
								 int nDataZhiCount = 0;
								 int nDataJi = 0;
								 float l_64nDataRegionZhiX = 0;
								 float l_64nDataRegionZhiY = 0;
								 float l_n64actualangle = 0;
								 for (int m = 0; m < BufLength; m += 2)
								 {
									 nDataJi = ((g_sNetData.m_pcData[m] & 0xFF) << 8) + (BYTE)g_sNetData.m_pcData[m + 1];//(BYTE)һ��Ҫ�ӣ����Ӿͻ���ָ�ֵ
									 if (m == n_sigcountpoint * 2 && count_framenum<n_sigcountpack)
									 {
										 countval[count_framenum] = nDataJi;
									 }
									 if (nDataJi > g_n32MaxDis)         //�����ֵ
										 nDataJi = g_n32MaxDis;
									 l_n64actualangle = nDataZhiCount *AngRatio;
									 l_64nDataRegionZhiX = nDataJi *cos(l_n64actualangle / 180 * 3.14) / 1000.0;
									 l_64nDataRegionZhiY = nDataJi *sin(l_n64actualangle / 180 * 3.14) / 1000.0;
									 g_n64ArrayZhiX[nDataZhiCount] = l_64nDataRegionZhiX;
									 g_n64ArrayZhiY[nDataZhiCount] = l_64nDataRegionZhiY;
									 g_n64ArrayZhiZ[nDataZhiCount] = 1;
									 nDataZhiCount++;
								 }
								 count_framenum++;
								 if (count_framenum >= n_sigcountpack)
								 {
									 int r_val[3] = {0};
									 getMaxOrMin(countval, count_framenum, r_val);
									 int max_val = r_val[0];
									 int min_val = r_val[1];
									 int avg_val = r_val[2];
									 if (abs(max_val) < g_n32MaxDis && abs(min_val) < g_n32MaxDis && abs(avg_val) < g_n32MaxDis)
										 emit CountDataView_sig(max_val, min_val, avg_val);
									 count_framenum = 0;
									 if (countval)
									 {
										 delete[]countval;
										 countval = NULL;
									 }
								 }
								 if (RatioMark == 0)
								 {
									 emit Draw_sig(1);//������ʾ
								 }
								 else if (RatioMark == 1)
								 {
									 emit Draw_sig(2);//������ʾ
								 }
							 }
							 else
							 {
								 int n = temp_Packnum;
								 temp_Packnum = 0;
								 wrong_framenum++;
							 }
							 wrong_prop = (float)wrong_framenum / (float)sum_framenum;
							 emit wrong_info(wrong_framenum, sum_framenum, wrong_prop);
							 PackSum = 0;
							 memset(&g_sNetData, 0, sizeof(g_sNetData));
							 b_readfinish = false;
							 g_n32CircleNo = CirclNo;
						 }
			}
				break;
#pragma endregion
#pragma region 0x05
			case 0x05:
			{
						 switch ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][23])
						 {
						 case 0x02:
						 {
									  QString IP_First = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][26]), 10);
									  QString IP_Second = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][27]), 10);
									  QString IP_Third = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][28]), 10);
									  QString IP_Fourth = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][29]), 10);
									  QString IPAdress = IP_First + "." + IP_Second + "." + IP_Third + "." + IP_Fourth;
									  int port = ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][38] << 8) + (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][39];
									  QString Port = QString::number(port, 10);
									  QString Mask_First = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][30]), 10);
									  QString Mask_Second = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][31]), 10);
									  QString Mask_Third = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][32]), 10);
									  QString Mask_Fourth = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][33]), 10);
									  QString Mask = Mask_First + "." + Mask_Second + "." + Mask_Third + "." + Mask_Fourth;
									  QString GetWay_First = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][34]), 10);
									  QString GetWay_Second = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][35]), 10);
									  QString GetWay_Third = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][36]), 10);
									  QString GetWay_Fourth = QString::number((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][37]), 10);
									  QString GetWay = GetWay_First + "." + GetWay_Second + "." + GetWay_Third + "." + GetWay_Fourth;
									  QString mac_str1 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][40]), 2, 16, QLatin1Char('0'));
									  QString mac_str2 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][41]), 2, 16, QLatin1Char('0'));
									  QString mac_str3 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][42]), 2, 16, QLatin1Char('0'));
									  QString mac_str4 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][43]), 2, 16, QLatin1Char('0'));
									  QString mac_str5 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][44]), 2, 16, QLatin1Char('0'));
									  QString mac_str6 = QString("%1").arg((unsigned char)(g_cNetRecvBuf[g_n32NetRecvID][45]), 2, 16, QLatin1Char('0'));
									  QString mac = mac_str1 + "-" + mac_str2 + "-" + mac_str3 + "-" + mac_str4 + "-" + mac_str5 + "-" + mac_str6;
									  if (IPAdress.length() > 10 && Port.length() > 1 && Mask.length() > 10 && GetWay.length() > 10)
									  {
										  emit sig_NetParaview(IPAdress, Port, Mask, GetWay, mac);
									  }
						 }
							 break;
						 case  0x03:
						 {
									   if ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][29] == 1)
									   {
										   emit InfoView_sig(QString::fromLocal8Bit("����������óɹ���"));
									   }
									   else
									   {
										   emit InfoView_sig(QString::fromLocal8Bit("�����������ʧ�ܣ�"));
									   }
						 }
							 break;
						 case 0x10:
						 {
									  if (heart_zl.length() < 10)
									  {
										  heart_zl = pDfunc->QString2Hex("FFAA001E00000000000001010007000000000000000005100000AABBCCDD000CEEEE");
									  }
									  Sendzhiling(heart_zl);
						 }
							 break;
						 }
			}
				break;
#pragma endregion 
#pragma region 0x06
			case 0x06:
			{
						 switch ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][23])
						 {
						 case 0x01:
						 {
									  int heart, ratio;
									  heart = (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][26];
									  ratio = (unsigned char)g_cNetRecvBuf[g_n32NetRecvID][27];
									  emit sig_BaseParaView(heart, ratio);
						 }
							 break;
						 case 0x02:
						 {
									  if ((unsigned char)g_cNetRecvBuf[g_n32NetRecvID][29] == 1)
									  {
										  emit InfoView_sig(QString::fromLocal8Bit("�����������óɹ���"));
									  }
									  else
									  {
										  emit InfoView_sig(QString::fromLocal8Bit("������������ʧ�ܣ�"));
									  }
						 }
							 break;
						 }
			}
				break;
#pragma endregion
			default:
				break;
			}
			g_n32NetRecvID = (g_n32NetRecvID + 1) % NET_BUF_NUM;
		}
		else
		{
			xorflag = 1;
		}
	}
}

#pragma region ��ͼ�ۺ���
void workthread::Draw_slot(int Draw_kind)
{
	m_LaserPose[0] = 0;
	m_LaserPose[1] = 0;
	m_LaserPose[2] = 0;
	m_LaserPose[3] = 0;
	if (Draw_kind == 1)
	{
		//�ڲۺ����е���MainWindow��Ŀؼ���������
		pclfun->AddCloudPointArray(g_n64ArrayZhiX, g_n64ArrayZhiY, g_n64ArrayZhiZ, m_LaserPose, f_addAngEnergy, g_n64ArrayEnergy, 7200);
	}
	else if (Draw_kind == 2)
	{
		pclfun->AddCloudPointArray(g_n64ArrayZhiX, g_n64ArrayZhiY, g_n64ArrayZhiZ, m_LaserPose, f_addAngEnergy, g_n64ArrayEnergy, 3600);
	}
	f_addAngEnergy = false;
}
#pragma endregion 

#pragma region ����֡ͳ�Ʋۺ���
void workthread::wronginfo_slot(int wrongnum, int allnum, float wro_prop)
{
	Cki->showwrong(wrongnum, allnum, wro_prop);
}
#pragma endregion 

#pragma region ��������...��ʾ��Ϣ�ۺ���
void workthread::InfoView_slot(QString info)
{
	Cki->Infoview(1, "", info);
}
#pragma endregion

#pragma region ���ֵ...ͳ�Ʋۺ���
void workthread::CountDataView_slot(int max, int min, int avg)
{
	Cki->Countdataview(max, min, avg);
}
#pragma endregion

#pragma region �������С��ƽ��ֵ
void workthread::getMaxOrMin(int *arr, int count,int *rval)
{
	int val[3] = { 0 };
	val[0] = arr[0];
	val[1] = arr[0];
	int sum = arr[0];
	for (int i = 1; i < count; i++)
	{
		if (val[0]<arr[i])
		{
			val[0] = arr[i];
		}
		if (val[1]>arr[i])
		{
			val[1] = arr[i];
		}
		sum += arr[i];
	}
	val[2] = (int)(sum / count);
}
#pragma endregion

#pragma region TCP����ָ��
void workthread::Sendzhiling(QByteArray send)
{
	if (f_tcpNetConn)
	{
		if (TCPRecSocket != NULL)
		{
			TCPRecSocket->write(send, send.length());
			if (!TCPRecSocket->waitForBytesWritten(100))
			{
				qDebug() <<QString::fromLocal8Bit("����ָ��ʧ��");
			}
		}
	}
	else if (k_Protocal==0)//TCPЭ���²Ż���δ������ʾ
	{
		emit InfoView_sig(QString::fromLocal8Bit("����δ���ӣ�"));
	}
}
#pragma endregion

#pragma region TCP�Ͽ�����
bool workthread::DisconnectServer()
{
	if (f_tcpNetConn)
	{
		if (TCPRecSocket != NULL)
		{
			TCPRecSocket->disconnectFromHost();
			if (TCPRecSocket->waitForReadyRead(1000))
			{
				QByteArray a = TCPRecSocket->readAll();
				if (a.length() == 0)
				{
					return true;
					TCPRecSocket = NULL;
					f_tcpNetConn = false;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
			delete TCPRecSocket;
			TCPRecSocket = NULL;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
		emit InfoView_sig(QString::fromLocal8Bit("����δ���ӣ�"));
	}
}
#pragma endregion

#pragma region  TCP��������״̬�ж�
void workthread::connect_false(QAbstractSocket::SocketError a)
{
	qDebug() << TCPRecSocket->errorString();
	TCPRecSocket->close();
	//f_tcpNetConn = false;
}
#pragma endregion

#pragma region TCP��������״̬�ۺ���
void workthread::TcpConnInfo_slot(bool f_conn)
{
	Cki->TcpConnInfo(f_conn);
}
#pragma endregion

#pragma region ���������ѯ�ۺ���
void workthread::slot_NetParaview(QString ip, QString port, QString Mask, QString getway, QString mac)
{
	Cki->NetParaInfoView(ip, port, Mask, getway, mac);
}
#pragma endregion

#pragma region ����������ѯ�ۺ���
void workthread::slot_BaseParaView(int heart, int ratio)
{
	Cki->BaseParaInfoView(heart, ratio);
}
#pragma endregion 

