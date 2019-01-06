
// Test2View.cpp : CTest2View ���ʵ��
//

#include "stdafx.h"
#include "iostream"
using namespace std;
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test2.h"
#endif

#include "Test2Doc.h"
#include "Test2View.h"
#include "AlertDialog.h"
#include "AlertNum.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTest2View

IMPLEMENT_DYNCREATE(CTest2View, CView)

BEGIN_MESSAGE_MAP(CTest2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


//�Զ������
CPoint points[20];
/*���鱣��ѧ�ź���λ*/
bool num_array[10][25] = { 
	{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0,0,0,0,0,0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
bool Mask[500][500];
//������Ŀ
int pointNumber=0;

// CTest2View ����/����

CTest2View::CTest2View()
{
	// TODO:  �ڴ˴���ӹ������
	int minX=0;
	int minY=0;
	int maxX=0;
	int maxY=0;
}

CTest2View::~CTest2View()
{
}

BOOL CTest2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTest2View ����




// CTest2View ��ӡ

BOOL CTest2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTest2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTest2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CTest2View ���

#ifdef _DEBUG
void CTest2View::AssertValid() const
{
	CView::AssertValid();
}

void CTest2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest2Doc* CTest2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest2Doc)));
	return (CTest2Doc*)m_pDocument;
}
#endif //_DEBUG


void CTest2View::OnDraw(CDC* pDC)
{
	CTest2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//�ػ�
	/*paintImage(pDC);
	edgeMarkFilld(pDC, Mask, num_array, RGB(0, 0, 255));*/
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

// ��������ĵ㣬���ƶ����
void CTest2View::paintImage(CDC* cdc)
{
	AlertNum alertNum = new AlertNum();
	alertNum.DoModal();
	pointNumber = alertNum.m_pointNum;
	minX = 10000;
	maxX = -1;
	minY = 10000;
	maxY = -1;
	for (int i=0; i < pointNumber;i++)
	{
		AlertDialog alertDia = new AlertDialog();
		alertDia.DoModal();
		points[i].x = alertDia.m_pointx;
		points[i].y = alertDia.m_pointy;

		//��ö���ε�ͼ�η�Χ���Ա����ÿ��ƾ��εĴ�С
		if (points[i].x<minX)
		{
			minX = points[i].x;
		}
		if (points[i].x>maxX)
		{
			maxX = points[i].x;
		}
		if (points[i].y<minY)
		{
			minY = points[i].y;
		}
		if (points[i].y>maxY){
			maxY = points[i].y;
		}
	}
	
	cdc->Polygon(points, pointNumber);
}


// ������㷨
void CTest2View::edgeMarkFilld(CDC* cdc, bool mask[500][500], bool num_array[10][25], COLORREF color)
{
	
	for (int j = 0; j <500;j++){
		for (int i = 0; i < 500 ; i++)
		{
			Mask[j][i] = false;
		}
		
	}
	//��ÿ���ߴ��־
	for (int i = 0; i < pointNumber;i++)
	{
		DDLline(points[i].x, points[i].y, points[(i + 1) % pointNumber].x, points[(i + 1) % pointNumber].y);
	}

	
	//���������
	for (int i = minY+1; i <maxY-4; i++)
	{
		int j = minX-2;
//��ÿһ�����Ƿ��б߽���
		while (j<maxX)
		{
			j+=2;
			
			while ((!Mask[i][j]) && (j < maxX))
			{
				j++;
			}
			if (Mask[i][j] && (j < maxX))
			{
				j++;
				int num_y = i % 10;

				while ((Mask[i][j] == false) && (j < maxX))
				{

					int num_x = j % 25;

					if (num_array[num_y][num_x])
					{
						cdc->SetPixel(j, i, RGB(0, 0, 255));
					}
					j++;
				}
				
			}
		}
	}
}

//ֱ��ɨ�� ���־
void CTest2View::DDLline(int x1, int y1, int x2, int y2)
{
	double dx,dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
	dx /= e;
	dy /= e;
	x = x1;
	y = y1;
	for (int i = 0; i < e;i++)
	{
		Mask[(int)(y +0.5)][(int)(x + 0.5)] = true;
		
		x += dx;
		y += dy;
	}
}


void CTest2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	points[pointNumber].x = (int)point.x;
	points[pointNumber].y = (int)point.y;
	pointNumber++;
	CView::OnLButtonDown(nFlags, point);
}


void CTest2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	minX = 10000;
	maxX = -1;
	minY = 10000;
	maxY = -1;
	for (int i = 0; i < pointNumber;i++)
	{
	
		//��ö���ε�ͼ�η�Χ���Ա����ÿ��ƾ��εĴ�С
		if (points[i].x<minX)
		{
			minX = points[i].x;
		}
		if (points[i].x>maxX)
		{
			maxX = points[i].x;
		}
		if (points[i].y<minY)
		{
			minY = points[i].y;
		}
		if (points[i].y>maxY){
			maxY = points[i].y;
		}
	}
	CDC* cdc = GetDC();
	cdc->Polygon(points, pointNumber);
	edgeMarkFilld(cdc, Mask, num_array, RGB(0, 0,255));
	CView::OnRButtonDown(nFlags, point);
}
