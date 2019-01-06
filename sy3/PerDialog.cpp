// PerDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test3.h"
#include "PerDialog.h"
#include "afxdialogex.h"


// PerDialog �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IPerDialog ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {D800228E-5869-4E51-BF8B-5962481C9BA3}
static const IID IID_IPerDialog =
{ 0xD800228E, 0x5869, 0x4E51, { 0xBF, 0x8B, 0x59, 0x62, 0x48, 0x1C, 0x9B, 0xA3 } };

BEGIN_INTERFACE_MAP(PerDialog, CDialogEx)
	INTERFACE_PART(PerDialog, IID_IPerDialog, Dispatch)
END_INTERFACE_MAP()


// PerDialog ��Ϣ�������
