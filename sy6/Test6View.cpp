
// Test6View.cpp : CTest6View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test6.h"
#endif

#include "Test6Doc.h"
#include "Test6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//自定义
CPoint points[50];
CPoint midPoints[100];
int pointsNum = 0;
int midPointsNum = 0;
//视图区
CRect rect;
bool isRbtnDown = false;
bool  yEdgeFlag = false;
bool  xEdgeFlag = false;
//二次bezier曲线的绘制
float Mbezier[3][3] = { {1,-2,1}, {-2,2,0}, {1,0,0} };
float Fbezier[3][2];

CPen oldPen(PS_SOLID, 5, RGB(0, 0, 0));
// CTest6View

IMPLEMENT_DYNCREATE(CTest6View, CView)

BEGIN_MESSAGE_MAP(CTest6View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EndTimer, &CTest6View::OnEndtimer)
	ON_COMMAND(ID_StartTimer, &CTest6View::OnStarttimer)
END_MESSAGE_MAP()

// CTest6View 构造/析构

CTest6View::CTest6View()
{
	// TODO:  在此处添加构造代码
//	this->GetClientRect(rect);
}

CTest6View::~CTest6View()
{
	DeleteObject(oldPen);
}

BOOL CTest6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTest6View 绘制

void CTest6View::OnDraw(CDC* /*pDC*/)
{
	CTest6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CTest6View 打印

BOOL CTest6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTest6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTest6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CTest6View 诊断

#ifdef _DEBUG
void CTest6View::AssertValid() const
{
	CView::AssertValid();
}

void CTest6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest6Doc* CTest6View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest6Doc)));
	return (CTest6Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest6View 消息处理程序


void CTest6View::OnTimer(UINT_PTR nIDEvent)
{
	this->GetClientRect(rect);
//	ClearScreen();
	for (int i = 1; i <= pointsNum;i++)
	{
		if ((i-1)%2==0)
		{
			if (points[i - 1].y>=rect.bottom)
			{
				yEdgeFlag = true;
			}
			if (points[i - 1].y<rect.top)
			{
				yEdgeFlag = false;
			}
			if (yEdgeFlag)
			{
				points[i - 1].y -= 3 * i;
			}
			else
			{
			points[i - 1].y += 3 * i;
			}
		}
		else
		{
			if (points[i - 1].x>= rect.right)
			{
				xEdgeFlag = true;
			}
			if (points[i - 1].x < rect.left)
			{
				xEdgeFlag = false;
			}
			if (xEdgeFlag)
			{
				points[i - 1].x -= 3 * i;
			}
			else
			{
			points[i - 1].x += 3 * i;
			}
		}
	}
	draw(true);
	CView::OnTimer(nIDEvent);
}

void CTest6View::ClearScreen()
{

	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}
void CTest6View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!isRbtnDown)
	{
	if (pointsNum<50)
	{
		points[pointsNum] = point;
		if (pointsNum>0)
		{
			CDC* cd = this->GetDC();
			cd->MoveTo(points[pointsNum - 1]);
			cd->LineTo(points[pointsNum]);
		}
		pointsNum++;
	}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CTest6View::OnRButtonDown(UINT nFlags, CPoint point)
{
	isRbtnDown = true;
	CDC*cd = this->GetDC();
	cd->MoveTo(points[pointsNum - 1]);
	cd->LineTo(points[0]);
	
	draw(false);
		CView::OnRButtonDown(nFlags, point);
}


void CTest6View::Matrics()
{
	float matrics[3][2];
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 2; j++)
		{
			matrics[i][j] = Mbezier[i][0] * Fbezier[0][j] + Mbezier[i][1] * Fbezier[1][j] +
				Mbezier[i][2] * Fbezier[2][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
				Fbezier[i][j] = matrics[i][j];
		}
	}
	
}

void CTest6View::OnEndtimer()
{
	this->KillTimer(1);
}


void CTest6View::OnStarttimer()
{
	this->SetTimer(1,50, NULL);
}


void CTest6View::draw(bool drawFlag)
{
	midPointsNum = 0;
	CDC* cd = this->GetDC();
	//求多边形中点数组
	for (int i = 0; i < pointsNum; i++)
	{

		midPoints[midPointsNum].x = (points[i].x + points[(i + 1) % pointsNum].x) / (float)2;
		midPoints[midPointsNum].y = (points[i].y + points[(i + 1) % pointsNum].y) / (float)2;
		midPointsNum++;
		midPoints[midPointsNum] = points[(i + 1) % pointsNum];
		midPointsNum++;
	}
	//绘制多边形
	if (drawFlag)
	{
	ClearScreen();
	cd->SelectObject(&oldPen);
		cd->Polygon(points, pointsNum);
	}
	//绘制bezier曲线


	CPen pen(PS_SOLID,5, RGB(255, 0, 0));  //红色画笔
	cd->SelectObject(&pen);

	float x = 0;
	float dx = (float)1 / (float)200;
	bool flag = false;
	for (int i = 0; i < midPointsNum; i += 2)
	{
		x = 0;

		//求Fbezier
		for (int j = 0; j < 3; j++)
		{
			Fbezier[j][0] = midPoints[(i + j) % midPointsNum].x;
			Fbezier[j][1] = midPoints[(i + j) % midPointsNum].y;
		}
		//矩阵运算
		Matrics();
		//绘制二次Bezier曲线
		while (x <= 1)
		{
			CPoint point1;
			point1.x = Fbezier[0][0] * pow(x, 2) + Fbezier[1][0] * x + Fbezier[2][0];
			point1.y = Fbezier[0][1] * pow(x, 2) + Fbezier[1][1] * x + Fbezier[2][1];
			if (!flag)
			{
				cd->MoveTo(point1);
				flag = true;
			}
			else
			{
				cd->LineTo(point1);
				
			}
			x += dx;
		}
		flag = false;
	}
	DeleteObject(pen);
}
