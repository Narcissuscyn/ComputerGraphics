// PerDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "PerDialog.h"
#include "afxdialogex.h"


// PerDialog 对话框

IMPLEMENT_DYNAMIC(PerDialog, CDialogEx)

PerDialog::PerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(PerDialog::IDD, pParent)
	, per_x0(0)
	, per_y0(0)
	, per_z0(0)
{

	EnableAutomation();

}

PerDialog::~PerDialog()
{
}

void PerDialog::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void PerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X0, per_x0);
	DDX_Text(pDX, IDC_Y0, per_y0);
	//  DDX_Text(pDX, IDC_Z0, per_z0);
	DDX_Text(pDX, IDC_Z0, per_z0);
}


BEGIN_MESSAGE_MAP(PerDialog, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(PerDialog, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IPerDialog 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {D800228E-5869-4E51-BF8B-5962481C9BA3}
static const IID IID_IPerDialog =
{ 0xD800228E, 0x5869, 0x4E51, { 0xBF, 0x8B, 0x59, 0x62, 0x48, 0x1C, 0x9B, 0xA3 } };

BEGIN_INTERFACE_MAP(PerDialog, CDialogEx)
	INTERFACE_PART(PerDialog, IID_IPerDialog, Dispatch)
END_INTERFACE_MAP()


// PerDialog 消息处理程序
