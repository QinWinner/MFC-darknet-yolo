# MFC-darknet-yolo
我利用在windows10上编译的darknet，编写了一个简单的mfc demo利用我们生成的模型来实现目标检测功能。

![效果图片](/show.jpg)


## 参考的项目

	借助了git上面再windows端通过vs2013 vs2015配置darknet项目的过程。
[项目连接](https://github.com/AlexeyAB/darknet)
具体的项目训练和配置文件的撰写，可以参考blog[训练过程](https://www.cnblogs.com/pprp/p/9525508.html)
	
## 项目说明
	在data文件夹中放入我们的两个配置文件，同时放入我们训练好的模型，
	模型的名字默认为final.weights
	
### 主要利用api
	在yolo_cpp_dll.dll -api
```
        struct bbox_t {
    	unsigned int x, y, w, h;    // (x,y) - top-left corner, (w, h) - width & height of bounded box
       float prob;                    // confidence - probability that the object was found correctly
       unsigned int obj_id;        // class of object - from range [0, classes-1]
       unsigned int track_id;        // tracking id for video (0 - untracked, 1 - inf - tracked object)
       unsigned int frames_counter;// counter of frames on which the object was detected
};
class Detector {
public:
        Detector(std::string cfg_filename, std::string weight_filename, int gpu_id = 0);
        ~Detector();

        std::vector<bbox_t> detect(std::string image_filename, float thresh = 0.2, bool use_mean = false);
        std::vector<bbox_t> detect(image_t img, float thresh = 0.2, bool use_mean = false);
        static image_t load_image(std::string image_filename);
        static void free_image(image_t m);

#ifdef OPENCV
        std::vector<bbox_t> detect(cv::Mat mat, float thresh = 0.2, bool use_mean = false);
	std::shared_ptr<image_t> mat_to_image_resize(cv::Mat mat) const;
#endif
};
	
```

需要注意其中的`std::vector<bbox_t> detect(cv::Mat mat, float thresh = 0.2, bool use_mean = false);`
需要在编译darknet时候选择开启opencv才可以使用。





## 环境说明

	需要配置opencv，需要自行配置
	darknet的连接库和动态库，这边我编译好了vs2015 x64 的relase版本 放在了 hatdetect\include中
	同时在hatdetect\cpuban ,gpuban 给了cpu版本和gpu版本
	编译之后还有两个连接库pthreadGC2.dll pthreadVC2.dll
