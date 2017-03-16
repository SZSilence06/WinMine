// WinMineView.h : interface of the CWinMineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINMINEVIEW_H__61D5F0C5_1B38_456C_9CF4_ED820AABF3DB__INCLUDED_)
#define AFX_WINMINEVIEW_H__61D5F0C5_1B38_456C_9CF4_ED820AABF3DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinMineDoc.h"

class CWinMineView : public CView
{
protected: // create from serialization only
	CWinMineView();
	DECLARE_DYNCREATE(CWinMineView)

public:
	//{{AFX_DATA(CWinMineView)
	enum{ IDD = IDD_WINMINE_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CWinMineDoc* GetDocument();

// Operations
public:
	virtual void OnDraw(CDC *pDC);
	void DrawButton();
	void DrawShell();
	void DrawMine();
	void DrawCounter();
	void DrawTimer();
	void OnLRButtonDown(CPoint point);
	void OnLRButtonUp(CPoint point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinMineView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinMineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWinMineDoc *pDoc;

// Generated message map functions
protected:
	//{{AFX_MSG(CWinMineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WinMineView.cpp
inline CWinMineDoc* CWinMineView::GetDocument()
   { return (CWinMineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINMINEVIEW_H__61D5F0C5_1B38_456C_9CF4_ED820AABF3DB__INCLUDED_)
