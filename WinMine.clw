; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWinMineView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinMine.h"
LastPage=0

ClassCount=5
Class1=CWinMineApp
Class2=CWinMineDoc
Class3=CWinMineView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource7=IDD_WINMINE_FORM

[CLS:CWinMineApp]
Type=0
HeaderFile=WinMine.h
ImplementationFile=WinMine.cpp
Filter=N
LastObject=CWinMineApp

[CLS:CWinMineDoc]
Type=0
HeaderFile=WinMineDoc.h
ImplementationFile=WinMineDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CWinMineDoc

[CLS:CWinMineView]
Type=0
HeaderFile=WinMineView.h
ImplementationFile=WinMineView.cpp
Filter=W
LastObject=CWinMineView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=WinMine.cpp
ImplementationFile=WinMine.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_NEWGAME
Command2=ID_PRIMARY
Command3=ID_MEDIUM
Command4=ID_ADVANCE
Command5=ID_COLORFUL
Command6=ID_MARK
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_WINMINE_FORM]
Type=1
Class=CWinMineView
ControlCount=0

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

