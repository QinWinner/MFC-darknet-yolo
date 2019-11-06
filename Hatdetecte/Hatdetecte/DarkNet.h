#pragma once
//QinJian  这边就是使用darknet编译好的dll 用他的接口来实现yolo的检测

#include <iostream>
#include <opencv2/opencv.hpp>	// C++
#include "opencv2/highgui/highgui.hpp"
#include "include\yolo_v2_class.hpp"// imported functions from DLL
#include "opencv2/imgproc/imgproc.hpp"
#include <string>

extern "C"
{
	class CHatdetecteDlg;
}

 

class DarkNet
{
public:
	DarkNet();
	~DarkNet();
	void InitDarkNet(CHatdetecteDlg *csDlg);
	//void VideoDetecte(std::string filename, float thresh = 0.2);
	void PictureDetecte(cv::Mat image, float thresh = 0.2);
private:
	CHatdetecteDlg *m_csDlg = NULL;
	//模型的参数地址
	void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names,
		int current_det_fps = -1, int current_cap_fps = -1);
	std::vector<std::string> objects_names_from_file(std::string const filename);
	cv::Scalar obj_id_to_color(int obj_id);
	image_t cv_mat_to_image_t(cv::Mat& image); //把mat转换为yolo接收的格式 如果在yolo编译过程中定义了opencv的使用，这边是不需要的

};

