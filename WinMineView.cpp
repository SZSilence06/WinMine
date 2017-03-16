// WinMineView.cpp : implementation of the CWinMineView class
//

#include "stdafx.h"
#include "WinMine.h"

#include "WinMineDoc.h"
#include "WinMineView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinMineView

IMPLEMENT_DYNCREATE(CWinMineView, CView)

BEGIN_MESSAGE_MAP(CWinMineView, CView)
	//{{AFX_MSG_MAP(CWinMineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinMineView construction/destruction

CWinMineView::CWinMineView()
	: CView()
{
	//{{AFX_DATA_INIT(CWinMineView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CWinMineView::~CWinMineView()
{
}

void CWinMineView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinMineView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CWinMineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CWinMineView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CWinMineView diagnostics

#ifdef _DEBUG
void CWinMineView::AssertValid() const
{
	CView::AssertValid();
}

void CWinMineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinMineDoc* CWinMineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinMineDoc)));
	return (CWinMineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinMineView message handlers

void CWinMineView::DrawButton()
{
	pDoc=GetDocument();
	CClientDC dc(this);
	CDC cdc;
	CBitmap bmp;
	CRect rect;

	GetClientRect(rect);

	switch(pDoc->m_ColorMode)
	{
	case COLOR_COLOR:bmp.LoadBitmap(IDB_BUTTON_COLOR);break;
	case COLOR_GRAY:bmp.LoadBitmap(IDB_BUTTON_GRAY);break;
	}

	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(bmp);
	
	int l=rect.left,r=rect.right,t=rect.top,b=rect.bottom;
    dc.StretchBlt((l+r)/2-12,t+15,24,24,&cdc,0,pDoc->m_ButtonState*24,24,24,SRCCOPY);

	cdc.DeleteDC();
	bmp.DeleteObject();
}

void CWinMineView::DrawShell()
{
	CClientDC dc(this);
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();

	int x,y;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}
	
	dc.FillSolidRect(0,0,30+MINE_SIZE*x,5,WHITE);
	dc.FillSolidRect(0,0,5,74+MINE_SIZE*y,WHITE);
	dc.Draw3dRect(10,10,MINE_SIZE*x+6,34,DARK_GRAY,WHITE);
	dc.Draw3dRect(11,11,MINE_SIZE*x+4,34,DARK_GRAY-2,WHITE);
	dc.Draw3dRect(10,49,MINE_SIZE*x+6,MINE_SIZE*y+6,DARK_GRAY,WHITE);
	dc.Draw3dRect(11,50,MINE_SIZE*x+4,MINE_SIZE*y+4,DARK_GRAY,WHITE);
	dc.Draw3dRect(12,51,MINE_SIZE*x+2,MINE_SIZE*y+2,DARK_GRAY,WHITE);
}

void CWinMineView::DrawMine()
{
	pDoc=GetDocument();
	CBitmap bmp,MemBitmap;
	CClientDC dc(this);
	CDC MemDC,bmpDC;

	int x,y,i,j;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	switch(pDoc->m_ColorMode)
	{
	case COLOR_COLOR:bmp.LoadBitmap(IDB_MINE_COLOR);break;
	case COLOR_GRAY:bmp.LoadBitmap(IDB_MINE_GRAY);break;
	}

	bmpDC.CreateCompatibleDC(&MemDC);
	bmpDC.SelectObject(bmp);
	MemDC.CreateCompatibleDC(&dc);
	MemBitmap.CreateCompatibleBitmap(&dc,MINE_SIZE * x,MINE_SIZE * y);
	MemDC.SelectObject(&MemBitmap);
	

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			if(pDoc->m_mine[i][j].state==MINE_CLICKED)
			{
				MemDC.BitBlt(MINE_SIZE*i,MINE_SIZE*j,MINE_SIZE,MINE_SIZE,
					&bmpDC,0,240,SRCCOPY);
			}
			else if(pDoc->m_mine[i][j].state!=MINE_DETECTED)
			{
				MemDC.BitBlt(MINE_SIZE*i,MINE_SIZE*j,MINE_SIZE,MINE_SIZE,
					&bmpDC,0,MINE_SIZE*pDoc->m_mine[i][j].state,SRCCOPY);
			}
			else
			{
				MemDC.BitBlt(MINE_SIZE*i,MINE_SIZE*j,MINE_SIZE,MINE_SIZE,
					&bmpDC,0,240-MINE_SIZE*pDoc->m_mine[i][j].NearMine,SRCCOPY);
			}
		}
	}

	dc.BitBlt(13,52,1000,1000,&MemDC,0,0,SRCCOPY);

	bmpDC.DeleteDC();
	MemDC.DeleteDC();
	bmp.DeleteObject();
	MemBitmap.DeleteObject();
}

void CWinMineView::DrawCounter()
{
	pDoc=GetDocument();
	CBitmap bmp;
	CClientDC dc(this);
	CDC cdc;
	int LeftMine=pDoc->m_LeftMine;
	int num[3];

	if(LeftMine>=0)
	{
		if(LeftMine>999) LeftMine=999;
		num[0]=LeftMine/100;num[1]=LeftMine/10;num[2]=LeftMine%10;
	}
	else
	{
		if(LeftMine<-99) LeftMine=-99;
		num[0]=-1;num[1]=(-LeftMine)/10;num[2]=(-LeftMine)%10;
	}

	switch(pDoc->m_ColorMode)
	{
	case COLOR_COLOR:bmp.LoadBitmap(IDB_CLOCK_COLOR);break;
	case COLOR_GRAY:bmp.LoadBitmap(IDB_CLOCK_GRAY);break;
	}

	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(bmp);

	for(int i=0;i<3;i++)
	{
		if(num[i]==-1) dc.StretchBlt(18+13*i,15,13,23,&cdc,0,0,13,23,SRCCOPY);
		else dc.StretchBlt(18+13*i,15,13,23,&cdc,0,253-23*num[i],13,23,SRCCOPY);
	}

	cdc.DeleteDC();
	bmp.DeleteObject();
}

void CWinMineView::DrawTimer()
{
	pDoc=GetDocument();
	CBitmap bmp,MemBitmap;
	CClientDC dc(this);
	CDC MemDC,bmpDC;
	CRect rect;
	GetClientRect(rect);
	int time=pDoc->m_time;
	int num[3];
	int x,y;

	if(time>999) time=999;
	num[0]=time/100;num[1]=(time-num[0]*100)/10;num[2]=time%10;

	switch(pDoc->m_ColorMode)
	{
	case COLOR_COLOR:bmp.LoadBitmap(IDB_CLOCK_COLOR);break;
	case COLOR_GRAY:bmp.LoadBitmap(IDB_CLOCK_GRAY);break;
	}

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	bmpDC.CreateCompatibleDC(&MemDC);
	bmpDC.SelectObject(bmp);
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SetBkMode(TRANSPARENT);
	MemBitmap.CreateCompatibleBitmap(&dc,39,69);
	MemDC.SelectObject(&MemBitmap);
	
	for(int i=0;i<3;i++)  MemDC.BitBlt(13*i,0,13,23,&bmpDC,0,253-23*num[i],SRCCOPY);

	dc.BitBlt(MINE_SIZE*x-32,15,39,23,&MemDC,0,0,SRCCOPY);

	MemDC.DeleteDC();
	bmp.DeleteObject();
	MemBitmap.DeleteObject();
	bmpDC.DeleteDC();
}

void CWinMineView::OnDraw(CDC *pDC)
{
	pDoc=GetDocument();
	int x,y;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	pDC->FillSolidRect(0,0,20+MINE_SIZE*x,74+MINE_SIZE*y,GRAY);
	DrawButton();
	DrawShell();
	DrawCounter();
	DrawTimer();
	DrawMine();
}




void CWinMineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);

	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	pDoc->m_IsLR=false;
	
	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	CRect MineRect(13,52,13+MINE_SIZE*x,52+MINE_SIZE*y);
	CRect ButtonRect(rect.right/2-12,15,rect.right/2+12,39);

	//如果点击笑脸
	if(ButtonRect.PtInRect(point)) pDoc->m_ButtonState=CLICKED;
	else if(pDoc->m_IsEnded==true) return;
	else pDoc->m_ButtonState=CLICKMINE;
	
	//如果点击雷区
	if(MineRect.PtInRect(point))
	{
		if(nFlags   &   MK_RBUTTON)
		{
			OnLRButtonDown(point);
			return;
		}
		px=(point.x-13)/MINE_SIZE;
		py=(point.y-52)/MINE_SIZE;
		if(pDoc->m_mine[px][py].state==MINE_NORMAL)
		{
			pDoc->m_mine[px][py].state=MINE_CLICKED;
			CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));
			InvalidateRect(&InvalidRect);
		}
	}
	
	SetCapture();
	pDoc->m_prevhit=point;
	InvalidateRect(&ButtonRect);
	CView::OnLButtonDown(nFlags, point);
}



void CWinMineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);

	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	CRect MineRect(13,52,13+MINE_SIZE*x,52+MINE_SIZE*y);
	CRect ButtonRect(rect.right/2-12,15,rect.right/2+12,39);
	
	ReleaseCapture();

	//如果点击笑脸
	if(ButtonRect.PtInRect(point))
	{
		pDoc->InitGame();
		Invalidate();
	}
	else if(pDoc->m_IsEnded==true)
	{
		if(pDoc->m_ButtonState!=DEAD&&pDoc->m_LeftMine!=0)
		{
			pDoc->m_ButtonState=DEAD;
			InvalidateRect(ButtonRect);
		}
		else if(pDoc->m_ButtonState!=WIN&&pDoc->m_LeftMine==0)
		{
			pDoc->m_ButtonState=WIN;
			InvalidateRect(ButtonRect);
		}
		return;
	}

	//如果点击雷区
	else if(MineRect.PtInRect(point))
	{
		if(pDoc->m_IsLR)
		{
			OnLRButtonUp(point);
			return;
		}
		px=(point.x-13)/MINE_SIZE;
		py=(point.y-52)/MINE_SIZE;
		CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));

		if(pDoc->m_IsStarted==false) pDoc->StartGame();
		if(pDoc->m_mine[px][py].state==MINE_MARKED)
		{
			pDoc->m_ButtonState=NORMAL;
			InvalidateRect(&ButtonRect);
			CView::OnLButtonUp(nFlags, point);
			return;
		}
		if(pDoc->m_mine[px][py].IsMine==true) pDoc->Lose(px,py);
		else
		{
			if(pDoc->m_mine[px][py].state!=MINE_DETECTED)
			{
				pDoc->m_mine[px][py].state=MINE_DETECTED;
				pDoc->m_Undetected--;
				pDoc->CountNearMine(px,py);
				if(pDoc->m_Undetected==pDoc->m_TotalMine) pDoc->Win();
				if(pDoc->m_mine[px][py].NearMine==0)
				{
					pDoc->Expand(px,py);
					InvalidateRect(MineRect);
				}
			}
			pDoc->m_ButtonState=NORMAL;
		}	
	}
	else pDoc->m_ButtonState=NORMAL;

	InvalidateRect(&ButtonRect);
	CView::OnLButtonUp(nFlags, point);
}



void CWinMineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	if(!GetCapture()) return;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	CRect MineRect(13,52,13+MINE_SIZE*x,52+MINE_SIZE*y);
	CRect ButtonRect(rect.right/2-12,15,rect.right/2+12,39);

	if(pDoc->m_IsEnded==true) return;
	if(MineRect.PtInRect(point))
	{
		//如果是左右键同时按下
		if(pDoc->m_IsLR)
		{
			if(MineRect.PtInRect(pDoc->m_prevhit))
			{
				px=(pDoc->m_prevhit.x-13)/MINE_SIZE;
				py=(pDoc->m_prevhit.y-52)/MINE_SIZE;
				for(int i=px-1;i<=px+1;i++)
				{
					if(i<0||i>=x) continue;
					for(int j=py-1;j<=py+1;j++)
					{
						if(j<0||j>=y) continue;
						CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
						if(pDoc->m_mine[i][j].state==MINE_CLICKED)
						{
							pDoc->m_mine[i][j].state=MINE_NORMAL;
							InvalidateRect(&InvalidRect);
						}
					}
				}
			}
			px=(point.x-13)/MINE_SIZE;
			py=(point.y-52)/MINE_SIZE;
			for(int i=px-1;i<=px+1;i++)
			{
				if(i<0||i>=x) continue;
				for(int j=py-1;j<=py+1;j++)
				{
					if(j<0||j>=y) continue;
					CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
					if(pDoc->m_mine[i][j].state==MINE_NORMAL)
					{
						pDoc->m_mine[i][j].state=MINE_CLICKED;
						InvalidateRect(&InvalidRect);
					}
				}
			}
		}
		//不是左右键同时按下
		else
		{
			if(MineRect.PtInRect(pDoc->m_prevhit))
			{
				px=(pDoc->m_prevhit.x-13)/MINE_SIZE;
				py=(pDoc->m_prevhit.y-52)/MINE_SIZE;
				CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));
				if(pDoc->m_mine[px][py].state==MINE_CLICKED)
				{
					pDoc->m_mine[px][py].state=MINE_NORMAL;
					InvalidateRect(&InvalidRect);
				}
			}
			px=(point.x-13)/MINE_SIZE;
			py=(point.y-52)/MINE_SIZE;
			CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));
			if(pDoc->m_mine[px][py].state==MINE_NORMAL)
			{
				pDoc->m_mine[px][py].state=MINE_CLICKED;
				InvalidateRect(&InvalidRect);
			}
		}
	}
    else if(MineRect.PtInRect(pDoc->m_prevhit))
	{
		if(pDoc->m_IsLR)
		{
			px=(pDoc->m_prevhit.x-13)/MINE_SIZE;
			py=(pDoc->m_prevhit.y-52)/MINE_SIZE;
			for(int i=px-1;i<=px+1;i++)
			{
				if(i<0||i>=x) continue;
				for(int j=py-1;j<=py+1;j++)
				{
					if(j<0||j>=y) continue;
					CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
					if(pDoc->m_mine[i][j].state==MINE_CLICKED)
					{
						pDoc->m_mine[i][j].state=MINE_NORMAL;
						InvalidateRect(&InvalidRect);
					}
				}
			}
		}
		else
		{
			px=(pDoc->m_prevhit.x-13)/MINE_SIZE;
			py=(pDoc->m_prevhit.y-52)/MINE_SIZE;
			CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));\
			if(pDoc->m_mine[px][py].state==MINE_CLICKED)
			{
				pDoc->m_mine[px][py].state=MINE_NORMAL;
				InvalidateRect(&InvalidRect);
			}
		}
	}
	pDoc->m_prevhit=point;
	CView::OnMouseMove(nFlags, point);
}

void CWinMineView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	pDoc->m_IsLR=false;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	CRect MineRect(13,52,13+MINE_SIZE*x,52+MINE_SIZE*y);
	
	if(MineRect.PtInRect(point)&&pDoc->m_IsStarted&&!pDoc->m_IsEnded)
	{
		if(nFlags   &   MK_LBUTTON)
		{
			OnLRButtonDown(point);
			return;
		}
		px=(point.x-13)/MINE_SIZE;
		py=(point.y-52)/MINE_SIZE;
		CRect InvalidRect(13+MINE_SIZE*px,52+MINE_SIZE*py,13+MINE_SIZE*(px+1),52+MINE_SIZE*(py+1));
		if(pDoc->m_Mark)
		{
			switch(pDoc->m_mine[px][py].state)
			{
			case MINE_NORMAL:pDoc->m_mine[px][py].state=MINE_MARKED;
				pDoc->m_LeftMine--;
				break;
			case MINE_MARKED:pDoc->m_mine[px][py].state=MINE_QUESTIONED;
				pDoc->m_LeftMine++;
				break;
			case MINE_QUESTIONED:pDoc->m_mine[px][py].state=MINE_NORMAL;
				break;
			}
		}
		else
		{
			switch(pDoc->m_mine[px][py].state)
			{
			case MINE_NORMAL:pDoc->m_mine[px][py].state=MINE_MARKED;
				pDoc->m_LeftMine--;
				break;
			case MINE_MARKED:pDoc->m_mine[px][py].state=MINE_NORMAL;
				pDoc->m_LeftMine++;
				break;
			}
		}
		InvalidateRect(InvalidRect);
	}
	CView::OnRButtonDown(nFlags, point);
}

void CWinMineView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	CRect MineRect(13,52,13+MINE_SIZE*x,52+MINE_SIZE*y);
	
	if(MineRect.PtInRect(point)&&pDoc->m_IsStarted&&!pDoc->m_IsEnded)
	{
		if(pDoc->m_IsLR)
		{
			OnLRButtonUp(point);
			return;
		}
	}
	CView::OnRButtonUp(nFlags, point);
}

void CWinMineView::OnLRButtonDown(CPoint point)
{
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	pDoc->m_IsLR=true;
	pDoc->m_prevhit=point;
	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	px=(point.x-13)/MINE_SIZE;
	py=(point.y-52)/MINE_SIZE;
	switch(pDoc->m_mine[px][py].state)
	{
	case MINE_DETECTED:
	case MINE_CLICKED:
	case MINE_NORMAL:
		for(int i=px-1;i<=px+1;i++)
		{
			if(i<0||i>=x) continue;
			for(int j=py-1;j<=py+1;j++)
			{
				if(j<0||j>=y) continue;
				if(pDoc->m_mine[i][j].state==MINE_NORMAL) pDoc->m_mine[i][j].state=MINE_CLICKED;
				CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
				InvalidateRect(InvalidRect);
			}
		}
	}
}

void CWinMineView::OnLRButtonUp(CPoint point)
{
	CRect rect;
	GetClientRect(rect);
	CRect ButtonRect(rect.right/2-12,15,rect.right/2+12,39);
	CWinMineDoc *pDoc=(CWinMineDoc *)GetDocument();
	int x,y,px,py;

	pDoc->m_ButtonState=NORMAL;
	InvalidateRect(ButtonRect);

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	px=(point.x-13)/MINE_SIZE;
	py=(point.y-52)/MINE_SIZE;

	switch(pDoc->m_mine[px][py].state)
	{
	case MINE_DETECTED:
		pDoc->OnLRButton(px,py);
		break;
	case MINE_CLICKED:
	case MINE_MARKED:
	case MINE_NORMAL:
		for(int i=px-1;i<=px+1;i++)
		{
			if(i<0||i>=x) continue;
			for(int j=py-1;j<=py+1;j++)
			{
				if(j<0||j>=y) continue;
				if(pDoc->m_mine[i][j].state==MINE_CLICKED) pDoc->m_mine[i][j].state=MINE_NORMAL;
				CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
				InvalidateRect(InvalidRect);
			}
		};
	}
}


BOOL CWinMineView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}
