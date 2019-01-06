#pragma once


// TranDialog 对话框

class TranDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TranDialog)

public:
	TranDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TranDialog();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_TranDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	double tran_dx;
	double tran_dy;
	// z轴方向平移的距离
	double tran_dz;
};
