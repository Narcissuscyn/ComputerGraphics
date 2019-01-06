#pragma once


// AlertDialog 对话框

class AlertDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AlertDialog)

public:
	AlertDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AlertDialog();

// 对话框数据
	enum { IDD = ID_Alert };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 输入的x坐标
	int m_pointx;
	// 输入的点的坐标y
	int m_pointy;
};
