// TranDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test3.h"
#include "TranDialog.h"
#include "afxdialogex.h"


// TranDialog �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ITranDialog ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {1E29F271-2EE5-47C9-91D5-9D0C32FC529E}
static const IID IID_ITranDialog =
{ 0x1E29F271, 0x2EE5, 0x47C9, { 0x91, 0xD5, 0x9D, 0xC, 0x32, 0xFC, 0x52, 0x9E } };

BEGIN_INTERFACE_MAP(TranDialog, CDialogEx)
	INTERFACE_PART(TranDialog, IID_ITranDialog, Dispatch)
END_INTERFACE_MAP()


// TranDialog ��Ϣ�������
