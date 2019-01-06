#pragma once


// AlertNum 对话框

class AlertNum : public CDialogEx
{
	DECLARE_DYNAMIC(AlertNum)

public:
	AlertNum(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AlertNum();

// 对话框数据
	enum { IDD = ID_Alert_Num };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 多边形顶点个数
	int m_pointNum;
};
