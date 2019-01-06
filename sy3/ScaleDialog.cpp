// ScaleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// ScaleDialog 对话框

IMPLEMENT_DYNAMIC(ScaleDialog, CDialogEx)

ScaleDialog::ScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScaleDialog::IDD, pParent)
	, scale_sx(0)
	, scale_sy(0)
	, scale_sz(0)
{
	EnableAutomation();

}

ScaleDialog::~ScaleDialog()
{
}

void ScaleDialog::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void ScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SX, scale_sx);
	DDV_MinMaxDouble(pDX, scale_sx, 0, 20);
	DDX_Text(pDX, IDC_SY, scale_sy);
	DDV_MinMaxDouble(pDX, scale_sy, 0, 20);
	DDX_Text(pDX, IDC_SZ, scale_sz);
	DDV_MinMaxDouble(pDX, scale_sz, 0, 10);
}


BEGIN_MESSAGE_MAP(ScaleDialog, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(ScaleDialog, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IScaleDialog 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {DAF500DB-9B8F-4B69-991F-02C879477C9F}
static const IID IID_IScaleDialog =
{ 0xDAF500DB, 0x9B8F, 0x4B69, { 0x99, 0x1F, 0x2, 0xC8, 0x79, 0x47, 0x7C, 0x9F } };

BEGIN_INTERFACE_MAP(ScaleDialog, CDialogEx)
	INTERFACE_PART(ScaleDialog, IID_IScaleDialog, Dispatch)
END_INTERFACE_MAP()


// ScaleDialog 消息处理程序
