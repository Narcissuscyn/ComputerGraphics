
// Test2View.cpp : CTest2View 类的实现
//

#include "stdafx.h"
#include "iostream"
using namespace std;
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


//自定义变量
CPoint points[20];
/*数组保存学号后四位*/
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
//顶点数目
int pointNumber=0;

// CTest2View 构造/析构

CTest2View::CTest2View()
{
	// TODO:  在此处添加构造代码
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTest2View 绘制




// CTest2View 打印

BOOL CTest2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTest2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTest2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CTest2View 诊断

#ifdef _DEBUG
void CTest2View::AssertValid() const
{
	CView::AssertValid();
}

void CTest2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest2Doc* CTest2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest2Doc)));
	return (CTest2Doc*)m_pDocument;
}
#endif //_DEBUG


void CTest2View::OnDraw(CDC* pDC)
{
	CTest2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//重画
	/*paintImage(pDC);
	edgeMarkFilld(pDC, Mask, num_array, RGB(0, 0, 255));*/
	// TODO:  在此处为本机数据添加绘制代码
}

// 根据输入的点，绘制多边形
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

		//获得多边形的图形范围，以便设置控制矩形的大小
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


// 边填充算法
void CTest2View::edgeMarkFilld(CDC* cdc, bool mask[500][500], bool num_array[10][25], COLORREF color)
{
	
	for (int j = 0; j <500;j++){
		for (int i = 0; i < 500 ; i++)
		{
			Mask[j][i] = false;
		}
		
	}
	//对每条边打标志
	for (int i = 0; i < pointNumber;i++)
	{
		DDLline(points[i].x, points[i].y, points[(i + 1) % pointNumber].x, points[(i + 1) % pointNumber].y);
	}

	
	//按轮廓填充
	for (int i = minY+1; i <maxY-4; i++)
	{
		int j = minX-2;
//对每一行找是否有边界线
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

//直线扫描 打标志
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	points[pointNumber].x = (int)point.x;
	points[pointNumber].y = (int)point.y;
	pointNumber++;
	CView::OnLButtonDown(nFlags, point);
}


void CTest2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	minX = 10000;
	maxX = -1;
	minY = 10000;
	maxY = -1;
	for (int i = 0; i < pointNumber;i++)
	{
	
		//获得多边形的图形范围，以便设置控制矩形的大小
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
