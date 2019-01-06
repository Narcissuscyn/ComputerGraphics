
// Test3View.h : CTest3View 类的接口
//
#include <Windows.h>
#include "atltypes.h"

class Point_3D
{
public:
	double  x;
	double y;
	double z;
	Point_3D(){}
	Point_3D(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	~Point_3D(){}
private:

};
class CTest3View : public CView
{
protected: // 仅从序列化创建
	CTest3View();
	DECLARE_DYNCREATE(CTest3View)

// 特性
public:
	CTest3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTest3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnParallel();
	afx_msg void OnPerspective();


	//正方体的八个顶点 3D坐标
	Point_3D p_left_back;
	Point_3D p_right_back;
	Point_3D p_left_front;
	Point_3D p_right_front;
	Point_3D p_left_top_back;
	Point_3D p_right_top_back;
	Point_3D p_left_top_front;
	Point_3D p_right_top_front;

	//2d坐标
	CPoint m_left_back;
	CPoint m_right_back;
	CPoint m_left_front;
	CPoint m_right_front;
	CPoint m_left_top_back;
	CPoint m_right_top_back;
	CPoint m_left_top_front;
	CPoint m_right_top_front;

	void DrawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	// 画二维平面的立方体
	void DrawCubic();
	afx_msg void OnEqualAxes();
	void ClearScreen();
	// 坐标转换函数
	void From3dTo2d();
	afx_msg void OnCabinet();
	afx_msg void OnCavalier();
	afx_msg void OnTranslate();
	afx_msg void OnScale();
	afx_msg void OnRotate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	int moveFlag;
	double scale_sx;
	double scale_sy;
	double scale_sz;
	// 旋转变换函数
	void scale(double scale_sx, double scale_sy,double scale_sz);
	void rotate(double theta, int rotateDirection);
	// 初始化8个值，然后构造8个点	void multiple(Point_3D& pre_metric,double metric[4][4]);
	void initPointValue();
	void multiple(Point_3D& pre_metric, double metric[4][4]);
	void perFunc(Point_3D& point, CPoint& cpoint, double x0, double y0, double d);
};






#ifndef _DEBUG  // Test3View.cpp 中的调试版本
inline CTest3Doc* CTest3View::GetDocument() const
   { return reinterpret_cast<CTest3Doc*>(m_pDocument); }
#endif

