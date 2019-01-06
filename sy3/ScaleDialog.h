#pragma once


// ScaleDialog 对话框

class ScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDialog)

public:
	ScaleDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScaleDialog();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double scale_sx;
	double scale_sy;
	// 放大比例Sz
	double scale_sz;
};
