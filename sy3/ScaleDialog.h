#pragma once


// ScaleDialog �Ի���

class ScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDialog)

public:
	ScaleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ScaleDialog();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double scale_sx;
	double scale_sy;
	// �Ŵ����Sz
	double scale_sz;
};
