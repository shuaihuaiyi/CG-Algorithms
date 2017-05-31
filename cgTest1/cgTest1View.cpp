
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
	ON_COMMAND(ID_drawLine, &CcgTest1View::OnDrawline)
	ON_COMMAND(ID_drawRect, &CcgTest1View::OnDrawrect)
	ON_COMMAND(ID_clipping, &CcgTest1View::OnClipping)
	ON_COMMAND(ID_32785, &CcgTest1View::buildCoordinate)
	ON_COMMAND(ID_32792, &CcgTest1View::drawPol)
	ON_COMMAND(ID_32793, &CcgTest1View::moveUp)
	ON_COMMAND(ID_32794, &CcgTest1View::moveDown)
	ON_COMMAND(ID_32795, &CcgTest1View::moveLeft)
	ON_COMMAND(ID_32796, &CcgTest1View::moveRight)
	ON_COMMAND(ID_32789, &CcgTest1View::symx)
	ON_COMMAND(ID_32790, &CcgTest1View::symy)
	ON_COMMAND(ID_32791, &CcgTest1View::symo)
	ON_COMMAND(ID_32801, &CcgTest1View::symxy)
	ON_COMMAND(ID_32802, &CcgTest1View::protate)
	ON_COMMAND(ID_32798, &CcgTest1View::nrotate)
	ON_COMMAND(ID_32799, &CcgTest1View::smaller)
	ON_COMMAND(ID_32800, &CcgTest1View::larger)
	ON_COMMAND(ID_anm, &CcgTest1View::OnAnm)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CcgTest1View 构造/析构

CcgTest1View::CcgTest1View()
{
	// TODO: 在此处添加构造代码
	finish = false;
	m_pointNum = 0;
	points.clear();
	type = 1;
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
	finish = false;
	points.clear();
	type = DrawPolygon;
}
void CcgTest1View::OnFillpolygon()
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
			CPoint p1 = points[i];
			CPoint p2 = points[t];
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

void CcgTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDC *pDC = GetWindowDC();
	if (type == DrawPolygon)
	{
		points.push_back(point);
		m_pointNum++;
	}
	else if (type == DrawLine)
	{
		if (!finish)
		{
			line = new pair<CPoint, CPoint>;
			line->first = point;
			finish = true;
		}
		else
		{
			line->second = point;
			finish = false;
			CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->MoveTo(line->first);
			pDC->LineTo(line->second);
			pDC->SelectObject(pOldPen);
			lines.push_back(line);
		}
	}
	else if (type == DrawRect)
	{
		if (!finish)
		{
			rect.first = point;
			finish = true;
		}
		else
		{
			rect.second = point;
			pDC->Rectangle(rect.first.x, rect.first.y, rect.second.x, rect.second.y);
			type = STOP;
		}
	}
	else if (type == BuildCoordinate)
	{
		cx = point.x;
		cy = point.y;
		pDC->MoveTo(cx, 0);
		pDC->LineTo(cx, 2000);
		pDC->MoveTo(0, cy);
		pDC->LineTo(2000, cy);
		type = STOP;
	}
	else if (type==DrawPol)
	{
		points.push_back(point);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CcgTest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDC *pDC = GetWindowDC();
	if (type == DrawPolygon)
	{
		int i;
		for (i = 0; i < m_pointNum; i++)
		{
			int t;
			if (i < m_pointNum - 1)
				t = i + 1;
			else
				t = 0;
			drawLineMid(points[i], points[t]);
		}
		type = STOP;
	}
	else if (type == DrawPol)
	{
		for (int i = 0; i < points.size(); i++)
		{
			int t;
			if (i < points.size() - 1)
				t = i + 1;
			else
				t = 0;
			pDC->MoveTo(points[i]);
			pDC->LineTo(points[t]);
		}
		type = STOP;
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
	pDC->LineTo(-100, 100);
}

void CcgTest1View::OnDrawline()
{
	finish = false;
	type = DrawLine;
	lines.clear();
}

void CcgTest1View::OnDrawrect()
{
	finish = false;
	type = DrawRect;
}

void CcgTest1View::OnClipping()
{
	type = STOP;
	CDC *pDC = GetWindowDC();
	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines.at(i);
		char code1 = 0;
		char code2 = 0;
		if (line->first.x < rect.first.x)
			code1 += 1;
		else if (line->first.x > rect.second.x)
			code1 += 2;
		if (line->first.y < rect.first.y)
			code1 += 4;
		else if (line->first.y > rect.second.y)
			code1 += 8;
		if (line->second.x < rect.first.x)
			code2 += 1;
		else if (line->second.x > rect.second.x)
			code2 += 2;
		if (line->second.y < rect.first.y)
			code2 += 4;
		else if (line->second.y > rect.second.y)
			code2 += 8;
		if (code1 == 0 && code2 == 0)
		{
			pDC->MoveTo(line->first);
			pDC->LineTo(line->second);
			continue;
		}
		if ((code1&code2) == 0)
		{
			int x1, y1, x2, y2, x3, y3, x4, y4;
			vector<CPoint*> np;
			x1 = rect.first.x;
			y2 = rect.first.y;
			x3 = rect.second.x;
			y4 = rect.second.y;
			y1 = (x1 - line->first.x)*(line->second.y - line->first.y) / (line->second.x - line->first.x) + line->first.y;
			y3 = (x3 - line->first.x)*(line->second.y - line->first.y) / (line->second.x - line->first.x) + line->first.y;
			x2 = (y2 - line->first.y)*(line->second.x - line->first.x) / (line->second.y - line->first.y) + line->first.x;
			x4 = (y4 - line->first.y)*(line->second.x - line->first.x) / (line->second.y - line->first.y) + line->first.x;
			int sx, sy, lx, ly;
			sx = (line->first.x <= line->second.x ? line->first : line->second).x;
			sy = (line->first.y <= line->second.y ? line->first : line->second).y;
			lx = (line->first.x > line->second.x ? line->first : line->second).x;
			ly = (line->first.y > line->second.y ? line->first : line->second).y;
			if (y1<y4 && y1 > y2 && y1 < ly && y1 > sy)
				np.push_back(new CPoint(x1, y1));
			if (y3<y4 && y3 > y2&& y3 < ly && y3 > sy)
				np.push_back(new CPoint(x3, y3));
			if (x2<x3 && x2 > x1&& x2 < lx && x2 > sx)
				np.push_back(new CPoint(x2, y2));
			if (x4<x3 && x4 > x1&& x4 < lx && x4 > sx)
				np.push_back(new CPoint(x4, y4));
			if (code1 == 0)
				np.push_back(&line->first);
			if (code2 == 0)
				np.push_back(&line->second);
			if (np.size() == 2)
			{
				pDC->MoveTo(*np.at(0));
				pDC->LineTo(*np.at(1));
			}
		}
	}
	pDC->SelectObject(pOldPen);
}

void CcgTest1View::buildCoordinate()
{
	type = BuildCoordinate;
	RedrawWindow();
}

void CcgTest1View::drawPol()
{
	finish = false;
	type = DrawPol;
	points.clear();
}

void CcgTest1View::moveUp()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].y -= 10;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}

void CcgTest1View::moveDown()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].y += 10;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}

void CcgTest1View::moveLeft()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].x -= 10;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}

void CcgTest1View::moveRight()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].x += 10;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::symx()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].y = 2*cy - points[i].y;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}

void CcgTest1View::symy()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
		points[i].x = 2 * cx - points[i].x;
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::symo()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		points[i].y = 2 * cy - points[i].y;
		points[i].x = 2 * cx - points[i].x;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::symxy()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		int temp = points[i].x;
		points[i].x = cx + cy - points[i].y;
		points[i].y= cx + cy - temp;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}

void CcgTest1View::protate()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		int x = points[i].x -cx;
		int y = points[i].y-cy;
		points[i].x = cos(0.1)*x - sin(0.1)*y+cx;
		points[i].y = sin(0.1)*x + cos(0.1)*y+cy;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::nrotate()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		int x = points[i].x -cx;
		int y = points[i].y -cy;
		points[i].x = cos(-0.1)*x - sin(-0.1)*y +cx;
		points[i].y = sin(-0.1)*x + cos(-0.1)*y +cy;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::smaller()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		int x = points[i].x - cx;
		int y = points[i].y - cy;
		points[i].x = 0.5*x + cx;
		points[i].y = 0.5*y + cy;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::larger()
{
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < points.size(); i++)
	{
		int x = points[i].x - cx;
		int y = points[i].y - cy;
		points[i].x = 2*x + cx;
		points[i].y = 2*y + cy;
	}
	for (int i = 0; i < points.size(); i++)
	{
		int t;
		if (i < points.size() - 1)
			t = i + 1;
		else
			t = 0;
		pDC->MoveTo(points[i]);
		pDC->LineTo(points[t]);
	}
}


void CcgTest1View::OnAnm()
{
	SetTimer(1, 50, nullptr);
}


void CcgTest1View::OnTimer(UINT_PTR nIDEvent)
{
	CDC *pDC = GetWindowDC();
	RedrawWindow();
	pDC->Rectangle(cx1,cy1,cx2,cy2);
	cx1 += xs;
	cx2 += xs;
	cy1 += ys;
	cy2 += ys;
	if (cx1 > 1000 || cx1 < 100)
		xs = -xs;
	if (cy1 > 500 || cy1 < 100)
		ys = -ys;
	CView::OnTimer(nIDEvent);
}
