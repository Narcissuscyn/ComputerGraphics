
// Test6View.h : CTest6View 类的接口
//

#pragma once


class CTest6View : public CView
{
protected: // 仅从序列化创建
	CTest6View();
	DECLARE_DYNCREATE(CTest6View)

// 特性
public:
	CTest6Doc* GetDocument() const;

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
	virtual ~CTest6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEndtimer();
	afx_msg void OnStarttimer();
	void Matrics();
	void draw(bool flag);
	void ClearScreen();
};

#ifndef _DEBUG  // Test6View.cpp 中的调试版本
inline CTest6Doc* CTest6View::GetDocument() const
   { return reinterpret_cast<CTest6Doc*>(m_pDocument); }
#endif

