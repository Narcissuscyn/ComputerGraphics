
// Test1View.h : CTest1View 类的接口
//

#pragma once


class CTest1View : public CView
{
protected: // 仅从序列化创建
	CTest1View();
	DECLARE_DYNCREATE(CTest1View)

// 特性
public:
	CTest1Doc* GetDocument() const;

// 操作
public:
	int type;
	CPoint pointStart;
	CPoint pointEnd;
	bool isKeyUp;
	bool isKeyDown;
	int radius = 0;
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
	virtual ~CTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCircle();
	afx_msg void OnRecCircle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 中点画圆算法
	void midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// Bresanham画椭圆算法
	void bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color);
	// bresenham画圆算法
	void bresenhamFullCicle(CDC* cdc, int x0, int y0, int r, COLORREF color);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
};

#ifndef _DEBUG  // Test1View.cpp 中的调试版本
inline CTest1Doc* CTest1View::GetDocument() const
   { return reinterpret_cast<CTest1Doc*>(m_pDocument); }
#endif

