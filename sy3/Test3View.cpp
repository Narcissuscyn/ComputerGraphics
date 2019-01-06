
// Test3View.cpp : CTest3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test3.h"
#endif

#include "Test3Doc.h"
#include "Test3View.h"
#include "TranDialog.h"
#include "ScaleDialog.h"
#include "RotateDialog.h"
#include "PerDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTest3View

IMPLEMENT_DYNCREATE(CTest3View, CView)

BEGIN_MESSAGE_MAP(CTest3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Perspective, &CTest3View::OnPerspective)
	ON_COMMAND(ID_Equal_Axes, &CTest3View::OnEqualAxes)
	ON_COMMAND(ID_CABINET, &CTest3View::OnCabinet)
	ON_COMMAND(ID_CAVALIER, &CTest3View::OnCavalier)
	ON_COMMAND(ID_TRANSLATE, &CTest3View::OnTranslate)
	ON_COMMAND(ID_SCALE, &CTest3View::OnScale)
	ON_COMMAND(ID_ROTATE, &CTest3View::OnRotate)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


//自定义

enum enumFlag{ parallel, perspective };
enumFlag projectionFlag;
//投影变换矩阵
double m_proj_matri[4][4];

/************************************************************************/
/* 三维变换方式1-平移 2-缩放 3-旋转*/
/************************************************************************/
int moveType=1;
double theta;
int direction = 3;
/**
顶点坐标值

*/

int left_bd = 100;
int right_bd = 200;
int buttom_bd = 100;
int top_bd = 200;
int back_bd = 100;
int front_bd = 200;
/************************************************************************/
/* 移动间隔(像素为单位)-----缩放比例----旋转角度                                                                     */
/************************************************************************/
double change_dx=0;
double change_dy = 0;
double change_dz = 0;
//三维变换矩阵
double metric[4][4];

double parallel_proc[4][4];
// CTest3View 构造/析构

double per_x0 = 0;
double per_y0=0;
double per_z0 = 0;

CTest3View::CTest3View()
{

	p_left_back = Point_3D(left_bd, back_bd, buttom_bd);//(100,100,100)
	p_left_top_back = Point_3D(left_bd, back_bd, top_bd);//(100,100,200)
	p_left_front = Point_3D(left_bd, front_bd, buttom_bd);//(100,200,100)
	p_left_top_front = Point_3D(left_bd, front_bd, top_bd);//(100,200,200)
	p_right_back = Point_3D(right_bd, back_bd, buttom_bd);//(200,100,100)
	p_right_top_back = Point_3D(right_bd, back_bd, top_bd);//(200,100,200)
	p_right_front = Point_3D(right_bd, front_bd, buttom_bd);//(200,200,100)
	p_right_top_front = Point_3D(right_bd, front_bd, top_bd);//(200,200,200)


	moveFlag = 0;
	scale_sx = 0.0;
	scale_sy = 0.0;
}

CTest3View::~CTest3View()
{
}

BOOL CTest3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTest3View 绘制

void CTest3View::OnDraw(CDC* /*pDC*/)
{
	CTest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CTest3View 打印

BOOL CTest3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTest3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTest3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CTest3View 诊断

#ifdef _DEBUG
void CTest3View::AssertValid() const
{
	CView::AssertValid();
}

void CTest3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest3Doc* CTest3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest3Doc)));
	return (CTest3Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest3View 消息处理程序


// 矩阵相乘---即乘以变换矩阵
void CTest3View::multiple(Point_3D& pre_metric, double metric[4][4])
{
	double temp[4] = { pre_metric.x, pre_metric.y, pre_metric.z, 1 };
	pre_metric.x = 0;
	pre_metric.y = 0;
	pre_metric.z = 0;
	for (int j = 0; j < 4; j++)
	{
		pre_metric.x += temp[j] * metric[j][0];
		pre_metric.y += temp[j] * metric[j][1];
		pre_metric.z += temp[j] * metric[j][2];
	}

}
// 初始化8个值，然后构造8个点
void CTest3View::initPointValue()
{
	int left_bd = 100;
	int right_bd = 200;
	int buttom_bd = 100;
	int top_bd = 200;
	int back_bd = 100;
	int front_bd = 200;
	p_left_back = Point_3D(left_bd, back_bd, buttom_bd);//(100,100,100)
	p_left_top_back = Point_3D(left_bd, back_bd, top_bd);//(100,100,200)
	p_left_front = Point_3D(left_bd, front_bd, buttom_bd);//(100,200,100)
	p_left_top_front = Point_3D(left_bd, front_bd, top_bd);//(100,200,200)
	p_right_back = Point_3D(right_bd, back_bd, buttom_bd);//(200,100,100)
	p_right_top_back = Point_3D(right_bd, back_bd, top_bd);//(200,100,200)
	p_right_front = Point_3D(right_bd, front_bd, buttom_bd);//(200,200,100)
	p_right_top_front = Point_3D(right_bd, front_bd, top_bd);//(200,200,200)
}

// 画二维平面的立方体
void CTest3View::DrawCubic()
{
	CDC* cd = this->GetDC();

	DrawRect(m_left_back, m_left_top_back, m_left_top_front, m_left_front);//画左面

	DrawRect(m_right_back, m_right_top_back, m_right_top_front, m_right_front);
	DrawRect(m_left_back, m_right_back, m_right_top_back, m_left_top_back);
	DrawRect(m_left_front, m_right_front, m_right_top_front, m_left_top_front);
	DrawRect(m_left_back, m_left_front, m_right_front, m_right_back);
	DrawRect(m_left_top_back, m_left_top_front, m_left_front, m_left_back);

}
//清理窗口
void CTest3View::ClearScreen()
{

	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}

// 坐标转换函数
void CTest3View::From3dTo2d()
{
	/*multiple(p_left_back, m_proj_matri);
	multiple(p_left_top_back, m_proj_matri);
	multiple(p_left_front, m_proj_matri);
	multiple(p_left_top_front, m_proj_matri);
	multiple(p_right_back, m_proj_matri);
	multiple(p_right_top_back, m_proj_matri);
	multiple(p_right_front, m_proj_matri);
	multiple(p_right_top_front, m_proj_matri);
	*/
	m_left_back.x = p_left_back.x*m_proj_matri[0][0] + p_left_back.y*m_proj_matri[0][1] + p_left_back.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_left_back.y = p_left_back.x*m_proj_matri[1][0] + p_left_back.y*m_proj_matri[1][1] + p_left_back.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_left_top_back.x = p_left_top_back.x*m_proj_matri[0][0] + p_left_top_back.y*m_proj_matri[0][1] + p_left_top_back.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_left_top_back.y = p_left_top_back.x*m_proj_matri[1][0] + p_left_top_back.y*m_proj_matri[1][1] + p_left_top_back.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_left_front.x = p_left_front.x*m_proj_matri[0][0] + p_left_front.y*m_proj_matri[0][1] + p_left_front.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_left_front.y = p_left_front.x*m_proj_matri[1][0] + p_left_front.y*m_proj_matri[1][1] + p_left_front.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_left_top_front.x = p_left_top_front.x*m_proj_matri[0][0] + p_left_top_front.y*m_proj_matri[0][1] + p_left_top_front.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_left_top_front.y = p_left_top_front.x*m_proj_matri[1][0] + p_left_top_front.y*m_proj_matri[1][1] + p_left_top_front.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_right_back.x = p_right_back.x*m_proj_matri[0][0] + p_right_back.y*m_proj_matri[0][1] + p_right_back.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_right_back.y = p_right_back.x*m_proj_matri[1][0] + p_right_back.y*m_proj_matri[1][1] + p_right_back.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_right_top_back.x = p_right_top_back.x*m_proj_matri[0][0] + p_right_top_back.y*m_proj_matri[0][1] + p_right_top_back.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_right_top_back.y = p_right_top_back.x*m_proj_matri[1][0] + p_right_top_back.y*m_proj_matri[1][1] + p_right_top_back.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_right_front.x = p_right_front.x*m_proj_matri[0][0] + p_right_front.y*m_proj_matri[0][1] + p_right_front.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_right_front.y = p_right_front.x*m_proj_matri[1][0] + p_right_front.y*m_proj_matri[1][1] + p_right_front.z*m_proj_matri[1][2] + m_proj_matri[1][3];

	m_right_top_front.x = p_right_top_front.x*m_proj_matri[0][0] + p_right_top_front.y*m_proj_matri[0][1] + p_right_top_front.z*m_proj_matri[0][2] + m_proj_matri[0][3];
	m_right_top_front.y = p_right_top_front.x*m_proj_matri[1][0] + p_right_top_front.y*m_proj_matri[1][1] + p_right_top_front.z*m_proj_matri[1][2] + m_proj_matri[1][3];



}
/************************************************************************/
/* 通过各种投影画出立方体                                                                     */
/************************************************************************/
/************************************************************************/
/**
透视投影
*/
void CTest3View::OnPerspective()
{
	projectionFlag = perspective;

	initPointValue();

	PerDialog perDialog = new PerDialog();
	perDialog.DoModal();
	per_x0 = perDialog.per_x0;
	per_y0 = perDialog.per_y0;
	per_z0 = perDialog.per_z0;

	ClearScreen();


	/*for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
		{
		m_proj_matri[i][j] = 0;
		}
		}
		m_proj_matri[0][0] = 1;
		m_proj_matri[1][1] = 1;
		m_proj_matri[2][0] = per_x0/per_z0;
		m_proj_matri[2][1] =per_y0/per_z0;
		m_proj_matri[2][3] = 1.0 / per_z0;
		m_proj_matri[3][3] = 1;*/
	/*double x0 = 2;
	double y0 = 1;
	double d = 1;*/

	
	/*m_proj_matri[0][0] = 1;
	m_proj_matri[0][1] = 0;
	m_proj_matri[0][2] =per_x0/per_z0;
	m_proj_matri[0][3] = 0;

	m_proj_matri[1][0] = 0;
	m_proj_matri[1][1] = 1;
	m_proj_matri[1][2] = per_y0/per_z0;
	m_proj_matri[1][3] = 0;

	m_proj_matri[2][0] = 0;
	m_proj_matri[2][1] = 0;
	m_proj_matri[2][2] = 0;
	m_proj_matri[2][3] = 0;

	m_proj_matri[3][0] = 0;
	m_proj_matri[3][1] = 0;
	m_proj_matri[3][2] = 1.0/per_z0;
	m_proj_matri[3][3] = 0;*/
	//From3dTo2d();
	perFunc(p_left_back, m_left_back, per_x0, per_x0, per_z0);
	perFunc(p_left_front, m_left_front, per_x0, per_x0, per_z0);
	perFunc(p_left_top_back, m_left_top_back, per_x0, per_x0, per_z0);
	perFunc(p_left_top_front, m_left_top_front, per_x0, per_x0, per_z0);
	perFunc(p_right_back, m_right_back, per_x0, per_x0, per_z0);
	perFunc(p_right_front,m_right_front, per_x0, per_x0, per_z0);
	perFunc(p_right_top_back, m_right_top_back, per_x0, per_x0, per_z0);
	perFunc(p_right_top_front, m_right_top_front, per_x0, per_x0, per_z0);
	
	DrawCubic();

}
/************************************************************************/
/* 平行投影----等轴投影                                                                     */
/************************************************************************/
void CTest3View::OnEqualAxes()
{
	initPointValue();
	ClearScreen();
	m_proj_matri[0][0] = 0.70710678118655;
	m_proj_matri[0][1] = 0.70710678118655;
	m_proj_matri[0][2] = 0;
	m_proj_matri[0][3] = 0;
	m_proj_matri[1][0] = -0.40824829046386;
	m_proj_matri[1][1] = 0.40824829046386;
	m_proj_matri[1][2] = 0.81649658092772;
	m_proj_matri[1][3] = 0;
	m_proj_matri[2][0] = 0;
	m_proj_matri[2][1] = 0;
	m_proj_matri[2][2] = 0;
	m_proj_matri[2][3] = 0;
	m_proj_matri[3][0] = 0;
	m_proj_matri[3][1] = 0;
	m_proj_matri[3][2] = 0;
	m_proj_matri[3][3] = 1;


	From3dTo2d();
	DrawCubic();
}
/**
平行投影----斜交投影---斜二侧投影
*/
void CTest3View::OnCabinet()
{
	initPointValue();
	ClearScreen();
	double L = 2 / sqrt((FLOAT)3);
	double alpha = 20;
	alpha *= 3.1415926 / 180;
	double c = cos(alpha);
	double s = sin(alpha);
	m_proj_matri[0][0] = 1;
	m_proj_matri[0][1] = 0;
	m_proj_matri[0][2] = L*c;
	m_proj_matri[0][3] = 0;

	m_proj_matri[1][0] = 0;
	m_proj_matri[1][1] = 1;
	m_proj_matri[1][2] = L*s;
	m_proj_matri[1][3] = 0;

	m_proj_matri[2][0] = 0;
	m_proj_matri[2][1] = 0;
	m_proj_matri[2][2] = 0;
	m_proj_matri[2][3] = 0;

	m_proj_matri[3][0] = 0;
	m_proj_matri[3][1] = 0;
	m_proj_matri[3][2] = 0;
	m_proj_matri[3][3] = 1;
	From3dTo2d();
	DrawCubic();
}
//平行投影----斜交投影---斜等轴投影
void CTest3View::OnCavalier()
{
	initPointValue();
	ClearScreen();
	double L = 1;
	double alpha = 45;
	alpha *= 3.1415926 / 180;
	double c = cos(alpha);
	double s = sin(alpha);
	m_proj_matri[0][0] = 1;
	m_proj_matri[0][1] = 0;
	m_proj_matri[0][2] = L*c;
	m_proj_matri[0][3] = 0;

	m_proj_matri[1][0] = 0;
	m_proj_matri[1][1] = 1;
	m_proj_matri[1][2] = L*s;
	m_proj_matri[1][3] = 0;

	m_proj_matri[2][0] = 0;
	m_proj_matri[2][1] = 0;
	m_proj_matri[2][2] = 0;
	m_proj_matri[2][3] = 0;

	m_proj_matri[3][0] = 0;
	m_proj_matri[3][1] = 0;
	m_proj_matri[3][2] = 0;
	m_proj_matri[3][3] = 1;
	From3dTo2d();
	DrawCubic();
}
/**
画矩形函数
*/
void CTest3View::DrawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4)
{
	CClientDC dc(this);
	dc.MoveTo(p1);
	dc.LineTo(p2);
	dc.LineTo(p3);
	dc.LineTo(p4);

}


/**
平移变换
*/
void CTest3View::OnTranslate()
{
	moveType = 1;
	TranDialog tran_dialog=new TranDialog();
	tran_dialog.DoModal();
	change_dx = tran_dialog.tran_dx;
	change_dy = tran_dialog.tran_dy;
	change_dz = tran_dialog.tran_dz;
	

}

/************************************************************************/
/* 比例变换                                                                     */
/************************************************************************/
void CTest3View::OnScale()
{
	moveType = 2;

	ScaleDialog scaleDialog = new ScaleDialog();
	scaleDialog.DoModal();
	scale_sx = scaleDialog.scale_sx;
	scale_sy = scaleDialog.scale_sy;
	scale_sz = scaleDialog.scale_sz;
	scale(scale_sx, scale_sy,scale_sz);
}

/************************************************************************/
/* 旋转变换                                                                     */
/************************************************************************/
void CTest3View::OnRotate()
{
	moveType = 3;

	RotateDialog rotateDioalog = new RotateDialog();
	rotateDioalog.DoModal();
	theta = rotateDioalog.rotate_theta;
	direction = rotateDioalog.rotate_direc;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
		{
			metric[i][j] = 0;
		}
	}
	rotate(theta, direction);
	multiple(p_left_back, metric);
	multiple(p_left_front, metric);
	multiple(p_left_top_back, metric);
	multiple(p_left_top_front, metric);
	multiple(p_right_back, metric);
	multiple(p_right_front, metric);
	multiple(p_right_top_back, metric);
	multiple(p_right_top_front, metric);

	if (projectionFlag==perspective)
	{
		perFunc(p_left_back, m_left_back, per_x0, per_x0, per_z0);
		perFunc(p_left_front, m_left_front, per_x0, per_x0, per_z0);
		perFunc(p_left_top_back, m_left_top_back, per_x0, per_x0, per_z0);
		perFunc(p_left_top_front, m_left_top_front, per_x0, per_x0, per_z0);
		perFunc(p_right_back, m_right_back, per_x0, per_x0, per_z0);
		perFunc(p_right_front, m_right_front, per_x0, per_x0, per_z0);
		perFunc(p_right_top_back, m_right_top_back, per_x0, per_x0, per_z0);
		perFunc(p_right_top_front, m_right_top_front, per_x0, per_x0, per_z0);
	}
	else
	{
		From3dTo2d();
	}

	ClearScreen();
	DrawCubic();
	

}
// 比例变换函数
void CTest3View::scale(double scale_sx, double scale_sy,double scale_sz)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
		{
			metric[i][j] = 0;
		}
	}

	metric[0][0] = scale_sx;
	metric[1][1] = scale_sy;
	metric[2][2] = scale_sz;
	metric[3][3] = 1;
	multiple(p_left_back, metric);
	multiple(p_left_front, metric);
	multiple(p_left_top_back, metric);
	multiple(p_left_top_front, metric);
	multiple(p_right_back, metric);
	multiple(p_right_front, metric);
	multiple(p_right_top_back, metric);
	multiple(p_right_top_front, metric);

	if (projectionFlag == perspective)
	{
		perFunc(p_left_back, m_left_back, per_x0, per_x0, per_z0);
		perFunc(p_left_front, m_left_front, per_x0, per_x0, per_z0);
		perFunc(p_left_top_back, m_left_top_back, per_x0, per_x0, per_z0);
		perFunc(p_left_top_front, m_left_top_front, per_x0, per_x0, per_z0);
		perFunc(p_right_back, m_right_back, per_x0, per_x0, per_z0);
		perFunc(p_right_front, m_right_front, per_x0, per_x0, per_z0);
		perFunc(p_right_top_back, m_right_top_back, per_x0, per_x0, per_z0);
		perFunc(p_right_top_front, m_right_top_front, per_x0, per_x0, per_z0);
	}
	else
	{
		From3dTo2d();
	}
	ClearScreen();
	DrawCubic();
}
//旋转变换函数
void CTest3View::rotate(double theta, int rotateDirection)
{
	if (direction == 3)
	{
		theta *= 3.1415926 / 180;
		metric[0][0] = cos(theta);
		metric[0][1] = sin(theta);
		metric[1][0] = -sin(theta);
		metric[1][1] = cos(theta);
		metric[2][2] = 1;
		metric[3][3] = 1;
	}
}
/************************************************************************/
/* 鼠标事件---主要响应平移变换和比例变换                                                                     */
/************************************************************************/
void CTest3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (moveType==1)
	{

	switch (nChar)
	{
	case VK_LEFT:

		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++)
			{
				metric[i][j] = 0;
			}
		}

		metric[0][0] = 1;
		metric[1][1] = 1;
		metric[2][2] = 1;
		metric[3][3] = 1;
		metric[3][0] =change_dx;
		metric[3][1] = 0;
		metric[3][2] = 0;
		multiple(p_left_back, metric);
		multiple(p_left_front, metric);
		multiple(p_left_top_back, metric);
		multiple(p_left_top_front, metric);
		multiple(p_right_back, metric);
		multiple(p_right_front, metric);
		multiple(p_right_top_back, metric);
		multiple(p_right_top_front, metric);
		From3dTo2d();
		ClearScreen();
		DrawCubic();
		break;
	case VK_RIGHT:
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++)
			{
				metric[i][j] = 0;
			}
		}

		metric[0][0] = 1;
		metric[1][1] = 1;
		metric[2][2] = 1;
		metric[3][3] = 1;
		metric[3][0] = 0;
		metric[3][1] = change_dy;
		metric[3][2] = 0;
		multiple(p_left_back, metric);
		multiple(p_left_front, metric);
		multiple(p_left_top_back, metric);
		multiple(p_left_top_front, metric);
		multiple(p_right_back, metric);
		multiple(p_right_front, metric);
		multiple(p_right_top_back, metric);
		multiple(p_right_top_front, metric);
		From3dTo2d();
		ClearScreen();
		DrawCubic();
		break;
	case VK_UP:
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++)
			{
				metric[i][j] = 0;
			}
		}

		metric[0][0] = 1;
		metric[1][1] = 1;
		metric[2][2] = 1;
		metric[3][3] = 1;
		metric[3][0] = 0;
		metric[3][1] = 0;
		metric[3][2] = change_dz;
		multiple(p_left_back, metric);
		multiple(p_left_front, metric);
		multiple(p_left_top_back, metric);
		multiple(p_left_top_front, metric);
		multiple(p_right_back, metric);
		multiple(p_right_front, metric);
		multiple(p_right_top_back, metric);
		multiple(p_right_top_front, metric);
		From3dTo2d();
		ClearScreen();
		DrawCubic();
		break;
	case VK_DOWN:
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++)
			{
				metric[i][j] = 0;
			}
		}

		metric[0][0] = 1;
		metric[1][1] = 1;
		metric[2][2] = 1;
		metric[3][3] = 1;
		metric[3][0] = change_dx;
		metric[3][1] = change_dy;
		metric[3][2] = change_dz;
		multiple(p_left_back, metric);
		multiple(p_left_front, metric);
		multiple(p_left_top_back, metric);
		multiple(p_left_top_front, metric);
		multiple(p_right_back, metric);
		multiple(p_right_front, metric);
		multiple(p_right_top_back, metric);
		multiple(p_right_top_front, metric);

		if (projectionFlag == perspective)
		{
			perFunc(p_left_back, m_left_back, per_x0, per_x0, per_z0);
			perFunc(p_left_front, m_left_front, per_x0, per_x0, per_z0);
			perFunc(p_left_top_back, m_left_top_back, per_x0, per_x0, per_z0);
			perFunc(p_left_top_front, m_left_top_front, per_x0, per_x0, per_z0);
			perFunc(p_right_back, m_right_back, per_x0, per_x0, per_z0);
			perFunc(p_right_front, m_right_front, per_x0, per_x0, per_z0);
			perFunc(p_right_top_back, m_right_top_back, per_x0, per_x0, per_z0);
			perFunc(p_right_top_front, m_right_top_front, per_x0, per_x0, per_z0);
		}
		else
		{
			From3dTo2d();
		}
		ClearScreen();
		DrawCubic();
		break;
	}
	}

	if (moveType==2)
	{
		switch (nChar)
		{
		case VK_UP:
			scale_sx = 0;
			scale_sy = 1.5;
			scale(scale_sx, scale_sy,scale_sz);
			break;
		case VK_DOWN:
			scale_sx = 0;
			scale_sy = 0.5;
			scale(scale_sx, scale_sy,scale_sz);
			break;
		case VK_LEFT:
			scale_sx = 0.5;
			scale_sy = 0;
			scale(scale_sx, scale_sy,scale_sz);
			break;
		case VK_RIGHT:
			scale_sx = 1.5;
			scale_sy = 0;
			scale(scale_sx, scale_sy,scale_sz);
			break;
		}
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}





void CTest3View::perFunc(Point_3D& point, CPoint& cpoint, double x0,double y0,double d)
{
	cpoint.x = x0+d*(point.x-x0)/(point.z+d);
	cpoint.y = y0 + d*(point.y - y0) / (point.z + d);
}
