#pragma once


// AlertDialog �Ի���

class AlertDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AlertDialog)

public:
	AlertDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlertDialog();

// �Ի�������
	enum { IDD = ID_Alert };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �����x����
	int m_pointx;
	// ����ĵ������y
	int m_pointy;
};
