
// MFCDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDemo.h"
#include "MFCDemoDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 3333
#define MAXLINE     2048

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


// CMFCDemoDlg dialog



CMFCDemoDlg::CMFCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_listbox0);
    DDX_Control(pDX, IDC_LIST3, m_listBox1);
    DDX_Control(pDX, IDC_LIST4, m_listbox2);
    DDX_Control(pDX, IDC_LIST5, m_listbox3);
    DDX_Control(pDX, IDC_LIST6, m_listbox4);
}

BEGIN_MESSAGE_MAP(CMFCDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CMFCDemoDlg::OnBnClickedOk)
    ON_LBN_SELCHANGE(IDC_LIST2, &CMFCDemoDlg::OnLbnSelchangeList2)
    ON_LBN_SELCHANGE(IDC_LIST3, &CMFCDemoDlg::OnLbnSelchangeList3)
    ON_MESSAGE(WM_ADDSTRING0, &CMFCDemoDlg::OnAddString)
    ON_MESSAGE(WM_ADDSTRING5, &CMFCDemoDlg::OnAddString5)
    ON_LBN_SELCHANGE(IDC_LIST5, &CMFCDemoDlg::OnLbnSelchangeList5)
    ON_LBN_SELCHANGE(IDC_LIST6, &CMFCDemoDlg::OnLbnSelchangeList6)
    ON_WM_TIMER()
END_MESSAGE_MAP()

//#include <iostream>
//#include <cstring> // 为了使用std::strlen和std::strcmp

// 自定义的搜索函数，考虑字符串的长度
char* my_strstr(const char* haystack, size_t haystack_len, const char* needle, size_t needle_len) {
    if (needle_len == 0) {
        return const_cast<char*>(haystack); // 空字符串总是匹配在任何位置
    }

    if (haystack_len < needle_len) {
        return nullptr; // 如果被搜索字符串比子字符串短，则无法匹配
    }

    // 遍历haystack，尝试找到匹配的子字符串
    for (size_t i = 0; i <= haystack_len - needle_len; ++i) {
        // 检查从当前位置开始的子字符串是否与needle匹配
        if (std::strncmp(haystack + i, needle, needle_len) == 0) {
            return const_cast<char*>(haystack + i); // 返回匹配的起始位置
        }
    }

    return nullptr; // 没有找到匹配
}

//int main() {
//    // 示例字符串，包含空字符
//    char haystack[] = "Hello\0World\0Example";
//    size_t haystack_len = sizeof(haystack) - 1; // 字符串的实际长度，不包括最后的'\0'（如果有的话）
//                                                // 注意：如果haystack是以'\0'结尾的，并且你想要包括最后的'\0'之前的所有字符，
//                                                // 你需要手动计算长度，或者使用strlen（但这在包含'\0'的情况下不起作用）
//                                                // 在这里，我们假设我们知道字符串的实际长度。
//
//    const char* needle = "World";
//    size_t needle_len = std::strlen(needle);
//
//    // 调用自定义的搜索函数
//    char* result = my_strstr(haystack, haystack_len, needle, needle_len);
//
//    if (result != nullptr) {
//        std::cout << "Found the substring!" << std::endl;
//    }
//    else {
//        std::cout << "Substring not found." << std::endl;
//    }
//
//    return 0;
//}


LRESULT CMFCDemoDlg::OnAddString(WPARAM wParam, LPARAM lParam)
{
    char *szBuf = (char*)wParam;
    int bytesReceived = lParam;

    char szBuf1[1024] = { 0 };
    sprintf(szBuf1, "444 11 Entry OnAddString bytesReceived:%d\n", bytesReceived);
    OutputDebugStringA(szBuf1);

    char* result = my_strstr(szBuf, bytesReceived, "/tuio/2Dcur", strlen("/tuio/2Dcur"));
    if (result)
    {
        sprintf(szBuf1, "555 11 Entry OnAddString result:%p\n", result);
        OutputDebugStringA(szBuf1);

        result = my_strstr(szBuf, bytesReceived, "set", strlen("set"));
        if (result)
        {
            ProcessPacket(szBuf, bytesReceived);

            char szRes[128] = { 0 };
            sprintf(szRes, "/tuio/2Dcur cameraId: %d", result[7]);
            if (result[7] == 0)
            {
                //m_listbox0.AddString(szRes);
            }
            else
            {
                //m_listBox1.AddString(szRes);
            }

            char szBuf[1024] = { 0 };
            sprintf(szBuf, "444 11 OnAddString CameraId:%d\n", result[7]);
            OutputDebugStringA(szBuf);
            //Invalidate();
            //PostMessage(pThis->GetSafeHwnd(), WM_ADDSTRING0, (WPARAM)recvBuf, 0);
        }
    }

    delete[] szBuf;
    return 0;
}

LRESULT CMFCDemoDlg::OnAddString5(WPARAM wParam, LPARAM lParam)
{
    int gunId = -1;
    int x = 0;
    int y = 0;
    char *szBuf = (char*)wParam;
    int bytesReceived = lParam;
    char* result = my_strstr(szBuf, bytesReceived, "ptScreen_x", strlen("ptScreen_x"));
    if (result)
    {
        sscanf(szBuf, "laserid:%d, ptScreen_x:%d, ptScreen_y:%d", &gunId, &x, &y);
        if (gunId != -1)
        {
            m_2DcurSetBuf[gunId] = szBuf;
        }
    }

    int shootId = -1;
    result = my_strstr(szBuf, bytesReceived, "dwCameraId", strlen("dwCameraId"));
    if (result)
    {
        sscanf(szBuf, "laserid:%d, dwCameraId:%d", &gunId, &shootId);
        if (shootId == 0)
        {
            int nIndex = LB_ERR;
            for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
            {
                if (iter->first == gunId)
                {
                    std::string strList = iter->second.c_str();
                    if (string::npos != strList.find(","))
                    {
                        strList = strList.substr(strList.find(",") + 1);
                    }

                    strList += ",laserid:0";

                    nIndex = m_listbox0.AddString(strList.c_str());
                    //nIndex = m_listbox0.AddString(iter->second.c_str());
                    iter = m_2DcurSetBuf.erase(iter);
                }
                else
                {
                    iter++;
                }
            }

            //nIndex = m_listbox0.AddString(szBuf);
            if (nIndex != LB_ERR)
            {
                m_listbox0.SetCurSel(nIndex);
                m_listbox0.SetTopIndex(nIndex);
                m_listbox0.Invalidate();
                m_listbox0.UpdateWindow();
            }
        }
        else if (shootId == 1)
        {
            int nIndex = LB_ERR;
            for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
            {
                if (iter->first == gunId)
                {
                    std::string strList = iter->second.c_str();
                    if (string::npos != strList.find(","))
                    {
                        strList = strList.substr(strList.find(",") + 1);
                    }

                    strList += ",laserid:1";

                    nIndex = m_listBox1.AddString(strList.c_str());

                    //nIndex = m_listBox1.AddString(iter->second.c_str());
                    iter = m_2DcurSetBuf.erase(iter);
                }
                else
                {
                    iter++;
                }
            }

            //int nIndex = m_listBox1.AddString(szBuf);
            if (nIndex != LB_ERR)
            {
                m_listBox1.SetCurSel(nIndex);
                m_listBox1.SetTopIndex(nIndex);
                m_listBox1.Invalidate();
                m_listBox1.UpdateWindow();
            }
        }
        else if (shootId == 2)
        {
            int nIndex = LB_ERR;
            for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
            {
                if (iter->first == gunId)
                {
                    std::string strList = iter->second.c_str();
                    if (string::npos != strList.find(","))
                    {
                        strList = strList.substr(strList.find(",") + 1);
                    }

                    strList += ",laserid:2";

                    nIndex = m_listbox2.AddString(strList.c_str());

                    //nIndex = m_listbox2.AddString(iter->second.c_str());
                    iter = m_2DcurSetBuf.erase(iter);
                }
                else
                {
                    iter++;
                }
            }

            //int nIndex = m_listbox2.AddString(szBuf);
            if (nIndex != LB_ERR)
            {
                m_listbox2.SetCurSel(nIndex);
                m_listbox2.SetTopIndex(nIndex);
                m_listbox2.Invalidate();
                m_listbox2.UpdateWindow();
            }
        }
        else if (shootId == 3)
        {
            int nIndex = LB_ERR;
            for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
            {
                if (iter->first == gunId)
                {
                    std::string strList = iter->second.c_str();
                    if (string::npos != strList.find(","))
                    {
                        strList = strList.substr(strList.find(",") + 1);
                    }

                    strList += ",laserid:3";
                    nIndex = m_listbox3.AddString(strList.c_str());

                    //nIndex = m_listbox3.AddString(iter->second.c_str());
                    iter = m_2DcurSetBuf.erase(iter);
                }
                else
                {
                    iter++;
                }
            }

            //int nIndex = m_listbox3.AddString(szBuf);
            if (nIndex != LB_ERR)
            {
                m_listbox3.SetCurSel(nIndex);
                m_listbox3.SetTopIndex(nIndex);
                m_listbox3.Invalidate();
                m_listbox3.UpdateWindow();
            }
        }
        else if (shootId == 4)
        {
            int nIndex = LB_ERR;
            for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
            {
                if (iter->first == gunId)
                {
                    std::string strList = iter->second.c_str();
                    if (string::npos != strList.find(","))
                    {
                        strList = strList.substr(strList.find(",") + 1);
                    }

                    strList += ",laserid:4";
                    nIndex = m_listbox4.AddString(strList.c_str());

                    //nIndex = m_listbox4.AddString(iter->second.c_str());
                    iter = m_2DcurSetBuf.erase(iter);
                }
                else
                {
                    iter++;
                }
            }

            //int nIndex = m_listbox4.AddString(szBuf);
            if (nIndex != LB_ERR)
            {
                m_listbox4.SetCurSel(nIndex);
                m_listbox4.SetTopIndex(nIndex);
                m_listbox4.Invalidate();
                m_listbox4.UpdateWindow();
            }
        }

    }


    //char szBuf[1024] = { 0 };
    //sprintf(szBuf, "TuioClient s_id:%d, xpos:%f, ypos:%f, maccel:%f, shootID:%d, iGunId:%d\n", s_id, xpos, ypos, maccel, iCameraId, iGunId);
    //OutputDebugStringA(szBuf);

    //if (iCameraId == -1 && iGunId != -1)
    //{
    //    m_2DcurSetBuf[iGunId] = szBuf;
    //}

    delete[] szBuf;
    return 0;
}

// CMFCDemoDlg message handlers
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    CMFCDemoDlg *pThis = (CMFCDemoDlg*)lpParam;

    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        return 0;
    }
    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();
        return 0;
    }
    std::cout << "Hello from the new thread!" << std::endl;

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return -1;
    }

    char szbuf[1024] = { 0 };
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int bytesReceived = recvfrom(sockfd, (char*)szbuf, sizeof(szbuf), 0, (sockaddr*)&clientAddr, &clientAddrSize);

    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Error receiving data" << std::endl;
    }

    // 建立连接
    bytesReceived = connect(sockfd, (SOCKADDR*)&clientAddr, clientAddrSize);
    if (bytesReceived < 0)
    {
        std::cout << "connect failed!" << std::endl;
    }

    while (true)
    {
        //int data[3];
        //char szbuf[1024] = { 0 };
        //sockaddr_in clientAddr;
        //int clientAddrSize = sizeof(clientAddr);
        //int bytesReceived = recvfrom(sockfd, (char*)szbuf, sizeof(szbuf), 0, (sockaddr*)&clientAddr, &clientAddrSize);

        //if (bytesReceived == SOCKET_ERROR) {
        //    std::cerr << "Error receiving data" << std::endl;
        //}
        //else {
        //    /*int data_1 = ntohl(data[0]);
        //    int data_2 = ntohl(data[1]);
        //    int data_3 = ntohl(data[2]);*/
        //    std::cout << "Received data: " << szbuf << std::endl;
        //    OutputDebugStringA(szbuf);
        //}

        char *recvBuf = new char[MAXLINE];
        //char recvBuf[MAXLINE];// 存储接收数据
        memset(recvBuf, 0, MAXLINE);// 重置接收空间
        bytesReceived = recv(sockfd, recvBuf, MAXLINE, 0);
        if (bytesReceived < 0)
            std::cout << "recvfrom failed" << std::endl;

        //if (strstr(recvBuf, "/tuio/2Dcur") != NULL)

        //ReceivedPacket p(recvBuf, bytesReceived);

        //pThis->ProcessPacket(recvBuf, bytesReceived);

        char* result = my_strstr(recvBuf, bytesReceived, "/tuio/2Dcur", strlen("/tuio/2Dcur"));
        if(result)
        {
            char* result1 = my_strstr(result, bytesReceived, "set", strlen("set"));
            if (result1)
            {
                PostMessage(pThis->GetSafeHwnd(), WM_ADDSTRING0, (WPARAM)recvBuf, (LPARAM)bytesReceived);
            }
        }
        printf("receive from client: %s \n", recvBuf);
    }


    closesocket(sockfd);
    WSACleanup();

    return 0;
}

//if (p.IsBundle()) ProcessBundle(ReceivedBundle(p), remoteEndpoint);
//else ProcessMessage(ReceivedMessage(p), remoteEndpoint);

void CMFCDemoDlg::ProcessBundle(const ReceivedBundle& b) {

    try {
        for (ReceivedBundle::const_iterator i = b.ElementsBegin(); i != b.ElementsEnd(); ++i) {
            if (i->IsBundle())
                ProcessBundle(ReceivedBundle(*i));
            else
                processOSC(ReceivedMessage(*i));
        }
    }
    catch (MalformedBundleException& e) {
        std::cerr << "malformed OSC bundle: " << e.what() << std::endl;
    }

}

void CMFCDemoDlg::ProcessPacket(const char *data, int size) {
    try {
        ReceivedPacket p(data, size);
        if (p.IsBundle()) ProcessBundle(ReceivedBundle(p));
        else processOSC(ReceivedMessage(p));
    }
    catch (MalformedBundleException& e) {
        std::cerr << "malformed OSC bundle: " << e.what() << std::endl;
    }
}



#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

#define PORT_SERVER 18889
#define BUFFER_SIZE 1024
const char* KEY = "secret";

void xor_encrypt_decrypt(char* data, int len, const char* key, int key_len) {
    for (int i = 0; i < len; ++i) {
        data[i] ^= key[i % key_len];
    }
}

void server_thread(void *para) {
    CMFCDemoDlg* pThis = (CMFCDemoDlg*)para;
    WSADATA wsa;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr = { 0 };
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT_SERVER);
    if (::bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        DWORD err = GetLastError();
        return;
    }
    listen(server_sock, SOMAXCONN);

    fd_set master_set;
    FD_ZERO(&master_set);
    FD_SET(server_sock, &master_set);

    std::cout << "Server started on port " << PORT_SERVER << std::endl;

    while (pThis->m_threadRunning) {
        fd_set read_set = master_set;
        timeval timeout = { 1, 0 };
        int activity = select(0, &read_set, NULL, NULL, &timeout);

        if (activity == SOCKET_ERROR) break;

        for (u_int i = 0; i < read_set.fd_count; ++i) {
            SOCKET sock = read_set.fd_array[i];
            if (sock == server_sock) {
                SOCKET client = accept(server_sock, NULL, NULL);
                FD_SET(client, &master_set);
                std::cout << "New client connected\n";
            }
            else {
                char buffer[BUFFER_SIZE] = { 0 };
                //char *buffer = new char[BUFFER_SIZE];
                memset(buffer, 0, BUFFER_SIZE);
                int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
                if (bytes <= 0) {
                    std::cout << "Client disconnected\n";
                    closesocket(sock);
                    FD_CLR(sock, &master_set);
                }
                else {
                    //xor_encrypt_decrypt(buffer, bytes, KEY, strlen(KEY));
                    std::cout << "Received: " << buffer << std::endl;

                    pThis->m_strBuffer.append(buffer, bytes);
                    //delete[] buffer;

                    int index = pThis->m_strBuffer.find(";");
                    while (-1 != index)
                    {
                        std::string strTmp = pThis->m_strBuffer.substr(0, index);

                        char* bufferT = new char[BUFFER_SIZE];
                        memset(bufferT, 0, BUFFER_SIZE);
                        strcpy(bufferT, strTmp.c_str());

                        PostMessage(pThis->GetSafeHwnd(), WM_ADDSTRING5, (WPARAM)bufferT, (LPARAM)strTmp.size());
                        pThis->m_strBuffer.erase(0, index + 1);
                        index = pThis->m_strBuffer.find(";");
                    }

                    std::string reply = std::string("Server echo: ") + buffer;
                    //xor_encrypt_decrypt(&reply[0], reply.size(), KEY, strlen(KEY));
                    send(sock, reply.c_str(), reply.size(), 0);
                }
            }
        }
    }

    closesocket(server_sock);
    WSACleanup();
}


CMFCDemoDlg::~CMFCDemoDlg()
{
    m_threadRunning = false;
    // 等待接收线程结束
    if (net_client_thread.joinable()) {
        net_client_thread.join();
    }
}

BOOL CMFCDemoDlg::OnInitDialog()
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
    //WSADATA wsaData;
    //WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    HANDLE hThread;
    DWORD dwThreadId;
    //cout << "This is main thread " << endl;
    hThread = CreateThread(NULL, 0, ThreadFunc, this, 0, &dwThreadId);
    //cout << "new thread id == " << dwThreadId << endl;
    if (hThread == NULL) {
        std::cerr << "Failed to create thread!" << std::endl;
        return 1;
    }

    m_listFont.CreatePointFont(120, _T("微软雅黑"));
    m_listbox0.SetFont(&m_listFont);
    m_listBox1.SetFont(&m_listFont);
    m_listbox2.SetFont(&m_listFont);
    m_listbox3.SetFont(&m_listFont);
    m_listbox4.SetFont(&m_listFont);

    m_threadRunning = true;
    net_client_thread = std::thread(server_thread, this);

    SetTimer(1, 10*1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDemoDlg::OnPaint()
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
HCURSOR CMFCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDemoDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    return;

    //CDialogEx::OnOK();
}


void CMFCDemoDlg::OnLbnSelchangeList2()
{
    // TODO: Add your control notification handler code here
}


void CMFCDemoDlg::OnLbnSelchangeList3()
{
    // TODO: Add your control notification handler code here
}

void CMFCDemoDlg::processOSC(const ReceivedMessage& msg) {
    try {
        ReceivedMessageArgumentStream args = msg.ArgumentStream();
        //ReceivedMessage::const_iterator arg = msg.ArgumentsBegin();

        if (strcmp(msg.AddressPattern(), "/tuio/2Dobj") == 0) {

            const char* cmd;
            args >> cmd;

            if (strcmp(cmd, "source") == 0) {
                const char* src;
                args >> src;

                //source_name = strtok((char*)src, "@");
                //char *addr = strtok(NULL, "@");

                //if (addr != NULL) source_addr = addr;
                //else source_addr = (char*)"localhost";

                //// check if we know that source
                //std::string source_str(src);
                //std::map<std::string, int>::iterator iter = sourceList.find(source_str);

                //// add a new source
                //if (iter == sourceList.end()) {
                //    source_id = sourceList.size();
                //    sourceList[source_str] = source_id;
                //}
                //else {
                //    // use the found source_id
                //    source_id = sourceList[source_str];
                //}

            }
            else if (strcmp(cmd, "set") == 0) {
                int32 s_id, c_id;
                float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
                args >> s_id >> c_id >> xpos >> ypos >> angle >> xspeed >> yspeed >> rspeed >> maccel >> raccel;

                /*lockObjectList();
                std::list<TuioObject*>::iterator tobj;
                for (tobj = objectList.begin(); tobj != objectList.end(); tobj++)
                    if ((*tobj)->getSessionID() == (long)s_id) break;

                if (tobj == objectList.end()) {

                    TuioObject *addObject = new TuioObject((long)s_id, (int)c_id, xpos, ypos, angle);
                    frameObjects.push_back(addObject);

                }
                else if (((*tobj)->getX() != xpos) || ((*tobj)->getY() != ypos) || ((*tobj)->getAngle() != angle) || ((*tobj)->getXSpeed() != xspeed) || ((*tobj)->getYSpeed() != yspeed) || ((*tobj)->getRotationSpeed() != rspeed) || ((*tobj)->getMotionAccel() != maccel) || ((*tobj)->getRotationAccel() != raccel)) {

                    TuioObject *updateObject = new TuioObject((long)s_id, (*tobj)->getSymbolID(), xpos, ypos, angle);
                    updateObject->update(xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel);
                    frameObjects.push_back(updateObject);

                }
                unlockObjectList();*/

            }
            else if (strcmp(cmd, "alive") == 0) {

                int32 s_id;
                //aliveObjectList.clear();
                while (!args.Eos()) {
                    args >> s_id;
                    //aliveObjectList.push_back((long)s_id);
                }

            }
            else if (strcmp(cmd, "fseq") == 0) {

                int32 fseq;
                args >> fseq;

                printf("processOSC fseq:%d\n", fseq);
                //bool lateFrame = false;
                //if (fseq>0) {
                //    if (fseq>currentFrame) currentTime = TuioTime::getSessionTime();
                //    if ((fseq >= currentFrame) || ((currentFrame - fseq)>100)) currentFrame = fseq;
                //    else lateFrame = true;
                //}
                //else if ((TuioTime::getSessionTime().getTotalMilliseconds() - currentTime.getTotalMilliseconds())>100) {
                //    currentTime = TuioTime::getSessionTime();
                //}

                //if (!lateFrame) {

                //    lockObjectList();
                //    //find the removed objects first
                //    for (std::list<TuioObject*>::iterator tobj = objectList.begin(); tobj != objectList.end(); tobj++) {
                //        if ((*tobj)->getTuioSourceID() == source_id) {
                //            std::list<long>::iterator iter = find(aliveObjectList.begin(), aliveObjectList.end(), (*tobj)->getSessionID());
                //            if (iter == aliveObjectList.end()) {
                //                (*tobj)->remove(currentTime);
                //                frameObjects.push_back(*tobj);
                //            }
                //        }
                //    }
                //    unlockObjectList();

                //    for (std::list<TuioObject*>::iterator iter = frameObjects.begin(); iter != frameObjects.end(); iter++) {
                //        TuioObject *tobj = (*iter);

                //        TuioObject *frameObject = NULL;
                //        switch (tobj->getTuioState()) {
                //        case TUIO_REMOVED:

                //            frameObject = tobj;
                //            frameObject->remove(currentTime);

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->removeTuioObject(frameObject);

                //            lockObjectList();
                //            for (std::list<TuioObject*>::iterator delobj = objectList.begin(); delobj != objectList.end(); delobj++) {
                //                if ((*delobj)->getSessionID() == frameObject->getSessionID()) {
                //                    objectList.erase(delobj);
                //                    break;
                //                }
                //            }
                //            unlockObjectList();
                //            break;
                //        case TUIO_ADDED:

                //            lockObjectList();
                //            frameObject = new TuioObject(currentTime, tobj->getSessionID(), tobj->getSymbolID(), tobj->getX(), tobj->getY(), tobj->getAngle());
                //            if (source_name) frameObject->setTuioSource(source_id, source_name, source_addr);
                //            objectList.push_back(frameObject);
                //            unlockObjectList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->addTuioObject(frameObject);

                //            break;
                //        default:

                //            lockObjectList();
                //            std::list<TuioObject*>::iterator iter;
                //            for (iter = objectList.begin(); iter != objectList.end(); iter++) {
                //                if (((*iter)->getTuioSourceID() == source_id) && ((*iter)->getSessionID() == tobj->getSessionID())) {
                //                    frameObject = (*iter);
                //                    break;
                //                }
                //            }

                //            if (iter == objectList.end()) {
                //                unlockObjectList();
                //                break;
                //            }

                //            if ((tobj->getX() != frameObject->getX() && tobj->getXSpeed() == 0) || (tobj->getY() != frameObject->getY() && tobj->getYSpeed() == 0))
                //                frameObject->update(currentTime, tobj->getX(), tobj->getY(), tobj->getAngle());
                //            else
                //                frameObject->update(currentTime, tobj->getX(), tobj->getY(), tobj->getAngle(), tobj->getXSpeed(), tobj->getYSpeed(), tobj->getRotationSpeed(), tobj->getMotionAccel(), tobj->getRotationAccel());

                //            unlockObjectList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->updateTuioObject(frameObject);
                //        }
                //        delete tobj;
                //    }

                //    for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //        (*listener)->refresh(currentTime);

                //}
                //else {
                //    for (std::list<TuioObject*>::iterator iter = frameObjects.begin(); iter != frameObjects.end(); iter++) {
                //        TuioObject *tobj = (*iter);
                //        delete tobj;
                //    }
                //}

                //frameObjects.clear();
            }
        }
        else if (strcmp(msg.AddressPattern(), "/tuio/2Dcur") == 0) {
            const char* cmd;
            args >> cmd;

            if (strcmp(cmd, "source") == 0) {
                const char* src;
                args >> src;

                //source_name = strtok((char*)src, "@");
                //char *addr = strtok(NULL, "@");

                //if (addr != NULL) source_addr = addr;
                //else source_addr = (char*)"localhost";

                //// check if we know that source
                //std::string source_str(src);
                //std::map<std::string, int>::iterator iter = sourceList.find(source_str);

                //// add a new source
                //if (iter == sourceList.end()) {
                //    source_id = sourceList.size();
                //    sourceList[source_str] = source_id;
                //    maxCursorID[source_id] = -1;
                //}
                //else {
                //    // use the found source_id
                //    source_id = sourceList[source_str];
                //}

            }
            else if (strcmp(cmd, "set") == 0) {

                int32 s_id;
                float xpos, ypos, xspeed, yspeed, maccel;
                int32 iCameraId = -1;
                int32 iGunId = -1;
                args >> s_id >> xpos >> ypos >> xspeed >> yspeed >> maccel >> iCameraId >> iGunId;

                //char szBuf[1024] = { 0 };
                //sprintf(szBuf, "TuioClient s_id:%d, xpos:%f, ypos:%f, maccel:%f, iGunId:%d, shootID:%d\n", s_id, xpos, ypos, maccel, iGunId, iCameraId);
                //OutputDebugStringA(szBuf);

				char szBuf[1024] = { 0 };
				sprintf(szBuf, "TuioClient s_id:%d, xpos:%f, ypos:%f, maccel:%f, iCameraId:%d, iGunId:%d\n", s_id, xpos, ypos, maccel, iCameraId, iGunId);
				OutputDebugStringA(szBuf);

                //if (iCameraId == -1 && iGunId != -1)
                //{
                //    m_2DcurSetBuf[iGunId] = szBuf;
                //}

                if (iCameraId == 0)
                {
                    int nIndex = LB_ERR;
                    nIndex = m_listbox0.AddString(szBuf);
                    /*for (auto iter= m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
                    {*/
                        //if (iter->first == iGunId)
                        //{
                            //std::string strList = iter->second.c_str();
                            //std::string strTmp;
                            //if (string::npos != strList.rfind(","))
                            //{
                            //    int index = strList.rfind(",");
                            //    strTmp = strList;
                            //    strList = strList.substr(0, index);
                            //    strTmp = strTmp.substr(index + 1);
                            //}
                            //if (string::npos != strList.rfind(","))
                            //{
                            //    strList = strList.substr(0, strList.rfind(","));
                            //    //strTmp = strList.substr(strList.rfind(",") + 1);
                            //}

                            //strList += ",iCameraId:0";
                            //strList += ",";
                            //strList += strTmp;
                            ////strList += ",laserid:0";

                            //nIndex = m_listbox0.AddString(strList.c_str());
                            //iter = m_2DcurSetBuf.erase(iter);
                        //}
                    //    else
                    //    {
                    //        iter++;
                    //    }
                    //}

                    //nIndex = m_listbox0.AddString(szBuf);
                    if (nIndex != LB_ERR)
                    {
                        m_listbox0.SetCurSel(nIndex);
                        m_listbox0.SetTopIndex(nIndex);
                        m_listbox0.Invalidate();
                        m_listbox0.UpdateWindow();
                    }
                }
                else if(iCameraId == 1)
                {
                    int nIndex = LB_ERR;
                    nIndex = m_listBox1.AddString(szBuf);
                    //for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
                    //{
                    //    if (iter->first == iGunId)
                    //    {
                    //        std::string strList = iter->second.c_str();
                    //        std::string strTmp;
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            int index = strList.rfind(",");
                    //            strTmp = strList;
                    //            strList = strList.substr(0, index);
                    //            strTmp = strTmp.substr(index + 1);
                    //        }
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            strList = strList.substr(0, strList.rfind(","));
                    //            //strTmp = strList.substr(strList.rfind(",") + 1);
                    //        }

                    //        strList += ",iCameraId:1";
                    //        strList += ",";
                    //        strList += strTmp;
                    //        //strList += ",laserid:1";

                    //        nIndex = m_listBox1.AddString(strList.c_str());
                    //        iter = m_2DcurSetBuf.erase(iter);
                    //    }
                    //    else
                    //    {
                    //        iter++;
                    //    }
                    //}

                    //int nIndex = m_listBox1.AddString(szBuf);
                    if (nIndex != LB_ERR)
                    {
                        m_listBox1.SetCurSel(nIndex);
                        m_listBox1.SetTopIndex(nIndex);
                        m_listBox1.Invalidate();
                        m_listBox1.UpdateWindow();
                    }
                }
                else if (iCameraId == 2)
                {
                    int nIndex = LB_ERR;
                    nIndex = m_listbox2.AddString(szBuf);
                    //for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
                    //{
                    //    if (iter->first == iGunId)
                    //    {
                    //        std::string strList = iter->second.c_str();
                    //        std::string strTmp;
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            int index = strList.rfind(",");
                    //            strTmp = strList;
                    //            strList = strList.substr(0, index);
                    //            strTmp = strTmp.substr(index + 1);
                    //        }
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            strList = strList.substr(0, strList.rfind(","));
                    //            //strTmp = strList.substr(strList.rfind(",") + 1);
                    //        }

                    //        strList += ",iCameraId:2";
                    //        strList += ",";
                    //        strList += strTmp;

                    //        nIndex = m_listbox2.AddString(strList.c_str());
                    //        iter = m_2DcurSetBuf.erase(iter);
                    //    }
                    //    else
                    //    {
                    //        iter++;
                    //    }
                    //}

                    //int nIndex = m_listbox2.AddString(szBuf);
                    if (nIndex != LB_ERR)
                    {
                        m_listbox2.SetCurSel(nIndex);
                        m_listbox2.SetTopIndex(nIndex);
                        m_listbox2.Invalidate();
                        m_listbox2.UpdateWindow();
                    }
                }
                else if (iCameraId == 3)
                {
                    int nIndex = LB_ERR;
                    nIndex = m_listbox3.AddString(szBuf);
                    //for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
                    //{
                    //    if (iter->first == iGunId)
                    //    {
                    //        std::string strList = iter->second.c_str();
                    //        std::string strTmp;
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            int index = strList.rfind(",");
                    //            strTmp = strList;
                    //            strList = strList.substr(0, index);
                    //            strTmp = strTmp.substr(index + 1);
                    //        }
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            strList = strList.substr(0, strList.rfind(","));
                    //            //strTmp = strList.substr(strList.rfind(",") + 1);
                    //        }

                    //        strList += ",iCameraId:3";
                    //        strList += ",";
                    //        strList += strTmp;

                    //        nIndex = m_listbox3.AddString(strList.c_str());
                    //        iter = m_2DcurSetBuf.erase(iter);
                    //    }
                    //    else
                    //    {
                    //        iter++;
                    //    }
                    //}

                    //int nIndex = m_listbox3.AddString(szBuf);
                    if (nIndex != LB_ERR)
                    {
                        m_listbox3.SetCurSel(nIndex);
                        m_listbox3.SetTopIndex(nIndex);
                        m_listbox3.Invalidate();
                        m_listbox3.UpdateWindow();
                    }
                }
                else if (iCameraId == 4)
                {
                    int nIndex = LB_ERR;
                    nIndex = m_listbox4.AddString(szBuf);
                    //for (auto iter = m_2DcurSetBuf.begin(); iter != m_2DcurSetBuf.end();)
                    //{
                    //    if (iter->first == iGunId)
                    //    {
                    //        std::string strList = iter->second.c_str();
                    //        std::string strTmp;
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            int index = strList.rfind(",");
                    //            strTmp = strList;
                    //            strList = strList.substr(0, index);
                    //            strTmp = strTmp.substr(index + 1);
                    //        }
                    //        if (string::npos != strList.rfind(","))
                    //        {
                    //            strList = strList.substr(0, strList.rfind(","));
                    //            //strTmp = strList.substr(strList.rfind(",") + 1);
                    //        }

                    //        strList += ",iCameraId:4";
                    //        strList += ",";
                    //        strList += strTmp;

                    //        nIndex = m_listbox4.AddString(strList.c_str());
                    //        iter = m_2DcurSetBuf.erase(iter);
                    //    }
                    //    else
                    //    {
                    //        iter++;
                    //    }
                    //}

                    //int nIndex = m_listbox4.AddString(szBuf);
                    if (nIndex != LB_ERR)
                    {
                        m_listbox4.SetCurSel(nIndex);
                        m_listbox4.SetTopIndex(nIndex);
                        m_listbox4.Invalidate();
                        m_listbox4.UpdateWindow();
                    }
                }

                /*lockCursorList();
                std::list<TuioCursor*>::iterator tcur;
                for (tcur = cursorList.begin(); tcur != cursorList.end(); tcur++)
                    if (((*tcur)->getSessionID() == (long)s_id) && ((*tcur)->getTuioSourceID() == source_id)) break;

                if (tcur == cursorList.end()) {

                    TuioCursor *addCursor = new TuioCursor((long)s_id, -1, xpos, ypos, iCameraId);
                    frameCursors.push_back(addCursor);

                }
                else if (((*tcur)->getX() != xpos) || ((*tcur)->getY() != ypos) || ((*tcur)->getXSpeed() != xspeed) || ((*tcur)->getYSpeed() != yspeed) || ((*tcur)->getMotionAccel() != maccel)) {

                    TuioCursor *updateCursor = new TuioCursor((long)s_id, (*tcur)->getCursorID(), xpos, ypos, iCameraId);
                    updateCursor->update(xpos, ypos, xspeed, yspeed, maccel);
                    frameCursors.push_back(updateCursor);

                }
                unlockCursorList();*/

            }
            else if (strcmp(cmd, "alive") == 0) {

                int32 s_id;
                //aliveCursorList.clear();
                while (!args.Eos()) {
                    args >> s_id;
                    //aliveCursorList.push_back((long)s_id);
                }

            }
            else if (strcmp(cmd, "fseq") == 0) {
                int32 fseq;
                args >> fseq;

                printf(" processOSC fseq:%d", fseq);
                //bool lateFrame = false;
                //if (fseq>0) {
                //    if (fseq>currentFrame) currentTime = TuioTime::getSessionTime();
                //    if ((fseq >= currentFrame) || ((currentFrame - fseq)>100)) currentFrame = fseq;
                //    else lateFrame = true;
                //}
                //else if ((TuioTime::getSessionTime().getTotalMilliseconds() - currentTime.getTotalMilliseconds())>100) {
                //    currentTime = TuioTime::getSessionTime();
                //}

                //if (!lateFrame) {

                //    lockCursorList();
                //    // find the removed cursors first
                //    for (std::list<TuioCursor*>::iterator tcur = cursorList.begin(); tcur != cursorList.end(); tcur++) {
                //        if ((*tcur)->getTuioSourceID() == source_id) {
                //            std::list<long>::iterator iter = find(aliveCursorList.begin(), aliveCursorList.end(), (*tcur)->getSessionID());

                //            if (iter == aliveCursorList.end()) {
                //                (*tcur)->remove(currentTime);
                //                frameCursors.push_back(*tcur);
                //            }
                //        }
                //    }
                //    unlockCursorList();

                //    for (std::list<TuioCursor*>::iterator iter = frameCursors.begin(); iter != frameCursors.end(); iter++) {
                //        TuioCursor *tcur = (*iter);

                //        int c_id = 0;
                //        int free_size = 0;
                //        TuioCursor *frameCursor = NULL;
                //        switch (tcur->getTuioState()) {
                //        case TUIO_REMOVED:

                //            frameCursor = tcur;
                //            frameCursor->remove(currentTime);

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->removeTuioCursor(frameCursor);

                //            lockCursorList();
                //            for (std::list<TuioCursor*>::iterator delcur = cursorList.begin(); delcur != cursorList.end(); delcur++) {
                //                if (((*delcur)->getTuioSourceID() == source_id) && ((*delcur)->getSessionID() == frameCursor->getSessionID())) {
                //                    cursorList.erase(delcur);
                //                    break;
                //                }
                //            }

                //            if (frameCursor->getCursorID() == maxCursorID[source_id]) {
                //                maxCursorID[source_id] = -1;
                //                delete frameCursor;

                //                if (cursorList.size()>0) {
                //                    std::list<TuioCursor*>::iterator clist;
                //                    for (clist = cursorList.begin(); clist != cursorList.end(); clist++) {
                //                        if ((*clist)->getTuioSourceID() == source_id) {
                //                            c_id = (*clist)->getCursorID();
                //                            if (c_id>maxCursorID[source_id]) maxCursorID[source_id] = c_id;
                //                        }
                //                    }

                //                    freeCursorBuffer.clear();
                //                    for (std::list<TuioCursor*>::iterator flist = freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
                //                        TuioCursor *freeCursor = (*flist);
                //                        if (freeCursor->getTuioSourceID() == source_id) {
                //                            if (freeCursor->getCursorID()>maxCursorID[source_id]) delete freeCursor;
                //                            else freeCursorBuffer.push_back(freeCursor);
                //                        }
                //                        else freeCursorBuffer.push_back(freeCursor);
                //                    }
                //                    freeCursorList = freeCursorBuffer;

                //                }
                //                else {
                //                    freeCursorBuffer.clear();
                //                    for (std::list<TuioCursor*>::iterator flist = freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
                //                        TuioCursor *freeCursor = (*flist);
                //                        if (freeCursor->getTuioSourceID() == source_id) delete freeCursor;
                //                        else freeCursorBuffer.push_back(freeCursor);
                //                    }
                //                    freeCursorList = freeCursorBuffer;

                //                }
                //            }
                //            else if (frameCursor->getCursorID()<maxCursorID[source_id]) {
                //                freeCursorList.push_back(frameCursor);
                //            }

                //            unlockCursorList();
                //            break;
                //        case TUIO_ADDED:

                //            lockCursorList();
                //            for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter != cursorList.end(); iter++)
                //                if ((*iter)->getTuioSourceID() == source_id) c_id++;

                //            for (std::list<TuioCursor*>::iterator iter = freeCursorList.begin(); iter != freeCursorList.end(); iter++)
                //                if ((*iter)->getTuioSourceID() == source_id) free_size++;

                //            if ((free_size <= maxCursorID[source_id]) && (free_size>0)) {
                //                std::list<TuioCursor*>::iterator closestCursor = freeCursorList.begin();

                //                for (std::list<TuioCursor*>::iterator iter = freeCursorList.begin(); iter != freeCursorList.end(); iter++) {
                //                    if (((*iter)->getTuioSourceID() == source_id) && ((*iter)->getDistance(tcur)<(*closestCursor)->getDistance(tcur))) closestCursor = iter;
                //                }

                //                if (closestCursor != freeCursorList.end()) {
                //                    TuioCursor *freeCursor = (*closestCursor);
                //                    c_id = freeCursor->getCursorID();
                //                    freeCursorList.erase(closestCursor);
                //                    delete freeCursor;
                //                }
                //            }
                //            else maxCursorID[source_id] = c_id;

                //            frameCursor = new TuioCursor(currentTime, tcur->getSessionID(), c_id, tcur->getX(), tcur->getY(), tcur->getCameraId());
                //            if (source_name) frameCursor->setTuioSource(source_id, source_name, source_addr);
                //            cursorList.push_back(frameCursor);

                //            delete tcur;
                //            unlockCursorList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->addTuioCursor(frameCursor);

                //            break;
                //        default:

                //            lockCursorList();
                //            std::list<TuioCursor*>::iterator iter;
                //            for (iter = cursorList.begin(); iter != cursorList.end(); iter++) {
                //                if (((*iter)->getTuioSourceID() == source_id) && ((*iter)->getSessionID() == tcur->getSessionID())) {
                //                    frameCursor = (*iter);
                //                    break;
                //                }
                //            }

                //            if (iter == cursorList.end()) {
                //                unlockCursorList();
                //                break;
                //            }

                //            if ((tcur->getX() != frameCursor->getX() && tcur->getXSpeed() == 0) || (tcur->getY() != frameCursor->getY() && tcur->getYSpeed() == 0))
                //                frameCursor->update(currentTime, tcur->getX(), tcur->getY());
                //            else
                //                frameCursor->update(currentTime, tcur->getX(), tcur->getY(), tcur->getXSpeed(), tcur->getYSpeed(), tcur->getMotionAccel());

                //            delete tcur;
                //            unlockCursorList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->updateTuioCursor(frameCursor);

                //        }
                //    }

                //    for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //        (*listener)->refresh(currentTime);

                //}
                //else {
                //    for (std::list<TuioCursor*>::iterator iter = frameCursors.begin(); iter != frameCursors.end(); iter++) {
                //        TuioCursor *tcur = (*iter);
                //        delete tcur;
                //    }
                //}

                //frameCursors.clear();
            }
        }
        else if (strcmp(msg.AddressPattern(), "/tuio/2Dblb") == 0) {
            const char* cmd;
            args >> cmd;

            if (strcmp(cmd, "source") == 0) {
                const char* src;
                args >> src;

                //source_name = strtok((char*)src, "@");
                //char *addr = strtok(NULL, "@");

                //if (addr != NULL) source_addr = addr;
                //else source_addr = (char*)"localhost";

                //// check if we know that source
                //std::string source_str(src);
                //std::map<std::string, int>::iterator iter = sourceList.find(source_str);

                //// add a new source
                //if (iter == sourceList.end()) {
                //    source_id = sourceList.size();
                //    sourceList[source_str] = source_id;
                //    maxBlobID[source_id] = -1;
                //}
                //else {
                //    // use the found source_id
                //    source_id = sourceList[source_str];
                //}

            }
            else if (strcmp(cmd, "set") == 0) {

                int32 s_id;
                float xpos, ypos, angle, width, height, area, xspeed, yspeed, rspeed, maccel, raccel;
                args >> s_id >> xpos >> ypos >> angle >> width >> height >> area >> xspeed >> yspeed >> rspeed >> maccel >> raccel;

                /*lockBlobList();
                std::list<TuioBlob*>::iterator tblb;
                for (tblb = blobList.begin(); tblb != blobList.end(); tblb++)
                    if ((*tblb)->getSessionID() == (long)s_id) break;

                if (tblb == blobList.end()) {

                    TuioBlob *addBlob = new TuioBlob((long)s_id, -1, xpos, ypos, angle, width, height, area);
                    frameBlobs.push_back(addBlob);

                }
                else if (((*tblb)->getX() != xpos) || ((*tblb)->getY() != ypos) || ((*tblb)->getAngle() != angle) || ((*tblb)->getWidth() != width) || ((*tblb)->getHeight() != height) || ((*tblb)->getArea() != area) || ((*tblb)->getXSpeed() != xspeed) || ((*tblb)->getYSpeed() != yspeed) || ((*tblb)->getMotionAccel() != maccel)) {

                    TuioBlob *updateBlob = new TuioBlob((long)s_id, (*tblb)->getBlobID(), xpos, ypos, angle, width, height, area);
                    updateBlob->update(xpos, ypos, angle, width, height, area, xspeed, yspeed, rspeed, maccel, raccel);
                    frameBlobs.push_back(updateBlob);
                }
                unlockBlobList();*/

            }
            else if (strcmp(cmd, "alive") == 0) {

                int32 s_id;
                //aliveBlobList.clear();
                while (!args.Eos()) {
                    args >> s_id;
                    //aliveBlobList.push_back((long)s_id);
                }

            }
            else if (strcmp(cmd, "fseq") == 0) {

                int32 fseq;
                args >> fseq;

                printf(" processOSC fseq:%d\n", fseq);
                //bool lateFrame = false;
                //if (fseq>0) {
                //    if (fseq>currentFrame) currentTime = TuioTime::getSessionTime();
                //    if ((fseq >= currentFrame) || ((currentFrame - fseq)>100)) currentFrame = fseq;
                //    else lateFrame = true;
                //}
                //else if ((TuioTime::getSessionTime().getTotalMilliseconds() - currentTime.getTotalMilliseconds())>100) {
                //    currentTime = TuioTime::getSessionTime();
                //}

                //if (!lateFrame) {

                //    lockBlobList();
                //    // find the removed blobs first
                //    for (std::list<TuioBlob*>::iterator tblb = blobList.begin(); tblb != blobList.end(); tblb++) {
                //        if ((*tblb)->getTuioSourceID() == source_id) {
                //            std::list<long>::iterator iter = find(aliveBlobList.begin(), aliveBlobList.end(), (*tblb)->getSessionID());

                //            if (iter == aliveBlobList.end()) {
                //                (*tblb)->remove(currentTime);
                //                frameBlobs.push_back(*tblb);
                //            }
                //        }
                //    }
                //    unlockBlobList();

                //    for (std::list<TuioBlob*>::iterator iter = frameBlobs.begin(); iter != frameBlobs.end(); iter++) {
                //        TuioBlob *tblb = (*iter);

                //        int b_id = 0;
                //        int free_size = 0;
                //        TuioBlob *frameBlob = NULL;
                //        switch (tblb->getTuioState()) {
                //        case TUIO_REMOVED:
                //            frameBlob = tblb;
                //            frameBlob->remove(currentTime);

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->removeTuioBlob(frameBlob);

                //            lockBlobList();
                //            for (std::list<TuioBlob*>::iterator delblb = blobList.begin(); delblb != blobList.end(); delblb++) {
                //                if (((*delblb)->getTuioSourceID() == source_id) && ((*delblb)->getSessionID() == frameBlob->getSessionID())) {
                //                    blobList.erase(delblb);
                //                    break;
                //                }
                //            }

                //            if (frameBlob->getBlobID() == maxBlobID[source_id]) {
                //                maxBlobID[source_id] = -1;
                //                delete frameBlob;

                //                if (blobList.size()>0) {
                //                    std::list<TuioBlob*>::iterator clist;
                //                    for (clist = blobList.begin(); clist != blobList.end(); clist++) {
                //                        if ((*clist)->getTuioSourceID() == source_id) {
                //                            b_id = (*clist)->getBlobID();
                //                            if (b_id>maxBlobID[source_id]) maxBlobID[source_id] = b_id;
                //                        }
                //                    }

                //                    freeBlobBuffer.clear();
                //                    for (std::list<TuioBlob*>::iterator flist = freeBlobList.begin(); flist != freeBlobList.end(); flist++) {
                //                        TuioBlob *freeBlob = (*flist);
                //                        if (freeBlob->getTuioSourceID() == source_id) {
                //                            if (freeBlob->getBlobID()>maxBlobID[source_id]) delete freeBlob;
                //                            else freeBlobBuffer.push_back(freeBlob);
                //                        }
                //                        else freeBlobBuffer.push_back(freeBlob);
                //                    }
                //                    freeBlobList = freeBlobBuffer;

                //                }
                //                else {
                //                    freeBlobBuffer.clear();
                //                    for (std::list<TuioBlob*>::iterator flist = freeBlobList.begin(); flist != freeBlobList.end(); flist++) {
                //                        TuioBlob *freeBlob = (*flist);
                //                        if (freeBlob->getTuioSourceID() == source_id) delete freeBlob;
                //                        else freeBlobBuffer.push_back(freeBlob);
                //                    }
                //                    freeBlobList = freeBlobBuffer;

                //                }
                //            }
                //            else if (frameBlob->getBlobID()<maxBlobID[source_id]) {
                //                freeBlobList.push_back(frameBlob);
                //            }

                //            unlockBlobList();
                //            break;
                //        case TUIO_ADDED:

                //            lockBlobList();
                //            for (std::list<TuioBlob*>::iterator iter = blobList.begin(); iter != blobList.end(); iter++)
                //                if ((*iter)->getTuioSourceID() == source_id) b_id++;

                //            for (std::list<TuioBlob*>::iterator iter = freeBlobList.begin(); iter != freeBlobList.end(); iter++)
                //                if ((*iter)->getTuioSourceID() == source_id) free_size++;

                //            if ((free_size <= maxBlobID[source_id]) && (free_size>0)) {
                //                std::list<TuioBlob*>::iterator closestBlob = freeBlobList.begin();

                //                for (std::list<TuioBlob*>::iterator iter = freeBlobList.begin(); iter != freeBlobList.end(); iter++) {
                //                    if (((*iter)->getTuioSourceID() == source_id) && ((*iter)->getDistance(tblb)<(*closestBlob)->getDistance(tblb))) closestBlob = iter;
                //                }

                //                if (closestBlob != freeBlobList.end()) {
                //                    TuioBlob *freeBlob = (*closestBlob);
                //                    b_id = freeBlob->getBlobID();
                //                    freeBlobList.erase(closestBlob);
                //                    delete freeBlob;
                //                }
                //            }
                //            else maxBlobID[source_id] = b_id;

                //            frameBlob = new TuioBlob(currentTime, tblb->getSessionID(), b_id, tblb->getX(), tblb->getY(), tblb->getAngle(), tblb->getWidth(), tblb->getHeight(), tblb->getArea());
                //            if (source_name) frameBlob->setTuioSource(source_id, source_name, source_addr);
                //            blobList.push_back(frameBlob);

                //            delete tblb;
                //            unlockBlobList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->addTuioBlob(frameBlob);

                //            break;
                //        default:

                //            lockBlobList();
                //            std::list<TuioBlob*>::iterator iter;
                //            for (iter = blobList.begin(); iter != blobList.end(); iter++) {
                //                if (((*iter)->getTuioSourceID() == source_id) && ((*iter)->getSessionID() == tblb->getSessionID())) {
                //                    frameBlob = (*iter);
                //                    break;
                //                }
                //            }

                //            if (iter == blobList.end()) {
                //                unlockBlobList();
                //                break;
                //            }

                //            if ((tblb->getX() != frameBlob->getX() && tblb->getXSpeed() == 0) || (tblb->getY() != frameBlob->getY() && tblb->getYSpeed() == 0) || (tblb->getAngle() != frameBlob->getAngle() && tblb->getRotationSpeed() == 0))
                //                frameBlob->update(currentTime, tblb->getX(), tblb->getY(), tblb->getAngle(), tblb->getWidth(), tblb->getHeight(), tblb->getArea());
                //            else
                //                frameBlob->update(currentTime, tblb->getX(), tblb->getY(), tblb->getAngle(), tblb->getWidth(), tblb->getHeight(), tblb->getArea(), tblb->getXSpeed(), tblb->getYSpeed(), tblb->getRotationSpeed(), tblb->getMotionAccel(), tblb->getRotationAccel());

                //            delete tblb;
                //            unlockBlobList();

                //            for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //                (*listener)->updateTuioBlob(frameBlob);
                //        }
                //    }

                //    for (std::list<TuioListener*>::iterator listener = listenerList.begin(); listener != listenerList.end(); listener++)
                //        (*listener)->refresh(currentTime);

                //}
                //else {
                //    for (std::list<TuioBlob*>::iterator iter = frameBlobs.begin(); iter != frameBlobs.end(); iter++) {
                //        TuioBlob *tblb = (*iter);
                //        delete tblb;
                //    }
                //}

                //frameBlobs.clear();
            }
        }
    }
    catch (Exception& e) {
        std::cerr << "error parsing TUIO message: " << msg.AddressPattern() << " - " << e.what() << std::endl;
    }
}

void CMFCDemoDlg::OnLbnSelchangeList5()
{
    // TODO: Add your control notification handler code here
}


void CMFCDemoDlg::OnLbnSelchangeList6()
{
    // TODO: Add your control notification handler code here
}


void CMFCDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (0 == m_listCount0)
    {
        m_listCount0 = m_listbox0.GetCount();
    }
    else
    {
        int listcount = m_listbox0.GetCount() - m_listCount0;
        char szTmp[1024] = { 0 };
        sprintf(szTmp, " 最近10秒之内增加的条数:%d\n", listcount);
        GetDlgItem(IDC_STATIC_1)->SetWindowText(szTmp);
        m_listCount0 = m_listbox0.GetCount();
    }

    if (0 == m_listCount1)
    {
        m_listCount1 = m_listBox1.GetCount();
    }
    else
    {
        int listcount = m_listBox1.GetCount() - m_listCount1;
        char szTmp[1024] = { 0 };
        sprintf(szTmp, " 最近10秒之内增加的条数:%d\n", listcount);
        GetDlgItem(IDC_STATIC_2)->SetWindowText(szTmp);
        m_listCount1 = m_listBox1.GetCount();
    }

    if (0 == m_listCount2)
    {
        m_listCount2 = m_listbox2.GetCount();
    }
    else
    {
        int listcount = m_listbox2.GetCount() - m_listCount2;
        char szTmp[1024] = { 0 };
        sprintf(szTmp, " 最近10秒之内增加的条数:%d\n", listcount);
        GetDlgItem(IDC_STATIC_3)->SetWindowText(szTmp);
        m_listCount2 = m_listbox2.GetCount();
    }

    if (0 == m_listCount3)
    {
        m_listCount3 = m_listbox3.GetCount();
    }
    else
    {
        int listcount = m_listbox3.GetCount() - m_listCount3;
        char szTmp[1024] = { 0 };
        sprintf(szTmp, " 最近10秒之内增加的条数:%d\n", listcount);
        GetDlgItem(IDC_STATIC_4)->SetWindowText(szTmp);
        m_listCount3 = m_listbox3.GetCount();
    }

    if (0 == m_listCount4)
    {
        m_listCount4 = m_listbox4.GetCount();
    }
    else
    {
        int listcount = m_listbox4.GetCount() - m_listCount4;
        char szTmp[1024] = { 0 };
        sprintf(szTmp, " 最近10秒之内增加的条数:%d\n", listcount);
        GetDlgItem(IDC_STATIC_5)->SetWindowText(szTmp);
        m_listCount4 = m_listbox4.GetCount();
    }

    CDialogEx::OnTimer(nIDEvent);
}
