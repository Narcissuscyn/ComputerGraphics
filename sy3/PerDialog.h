#pragma once


// PerDialog 对话框

class PerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PerDialog)

public:
	PerDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PerDialog();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_PerspecDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double per_x0;
	double per_y0;
	double per_z0;
};
