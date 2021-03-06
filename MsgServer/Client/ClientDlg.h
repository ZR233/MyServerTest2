
// ClientDlg.h: 头文件
//

#pragma once
#include "..\MsgSystem\CClient.h"
#include "afxwin.h"


// CClientDlg 对话框
class CClientDlg : public CDialog
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//std::shared_ptr<CClient> cclient;
	CClient cclient;

public:
	afx_msg void OnEnChangeText();
	afx_msg void OnIpnFieldchangedIpaddr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedAdd();
	// 手机号列表
	CListBox m_ph_list;
	afx_msg void OnBnClickedMin();
	afx_msg void OnBnClickedSend();
};
