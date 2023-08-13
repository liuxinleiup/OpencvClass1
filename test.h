#include<opencv2/opencv.hpp>
using namespace cv;

//创建一个QuickDemo对象
class QuickDemo 
{
	public:
		//色彩转换
		void colorSpace_Demo(Mat &imge);
		//图像对象的创建
		void mat_creation_demo(Mat &imge);
		//图像像素的读写
		void pixel_visit_demo1(Mat &image);	//数组
		void pixel_visit_demo2(Mat &image);	//指针
		//图像像素的算术操作
		void operators_demo(Mat &image);
		//滚动条调整图像亮度
		void tracking_bar_demo1(Mat &image);
		//滚滚动条参数传递(亮度和对比度)
		void tracking_bar_demo2(Mat &image);
		//键盘响应
		void key_demo(Mat &image);
		//opencv自带颜色操作
		void color_style_demo(Mat &image);
		//图像像素的逻辑操作
		void bitwise_demo(Mat &image);
		//通道的分离与合并
		void channels_demo(Mat &image);
		//图像色彩空间转换
		void inrange_demo(Mat &image);

		//图像像素值统计
		void pixel_statistic_demo(Mat &image);

		//图像几何形状的绘制
		void drawing_demo(Mat &image);

		//随机数与随机颜色
		void QuickDemo::random_drawing();

		//多边形填充与绘制
		void QuickDemo::polyline_drawing_demo(Mat &image);

		//鼠标操作与响应
		void QuickDemo::mouse_drawing_demo(Mat &image);

		//图像像素类型的转换与归一化
		void QuickDemo::norm_demo(Mat &image);

		//图像的放缩与差值
		void QuickDemo::resize_demo(Mat &image);

		//图像的旋转：定义好的
		void QuickDemo::flip_demo(Mat &image);

		//图像的旋转：自定义
		void QuickDemo::rotate_demo(Mat &image);

		//视频文件摄像头使用
		void QuickDemo::video_demo1(Mat &image);

		//视频处理与保存
		void QuickDemo::video_demo2(Mat &image);

		//图像直方图
		void QuickDemo::histogram_demo(Mat &image);

		//二维直方图
		void QuickDemo::histogram_2d_demo(Mat &image);

		//直方图的均衡化
		void QuickDemo::histogram_eq_demo(Mat &image);

		//图像卷积操作
		void QuickDemo::blur_demo(Mat &image);

		//高斯模糊
		void QuickDemo::gaussian_blur_demo(Mat &image);

		//高斯双边模糊
		void QuickDemo::bifilter_demo(Mat &image);

		//实时人脸检测
		void QuickDemo::face_detection_demo(Mat &image);
};