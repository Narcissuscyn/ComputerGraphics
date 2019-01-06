
// Test4View.cpp : CTest4View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}
// CTest4View ����
void CTest4View::OnDraw(CDC* pDC)
{
	CTest4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*if (!pDoc)
		return;
*/
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}
// CTest4View ��ӡ
BOOL CTest4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}
void CTest4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}
void CTest4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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

CTest4Doc* CTest4View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest4Doc)));
	return (CTest4Doc*)m_pDocument;
}
#endif //_DEBUG

BEGIN_MESSAGE_MAP(CTest4View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CUT, &CTest4View::OnCut)
END_MESSAGE_MAP()


//�Զ�������

//�ü����ε������Խ�����
CPoint recPoints[2];

//�ü�����εĶ�������---����洢
CPoint attrPoints[100];
CPoint pOut[100];
CPoint pSave[100];
static CPoint pNext[2];
bool Mask[500][500];

//����ζ������
int pointsNum=0;

//������¼������ֱ���

bool mouseFlag = false;

// CTest4View ����/����

CDC* cd;

//const int clip_num = 4;

CTest4View::CTest4View()
{
	pointsNum = 0;

}



// CTest4View ��Ϣ�������


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





// �ж�һ������ü��ߵĹ�ϵ---����ֵ��0--�������棻1--s����p���ڣ�2--s���ڣ�p���⣻3--s,p�����ڲ�
//edgeFlag:0--xl;1--xr;2--yt;3--yb


// �ж�һ�����Ƿ��ڲü��ߵ��ڲ�
bool CTest4View::isPointInside(CPoint p, Boundary b, CPoint winPointMin, CPoint winPointMax)
{
	switch (b)
	{
	case 0://��
		if (p.x<winPointMin.x)
		{
			return false; 
		}
		break;
	case 1://��
		if (p.y < winPointMin.y)
		{
			return false;
		}
		break;
	case 2://��
		if (p.x> winPointMax.x)
		{
			return false;
		}
		break;
	
	case 3://��
		if (p.y> winPointMax.y)
		{
			return false;
		}
		break;
	}

	return true;//���ڲ��ͷ���true
}


// �жϱ��봰�ڱ߽�Ĺ�ϵ
bool CTest4View::isCross(CPoint p1, CPoint p2, Boundary b, CPoint winPointMin, CPoint winPointMax)
{

	if ((!isPointInside(p1,b,winPointMin,winPointMax))&&(!isPointInside(p2,b,winPointMin,winPointMax)))//��������㶼�ڴ�����ߣ��򷵻�false;����Ҫ������
	{
		pNext[0].x = 0;
		pNext[0].y = 0;
		pNext[1].x = 0;
		pNext[1].y = 0;
		return false;
	}
	if (isPointInside(p1, b, winPointMin, winPointMax)&&(!isPointInside(p2, b, winPointMin, winPointMax)))//p1-->�ڣ�p2--->��
	{
		//�������pNext[0];
		pNext[0] = interSect(p1, p2, b, winPointMin, winPointMax);
		pNext[1].x = 0;
		pNext[1].y = 0;
	}
	if ((!isPointInside(p1, b, winPointMin, winPointMax)) && isPointInside(p2, b, winPointMin, winPointMax))//p2-->�ڣ�p1--->��
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


// �󽻵�
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
		case 0://��
			pTemp.x = winMin.x;
			pTemp.y = p2.y + (winMin.x - p2.x)*k;
			break;
		case 1://��
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
		case 2://��
			pTemp.x = winMax.x;
			pTemp.y = p2.y + (winMax.x - p2.x)*k;
			break;
		
		case 3://��
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

// ��ü��к����������
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


//ֱ��ɨ�� ���־
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

// ���ݸ��������������
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
	//��ÿ���ߴ��־
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


	//���������
	for (int i = minY+1 ; i < maxY; i++)
	{
		//��ÿһ�����Ƿ��б߽���
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
// ������㷨
void CTest4View::edgeMarkFilld(CDC* cdc, bool mask[500][500], COLORREF color)
{

	
}
