#pragma once
//QinJian ��һ�� �������Ҫʵ�ֵĹ�������ʾ��ʾͼ����mfc�Ľ����ϣ���С�ı�ɿؼ��Ĵ�С
//������δ������ʹ��Opencv�����ǰ�opencv�Ĵ��ڿ۵�mfc֮����ʹ��
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
	//void SetTextToImg(CString strText, float TTop, float TLeft);//��ͼƬ��д��
	cv::Size m_cameraViewSize;
private:
	CHatdetecteDlg *m_csDlg = NULL;
};