
// Test2View.h : CTest2View ��Ľӿ�
//

#pragma once


class CTest2View : public CView
{
protected: // �������л�����
	CTest2View();
	DECLARE_DYNCREATE(CTest2View)

// ����
public:
	CTest2Doc* GetDocument() const;

// ����
public:
	int minX;
	int minY;
	int maxX;
	int maxY;
	bool isInside;
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
	virtual ~CTest2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// ��������ĵ㣬���ƶ����
	void paintImage(CDC* cdc);
	// ������㷨
	void edgeMarkFilld(CDC* cdc, bool mask[500][500], bool num_array[10][25], COLORREF color);
	void DDLline(int x1, int y1, int x2, int y2);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Test2View.cpp �еĵ��԰汾
inline CTest2Doc* CTest2View::GetDocument() const
   { return reinterpret_cast<CTest2Doc*>(m_pDocument); }
#endif

