
// MFCDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "osc/OscReceivedElements.h"
#include <thread>
#include <map>
#include <string>

using namespace std;
using namespace osc;

#define WM_ADDSTRING0 WM_USER + 2000
#define WM_ADDSTRING1 WM_USER + 2001

#define WM_ADDSTRING5 WM_USER + 2005

// CMFCDemoDlg dialog
class CMFCDemoDlg : public CDialogEx
{
// Construction
public:
	CMFCDemoDlg(CWnd* pParent = NULL);	// standard constructor
    ~CMFCDemoDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDEMO_DIALOG };
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
    afx_msg void OnBnClickedOk();
    afx_msg void OnLbnSelchangeList2();
    afx_msg void OnLbnSelchangeList3();

    afx_msg LRESULT OnAddString(WPARAM wParam, LPARAM lParam);

    afx_msg LRESULT OnAddString5(WPARAM wParam, LPARAM lParam);

    void processOSC(const ReceivedMessage& msg);

    void ProcessBundle(const ReceivedBundle& b);

    void ProcessPacket(const char *data, int size);

    CListBox m_listbox0;
    CListBox m_listBox1;
    CListBox m_listbox2;
    CListBox m_listbox3;
    CListBox m_listbox4;

    CFont m_listFont;

    map<int32, std::string> m_2DcurSetBuf;

    int m_listCount0 = 0;
    int m_listCount1 = 0;
    int m_listCount2 = 0;
    int m_listCount3 = 0;
    int m_listCount4 = 0;

    std::string m_strBuffer;

    volatile bool m_threadRunning = false;

    std::thread  net_client_thread;

    afx_msg void OnLbnSelchangeList5();
    afx_msg void OnLbnSelchangeList6();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CListBox m_listbox5;
};
