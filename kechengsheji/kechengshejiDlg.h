
// kechengshejiDlg.h: 头文件
//

#pragma once
#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
#include "sigslot.h"
using namespace itas109;
using namespace sigslot;

// CkechengshejiDlg 对话框
class CkechengshejiDlg : public CDialogEx,public has_slots<>
{
// 构造
public:
	CkechengshejiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KECHENGSHEJI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	void OnReceive();

private:
	CSerialPort m_serialPort;


// 实现
protected:
	HICON m_hIcon;
	CString File_Path;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnCbnSelchangeCombo1();
//	CString PortID;
	afx_msg void OnBnClickedButton2();
	CComboBox m_PortNr;
	CComboBox m_BaudRate;
	CComboBox m_Parity;
	CComboBox m_Stop;
	afx_msg void OnBnClickedButton3();
	CButton m_OpenCloseCtrl;
};
