#include "stdafx.h"
#include "DarkNet.h"
#include "HatdetecteDlg.h"
#define OPENCV

const std::string  names_file = "../data/voc.names";//分类的名称
const std::string  cfg_file = "../data/yolov3-voc.cfg";  //yolo网络结构文件
const std::string  weights_file = "../data/final.weights"; //网络权重文件
Detector detector(cfg_file, weights_file);//初始化检测器  因为没有默认构造函数，保证一次的加载模型，就这这里定于为全局

DarkNet::DarkNet()
{

}

DarkNet::~DarkNet()
{

}
void DarkNet::InitDarkNet(CHatdetecteDlg *csDlg)
{
	m_csDlg = csDlg;
}

cv::Scalar DarkNet::obj_id_to_color(int obj_id)
{
	int const colors[6][3] = { { 1,0,1 },{ 0,0,1 },{ 0,1,1 },{ 0,1,0 },{ 1,1,0 },{ 1,0,0 } };
	int const offset = obj_id * 123457 % 6;
	int const color_scale = 150 + (obj_id * 123457) % 100;
	cv::Scalar color(colors[offset][0], colors[offset][1], colors[offset][2]);
	color *= color_scale;
	return color;
}

void DarkNet::draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names,
	int current_det_fps, int current_cap_fps)
{
	int const colors[6][3] = { { 1,0,1 },{ 0,0,1 },{ 0,1,1 },{ 0,1,0 },{ 1,1,0 },{ 1,0,0 } };
	for (auto &i : result_vec) {
		cv::Scalar color = obj_id_to_color(i.obj_id);
		cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
		if (obj_names.size() > i.obj_id) {
			std::string obj_name = obj_names[i.obj_id];
			if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
			cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
			int const max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
			cv::rectangle(mat_img, cv::Point2f(std::max((int)i.x - 1, 0), std::max((int)i.y - 30, 0)),
				cv::Point2f(std::min((int)i.x + max_width, mat_img.cols - 1), std::min((int)i.y, mat_img.rows - 1)),
				color, CV_FILLED, 8, 0);
			putText(mat_img, obj_name, cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(0, 0, 0), 2);
		}
	}
}

std::vector<std::string> DarkNet::objects_names_from_file(std::string const filename)
{
	std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for (std::string line; getline(file, line);)
	{
		std::cout << line << std::endl;
		file_lines.push_back(line);
	}
	std::cout << "object names loaded \n";
	return file_lines;
}

image_t make_empty_image(int w, int h, int c)
{
	image_t out;
	out.data = 0;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}

image_t make_image(int w, int h, int c)
{
	image_t out = make_empty_image(w, h, c);
	out.data = new float[w*h*c];
	return out;
}

image_t DarkNet::cv_mat_to_image_t(cv::Mat& image)
{
	cv::Mat dst;
	cv::cvtColor(image, dst, cv::COLOR_BGR2RGB);
	int w, h, c;
	w = image.cols;
	h = image.rows;
	int channels = image.channels();
	unsigned char *data = dst.data;
	if (!data)
		throw std::runtime_error("file not found");
	if (channels) c = channels;
	int i, j, k;
	image_t im = make_image(w, h, c);
	for (k = 0; k < c; ++k) {
		for (j = 0; j < h; ++j) {
			for (i = 0; i < w; ++i) {
				int dst_index = i + w * j + w * h*k;
				int src_index = k + c * i + c * w*j;
				im.data[dst_index] = (float)data[src_index] / 255.;
			}
		}
	}
	//free(data);
	return im;

}
/*  //这里也是参看csdn上面写的 但是一些原因占用内存特别大，建议换成程序原本接口
void DarkNet::VideoDetecte(std::string file, float thresh)
{

	extern CHatdetecteDlg m_dlg;
	if (file.size() == 0)
		AfxMessageBox(TEXT("没有文件路径"));

	auto obj_names = objects_names_from_file(names_file);//获得分类对象名称
	for (size_t i = 0; i < obj_names.size(); i++)
	{
		std::cout << obj_names[i] << std::endl;
	}

	cv::VideoCapture capture;
	capture.open(file);
	if (!capture.isOpened())
	{
		AfxMessageBox( TEXT("文件打开失败"));
	}
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cv::Mat frame;


	for (size_t i = 0; i < totalFrameNumber; i++)
	{
		capture >> frame;
		//std::vector<bbox_t> result_vec = detector.detect(cv_mat_to_image_t(frame), thresh,false);
		std::vector<bbox_t> result_vec = detector.detect(frame, thresh, false);
		draw_boxes(frame, result_vec, obj_names);
		m_csDlg->m_CameraView.ShowImage(frame);
	}

	return;
}
*/

void DarkNet::PictureDetecte(cv::Mat image, float thresh)
{
	if (image.empty())
	{ 
		AfxMessageBox(TEXT("请先打开图片"));
		return;
	}
		
	auto obj_names = objects_names_from_file(names_file);//获得分类对象名称
	for (size_t i = 0; i < obj_names.size(); i++)
	{
		std::cout << obj_names[i] << std::endl;
	}
	//std::vector<bbox_t> result_vec = detector.detect(cv_mat_to_image_t(image), thresh, false);
	std::vector<bbox_t> result_vec = detector.detect(image, thresh, false);
	draw_boxes(image, result_vec, obj_names);
	m_csDlg->m_CameraView.ShowImage(image);

}