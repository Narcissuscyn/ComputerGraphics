#pragma once


// PerDialog �Ի���

class PerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PerDialog)

public:
	PerDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PerDialog();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_PerspecDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double per_x0;
	double per_y0;
	double per_z0;
};
