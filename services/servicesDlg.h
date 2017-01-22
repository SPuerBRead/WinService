
// servicesDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CservicesDlg 对话框
class CservicesDlg : public CDialogEx
{
// 构造
public:
	CservicesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVICES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CRect m_DlgRect;
	CDWordArray m_control_info;
public:
	afx_msg void Win32();
	CListCtrl m_list;
	void ServiceEnum(DWORD Type);
	afx_msg void Driver();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	CRect m_rc;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
