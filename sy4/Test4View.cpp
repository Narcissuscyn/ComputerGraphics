
// Test4View.cpp : CTest4View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test4.h"
#endif

#include "Test4Doc.h"
#include "Test4View.h"
#include "file.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CTest4View
IMPLEMENT_DYNCREATE(CTest4View, CView)

CTest4View::~CTest4View()
{
}
BOOL CTest4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}
// CTest4View 绘制
void CTest4View::OnDraw(CDC* pDC)
{
	CTest4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*if (!pDoc)
		return;
*/
	// TODO:  在此处为本机数据添加绘制代码
}
// CTest4View 打印
BOOL CTest4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}
void CTest4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}
void CTest4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

#ifdef _DEBUG
void CTest4View::AssertValid() const
{
	CView::AssertValid();
}

void CTest4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest4Doc* CTest4View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest4Doc)));
	return (CTest4Doc*)m_pDocument;
}
#endif //_DEBUG

BEGIN_MESSAGE_MAP(CTest4View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CUT, &CTest4View::OnCut)
END_MESSAGE_MAP()


//自定义区域

//裁剪矩形的两个对角坐标
CPoint recPoints[2];

//裁剪多边形的顶点坐标---数组存储
CPoint attrPoints[100];
CPoint pOut[100];
CPoint pSave[100];
static CPoint pNext[2];
bool Mask[500][500];

//多边形顶点个数
int pointsNum=0;

//鼠标点击事件的区分变量

bool mouseFlag = false;

// CTest4View 构造/析构

CDC* cd;

//const int clip_num = 4;

CTest4View::CTest4View()
{
	pointsNum = 0;

}



// CTest4View 消息处理程序


void CTest4View::OnLButtonDown(UINT nFlags, CPoint point)
{	
	if (!mouseFlag)
{

	recPoints[0] = point;
}
	else if (pointsNum<20)
{
	attrPoints[pointsNum] = point;
	cd = this->GetDC();
	if (pointsNum== 0)
	{
		cd->MoveTo(attrPoints[0]);
	}
	else
	{
		cd->MoveTo(attrPoints[pointsNum-1]);
	cd->LineTo(attrPoints[pointsNum]);
	}
	pointsNum++;
}
	CView::OnLButtonDown(nFlags, point);
}


void CTest4View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!mouseFlag)
	{
	recPoints[1] = point;
	cd = this->GetDC();
	cd->MoveTo(recPoints[0]);

	cd->LineTo(recPoints[0].x,recPoints[1].y);
	cd->LineTo(recPoints[1]);
	cd->LineTo(recPoints[1].x, recPoints[0].y);
	cd->LineTo(recPoints[0]);
	}
	mouseFlag = true;
	CView::OnLButtonUp(nFlags, point);
}


void CTest4View::OnRButtonDown(UINT nFlags, CPoint point)
{
	cd = this->GetDC();
	cd->MoveTo(attrPoints[0]);
	cd->LineTo(attrPoints[pointsNum - 1]);
	//fillArea(cd, attrPoints, pointsNum, RGB(255, 0, 0));
	CView::OnRButtonDown(nFlags, point);
}


void CTest4View::OnCut()
{
	getPointSave(attrPoints, recPoints);
}





// 判断一条边与裁剪边的关系---返回值：0--都在外面；1--s在外p在内；2--s在内，p在外；3--s,p都在内部
//edgeFlag:0--xl;1--xr;2--yt;3--yb


// 判断一个点是否在裁剪边的内部
bool CTest4View::isPointInside(CPoint p, Boundary b, CPoint winPointMin, CPoint winPointMax)
{
	switch (b)
	{
	case 0://左
		if (p.x<winPointMin.x)
		{
			return false; 
		}
		break;
	case 1://下
		if (p.y < winPointMin.y)
		{
			return false;
		}
		break;
	case 2://右
		if (p.x> winPointMax.x)
		{
			return false;
		}
		break;
	
	case 3://上
		if (p.y> winPointMax.y)
		{
			return false;
		}
		break;
	}

	return true;//在内部就返回true
}


// 判断边与窗口边界的关系
bool CTest4View::isCross(CPoint p1, CPoint p2, Boundary b, CPoint winPointMin, CPoint winPointMax)
{

	if ((!isPointInside(p1,b,winPointMin,winPointMax))&&(!isPointInside(p2,b,winPointMin,winPointMax)))//如果两个点都在窗口外边，则返回false;不需要保留点
	{
		pNext[0].x = 0;
		pNext[0].y = 0;
		pNext[1].x = 0;
		pNext[1].y = 0;
		return false;
	}
	if (isPointInside(p1, b, winPointMin, winPointMax)&&(!isPointInside(p2, b, winPointMin, winPointMax)))//p1-->内，p2--->外
	{
		//输出交点pNext[0];
		pNext[0] = interSect(p1, p2, b, winPointMin, winPointMax);
		pNext[1].x = 0;
		pNext[1].y = 0;
	}
	if ((!isPointInside(p1, b, winPointMin, winPointMax)) && isPointInside(p2, b, winPointMin, winPointMax))//p2-->内，p1--->外
	{
		pNext[0] = interSect(p1, p2, b, winPointMin, winPointMax);
		pNext[1] = p2;
	}
	if ((isPointInside(p1, b, winPointMin, winPointMax)) &&(isPointInside(p2, b, winPointMin, winPointMax)))
	{
		pNext[0] = p2;
		pNext[1].x = 0;
		pNext[1].y = 0;
	}
	return true;


}


// 求交点
CPoint CTest4View::interSect(CPoint p1, CPoint p2, Boundary b, CPoint winMin, CPoint winMax)
{
	CPoint pTemp;
	float k=0 ;
	if (p1.x!=p2.x)
	{
		k = (float)(p1.y - p2.y) / (float)(p1.x - p2.x);
	}

		switch (b)
		{
		case 0://左
			pTemp.x = winMin.x;
			pTemp.y = p2.y + (winMin.x - p2.x)*k;
			break;
		case 1://下
			pTemp.y = winMin.y;
			if (p1.x != p2.x)
			{
				pTemp.x = p2.x + (float)(winMin.y - p2.y) / k;
			}
			else
			{
				pTemp.x = p2.x;
			}
			break;
		case 2://右
			pTemp.x = winMax.x;
			pTemp.y = p2.y + (winMax.x - p2.x)*k;
			break;
		
		case 3://上
			pTemp.y = winMax.y;
			if (p1.x != p2.x)
			{
				pTemp.x = p2.x + (winMax.y - p2.y) / k;
			}
			else
			{
				pTemp.x = p2.x;
			}
			break;
		}
	return pTemp;
}

//
void CTest4View::ClearScreen()
{

	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}

// 获得剪切后的连续数组
void CTest4View::getPointSave(CPoint* points, CPoint* rectP)
{
	CPoint attrTemp[100];
	for (int i = 0; i < pointsNum; i++)
	{
		attrTemp[i] = points[i];
	}
	cd = this->GetDC();
	int count = 0;
	int point_counts = pointsNum;
	for (int i = 0; i < 4;i++)
	{
		count = 0;
		for (int j = 0; j < point_counts; j++)
		{
			pNext[0].x = 0;
			pNext[0].y = 0;
			pNext[1].x = 0;
			pNext[1].y = 0;
			if (i == 1)
			{
				int s = 0;
			}
			isCross(points[j], points[(j + 1) % point_counts], i, rectP[0], rectP[1]);
			if (!((pNext[0].x == 0) && (pNext[0].y == 0)))
			{
				
				pSave[count] = pNext[0];
				
				count++;
			}
			
			if (!((pNext[1].x == 0) && (pNext[1].y == 0)))
			{
				pSave[count] = pNext[1];
				count++;
			}

		}
	
		for (int s = 0; s < count;s++)
		{
		points[s]= pSave[s];
		}
		point_counts = count;
	}
	
	CRgn   rgnA1;
	VERIFY(rgnA1.CreatePolygonRgn(attrTemp, pointsNum, ALTERNATE));
	CBrush brA1;
	VERIFY(brA1.CreateSolidBrush(RGB(0, 0, 255)));  // rgnA Red
	cd->FillRgn(&rgnA1, &brA1);

	CRgn   rgnA;
	VERIFY(rgnA.CreatePolygonRgn(pSave, count, ALTERNATE));
	CBrush brA;
	VERIFY(brA.CreateSolidBrush(RGB(255, 0, 0)));
	cd->FillRgn(&rgnA, &brA);
	
	}


//直线扫描 打标志
void CTest4View::DDLline(int x1, int y1, int x2, int y2)
{
	double dx, dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
	dx /= e;
	dy /= e;
	x = x1;
	y = y1;
	for (int i = 0; i < e; i++)
	{
		Mask[(int)(y + 0.5)][(int)(x + 0.5)] = true;

		x += dx;
		y += dy;
	}
}

// 根据给定顶点填充多边形
void CTest4View::fillArea(CDC* cdc, CPoint* p, int point_num, COLORREF color)
{
	int minX=1000, minY=1000, maxX=-1, maxY=-1;

	for (int j = 0; j < 200; j++)
	{
		for (int i = 0; i < 200; i++)
		{
			Mask[j][i] = false;
		}

	}
	//对每条边打标志
	for (int i = 0; i < point_num; i++)
	{
		DDLline(p[i].x, p[i].y, p[(i + 1) % point_num].x, p[(i + 1) % point_num].y);
		if (p[i].x<minX)
		{
			minX = p[i].x;
		}
		if (p[i].y<minY)
		{
			minY = p[i].y;
		}
		if (p[i].x>maxX)
		{
			maxX = p[i].x;
		}
		if (p[i].y>maxY)
		{
			maxY = p[i].y;
		}
	}


	//按轮廓填充
	for (int i = minY+1 ; i < maxY; i++)
	{
		//对每一行找是否有边界线
		int j = 0;
		while (j < maxX)
		{
			while ((!Mask[i][j]) && (j < maxX))
			{
				j++;
			}
				while ((Mask[i][j] == false) && (j < maxX))
				{
						cdc->SetPixel(j, i, color);
					j++;
				}

		}
	}
}
// 边填充算法
void CTest4View::edgeMarkFilld(CDC* cdc, bool mask[500][500], COLORREF color)
{

	
}
