
// servicesDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CservicesDlg �Ի���
class CservicesDlg : public CDialogEx
{
// ����
public:
	CservicesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVICES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
