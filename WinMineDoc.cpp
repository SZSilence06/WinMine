// WinMineDoc.cpp : implementation of the CWinMineDoc class
//

#include "stdafx.h"
#include "WinMine.h"

#include "WinMineDoc.h"
#include "WinMineView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinMineDoc

IMPLEMENT_DYNCREATE(CWinMineDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinMineDoc, CDocument)
	//{{AFX_MSG_MAP(CWinMineDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinMineDoc construction/destruction

CWinMineDoc::CWinMineDoc()
{
	// TODO: add one-time construction code here

}

CWinMineDoc::~CWinMineDoc()
{
}

BOOL CWinMineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	m_GameMode=PRIMARY;
	m_ColorMode=COLOR_COLOR;
	m_Mark=true;
	m_IsLR=false;
	InitGame();
	for(int i=0;i<200;i++)
	{
		for(int j=0;j<200;j++)
		{
			m_mine[i][j].x=i;m_mine[i][j].y=j;
		}
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWinMineDoc serialization

void CWinMineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWinMineDoc diagnostics

#ifdef _DEBUG
void CWinMineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinMineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinMineDoc commands

void CWinMineDoc::InitGame()
{
	m_ButtonState=NORMAL;
	m_time=0;
	m_IsStarted=m_IsEnded=false;
	int x,y,i,j;

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;
		m_TotalMine=PRIMARY_MINENUM;
		break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;
		m_TotalMine=MEDIUM_MINENUM;
		break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;
		m_TotalMine=ADVANCE_MINENUM;
		break;
	}
	m_LeftMine=m_TotalMine;
	m_Undetected=x*y;

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			m_mine[i][j].state=MINE_NORMAL;
			m_mine[i][j].IsMine=false;
		}
	}
}

void CWinMineDoc::InitMines()
{
	srand(time(NULL));
	int x,y,lx,ly,i,seed,minenum;
	
	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;
		minenum=PRIMARY_MINENUM;
		break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;
		minenum=MEDIUM_MINENUM;
		break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;
		minenum=ADVANCE_MINENUM;
		break;
	}

	for(i=0;i<minenum;i++)
	{
		seed=rand()%(x*y);
		lx=seed/y;
		ly=seed-y*lx;
		if(m_mine[lx][ly].IsMine==false) m_mine[lx][ly].IsMine=true;
		else i--;
	}
}

void CWinMineDoc::StartGame()
{
	CWnd *pWnd=AfxGetMainWnd();
	InitMines();
	m_IsStarted=true;
	pWnd->SetTimer(1,1000,NULL);
}


void CWinMineDoc::CountNearMine(int px,int py)
{
	int x,y,i,j,count=0;

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;
		break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;
		break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;
		break;
	}

	for(i=px-1;i<=px+1;i++)
	{
		if(i<0||i>=x) continue;
		for(j=py-1;j<=py+1;j++)
		{
			if(j<0||j>=y) continue;
			if(m_mine[i][j].IsMine==true) count++;
		}
	}
	m_mine[px][py].NearMine=count;
}

void CWinMineDoc::Expand(int px,int py)
{
	int x,y;
	bool Expanded[200][200]={0};

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;
		break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;
		break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;
		break;
	}

	queue<CMine *> q;
	q.push(&m_mine[px][py]);
	Expanded[px][py]=true;
	while(!q.empty())
	{
		CMine *qhead;
		qhead=q.front();
		for(int i=qhead->x-1;i<=qhead->x+1;i++)
		{
			if(i<0||i>=x) continue;
			for(int j=qhead->y-1;j<=qhead->y+1;j++)
			{
				if(j<0||j>=y) continue;
				if(m_mine[i][j].state!=MINE_DETECTED)
				{
					CountNearMine(i,j);
					m_mine[i][j].state=MINE_DETECTED;
					m_Undetected--;
					if(m_Undetected==m_TotalMine) Win();
				}
				if(m_mine[i][j].NearMine==0&&!Expanded[i][j])
				{
					q.push(&m_mine[i][j]);
					Expanded[i][j]=true;
				}
			}
		}
		q.pop();
	}
}

void CWinMineDoc::OnLRButton(int px,int py)
{
	int x,y,i,j,MarkedFlags=0;

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;
		break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;
		break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;
		break;
	}

	for(i=px-1;i<=px+1;i++)
	{
		if(i<0||i>=x) continue;
		for(j=py-1;j<=py+1;j++)
		{
			if(j<0||j>=y) continue;
			if(m_mine[i][j].state==MINE_MARKED) MarkedFlags++;
		}
	}
	if(MarkedFlags==m_mine[px][py].NearMine)
	{
		for(i=px-1;i<=px+1;i++)
		{
			if(i<0||i>=x) continue;
			for(j=py-1;j<=py+1;j++)
			{
				if(j<0||j>=y) continue;
				if(m_mine[i][j].state==MINE_MARKED) continue;
				if(m_mine[i][j].IsMine==true)
				{
					Lose(i,j);
					continue;
				}
				if(m_mine[i][j].state!=MINE_DETECTED)
				{
					CountNearMine(i,j);
					m_mine[i][j].state=MINE_DETECTED;
					m_Undetected--;
					CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
					AfxGetMainWnd()->InvalidateRect(InvalidRect);
					if(m_Undetected==m_TotalMine) Win();
				}
				if(m_mine[i][j].NearMine==0) Expand(i,j);
			}
		}
	}
	else
	{
		for(i=px-1;i<=px+1;i++)
		{
			if(i<0||i>=x) continue;
			for(j=py-1;j<=py+1;j++)
			{
				if(j<0||j>=y) continue;
				if(m_mine[i][j].state==MINE_CLICKED) m_mine[i][j].state=MINE_NORMAL;
				CRect InvalidRect(13+MINE_SIZE*i,52+MINE_SIZE*j,13+MINE_SIZE*(i+1),52+MINE_SIZE*(j+1));
				AfxGetMainWnd()->InvalidateRect(InvalidRect);
			}
		}
	}
}

void CWinMineDoc::Lose(int px,int py)
{
	m_mine[px][py].state=MINE_EXPLODE;
	m_ButtonState=DEAD;
	m_IsEnded=true;

	int x,y,i,j;

	CWnd *pWnd=AfxGetMainWnd();
	pWnd->KillTimer(1);

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			if(m_mine[i][j].IsMine==true&&m_mine[i][j].state==MINE_NORMAL) m_mine[i][j].state=MINE_ISMINE;
			if(m_mine[i][j].IsMine==false&&m_mine[i][j].state==MINE_MARKED) m_mine[i][j].state=MINE_WRONGMINE;
		}
	}
}

void CWinMineDoc::Win()
{
	m_ButtonState=WIN;
	m_IsEnded=true;
	m_LeftMine=0;

	int x,y,i,j;

	CWnd *pWnd=AfxGetMainWnd();
	pWnd->KillTimer(1);

	switch(m_GameMode)
	{
	case PRIMARY:x=PRIMARY_X;y=PRIMARY_Y;break;
	case MEDIUM:x=MEDIUM_X;y=MEDIUM_Y;break;
	case ADVANCE:x=ADVANCE_X;y=ADVANCE_Y;break;
	}

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			if(m_mine[i][j].IsMine==true) m_mine[i][j].state=MINE_MARKED;
		}
	}
}
