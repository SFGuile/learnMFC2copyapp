
// copyappDlg.cpp : implementation file
//

#include "stdafx.h"
#include "copyapp.h"
#include "copyappDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcopyappDlg dialog



CcopyappDlg::CcopyappDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COPYAPP_DIALOG, pParent)
	, copiesamount(0)
	, m_filepathstring(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcopyappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CopiesEdit, copiesamount);
	DDV_MinMaxInt(pDX, copiesamount, 1, 1000);
	DDX_Text(pDX, IDC_FilePathEdit, m_filepathstring);
}

BEGIN_MESSAGE_MAP(CcopyappDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FilePathBtn, &CcopyappDlg::OnBnClickedFilepathbtn)
	ON_BN_CLICKED(IDC_CopyBtn, &CcopyappDlg::OnBnClickedCopybtn)
	ON_BN_CLICKED(IDC_ExitBtn, &CcopyappDlg::OnBnClickedExitbtn)
END_MESSAGE_MAP()


// CcopyappDlg message handlers

BOOL CcopyappDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	copiesamount = 1;
	UpdateData(false);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcopyappDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CcopyappDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcopyappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcopyappDlg::OnBnClickedFilepathbtn()
{

	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE); // TRUE is to tell the dialog is used as an open CFileDialog.
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		m_filepathstring = sFilePath;
		SetDlgItemText(IDC_FilePathEdit, sFilePath);

	}
}

int LastIndexOf(const CString& s1, const CString& s2)
{
	int start = s1.Find(s2, 0);

	if (start >= 0)
	{
		while (start < s1.GetLength())
		{
			int idx = s1.Find(s2, start + 1);
			if (idx >= 0)
				start = idx;
			else
				break;
		}
	}

	return start;
}



void CcopyappDlg::OnBnClickedCopybtn()
{
	// TODO: Add your control notification handler code here
	if (::MessageBox(NULL,  L"确认复制吗？",L"提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (m_filepathstring.IsEmpty())
		{
			::MessageBox(
				NULL,
				L"先选择好要复制的文件后再试",
				NULL,
				MB_OK
			);
			return;
		 }

		if (GetFileAttributes(m_filepathstring) == INVALID_FILE_ATTRIBUTES)
		{
			::MessageBox(
				NULL,
				L"要复制的文件不存在",
				NULL,
				MB_OK
			);
			return;
		}

		if (copiesamount <= 0)
		{
			::MessageBox(
				NULL,
				L"要复制的数量不能小于等于0",
				NULL,
				MB_OK
			);
			return;
		}

		CString myentry =L".";
		int dotpostion = LastIndexOf(m_filepathstring, myentry);

		CString path1 = m_filepathstring.Mid(0, dotpostion);
		CString extension = m_filepathstring.Right(m_filepathstring.GetLength() - dotpostion-1);



		for (int i = 0; i < copiesamount; i++)
		{
			CString mystr;
			mystr.Format(L"%d", i+2);
			CString dest = path1 + mystr +L"."+ extension;
			CopyFile(m_filepathstring, dest, false);
		}
	}
}




void CcopyappDlg::OnBnClickedExitbtn()
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}
