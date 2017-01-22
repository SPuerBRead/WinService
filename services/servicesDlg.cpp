
// servicesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "services.h"
#include "servicesDlg.h"
#include "afxdialogex.h"
#include "Windows.h"
#include "WinNt.h"
#include "Winsvc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CservicesDlg 对话框



CservicesDlg::CservicesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVICES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DlgRect.SetRect(0, 0, 0, 0);
}

void CservicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CservicesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CservicesDlg::Win32)
	ON_BN_CLICKED(IDC_RADIO2, &CservicesDlg::Driver)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_START, &CservicesDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CservicesDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CservicesDlg 消息处理程序

BOOL CservicesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CRect rect;
	m_list.GetClientRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "服务名",LVCFMT_LEFT, rect.Width() / 3, 0);
	m_list.InsertColumn(1, "说明",LVCFMT_LEFT, rect.Width() / 2, 0);
	m_list.InsertColumn(2, "状态", LVCFMT_LEFT);
	m_list.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CservicesDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CservicesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CservicesDlg::Win32()
{
	ServiceEnum(SERVICE_WIN32);
}

void CservicesDlg::Driver()
{
	ServiceEnum(SERVICE_DRIVER);
}

void CservicesDlg::ServiceEnum(DWORD Type)
{
	LPENUM_SERVICE_STATUS databuffer;
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(_T("错误码：") + GetLastError());
		exit(0);
	}
	m_list.DeleteAllItems();
	DWORD dwSize = 0, dwServiceCount = 0;
	BOOL RRET = EnumServicesStatus(hSCM, Type, SERVICE_STATE_ALL, NULL, 0, &dwSize, &dwServiceCount, NULL);
	if (!RRET && GetLastError() == ERROR_MORE_DATA)
	{
		databuffer = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
		RRET = EnumServicesStatus(hSCM, Type, SERVICE_STATE_ALL, (LPENUM_SERVICE_STATUS)databuffer, dwSize, &dwSize, &dwServiceCount, NULL);
		if (!RRET)
		{
			CloseServiceHandle(hSCM);
			return;
		}
		for (DWORD i = 0; i < dwServiceCount; i++)
		{
			m_list.InsertItem(i, databuffer[i].lpServiceName);
			m_list.SetItemText(i, 1, databuffer[i].lpDisplayName);
			switch (databuffer[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_PAUSED:
			{
				m_list.SetItemText(i, 2, _T("暂停"));
				break;
			}
			case SERVICE_STOPPED:
			{
				m_list.SetItemText(i, 2, _T("停止"));
				break;
			}
			case SERVICE_RUNNING:
			{
				m_list.SetItemText(i, 2, _T("运行"));
				break;
			}
			default:
			{
				m_list.SetItemText(i, 2, _T("其他"));
			}
			}
		}
		delete databuffer;
		CloseServiceHandle(hSCM);
	}
}

void CservicesDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpMMI->ptMinTrackSize.x <= 580)
		lpMMI->ptMinTrackSize.x = 580;
	if (lpMMI->ptMinTrackSize.y <= 450)
		lpMMI->ptMinTrackSize.y = 450;
	if (lpMMI->ptMaxTrackSize.x > 580)
		lpMMI->ptMaxTrackSize.x = 580;
	if (lpMMI->ptMaxTrackSize.y > 450)
		lpMMI->ptMaxTrackSize.y = 450;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}




void CservicesDlg::OnBnClickedStart()
{
	POSITION Pos = m_list.GetFirstSelectedItemPosition();
	int SelectNum = -1;
	while (Pos)
	{
		SelectNum = m_list.GetNextSelectedItem(Pos);
	}
	if (SelectNum == -1)
	{
		MessageBox(_T("选择你要开启的服务"));
		return;
	}
	char SelectName[MAXBYTE] = { 0 };
	m_list.GetItemText(SelectNum, 0,SelectName, MAXBYTE);
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(_T("错误码：") + GetLastError());
		exit(0);
	}
	SC_HANDLE hSCService = OpenService(hSCM, SelectName, SERVICE_ALL_ACCESS);
	BOOL RRET = StartService(hSCService, 0, NULL);
	if (RRET == TRUE)
	{
		m_list.SetItemText(SelectNum, 2, _T("运行"));
	}
	else
	{
		MessageBox(_T("启动失败"));
	}
	CloseServiceHandle(hSCService);
	CloseServiceHandle(hSCM);
}


void CservicesDlg::OnBnClickedStop()
{
	POSITION Pos = m_list.GetFirstSelectedItemPosition();
	int SelectNum = -1;
	while (Pos)
	{
		SelectNum = m_list.GetNextSelectedItem(Pos);
	}
	if (SelectNum == -1)
	{
		MessageBox(_T("选择你要关闭的服务"));
		return;
	}
	char SelectName[MAXBYTE] = { 0 };
	m_list.GetItemText(SelectNum, 0, SelectName, MAXBYTE);
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(_T("错误码：") + GetLastError());
		exit(0);
	}
	SC_HANDLE hSCService = OpenService(hSCM, SelectName, SERVICE_ALL_ACCESS);
	SERVICE_STATUS status;
	BOOL RRET = ControlService(hSCService, SERVICE_CONTROL_STOP, &status);
	if (RRET == TRUE)
	{
		m_list.SetItemText(SelectNum, 2, _T("停止"));
	}
	else
	{
		MessageBox(_T("关闭失败"));
	}
	CloseServiceHandle(hSCService);
	CloseServiceHandle(hSCM);
}
