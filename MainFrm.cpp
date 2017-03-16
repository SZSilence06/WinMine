// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WinMine.h"

#include "MainFrm.h"
#include "WinMineDoc.h"
#include "WinMineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MEDIUM, OnMedium)
	ON_COMMAND(ID_ADVANCE, OnAdvance)
	ON_COMMAND(ID_COLORFUL, OnColorful)
	ON_COMMAND(ID_PRIMARY, OnPrimary)
	ON_UPDATE_COMMAND_UI(ID_ADVANCE, OnUpdateAdvance)
	ON_UPDATE_COMMAND_UI(ID_PRIMARY, OnUpdatePrimary)
	ON_UPDATE_COMMAND_UI(ID_MEDIUM, OnUpdateMedium)
	ON_UPDATE_COMMAND_UI(ID_COLORFUL, OnUpdateColorful)
	ON_COMMAND(ID_MARK, OnMark)
	ON_UPDATE_COMMAND_UI(ID_MARK, OnUpdateMark)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style&=~(WS_MAXIMIZEBOX|WS_THICKFRAME|FWS_ADDTOTITLE); //固定窗口大小并指定窗口标题风格
	//设置初始窗口大小为“初级”难度的大小
	cs.cx=30+MINE_SIZE*PRIMARY_X;  
	cs.cy=110+MINE_SIZE*PRIMARY_Y;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ReCreate()
{
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	CRect rect;

	GetClientRect(rect);

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:SetWindowPos(&wndTopMost,0,0,30+MINE_SIZE*PRIMARY_X,
					 110+MINE_SIZE*PRIMARY_Y,SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
		break;
	case MEDIUM:SetWindowPos(&wndTopMost,0,0,30+MINE_SIZE*MEDIUM_X,
					 110+MINE_SIZE*MEDIUM_Y,SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
		break;
	case ADVANCE:SetWindowPos(&wndTopMost,0,0,30+MINE_SIZE*ADVANCE_X,
					 110+MINE_SIZE*ADVANCE_Y,SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
		break;
	}
	Invalidate();
}

void CMainFrame::OnPrimary() 
{
	// TODO: Add your command handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	pDoc->m_GameMode=PRIMARY;
	pDoc->InitGame();

	ReCreate();
}

void CMainFrame::OnMedium() 
{
	// TODO: Add your command handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	pDoc->m_GameMode=MEDIUM;
	pDoc->InitGame();

	ReCreate();
}



void CMainFrame::OnAdvance() 
{
	// TODO: Add your command handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	pDoc->m_GameMode=ADVANCE;
	pDoc->InitGame();

	ReCreate();
}

void CMainFrame::OnColorful() 
{
	// TODO: Add your command handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	
	if(pDoc->m_ColorMode==COLOR_COLOR) pDoc->m_ColorMode=COLOR_GRAY;
	else pDoc->m_ColorMode=COLOR_COLOR;
	
	Invalidate();
}

void CMainFrame::OnMark() 
{
	// TODO: Add your command handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	pDoc->m_Mark=!pDoc->m_Mark;
}


void CMainFrame::OnUpdatePrimary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	if(pDoc->m_GameMode==PRIMARY) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}

void CMainFrame::OnUpdateMedium(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	if(pDoc->m_GameMode==MEDIUM) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}

void CMainFrame::OnUpdateAdvance(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	if(pDoc->m_GameMode==ADVANCE) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}

void CMainFrame::OnUpdateColorful(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	if(pDoc->m_ColorMode==COLOR_COLOR) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateMark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	if(pDoc->m_Mark==true) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
	CWinMineDoc *pDoc=(CWinMineDoc *)GetActiveDocument();
	int x,y;
	
	if(pDoc->m_IsStarted==false) return;
	if(pDoc->m_IsEnded==true) return;

	switch(pDoc->m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	pDoc->m_time++;

	CRect TimerRect(MINE_SIZE*x-32,15,MINE_SIZE*x+7,38);
	InvalidateRect(&TimerRect);
	CFrameWnd::OnTimer(nIDEvent);
}
