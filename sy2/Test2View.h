
// Test2View.h : CTest2View 类的接口
//

#pragma once


class CTest2View : public CView
{
protected: // 仅从序列化创建
	CTest2View();
	DECLARE_DYNCREATE(CTest2View)

// 特性
public:
	CTest2Doc* GetDocument() const;

// 操作
public:
	int minX;
	int minY;
	int maxX;
	int maxY;
	bool isInside;
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
	virtual ~CTest2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 根据输入的点，绘制多边形
	void paintImage(CDC* cdc);
	// 边填充算法
	void edgeMarkFilld(CDC* cdc, bool mask[500][500], bool num_array[10][25], COLORREF color);
	void DDLline(int x1, int y1, int x2, int y2);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Test2View.cpp 中的调试版本
inline CTest2Doc* CTest2View::GetDocument() const
   { return reinterpret_cast<CTest2Doc*>(m_pDocument); }
#endif

