// TranDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "TranDialog.h"
#include "afxdialogex.h"


// TranDialog 对话框

IMPLEMENT_DYNAMIC(TranDialog, CDialogEx)

TranDialog::TranDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TranDialog::IDD, pParent)
	, tran_dx(5)
	, tran_dy(5)
	, tran_dz(5)
{

	EnableAutomation();

}

TranDialog::~TranDialog()
{
}

void TranDialog::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void TranDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DX, tran_dx);
	DDX_Text(pDX, IDC_DY, tran_dy);
	DDX_Text(pDX, IDC_DZ, tran_dz);
}


BEGIN_MESSAGE_MAP(TranDialog, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(TranDialog, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITranDialog 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {1E29F271-2EE5-47C9-91D5-9D0C32FC529E}
static const IID IID_ITranDialog =
{ 0x1E29F271, 0x2EE5, 0x47C9, { 0x91, 0xD5, 0x9D, 0xC, 0x32, 0xFC, 0x52, 0x9E } };

BEGIN_INTERFACE_MAP(TranDialog, CDialogEx)
	INTERFACE_PART(TranDialog, IID_ITranDialog, Dispatch)
END_INTERFACE_MAP()


// TranDialog 消息处理程序
