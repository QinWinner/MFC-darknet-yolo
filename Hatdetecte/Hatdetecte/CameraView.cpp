#include "stdafx.h"
#include "CameraView.h"
#include "HatdetecteDlg.h"
#include "resource.h"


CameraView::CameraView()
{
}

CameraView::~CameraView()
{
}

void CameraView::InitCameraView(CHatdetecteDlg *csDlg)
{
	this->m_csDlg = csDlg;
	//初始化窗口显示
	cv::namedWindow("CameraView", cv::WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("CameraView");//"CameraView"
	CWnd * pWnd = AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_PICTURE_CAMERA);
	HWND hParent = ::GetParent(hWnd); 
	::SetParent(hWnd, pWnd->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	//获取窗口大小
	CRect rect;
	csDlg->GetDlgItem(IDC_PICTURE_CAMERA)->GetClientRect(&rect);
	m_cameraViewSize = cv::Size(rect.Width(), rect.Height());
}

void CameraView::ShowImage(cv::Mat image)
{
	cv::resize(image, image, m_cameraViewSize);
	cv::imshow("CameraView", image);
}