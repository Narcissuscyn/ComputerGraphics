
// Test1View.cpp : CTest1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CTest1View 构造/析构

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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTest1View 绘制

void CTest1View::OnDraw(CDC* pDC)
{
	CTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//midPointCircle(pDC, 100,100, 40, RGB(0, 255, 0));
	// TODO:  在此处为本机数据添加绘制代码
}


// CTest1View 打印

BOOL CTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CTest1View 诊断

#ifdef _DEBUG
void CTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest1Doc* CTest1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest1Doc)));
	return (CTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest1View 消息处理程序


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


// 中点画圆算法
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	GetParent()->Invalidate(true);
	CView::OnRButtonDown(nFlags, point);
}


// Bresanham画椭圆算法
void CTest1View::bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color)
{
	int x, y, p;
	int aa = a*a;
	int bb = b*b;
	//绘制第一部分
	x = 0; y = b; p = 2 * bb + aa*(1 - 2 * b);
	while (bb*x <= aa*y){
		//绘制对称的四个点
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
	//绘制第二部分
	x = a; y = 0; p = 2 * aa + bb*(1 - 2 * a);
	while (bb*x > aa*y){
		//绘制四个对称点
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


// bresenham画圆算法
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if ((!isKeyUp)&&(isKeyDown))
	{
		CDC* cdc = this->GetDC();
		
		pointEnd = point;

			cdc->SetROP2(R2_NOT);//设置绘图模式为R2_NOT
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
