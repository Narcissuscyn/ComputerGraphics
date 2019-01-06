
// Test1View.cpp : CTest1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test1.h"
#endif

#include "Test1Doc.h"
#include "Test1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
using namespace std;
// CTest1View

IMPLEMENT_DYNCREATE(CTest1View, CView)

BEGIN_MESSAGE_MAP(CTest1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_CIRCLE, &CTest1View::OnCircle)
	ON_COMMAND(ID_REC_CIRCLE, &CTest1View::OnRecCircle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTest1View ����/����

CTest1View::CTest1View()
{
	isKeyDown = false;
	isKeyUp = true;

}

CTest1View::~CTest1View()
{
}

BOOL CTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTest1View ����

void CTest1View::OnDraw(CDC* pDC)
{
	CTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//midPointCircle(pDC, 100,100, 40, RGB(0, 255, 0));
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTest1View ��ӡ

BOOL CTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CTest1View ���

#ifdef _DEBUG
void CTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest1Doc* CTest1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest1Doc)));
	return (CTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest1View ��Ϣ�������


void CTest1View::OnCircle()
{
	type = 1;
	//CDC* p = this->GetDC();
	//p->LineTo(200, 200);
}


void CTest1View::OnRecCircle()
{
	type = 2;
}


void CTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	isKeyDown = true;
	isKeyUp = false;
		pointStart = point;
		pointEnd = point;
	CView::OnLButtonDown(nFlags, point);
}


void CTest1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	isKeyUp = true;
	isKeyDown = false;
	CDC* cdc = this->GetDC();
	pointEnd = point;
	if ((type == 1))
	{
		//midPointCircle(cdc, 100, 100, 40, RGB(0, 255, 0));
		radius = (int)sqrt((pointEnd.x - pointStart.x)*( pointEnd.x - pointStart.x) + (pointEnd.y - pointStart.y)*( pointEnd.y - pointStart.y));
		midPointCircle(cdc,(int) pointStart.x,(int) pointStart.y, radius, RGB(255, 0, 0));
		//bresenhamFullCicle(cdc, (int)pointStart.x, (int)pointStart.y, radius, RGB(255, 0, 0));
	}
	else
	{
		bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointEnd.x - pointStart.y), (int)abs(pointEnd.y - pointStart.y), RGB(0, 0, 255));
	
	}
	cdc->DeleteDC();
	CView::OnLButtonUp(nFlags, point);
}


// �е㻭Բ�㷨
void CTest1View::midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color)
{
	int x, y, dx, dy, d;
	x = 0; y = R; d = 1 - R;
	dx = 3; dy = 5 - (R << 1);
	while (x < y){
		pDC->SetPixel(x + x0,y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		pDC->SetPixel(y + x0, x + y0, color);	
		pDC->SetPixel(-y + x0, x + y0, color);
		pDC->SetPixel(y + x0, -x + y0, color);
		pDC->SetPixel(-y+ x0, -x + y0, color);
		if (d < 0){
			d += dx;
			dx += 2;
			x++;
		}
		else
		{
			d += dx + dy;
			dx += 2;
			dy += 2;
			x++;
			y--;
		}
	}
}


void CTest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetParent()->Invalidate(true);
	CView::OnRButtonDown(nFlags, point);
}


// Bresanham����Բ�㷨
void CTest1View::bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color)
{
	int x, y, p;
	int aa = a*a;
	int bb = b*b;
	//���Ƶ�һ����
	x = 0; y = b; p = 2 * bb + aa*(1 - 2 * b);
	while (bb*x <= aa*y){
		//���ƶԳƵ��ĸ���
		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		if (p >= 0){
			p += 4 * aa*(1 - y) + bb*(4 * x + 6);
			y--;
		}
		else{
			p += bb*(4 * x + 6);
		}
		x++;
	}
	//���Ƶڶ�����
	x = a; y = 0; p = 2 * aa + bb*(1 - 2 * a);
	while (bb*x > aa*y){
		//�����ĸ��ԳƵ�
		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		if (p > 0){
			p += 4 * bb*(1 - x) + aa*(4 * y + 6);
			x--;
		}
		else
		{
			p += aa*(4 * y + 6);
		}
		y++;
	}

}


// bresenham��Բ�㷨
void CTest1View::bresenhamFullCicle(CDC* cdc, int x0, int y0, int r, COLORREF color)
{
	int x, y, p;
	x = 0; y = r; p = 3 - (r << 1);
	for (; x <= y;x++){
		cdc->SetPixel(x + x0, y + y0, color);
		cdc->SetPixel(-x + x0, y + y0, color);
		cdc->SetPixel(x + x0, -y + y0, color);
		cdc->SetPixel(-x + x0, -y + y0, color);
		cdc->SetPixel(y + x0, x + y0, color);
		cdc->SetPixel(-y + x0, x + y0, color);
		cdc->SetPixel(y + x0, -x + y0, color);
		cdc->SetPixel(-y + x0, -x + y0, color);
		if (p < 0){
			p += ((x << 2) + 6);
		}
		else
		{
			p += (((x - y) << 2) +10);
			y--;
		}
		}
	}



void CTest1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((!isKeyUp)&&(isKeyDown))
	{
		CDC* cdc = this->GetDC();
		
		pointEnd = point;

			cdc->SetROP2(R2_NOT);//���û�ͼģʽΪR2_NOT
		if ((type == 1))
		{
			//midPointCircle(cdc, 100, 100, 40, RGB(0, 255, 0));
			radius = (int)sqrt((pointEnd.x - pointStart.x)*(pointEnd.x - pointStart.x) + (pointEnd.y - pointStart.y)*(pointEnd.y - pointStart.y));
			midPointCircle(cdc, (int)pointStart.x, (int)pointStart.y, radius, RGB(255, 0, 0));
			midPointCircle(cdc, (int)pointStart.x, (int)pointStart.y, radius, RGB(0, 0, 0));

			//bresenhamFullCicle(cdc, (int)pointStart.x, (int)pointStart.y, radius, RGB(255, 0, 0));
		}
		else
		{
			bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointEnd.x - pointStart.y), (int)abs(pointEnd.y - pointStart.y), RGB(0, 0, 0));

			bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointEnd.x - pointStart.y), (int)abs(pointEnd.y - pointStart.y), RGB(0, 0, 255));
		}
	//GetParent()->Invalidate(true);
			//Sleep(1);*/
	}

	CView::OnMouseMove(nFlags, point);
}
