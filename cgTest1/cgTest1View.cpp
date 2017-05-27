
// cgTest1View.cpp : CcgTest1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgTest1.h"
#endif

#include "cgTest1Doc.h"
#include "cgTest1View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgTest1View

IMPLEMENT_DYNCREATE(CcgTest1View, CView)

BEGIN_MESSAGE_MAP(CcgTest1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgTest1View::OnFilePrintPreview)
	//ON_WM_CONTEXTMENU()
	//	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POLYGON, &CcgTest1View::OnPolygon)
	ON_COMMAND(ID_FILLPOLYGON, &CcgTest1View::OnFillpolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CHANGE_DC, &CcgTest1View::OnChangeDc)
END_MESSAGE_MAP()

// CcgTest1View 构造/析构

CcgTest1View::CcgTest1View()
{
	// TODO: 在此处添加构造代码
	finish = false;
	m_pointNum = 0;
	m_point.clear();
	m_graphType = 1;
}

CcgTest1View::~CcgTest1View()
{
}

BOOL CcgTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgTest1View 绘制

void CcgTest1View::OnDraw(CDC* /*pDC*/)
{
	CcgTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CcgTest1View 打印


void CcgTest1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

//void CcgTest1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

//	void CcgTest1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//	{
//#ifndef SHARED_HANDLERS
//		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//	}


	// CcgTest1View 诊断

#ifdef _DEBUG
void CcgTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CcgTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgTest1Doc* CcgTest1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgTest1Doc)));
	return (CcgTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CcgTest1View 消息处理程序


void CcgTest1View::OnPolygon()
{
	// TODO: 在此添加命令处理程序代码
	m_graphType = 1;
}


void CcgTest1View::OnFillpolygon()
{
	// TODO: 在此添加命令处理程序代码
	m_graphType = 2;
}


void CcgTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_graphType == 1 && !finish)
	{
		m_point.push_back(point);
		m_pointNum++;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CcgTest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_graphType == 1)
	{
		finish = true;
		int i;
		for (i = 0; i < m_pointNum; i++)
		{
			int t;
			if (i < m_pointNum - 1)
				t = i + 1;
			else
				t = 0;
			drawLineMid(m_point[i], m_point[t]);
		}
		//drawLineMid(m_point[0],m_point[1]);
	}
	else
	{
		CDC *pDC = GetWindowDC();
		double y = 0.5;//saomiaoxian
		for (; y < 1000; y++)
		{
			vector<int> c;
			for (int i = 0; i < m_pointNum; i++)
			{
				int t;
				if (i < m_pointNum - 1)
					t = i + 1;
				else
					t = 0;
				CPoint p1 = m_point[i];
				CPoint p2 = m_point[t];
				if ((y<p1.y&&y>p2.y) || (y > p1.y&&y < p2.y))
				{
					int x = (y - p2.y)*(p1.x - p2.x) / (p1.y - p2.y) + p2.x;
					c.push_back(x);
				}
			}
			sort(c.begin(), c.end());
			for (int i = 0, j = 1; j < c.size(); i += 2, j += 2)
			{
				for (int x = c[i]; x <= c[j]; x++)
					pDC->SetPixel(CPoint(x, (int)y), RGB(255, 0, 0));
			}
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CcgTest1View::drawLineMid(CPoint p1, CPoint p2)
{
	CDC *pDC = GetWindowDC();

	if (p1.x > p2.x)
	{
		CPoint t = p1;
		p1 = p2;
		p2 = t;
	}
	bool convert_y = false, convert_xy = false;
	if (p1.y > p2.y)
	{
		convert_y = true;
		p1.y = -p1.y;
		p2.y = -p2.y;
	}
	if (p1.x == p2.x)
	{
		for (int i = p1.y; i <= p2.y; i++)
			pDC->SetPixel(CPoint(p1.x, i), RGB(255, 0, 0));
		return;
	}
	if (p1.y == p2.y)
	{
		for (int i = p1.x; i <= p2.x; i++)
			pDC->SetPixel(CPoint(i, p1.y), RGB(255, 0, 0));
		return;
	}
	if (p2.y - p1.y > p2.x - p1.x)
	{
		convert_xy = true;
		int t = p1.x;
		p1.x = p1.y;
		p1.y = t;
		t = p2.x;
		p2.x = p2.y;
		p2.y = t;
	}
	int a = p1.y - p2.y;
	int b = p2.x - p1.x;
	int d = 2 * a + b;
	int deta1 = 2 * a;
	int deta2 = 2 * (a + b);
	int x = p1.x, y = p1.y, px = x, py = y;
	while (x < p2.x)
	{
		px = x;
		py = y;
		if (convert_xy)
		{
			int t = px;
			px = py;
			py = t;
		}
		if (convert_y)
		{
			py = -py;
		}
		pDC->SetPixel(CPoint(px, py), RGB(255, 0, 0));

		if (d < 0)
		{
			x = x + 1;
			y = y + 1;
			d = d + deta2;
		}
		else
		{
			x = x + 1;
			d = d + deta1;
		}
	}
}


void CcgTest1View::OnChangeDc()
{
	// TODO: 在此添加命令处理程序代码
	CDC *pDC = GetWindowDC();
	pDC->LineTo(100, 100);
}
