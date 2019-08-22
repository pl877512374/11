#ifndef DATADEALFUNC_H
#define DATADEALFUNC_H

#include <QObject>

class DataDealFunc : public QObject
{
	Q_OBJECT

public:
	DataDealFunc(QObject *parent);
	~DataDealFunc();
	void Xor(char* sendbuf, int sendlen);
	bool checkXor(char* recvbuf, int recvlen);
	QString GetBCCXorCode(QString str);
	QByteArray QString2Hex(QString str);
	char ConvertHexChar(char ch);
	QString GetInforFromMark(QString Info, char Mark);
private:
	
};

#endif // DATADEALFUNC_H
