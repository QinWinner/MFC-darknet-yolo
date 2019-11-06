
// HatdetecteDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include "CameraView.h"
#include "DarkNet.h"

// CHatdetecteDlg �Ի���
class CHatdetecteDlg : public CDialogEx
{
// ����
public:
	CHatdetecteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HATDETECTE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	CameraView m_CameraView;
	cv::Mat image; //ȫ�ֵ�һ��ͼƬ����ȡ������
	DarkNet m_darknet;
public:
//	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDetecte();
	afx_msg void OnBnClickedOpenvideo();
};
