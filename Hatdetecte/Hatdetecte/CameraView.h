#pragma once
//QinJian 第一版 本类别主要实现的功能是显示显示图像在mfc的界面上，大小改变成控件的大小
//具体是未来方便使用Opencv我们是把opencv的窗口扣到mfc之中来使用
#include <opencv2\opencv.hpp>
extern "C"
{
	class CHatdetecteDlg;
}

class CameraView
{
public:
	CameraView();
	~CameraView();
	void InitCameraView(CHatdetecteDlg *csDlg);
	void ShowImage(cv::Mat image);
	//void SetTextToImg(CString strText, float TTop, float TLeft);//在图片上写字
	cv::Size m_cameraViewSize;
private:
	CHatdetecteDlg *m_csDlg = NULL;
};