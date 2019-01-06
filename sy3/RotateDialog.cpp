// RotateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "RotateDialog.h"
#include "afxdialogex.h"


// RotateDialog 对话框

IMPLEMENT_DYNAMIC(RotateDialog, CDialogEx)

RotateDialog::RotateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(RotateDialog::IDD, pParent)
	, rotate_theta(0)
	, rotate_direc(0)
{

}

RotateDialog::~RotateDialog()
{
}

void RotateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Theta, rotate_theta);
	DDV_MinMaxDouble(pDX, rotate_theta, -360, 360);
	DDX_Text(pDX, IDC_Direc, rotate_direc);
	DDV_MinMaxInt(pDX, rotate_direc, 1, 3);
}


BEGIN_MESSAGE_MAP(RotateDialog, CDialogEx)
END_MESSAGE_MAP()


// RotateDialog 消息处理程序
