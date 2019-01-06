// ScaleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test3.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// ScaleDialog �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IScaleDialog ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {DAF500DB-9B8F-4B69-991F-02C879477C9F}
static const IID IID_IScaleDialog =
{ 0xDAF500DB, 0x9B8F, 0x4B69, { 0x99, 0x1F, 0x2, 0xC8, 0x79, 0x47, 0x7C, 0x9F } };

BEGIN_INTERFACE_MAP(ScaleDialog, CDialogEx)
	INTERFACE_PART(ScaleDialog, IID_IScaleDialog, Dispatch)
END_INTERFACE_MAP()


// ScaleDialog ��Ϣ�������
