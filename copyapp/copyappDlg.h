
// copyappDlg.h : header file
//

#pragma once


// CcopyappDlg dialog
class CcopyappDlg : public CDialogEx
{
// Construction
public:
	CcopyappDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COPYAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int copiesamount;
	CString m_filepathstring;
	afx_msg void OnBnClickedFilepathbtn();
	afx_msg void OnBnClickedCopybtn();
	afx_msg void OnBnClickedExitbtn();
};
