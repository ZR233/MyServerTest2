
// ClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PH_LIST, m_ph_list);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_TEXT, &CClientDlg::OnEnChangeText)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDR, &CClientDlg::OnIpnFieldchangedIpaddr)
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnBnClickedConnect)
	ON_LBN_SELCHANGE(IDC_LIST1, &CClientDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_DISCONNECT, &CClientDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_ADD, &CClientDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_MIN, &CClientDlg::OnBnClickedMin)
	ON_BN_CLICKED(IDC_SEND, &CClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_TEXT)->EnableWindow(false);
	GetDlgItem(IDC_SENDTEXT)->EnableWindow(false);
	GetDlgItem(IDC_SEND)->EnableWindow(false);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnEnChangeText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CClientDlg::OnIpnFieldchangedIpaddr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CClientDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码

	CString ip_addr, port, username, password;
	GetDlgItem(IDC_IPADDR)->GetWindowText(ip_addr);
	GetDlgItem(IDC_PORT)->GetWindowText(port);
	GetDlgItem(IDC_USER)->GetWindowText(username);
	GetDlgItem(IDC_PASS)->GetWindowText(password);
	if (ip_addr ==""|| port == "")
	{
		CString temp("服务器地址或端口不能为空");
		MessageBox(temp);
	}
	else
	{
		std::string ip_addr_str(ip_addr.GetBuffer(0)),user(username.GetBuffer(0)),pass(password.GetBuffer(0));
		
		/*cclient = std::shared_ptr<CClient>(new CClient())*/;

		cclient.setIp(ip_addr_str);
		cclient.setPort(atoi(port));
		GetDlgItem(IDC_CONNECT)->EnableWindow(false);
		int a = 1;
		try
		{
			a = cclient.bind(user, pass);
		}
		catch (const std::exception& e)
		{
			MessageBox(e.what());
		}

		if (a == 0)
		{
			GetDlgItem(IDC_DISCONNECT)->EnableWindow(true);
			GetDlgItem(IDC_SENDTEXT)->EnableWindow(true);
			GetDlgItem(IDC_SEND)->EnableWindow(true);
	
		}
		else
		{
			MessageBox(_T("连接失败"));
			GetDlgItem(IDC_CONNECT)->EnableWindow(true);

		}
		
		
	}
}





void CClientDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CClientDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	
	try
	{
		int r = cclient.unBind();
		if (r ==0)
		{
			GetDlgItem(IDC_CONNECT)->EnableWindow(true);
		}
	}
	catch (const std::exception& e )
	{
		MessageBox(e.what());
		GetDlgItem(IDC_CONNECT)->EnableWindow(true);
	}
	
	
	
}


void CClientDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ph_num;
	GetDlgItem(IDC_ADD_PH)->GetWindowText(ph_num);
	GetDlgItem(IDC_ADD_PH)->SetWindowText(_T(""));
	m_ph_list.AddString(ph_num);
}


void CClientDlg::OnBnClickedMin()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_ph_list.GetCount(); ++i)
	{
		if (m_ph_list.GetSel(i) != 0)
		{
			m_ph_list.DeleteString(i);
		}
	}

}


void CClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码

	CString c_ph_num;
	CString c_text;
	std::vector<std::string> ph_nums;
	std::string ph_num;
	std::string text;


	for (int i = 0; i < m_ph_list.GetCount(); ++i)
	{
		m_ph_list.GetText(i,c_ph_num);
		ph_num = c_ph_num.GetBuffer(0);
		ph_nums.push_back(ph_num);
	}



	GetDlgItem(IDC_SENDTEXT)->GetWindowText(c_text);
	text = c_text.GetBuffer(0);
	int r = 1;
	try
	{
		r = cclient.submit(ph_nums,text);
		
	}
	catch (const std::exception& e)
	{
		MessageBox(e.what());
	}

}
