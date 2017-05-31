
// cgTest1View.h : CcgTest1View 类的接口
//

#pragma once

#include <vector>
#include <algorithm>
#define STOP 0
#define DrawPolygon 1
#define DrawLine 2
#define DrawRect 3
#define BuildCoordinate 4 

using namespace std;

class CcgTest1View : public CView
{
protected: // 仅从序列化创建
	CcgTest1View();
	DECLARE_DYNCREATE(CcgTest1View)

// 特性
public:
	CcgTest1Doc* GetDocument() const;

	int m_pointNum;

	int type;
	bool finish;
	vector<CPoint> m_point; 

	pair<CPoint, CPoint>* line;
	vector<pair<CPoint, CPoint>*> lines;
	pair<CPoint, CPoint> rect;

	int cx, cy;

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
	virtual ~CcgTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPolygon();
	afx_msg void OnFillpolygon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void drawLineMid(CPoint p1,CPoint p2);
	afx_msg void OnChangeDc();
	afx_msg void OnDrawline();
	afx_msg void OnDrawrect();
	afx_msg void OnClipping();
	afx_msg void buildCoordinate();
};

#ifndef _DEBUG  // cgTest1View.cpp 中的调试版本
inline CcgTest1Doc* CcgTest1View::GetDocument() const
   { return reinterpret_cast<CcgTest1Doc*>(m_pDocument); }
#endif

