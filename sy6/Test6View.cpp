
// Test6View.cpp : CTest6View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test6.h"
#endif

#include "Test6Doc.h"
#include "Test6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//�Զ���
CPoint points[50];
CPoint midPoints[100];
int pointsNum = 0;
int midPointsNum = 0;
//��ͼ��
CRect rect;
bool isRbtnDown = false;
bool  yEdgeFlag = false;
bool  xEdgeFlag = false;
//����bezier���ߵĻ���
float Mbezier[3][3] = { {1,-2,1}, {-2,2,0}, {1,0,0} };
float Fbezier[3][2];

CPen oldPen(PS_SOLID, 5, RGB(0, 0, 0));
// CTest6View

IMPLEMENT_DYNCREATE(CTest6View, CView)

BEGIN_MESSAGE_MAP(CTest6View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EndTimer, &CTest6View::OnEndtimer)
	ON_COMMAND(ID_StartTimer, &CTest6View::OnStarttimer)
END_MESSAGE_MAP()

// CTest6View ����/����

CTest6View::CTest6View()
{
	// TODO:  �ڴ˴���ӹ������
//	this->GetClientRect(rect);
}

CTest6View::~CTest6View()
{
	DeleteObject(oldPen);
}

BOOL CTest6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTest6View ����

void CTest6View::OnDraw(CDC* /*pDC*/)
{
	CTest6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTest6View ��ӡ

BOOL CTest6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTest6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTest6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CTest6View ���

#ifdef _DEBUG
void CTest6View::AssertValid() const
{
	CView::AssertValid();
}

void CTest6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest6Doc* CTest6View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest6Doc)));
	return (CTest6Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest6View ��Ϣ�������


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
	//�������е�����
	for (int i = 0; i < pointsNum; i++)
	{

		midPoints[midPointsNum].x = (points[i].x + points[(i + 1) % pointsNum].x) / (float)2;
		midPoints[midPointsNum].y = (points[i].y + points[(i + 1) % pointsNum].y) / (float)2;
		midPointsNum++;
		midPoints[midPointsNum] = points[(i + 1) % pointsNum];
		midPointsNum++;
	}
	//���ƶ����
	if (drawFlag)
	{
	ClearScreen();
	cd->SelectObject(&oldPen);
		cd->Polygon(points, pointsNum);
	}
	//����bezier����


	CPen pen(PS_SOLID,5, RGB(255, 0, 0));  //��ɫ����
	cd->SelectObject(&pen);

	float x = 0;
	float dx = (float)1 / (float)200;
	bool flag = false;
	for (int i = 0; i < midPointsNum; i += 2)
	{
		x = 0;

		//��Fbezier
		for (int j = 0; j < 3; j++)
		{
			Fbezier[j][0] = midPoints[(i + j) % midPointsNum].x;
			Fbezier[j][1] = midPoints[(i + j) % midPointsNum].y;
		}
		//��������
		Matrics();
		//���ƶ���Bezier����
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
