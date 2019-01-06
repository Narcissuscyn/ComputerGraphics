// AlertDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Test2.h"
#include "AlertDialog.h"
#include "afxdialogex.h"


// AlertDialog 对话框

IMPLEMENT_DYNAMIC(AlertDialog, CDialogEx)

AlertDialog::AlertDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(AlertDialog::IDD, pParent)
	, m_pointx(0)
	, m_pointy(0)
{

}

AlertDialog::~AlertDialog()
{
}

void AlertDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_X, m_pointx);
	DDX_Text(pDX, IDC_Y, m_pointy);
}


BEGIN_MESSAGE_MAP(AlertDialog, CDialogEx)
END_MESSAGE_MAP()


// AlertDialog 消息处理程序
