
// Test4View.h : CTest4View ��Ľӿ�
//

#pragma once

#include "file.h"

class CTest4View : public CView
{
protected: // �������л�����
	CTest4View();
	DECLARE_DYNCREATE(CTest4View)

// ����
public:
	CTest4Doc* GetDocument() const;
	

// ����
public:
	//
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
	virtual ~CTest4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCut();
	// �ж�һ�����Ƿ��ڲü��ߵ��ڲ�	
	bool isPointInside(CPoint p, Boundary b, CPoint winPointMin, CPoint winPointMax);
	// �жϱ��봰�ڱ߽�Ĺ�ϵ
	bool isCross(CPoint p1, CPoint p2, Boundary b, CPoint winPointMin, CPoint winPointMax);
	// �󽻵�
	CPoint interSect(CPoint p1, CPoint p2, Boundary b, CPoint winMin, CPoint winMax);
	void cutPoint(CPoint p, Boundary b, CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s);
	void closeCut(CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s);
	int polygonPoint(CPoint winMin, CPoint winMax, int n, CPoint* pIn, CPoint* pOut);
	void ClearScreen();
	// ��ü��к����������
	void getPointSave(CPoint* pIn, CPoint* pOut);
	void DDLline(int x1, int y1, int x2, int y2);
	// ���ݸ��������������
	void fillArea(CDC* cdc, CPoint* p, int point_num, COLORREF color);
	void edgeMarkFilld(CDC* cdc, bool mask[500][500], COLORREF color);
};

#ifndef _DEBUG  // Test4View.cpp �еĵ��԰汾
inline CTest4Doc* CTest4View::GetDocument() const
   { return reinterpret_cast<CTest4Doc*>(m_pDocument); }
#endif

