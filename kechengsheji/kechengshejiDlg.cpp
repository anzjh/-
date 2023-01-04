
// kechengshejiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "kechengsheji.h"
#include "kechengshejiDlg.h"
#include "afxdialogex.h"
#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
#include "sigslot.h"
using namespace itas109;
using namespace sigslot;

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


// CkechengshejiDlg 对话框



CkechengshejiDlg::CkechengshejiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KECHENGSHEJI_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkechengshejiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, PortID);
	DDX_Control(pDX, IDC_COMBO1, m_PortNr);
	DDX_Control(pDX, IDC_COMBO2, m_BaudRate);
	DDX_Control(pDX, IDC_COMBO3, m_Parity);
	DDX_Control(pDX, IDC_COMBO4, m_Stop);
	DDX_Control(pDX, IDC_BUTTON3, m_OpenCloseCtrl);
}

BEGIN_MESSAGE_MAP(CkechengshejiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CkechengshejiDlg::OnBnClickedButton1)
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CkechengshejiDlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_BUTTON2, &CkechengshejiDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CkechengshejiDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CkechengshejiDlg 消息处理程序

BOOL CkechengshejiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CkechengshejiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CkechengshejiDlg::OnPaint()
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
HCURSOR CkechengshejiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CkechengshejiDlg::OnBnClickedButton1()    //打开串口按钮
{
	// TODO: 在此添加控件通知处理程序代码
	char portName[256] = { 0 };
	int SelBaudRate;
	int SelParity;
	int SelDataBits = 8;    //没有数据位下拉框，就写死在这里了
	int SelStop;
	CString temp;
	m_PortNr.GetWindowText(temp);
#ifdef UNICODE
	strcpy_s(portName, 256, CW2A(temp.GetString()));
#else
	strcpy_s(portName, 256, temp.GetBuffer());
#endif	
	m_BaudRate.GetWindowText(temp);
	SelBaudRate = _tstoi(temp);
	SelParity = m_Parity.GetCurSel();
	SelStop = m_Stop.GetCurSel();
	m_serialPort.init(portName ,SelBaudRate, itas109::Parity(SelParity), itas109::DataBits(SelDataBits), itas109::StopBits(SelStop)); //TODO: 关联串口号，波特率等参数与多选框内选中值
	m_serialPort.open();
	if (m_serialPort.isOpen())
	{
		MessageBox(_T("串口打开成功"));
	}
	else
	{
		MessageBox(_T("串口打开失败，请检查是否被占用或未开启串口虚拟软件"));
	}
}



void CkechengshejiDlg::OnBnClickedButton2()    //关闭串口按钮
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_serialPort.isOpen())
	{
		m_serialPort.close();
		MessageBox(_T("串口已关闭"));
	}
	else
	{
		MessageBox(_T("串口未打开"));
	}
}


void CkechengshejiDlg::OnReceive()  //CSerialPort
{
	char* str = NULL;
	str = new char[1024];
	int iRet = m_serialPort.readAllData(str);

	if (iRet > 0)
	{
		str[iRet] = '\0';
		CString str1((char*)str);
	}
}

void CkechengshejiDlg::OnBnClickedButton3()   //开始检测按钮
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	GetDlgItem(IDC_BUTTON3)->GetWindowText(temp);
	if (temp == "开始检测") {
		if (!m_serialPort.isOpen())
		{
			MessageBox(_T("串口未打开"));

		}
		m_OpenCloseCtrl.SetWindowText(_T("停止检测"));







	}



}
