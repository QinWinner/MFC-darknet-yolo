
// HatdetecteDlg.h : 头文件
//

#pragma once
#include <string>
#include "CameraView.h"
#include "DarkNet.h"

// CHatdetecteDlg 对话框
class CHatdetecteDlg : public CDialogEx
{
// 构造
public:
	CHatdetecteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HATDETECTE_DIALOG };
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
public:
	afx_msg void OnBnClickedOpen();
	CameraView m_CameraView;
	cv::Mat image; //全局的一个图片，读取进来的
	DarkNet m_darknet;
public:
//	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDetecte();
	afx_msg void OnBnClickedOpenvideo();
};
