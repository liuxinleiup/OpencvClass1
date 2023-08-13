//知识点	IM表示图片
	//读取图像：imread
	//显示图像：imshow
	//色彩空间转换函数(B G R)：cvtColor
		//COLOR_BGR2GRAY = 6彩色到灰度
		//COLOR_GRAY2BGR = 8灰度到彩色
		//COLOR_BGR2HSV  = 40BGR到HSV
		//COLOR_HSV2BGR  = 54HSV到BGR
	//保存图片：imwrite(保存路径，内存对象)



#include<opencv2/opencv.hpp>
#include<iostream>
#include<test.h>


using namespace std;
using namespace cv;
int main()
{
	//读取进来的数据以矩阵的形势
	Mat src = imread("F:/images/gril.jpg", IMREAD_ANYCOLOR);	    //第二个参数代表显示一张灰度图像

																	//看是否是空图片
	if (src.empty())
	{
		printf("图片不存在");
		return -1;
	}
	//创建了一个新窗口：超过屏幕的图像无法显示时候调用此函数
	namedWindow("输入窗口", WINDOW_FREERATIO);					   //参数1表示名称，参数二代表窗口自由显示

	//表示显示在新创建的输入窗口上
	imshow("输入窗口", src);									   //第一个参数表示窗口名称，src表示数据对象Mat 


	//在主函数中调用之前创建的类对象	
	QuickDemo qd;
		//色彩转换
		//qd.colorSpace_Demo(src);

		//图像对象的创建
		//qd.mat_creation_demo(src);

		//图像像素的读写
		//qd.pixel_visit_demo1(src);	//数组
		//qd.pixel_visit_demo2(src);	//指针

		//图像像素的算术操作
		//qd.operators_demo(src);

		//滚动条调整图像亮度
		//qd.tracking_bar_demo1(src);

		//滚动条参数传递(亮度和对比度)
		//qd.tracking_bar_demo2(src);

		//键盘响应
		//qd.key_demo(src);

		//opencv自带颜色操作
		//qd.color_style_demo(src);

		//图像像素的逻辑操作
		//qd.bitwise_demo(src);

		//通道的分离与合并
		//qd.channels_demo(src);

		//图像色彩空间转换
		//qd.inrange_demo(src);

		//图像像素值统计
		//qd.pixel_statistic_demo(src);

		//图像几何形状的绘制
		//qd.drawing_demo(src);

		//随机数与随机颜色
		//qd.random_drawing();

		//多边形填充与绘制
		//qd.polyline_drawing_demo(src);

		//鼠标操作与响应
		//qd.mouse_drawing_demo(src);

		//图像像素类型的转换与归一化
		//qd.norm_demo(src);

		//图像的放缩与差值
		//qd.resize_demo(src);

		//图像的旋转：定义好的
		//qd.flip_demo(src);

		//图像的旋转：自定义
		//qd.rotate_demo(src);

		//视频文件摄像头使用
		//qd.video_demo1(src);

		//视频处理与保存
		//qd.video_demo2(src);

		//图像直方图
		//qd.histogram_demo(src);

		//二维直方图
		//qd.histogram_2d_demo(src);

		//直方图的均衡化
		//qd.histogram_eq_demo(src);

		//图像卷积操作
		//qd.blur_demo(src);

		//高斯模糊
		//qd.gaussian_blur_demo(src);

		//高斯双边模糊
		//qd.bifilter_demo(src);

		//实时人脸检测
		qd.face_detection_demo(src);

	waitKey(0);													   //执行到这句，程序阻塞。参数表示延时时间。单位ms毫秒
	destroyAllWindows();										   //销毁前面创建的显示窗口
	return 0;
}