#pragma once


// TranDialog �Ի���

class TranDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TranDialog)

public:
	TranDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TranDialog();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_TranDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double tran_dx;
	double tran_dy;
	// z�᷽��ƽ�Ƶľ���
	double tran_dz;
};
