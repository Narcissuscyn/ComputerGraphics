
// Test4View.h : CTest4View 类的接口
//

#pragma once

#include "file.h"

class CTest4View : public CView
{
protected: // 仅从序列化创建
	CTest4View();
	DECLARE_DYNCREATE(CTest4View)

// 特性
public:
	CTest4Doc* GetDocument() const;
	

// 操作
public:
	//
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
	virtual ~CTest4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCut();
	// 判断一个点是否在裁剪边的内部	
	bool isPointInside(CPoint p, Boundary b, CPoint winPointMin, CPoint winPointMax);
	// 判断边与窗口边界的关系
	bool isCross(CPoint p1, CPoint p2, Boundary b, CPoint winPointMin, CPoint winPointMax);
	// 求交点
	CPoint interSect(CPoint p1, CPoint p2, Boundary b, CPoint winMin, CPoint winMax);
	void cutPoint(CPoint p, Boundary b, CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s);
	void closeCut(CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s);
	int polygonPoint(CPoint winMin, CPoint winMax, int n, CPoint* pIn, CPoint* pOut);
	void ClearScreen();
	// 获得剪切后的连续数组
	void getPointSave(CPoint* pIn, CPoint* pOut);
	void DDLline(int x1, int y1, int x2, int y2);
	// 根据给定顶点填充多边形
	void fillArea(CDC* cdc, CPoint* p, int point_num, COLORREF color);
	void edgeMarkFilld(CDC* cdc, bool mask[500][500], COLORREF color);
};

#ifndef _DEBUG  // Test4View.cpp 中的调试版本
inline CTest4Doc* CTest4View::GetDocument() const
   { return reinterpret_cast<CTest4Doc*>(m_pDocument); }
#endif

