// AlertNum.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test2.h"
#include "AlertNum.h"
#include "afxdialogex.h"


// AlertNum �Ի���

IMPLEMENT_DYNAMIC(AlertNum, CDialogEx)

AlertNum::AlertNum(CWnd* pParent /*=NULL*/)
	: CDialogEx(AlertNum::IDD, pParent)
	, m_pointNum(0)
{

}

AlertNum::~AlertNum()
{
}

void AlertNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_POINT_NUM, m_pointNum);
	DDV_MinMaxInt(pDX, m_pointNum, 3, 20);
}


BEGIN_MESSAGE_MAP(AlertNum, CDialogEx)
END_MESSAGE_MAP()


// AlertNum ��Ϣ�������
