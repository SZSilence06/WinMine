// WinMineDoc.h : interface of the CWinMineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINMINEDOC_H__7379C711_93F1_40FC_9ED8_3C4959DBB320__INCLUDED_)
#define AFX_WINMINEDOC_H__7379C711_93F1_40FC_9ED8_3C4959DBB320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"

class CWinMineDoc : public CDocument
{
protected: // create from serialization only
	CWinMineDoc();
	DECLARE_DYNCREATE(CWinMineDoc)

// Attributes
public:
	BUTTON_STATE m_ButtonState;
	CMine m_mine[200][200];
	GAME_MODE m_GameMode;
	COLOR_MODE m_ColorMode;
	int m_LeftMine;
	int m_TotalMine;
	int m_Undetected;
	int m_time;
	bool m_IsStarted;
	bool m_IsEnded;
	bool m_Mark;
	bool m_IsLR;
	CPoint m_prevhit;

// Operations
public:
	void InitGame();
	void StartGame();
	void InitMines();
	void CountNearMine(int px,int py);
	void Expand(int px,int py);
	void Lose(int px,int py);
	void OnLRButton(int px,int py);
	void Win();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinMineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinMineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinMineDoc)
	afx_msg void OnMedium();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINMINEDOC_H__7379C711_93F1_40FC_9ED8_3C4959DBB320__INCLUDED_)
