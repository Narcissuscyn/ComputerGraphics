#pragma once


// AlertNum �Ի���

class AlertNum : public CDialogEx
{
	DECLARE_DYNAMIC(AlertNum)

public:
	AlertNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlertNum();

// �Ի�������
	enum { IDD = ID_Alert_Num };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����ζ������
	int m_pointNum;
};
