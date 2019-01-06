
// Test1View.h : CTest1View ��Ľӿ�
//

#pragma once


class CTest1View : public CView
{
protected: // �������л�����
	CTest1View();
	DECLARE_DYNCREATE(CTest1View)

// ����
public:
	CTest1Doc* GetDocument() const;

// ����
public:
	int type;
	CPoint pointStart;
	CPoint pointEnd;
	bool isKeyUp;
	bool isKeyDown;
	int radius = 0;
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
	virtual ~CTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCircle();
	afx_msg void OnRecCircle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// �е㻭Բ�㷨
	void midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// Bresanham����Բ�㷨
	void bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color);
	// bresenham��Բ�㷨
	void bresenhamFullCicle(CDC* cdc, int x0, int y0, int r, COLORREF color);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
};

#ifndef _DEBUG  // Test1View.cpp �еĵ��԰汾
inline CTest1Doc* CTest1View::GetDocument() const
   { return reinterpret_cast<CTest1Doc*>(m_pDocument); }
#endif

