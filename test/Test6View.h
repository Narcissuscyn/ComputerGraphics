
// Test6View.h : CTest6View ��Ľӿ�
//

#pragma once


class CTest6View : public CView
{
protected: // �������л�����
	CTest6View();
	DECLARE_DYNCREATE(CTest6View)

// ����
public:
	CTest6Doc* GetDocument() const;

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
	virtual ~CTest6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Test6View.cpp �еĵ��԰汾
inline CTest6Doc* CTest6View::GetDocument() const
   { return reinterpret_cast<CTest6Doc*>(m_pDocument); }
#endif

