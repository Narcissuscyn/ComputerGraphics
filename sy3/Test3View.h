
// Test3View.h : CTest3View ��Ľӿ�
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
protected: // �������л�����
	CTest3View();
	DECLARE_DYNCREATE(CTest3View)

// ����
public:
	CTest3Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTest3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnParallel();
	afx_msg void OnPerspective();


	//������İ˸����� 3D����
	Point_3D p_left_back;
	Point_3D p_right_back;
	Point_3D p_left_front;
	Point_3D p_right_front;
	Point_3D p_left_top_back;
	Point_3D p_right_top_back;
	Point_3D p_left_top_front;
	Point_3D p_right_top_front;

	//2d����
	CPoint m_left_back;
	CPoint m_right_back;
	CPoint m_left_front;
	CPoint m_right_front;
	CPoint m_left_top_back;
	CPoint m_right_top_back;
	CPoint m_left_top_front;
	CPoint m_right_top_front;

	void DrawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	// ����άƽ���������
	void DrawCubic();
	afx_msg void OnEqualAxes();
	void ClearScreen();
	// ����ת������
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
	// ��ת�任����
	void scale(double scale_sx, double scale_sy,double scale_sz);
	void rotate(double theta, int rotateDirection);
	// ��ʼ��8��ֵ��Ȼ����8����	void multiple(Point_3D& pre_metric,double metric[4][4]);
	void initPointValue();
	void multiple(Point_3D& pre_metric, double metric[4][4]);
	void perFunc(Point_3D& point, CPoint& cpoint, double x0, double y0, double d);
};






#ifndef _DEBUG  // Test3View.cpp �еĵ��԰汾
inline CTest3Doc* CTest3View::GetDocument() const
   { return reinterpret_cast<CTest3Doc*>(m_pDocument); }
#endif

