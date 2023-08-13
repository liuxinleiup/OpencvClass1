#include<test.h>
#include<opencv2/dnn.hpp> 

//命名空间
using namespace cv;
using namespace std;

//色彩转换
void QuickDemo::colorSpace_Demo(Mat & image)
{
	Mat a, b;								//定义2个矩阵类的图像a和b，
	cvtColor(image, b, COLOR_BGR2HSV);		//图像转换函数，可以把image转成b，第三个参数是转成的类型	COLOR_BGR2HSV  = 40BGR到HSV
	cvtColor(image, a, COLOR_BGR2GRAY);		//图像转换函数，可以把image转成a，第三个参数是转成的类型	COLOR_BGR2GRAY = 6彩色到灰度

	imshow("HSV", b);
	imshow("灰度", a);

	//保存图片，前面是保存图的地址，后面是保存图的名称
	imwrite("F:/images/hsv.jpg", b);					
	imwrite("F:/images/gray.jpg", a);
}


//图像对象的创建
void QuickDemo::mat_creation_demo(Mat &image)
{
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);		//复制

	//创建空白图像		ones&zeros是初始化的方法
	Mat m3 = Mat::ones(Size(400,400), CV_8UC3);	//创建400*400；的CV8位的；无符号uU=nsigned char；通道为n=3数据的宽度和长度是由通道数决定的
	m3 = Scalar(255, 0, 0);//改变m3的颜色为蓝色

	//用来查看宽度，高度与通道数
	/*std::cout << "width:"<<m3.cols<<"height"<< m3.rows <<"channels"<<m3.channels()<< std::endl;
	std::cout << m3 << std::endl;*/


	Mat m4 = m3.clone();	 //克隆
	//m3.copyTo(m4);		 //把M3赋值给M4，M4就是蓝色
	m4 = Scalar(0, 255, 255);//改变m4的颜色为黄色

	//这里还有其他的
		//Mat m3 = m4;		//赋值
		//Mat kernel = (Mat_<char>(3,3) << 0, -1, 0,-1,5,-1,0,-1,-1 );


	imshow("图像3", m3);	//标题和图像名称   显示图像m3 纯蓝色
	imshow("图像4", m4);	//标题和图像名称
}


//图像像素的读写	第一种是数组访问模式
void QuickDemo::pixel_visit_demo1(Mat &image)
{
	int dims = image.channels();
	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			if (dims == 1) //单通道的灰度图像
			{
				int pv = image.at<uchar>(row, col);  //得到像素值
				image.at<uchar>(row, col) = 255 - pv;//给像素值重新赋值

			}
			if (dims == 3) //三通道的彩色图像
			{
				Vec3b bgr = image.at<Vec3b>(row, col);		//opencv特定的类型，获取三维颜色，3个值
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];//对彩色图像读取它的像素值，并且对像素值进行改写。
			}
		}
	}
	namedWindow("像素读写演示", WINDOW_FREERATIO);
	imshow("像素读写演示", image);
}

//图像像素的读写	第二种为指针访问模式
void QuickDemo::pixel_visit_demo2(Mat &image)
{
	int dims = image.channels();
	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++)
	{
		uchar *current_row = image.ptr<uchar>(row);

		for (int col = 0; col < w; col++)
		{
			if (dims == 1) //单通道的灰度图像
			{
				int pv = *current_row;	   //得到像素值
				*current_row++ = 255 - pv; //给像素值重新赋值

			}
			if (dims == 3) //三通道的彩色图像
			{
				*current_row++ = 255 - *current_row; //指针每做一次运算，就向后移动一位
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	namedWindow("像素读写演示", WINDOW_FREERATIO);
	imshow("像素读写演示", image);

}

//图像像素的算术操作
void QuickDemo::operators_demo(Mat &image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m   = Mat::zeros(image.size(), image.type());
	dst = image - Scalar(50, 50, 50);	//素点减50
	m = Scalar(50, 50, 50);

	//下面是内部的函数调用
	add(image, m, dst);				//加法操作 api
	imshow("加法操作", dst);
	namedWindow("加法操作", WINDOW_FREERATIO);

	//subtract(image, m, dst);		//减法操作 api
	//imshow("减法操作", dst);

	//multiply(image, m, dst);		//乘法操作 api
	//imshow("乘法操作", dst);

	//divide(image, m, dst);		//除法操作 api
	//imshow("除法操作", dst);


//	//加法操作底层
//	int dims = image.channels();
//	int h = image.rows;
//	int w = image.cols;
//	for (int row = 0; row < h; row++)
//	{
//		for (int col = 0; col < w; col++)
//		{
//			Vec3b p1 = image.at<Vec3b>(row, col); //opencv特定的类型，获取三维颜色，3个值
//			Vec3b p2 = m.at<Vec3b>(row, col);
//			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);	//saturate_cast用来防爆，小于0就是0，大于255就是255
//			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
//			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);	//对彩色图像读取它的像素值，并且对像素值进行改写。
//		}
//	}
//	imshow("加法操作", dst);
//
}


//滚动条调整图像亮度
Mat  src, dst, m;
int lightness = 50;								//定义初始的亮度为50
static void on_track(int, void*)
{
	m = Scalar(lightness, lightness, lightness);//创建调整亮度的数值
	subtract(src, m, dst);						//定义亮度变化为——减
	imshow("亮度调整", dst);					//显示调整亮度之后的图片
}
void QuickDemo::tracking_bar_demo1(Mat &image)
{
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	dst = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	  m = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	src = image;								 //给src赋值
	int max_value = 100;						 //定义最大值为100
	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);//调用函数实现功能。
	on_track(50, 0);
}


//滚动条参数传递(亮度和对比度)
static void on_lightness(int b, void* userdata)//亮度 目标图像
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());

	m = Scalar(b, b, b);

	//第一个图像 第一个图像的权重 第二个图像 第二个图像的权重 加到权重总和上的标量值 目标图像
	addWeighted(image, 1.0, m, 0, b, dst);		//融合两张图
	imshow("亮度&对比度调整", dst);
}
static void on_contrast(int b, void* userdata)  //对比度 目标图像
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());

	double contrast = b / 100.0;

	addWeighted(image, contrast, m, 0.0, 0, dst);//融合两张图
	imshow("亮度&对比度调整", dst);
}
void QuickDemo::tracking_bar_demo2(Mat &image)
{
	namedWindow("亮度&对比度调整", WINDOW_AUTOSIZE);

	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;

	//				 取名			窗口名			滑块初始值  滚动的最大值 接收回调函数  用户传给回调函数的数据
	createTrackbar("Value Bar:", "亮度&对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar:", "亮度&对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}


//键盘响应
void QuickDemo::key_demo(Mat &image)	//先要鼠标点击图片再按键盘
{
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		char c = waitKey(100);//停顿100ms 做视频处理都是1
		if (c == 27) {		  //esc 退出应用程序
			break;
		}
		if (c == 49)//key#1
		{
			std::cout << "你按下了 #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50)//key#2
		{
			std::cout << "你按下了 #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51)//key#3
		{
			std::cout << "你按下了 #3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("键盘响应", dst);
		std::cout << c << std::endl;
	}
}


//opencv自带颜色操作
void QuickDemo::color_style_demo(Mat &image)
{
	//各种色彩
	int colormap[] = {
		COLORMAP_AUTUMN ,
		COLORMAP_BONE,
		COLORMAP_CIVIDIS,
		COLORMAP_DEEPGREEN,
		COLORMAP_HOT,
		COLORMAP_HSV,
		COLORMAP_INFERNO,
		COLORMAP_JET,
		COLORMAP_MAGMA,
		COLORMAP_OCEAN,
		COLORMAP_PINK,
		COLORMAP_PARULA,
		COLORMAP_RAINBOW,
		COLORMAP_SPRING,
		COLORMAP_TWILIGHT,
		COLORMAP_TURBO,
		COLORMAP_TWILIGHT,
		COLORMAP_VIRIDIS,
		COLORMAP_TWILIGHT_SHIFTED,
		COLORMAP_WINTER
	};

	Mat dst;
	int index = 0;
	while (true)
	{
		char c = waitKey(100);		//停顿100ms 做视频处理都是1
		if (c == 27) {			    //esc 退出应用程序
			break;
		}
		if (c == 49)				//key#1 按下按键1时，保存图片到指定位置
		{
			std::cout << "你按下了 #1" << std::endl;
			imwrite("F:/images/gray.jpg", dst);
		}
		applyColorMap(image, dst, colormap[index % 19]);	//循环展示19种图片	(输入图像，输出图像，匹配颜色)
		index++;
		imshow("循环播放", dst);
	}
}


//图像像素的逻辑操作
void QuickDemo::bitwise_demo(Mat &image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);

	//图像，形状大小位置，颜色，线宽(>0表示绘制 <0表示填充)，线条样式，逆时针方向
	//颜色B G R
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);

	Mat dst;
	bitwise_and(m1, m2, dst);	//位操作与
	//bitwise_or(m1, m2, dst);	//位操作或
	//bitwise_not(image, dst);	//取反操作
	//bitwise_xor(m1, m2, dst);	//异或操作
	imshow("像素位操作", dst);
}


//通道的分离与合并
void QuickDemo::channels_demo(Mat &image)
{
	//容器
	std::vector<Mat>mv;
	//1.通道分离
	split(image, mv);
	//0,1,2三个通道分别代表BGR
		//imshow("蓝色", mv[0]);
		//imshow("绿色", mv[1]);
		//imshow("红色", mv[2]);

	Mat dst;
	//选择一个通道打开，其他关闭
		mv[0] = 0;
		mv[2] = 0;
	//2.通道合并
	merge(mv, dst);
	imshow("蓝色", dst);

	//3.通道混合
	int from_to[] = { 0,2,1,1,2,0 };				//两两依次一组
	mixChannels(&image, 1, &dst, 1, from_to, 3);	//3表示3个通道
	imshow("通道混合", dst);
}


//图像色彩空间转换
	//RGB色彩空间
	//HSV色彩空间
	//YUV色彩空间
	//YCrCb色彩空间
	
	//色彩空间转换：cvtColor（输入图像，输出图像，转换的颜色空间类型）
	//提取指定色彩范围区域：inRange（输入图像，最小值，最大值，提取指定范围的像素）

void QuickDemo::inrange_demo(Mat &image)							//可以替换照片背景，可以从ps相关来理解
{
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2GRAY);							//色彩空间转换

	Mat mask;
	//自己的照片背景颜色【去除】
		//inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);	//绿色
		inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);	//绿色
	imshow("mask", hsv);			//原图

	Mat redback = Mat::zeros(image.size(), image.type());
	
	//需要替换的背景颜色【替换】
		//redback = Scalar(40, 40, 200);	//红色
		redback = Scalar(230, 20, 20);		//蓝色

	bitwise_not(mask, mask);		//取反 黑白版图（根据颜色去背景）：去掉背景色(无颜色)+抠出人物(人物颜色不一样)
	imshow("mask", mask);	

	image.copyTo(redback, mask);	//蒙版之后的图：换背景=背景颜色+人物图实图								
	imshow("roi区域提取", redback);	
}


//图像像素值统计
	//最小(min)
	//最大(max)
	//均值(mean)
	//标准方差(standard deviation)
	//最大最小值minMaxLoc
	//计算均值与标准方差meanStdDev

void QuickDemo::pixel_statistic_demo(Mat &image)
{
	double minv, maxv;			//定义最值
	Point minLoc, maxLoc;		//定义最值地址

	std::vector<Mat>mv;			//mv是一个Mat类型的容器 装在这个容器内
	split(image, mv);
	for (int i = 0; i < mv.size(); i++)
	{
		//求出图像的最大值和最小值
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());	
		std::cout << "通道:" << i << "最小值:" << minv << "最大值:" << maxv << std::endl;
	}

	Mat mean, stddev;
		//求出图像的均值和方差
		Mat redback = Mat::zeros(image.size(), image.type());
	/*	redback = Scalar(40, 40, 200);
		meanStdDev(redback, mean, stddev);
		imshow("redback", redback);*/

		meanStdDev(image, mean, stddev);	
		std::cout << "均值:" << mean << std::endl;
		std::cout << "方差:" << stddev << std::endl;
}


//图像几何形状的绘制
void QuickDemo::drawing_demo(Mat &image)
{//
	////矩形
	//	Rect rect;
	//		rect.x = 30;
	//		rect.y = 90;
	//		rect.width = 50;
	//		rect.height = 50;
	//	//输入图像，矩形对象，颜色，线条宽度，线条类型，填充方式(0不填充)
	//	rectangle(image, rect, Scalar(255, 0, 0), 6, 8, 0);
	//	imshow("图形的绘制", image);

	////圆形		
	//	//输入图像,圆的中心点坐标(以像素为单位),圆的半径,颜色,线条宽度,线条类型,填充方式
	//	circle(image, Point(50, 90), 15, Scalar(255, 0, 0), 2, LINE_AA, 0);
	//	imshow("图形的绘制", image);
	
	////对两个图像进行加权合并
	//	Mat dst;
	//	Mat bg = Mat::zeros(image.size(), image.type());
	//	//输入图像,图像的权重(取值范围为[0,1]),输入图像,图像的权重(取值范围为[0,1]),像素值的加权和(范围为[-128,127]),输出图像
	//	addWeighted(image, 0.7, bg, 0.3, 0, image);
	//	imshow("图形的绘制", image);

	////直线
	//	//输入图像，起点，终点，颜色，线条宽度，线条类型，填充方式
	//	line(image, Point(10, 50), Point(100, 50), Scalar(0, 0, 255), 8, LINE_AA, 0);
	//	imshow("图形的绘制", image);
	
	//椭圆
		RotatedRect rtt;
			//指定椭圆的位置、大小和方向
			rtt.center = Point(90, 90);
			rtt.size = Size(20, 50);
			rtt.angle = 0.0;
		//输入图像，位置 大小 方向，颜色，线条宽度，线条类型
		ellipse(image, rtt, Scalar(0, 0, 255), 2, 8);
		imshow("图形的绘制", image);
}


//随机数与随机颜色
void QuickDemo::random_drawing()
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;

	//初始化
	RNG rng(2);

	while (true)
	{
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		//rng.uniform(low, high)将生成一个在范围[low, high)内的均匀分布的随机数
		int x1 = rng.uniform(0, canvas.cols);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, canvas.cols);
		int y2 = rng.uniform(0, h);

		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		canvas = Scalar(0, 0, 0);

		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 8, LINE_AA, 0);	
		imshow("随机绘制演示", canvas);
	}
}


//多边形填充与绘制
void QuickDemo::polyline_drawing_demo(Mat &image)
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
		//各个点
		Point p1(100, 100);
		Point p2(350, 100);
		Point p3(450, 280);
		Point p4(320, 450);
		Point p5(80, 400);

	//写入到容器
	std::vector<Point>pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);

	//绘制多边形轮廓填充[只能填充]：地方，包含多线段顶点坐标的数组，颜色，线段绘制方式，对齐坐标的位数
	//fillPoly(canvas, pts, Scalar(122, 155, 255), 8, 0);

	//绘制多边形轮廓：地方，包含多线段顶点坐标的数组，线段是否封闭，颜色，线宽，线段绘制方式，对齐坐标的位数
	//polylines(canvas, pts, true, Scalar(0, 0, 255), 2, 8, 0);

	std::vector<std::vector<Point>>contours;
	//把各个点导入数组
	contours.push_back(pts);
	//绘制多边形轮廓填充[能填充，还可以绘制]:地方，包含多线段顶点坐标的数组，-1表示填充(正表示多边形的绘制 为负表示多边形的填充)，轮廓的颜色，轮廓的线宽
	drawContours(canvas, contours, -1, Scalar(0, 0, 255), -1);

	imshow("多边形绘制", canvas);
}


//鼠标操作与响应
	Point sp(-1, -1);//鼠标的开始的位置
	Point ep(-1, -1);//鼠标放下的位置
	Mat temp;

//处理绘图事件:事件,x 和 y表示鼠标的坐标位置,标志或状态信息,指向用户数据的指针
static void on_draw(int event, int x, int y, int flags, void *userdata)
//event：表示发生的事件类型
//	EVENT_MOUSEMOVE（鼠标移动）
//	EVENT_LBUTTONDOWN（鼠标左键按下）
//	EVENT_RBUTTONDOWN（鼠标右键按下）
{
	//获取用户数据
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN)		//如果鼠标的左键按下   显示起点	
	{
		sp.x = x;
		sp.y = y;
		std::cout << "起点" << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)	//鼠标左键弹起事件		在新窗口显示图
	{
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;

		if (dx > 0 && dy > 0)
		{
			//区域
			Rect box(sp.x, sp.y, dx, dy);		

			//绘制一个窗口盒子
			rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			imshow("截取显示区域窗口", image(box));

			//复位，为下一次做准备
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == EVENT_MOUSEMOVE)	//鼠标移动			   在原图附件上面取图
	{
		if (sp.x > 0 && sp.y > 0)
		{
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0)
			{
				//截取绘制区域
				Rect box(sp.x, sp.y, dx, dy);

				//在原图附件上显示绘制的矩形
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);

				//复制到
				temp.copyTo(image);
			}
		}
	}
}
void QuickDemo::mouse_drawing_demo(Mat &image)
{
	//自动调整大小的窗
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);

	//窗口的名称,回调函数,指向void的指针
	setMouseCallback("鼠标绘制", on_draw, (void*)(&image));

	//原图附件
	imshow("鼠标绘制", image);

	//克隆显示（从原图附件截取的图片 克隆 到新建窗口）
	temp = image.clone();
}


//图像像素类型的转换与归一化
	//将图像或图像中的某个区域（如ROI）的像素值范围缩放到0到1之间，或者根据需要缩放到指定的范围
	//这是一种常用的图像预处理步骤，可以用于图像的对比度拉伸、色彩均衡、直方图均衡化等操作

	//归一化类型有四种，分别是NORM_L2、NORM_L1、NORM_INF、NORM_MINMAX12
	//	NORM_L2：默认值。计算L2范数，使用欧几里得距离
	//	NORM_L1：计算L1范数，即绝对值之和
	//	NORM_INF：计算最大元素的绝对值
	//	NORM_MINMAX：将像素值缩放到[0, 1]的范围内
void QuickDemo::norm_demo(Mat &image)
{
	Mat dst;
	//打印出来图片的类型
	std::cout << image.type() << std::endl;	

	//将dst数据转换成浮点型float32位数据
	image.convertTo(image, CV_32F);
	std::cout << image.type() << std::endl;

	//图像进行归一化操作：输入图像，输出图像，缩放因子-通常取值为1.0，偏移量-通常取值为0.0，归一化的类型
	normalize(image, dst, 1.0,0.0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;

	imshow("图像的归一化", dst);
}


//图像的放缩与差值
void QuickDemo::resize_demo(Mat &image)
{
	Mat zoomin, zoomout;

	int h = image.rows;
	int w = image.cols;

	//调整大小的图像,是否需要缩小图像,新的图像大小,在缩小图像时要在哪个位置开始采样,在缩小图像时要在哪个位置开始采样,插值方法
	//resize(image, zoomin, Size(w/2, h/2), 0, 0, INTER_LINEAR);
	//imshow("zoomin", zoomin);

	resize(image, zoomout, Size(w*3 , h*3), 0, 0, INTER_LINEAR);
	imshow("zoomin", zoomout);
}


//图像的旋转：定义好的
void QuickDemo::flip_demo(Mat &image)
{
	Mat dst;
	flip(image, dst, 0);//上下翻转 x对称

	flip(image, dst, 1);//左右翻转 y对称

	flip(image, dst, -1);//旋转180°

	imshow("图像翻转", dst);
}


//图像的旋转：自定义
void QuickDemo::rotate_demo(Mat &image)
{
	Mat dst, M;			//用于存储旋转后的图像和旋转矩阵
	int h = image.rows;	//定义输入图片的高度
	int w = image.cols;	//定义输入图片的宽度

	//旋转矩阵
		//2D旋转的变换矩阵：图像的中心点,旋转的角度(单位是度),旋转的缩放因子(1.0表示不进行缩放)
		M = getRotationMatrix2D(Point(w / 2, h / 2), 45, 1.0);

		//矩阵旋转获取角度	旋转矩阵是一个2x3的矩阵
		//旋转矩阵的第三个元素是0，这是因为在2D平面中进行旋转时，图像在Z轴上的位置没有变化
		//[cos(angle)   sin(angle)  0]
		//[-sin(angle)  cos(angle)  0]
			// 获取旋转矩阵的第一行第一列元素的绝对值，即cos(45度)
			double cos = abs(M.at<double>(0, 0));	
			// 获取旋转矩阵的第一行第二列元素的绝对值，即sin(45度)
			double sin = abs(M.at<double>(0, 1));

		//这里怎么算的：我放了张图
			// 根据旋转矩阵的元素计算旋转后的图像的宽度，等于cos(45度)*原宽度+sin(45度)*原高度
			int nw = cos * w + sin * h;
			// 根据旋转矩阵的元素计算旋转后的图像的高度，等于sin(45度)*原宽度+cos(45度)*原高度
			int nh = sin * w + cos * h;

	// 将旋转矩阵的第三列的第一项加上(旋转后的图像宽度的一半减去原图像宽度的一半)，以调整旋转后的图像的中心位置
	M.at<double>(0, 2) += (nw / 2 - w / 2);
	// 将旋转矩阵的第三列的第二项加上(旋转后的图像高度的一半减去原图像高度的一半)，以调整旋转后的图像的中心位置
	M.at<double>(1, 2) += (nh / 2 - h / 2);

	//图像进行放射变换:输入图像,输出图像,仿射变换矩阵(决定了图像的变换方式),输出图像的大小,双线性插值法,无填充（0表示无颜色合成）,填充颜色
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 255, 0));

	imshow("旋转演示", dst);
}


//视频文件摄像头使用
void QuickDemo::video_demo1(Mat &image)
{
	//读取视频的地址
	VideoCapture capture("F:/images/beauty.mp4");  
	Mat frame;

	while (true)
	{
		//读取视频
		capture.read(frame); 
		if (frame.empty())
		{
			break;
		}

		//图像镜像操作：左右翻转
		//flip(frame, frame, 1);

		imshow("视频播放", frame);

		//对视频调用之前的demo:色彩转换
		//colorSpace_Demo(frame);

		//控制速度
		int c = waitKey(10);

		if (c == 27) { //esc 退出应用程序
			break;
		}
	}

	//释放相机的资源
	capture.release();
}


//视频处理与保存
void QuickDemo::video_demo2(Mat &image)
{
	//读取视频的地址
	VideoCapture capture("F:/images/beauty.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);		//获取视频的宽度
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);		//获取视频的高度
	int count = capture.get(CAP_PROP_FRAME_COUNT);				//视频总的帧数												 
	double fps = capture.get(CAP_PROP_FPS);						//获取帧率

	std::cout << "宽度" << frame_width << std::endl;
	std::cout << "高度" << frame_height << std::endl;
	std::cout << "帧数" << count << std::endl;
	std::cout << "帧率" << fps << std::endl;

	//保存地址,获取图片的格式,图片的帧数,视频宽高,真
	VideoWriter writer("F:/images/test.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);


	Mat frame;
	while (true)
	{
		//读取视频
		capture.read(frame);
		if (frame.empty())
		{
			break;
		}

		//图像镜像操作：左右翻转
		//flip(frame, frame, 1);

		imshow("视频播放", frame);

		//对视频调用之前的demo:色彩转换
		//colorSpace_Demo(frame);

		//控制速度
		int c = waitKey(30);

		if (c == 27) { //esc 退出应用程序
			break;
		}
	}

	capture.release();	//释放相机的资源
	writer.release();	//释放存放的资源
}


//图像直方图
void QuickDemo::histogram_demo(Mat &image) {
	// 三通道分离
		std::vector<Mat> bgr_plane;
		//split函数被用于将一个BGR图像（即具有三个颜色通道的图像）拆分为三个单独的通道，每个通道都包含一个单通道的图像
		split(image, bgr_plane);

	// 定义参数变量
		const int channels[1] = { 0 };
		const int bins[1] = { 256 };			//存储直方图的bin（大小范围）
		float hranges[2] = { 0,255 };			//通道的强度范围
		const float* ranges[1] = { hranges };

	//存储计算得到的直方图
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// 计算Blue, Green, Red通道的直方图：计算图像的直方图
		//1~4：要计算直方图的图像,通道数,直方图的掩膜图像的通道索引,空的掩膜图像(使用掩膜计算直方图的图像区域)
		//5~8：存储计算得到的直方图,直方图的维度是一维,灰度图像的强度值范围为0到255，包含每个通道的强度范围数组
		calcHist(&bgr_plane[0], 1, channels, Mat(), b_hist, 1, bins, ranges);
		//calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
		calcHist(&bgr_plane[1], 1, channels, Mat(), g_hist, 1, bins, ranges);
		calcHist(&bgr_plane[2], 1, channels, Mat(), r_hist, 1, bins, ranges);


	// 显示直方图:创建一个大小为400x512的黑色图像（所有像素值初始化为0）
		int hist_w = 512;											//直方图的每个条形的宽度
		int hist_h = 400;											//直方图的高度
		int bin_w = cvRound((double)hist_w / bins[0]);				//每个直方图条形的宽度
			//cvRound()：返回跟参数最接近的整数值，即四舍五入
			//cvRound()函数转换为整数，以确保绘制的直线端点与像素中心对齐
		Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);		//存储创建的直方图图像
			//将数据类型设置为CV_8UC3。这表示每个像素使用8位无符号整数，并且具有三个通道（红、绿、蓝）
		
	// 对每个通道的直方图进行归一化：像素均匀分布
		//1~4：输入数组进行归一化的直方图数据,输出数组,归一化的最小值,归一化的最大值
		//5~7：归一化类型(将原始数据线性缩放到指定范围),用于存储归一化后的数据的矩阵,传递给函数作为可选的矩阵参数
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// 画曲线,将直方图数据可视化：绘制出每个通道的直方图，并将它们叠加在同一个图像上，以展示图像的颜色分布
		//方法一：嵌套
		for (int i = 1; i < bins[0]; i++) {		
			//在图像上绘制直线
				line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),		//输入图像，起点，终点
					//计算当前bin的横坐标:列表的索引是从0开始的，所以需要减去1才能对应到bin的索引
					//计算当前bin的纵坐标:b_hist.at<float>(i - 1)获取第i个bin的直方图值,，将纵坐标取反，即从直方图高度减去该值，以得到图像中对应的像素位置
					
					//在给定的代码中，hist_h是直方图的基线（即y=0的位置）是固定的
					//而cvRound(b_hist.at<float>(i - 1))则是第i个直方图的峰值
					//因此，通过减去cvRound(b_hist.at<float>(i - 1))，我们可以将直方图向下移动，使其与基线对齐
					//减去cvRound(b_hist.at<float>(i - 1))是为了将直方图向下移动一定的距离

			//定位直线起点和终点在图像中的位置			起点 终点，颜色，线宽为2个像素，线类型为8，没有像素偏移
				//通过使用Point对象，我们可以方便地指定直线的起点和终点在图像中的准确位置
				Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);	//起点，终点，蓝色

			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);	//绿色

			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);	//红色
		}
		
		//方法二：这个比较好理解
		for (int i = 0; i < 256; i++) {
			Point p01(bin_w * i, hist_h - cvRound(b_hist.at<float>(i)));
			Point p02(bin_w * i + 1, hist_h - cvRound(b_hist.at<float>(i + 1)));
			line(histImage, p01, p02, Scalar(255, 0, 0), 1, 8, 0);

			Point p11(bin_w * i, hist_h - cvRound(g_hist.at<float>(i)));
			Point p12(bin_w * i + 1, hist_h - cvRound(g_hist.at<float>(i + 1)));
			line(histImage, p11, p12, Scalar(0, 255, 0), 1, 8, 0);

			Point p21(bin_w * i, hist_h - cvRound(r_hist.at<float>(i)));
			Point p22(bin_w * i + 1, hist_h - cvRound(r_hist.at<float>(i + 1)));			
			line(histImage, p21, p22, Scalar(0, 0, 255), 1, 8, 0);

		}


	// 显示直方图
		namedWindow("直方图曲线", WINDOW_AUTOSIZE);
		imshow("直方图曲线", histImage);
}


//二维2D直方图
void QuickDemo::histogram_2d_demo(Mat &image) {
		Mat hsv,hs_hist;	//输入输出图像
		cvtColor(image, hsv, COLOR_BGR2HSV);

		int hbins = 30, sbins = 32;							//h30行,s32列
		int hist_bins[] = { hbins, sbins };					//直方图的bin数量

		float h_range[] = { 0, 180 };
		float s_range[] = { 0, 256 };
		const float* hs_ranges[] = { h_range, s_range };	//包含每个通道的取值范围的数组

	//计算一维数组的直方图
		int hs_channels[] = { 0, 1 };
		//计算一维数组的直方图:1~5:输入图像的指针，直方图的通道数，包含通道名称的数组，存储计算得到的直方图,输出图像即直方
		//					  6~10:直方图的维度-2D,直方图的bin数量,包含每个通道的取值范围的数组,是否将输入图像归一化,是否计算累积分布函数
		calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);

	//存储下面画的矩形
		double maxVal = 0;
		//这个函数的作用是在给定的数组或矩阵中寻找元素的最大值，并返回它们的位置
			//参数：计算最小值和最大值的输入数组或图像,要计算的维度或轴的参数- 0表示在第一个维度,存储计算得到的最大值,范围或边界,范围或边界
			minMaxLoc(hs_hist, 0, &maxVal, 0, 0);

		int scale = 10;
		//sbins*scale行和hbins*scale列，数据类型为CV_8UC3，即8位无符号整数（每个通道一个）
		Mat hist2d_image = Mat::zeros(sbins*scale, hbins * scale, CV_8UC3);

	//叠加矩形
		for (int h = 0; h < hbins; h++) {
			for (int s = 0; s < sbins; s++)
			{
				//位于横h，列s处的频次
				float binVal = hs_hist.at<float>(h, s);
				//颜色
				int intensity = cvRound(binVal * 255 / maxVal);

				//画矩形
				rectangle(hist2d_image,									//输入图像
						 Point(h*scale, s*scale),						//左上角的坐标
						 Point((h + 1)*scale - 1, (s + 1)*scale - 1),	//右下角的坐标
						Scalar::all(intensity),							//颜色
						-1);											//线条宽度
			}
		}

		//将灰度图像转换为彩色图像，以便更好地可视化直方图数据
		//通过对每个像素应用颜色映射来将灰度值映射为彩色值，从而将灰度图像转换为彩色图像
		//输入的2D直方图图像-通常为灰度图像,输出图像-即应用颜色映射后的图像,颜色映射类型-这里使用的是JET颜色映射
		applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);

	// 显示直方图
		imshow("二维直方图", hist2d_image);
		//imwrite("F:/images/zhifangtu.jpg", hist2d_image);
}


//直方图的均衡化
void QuickDemo::histogram_eq_demo(Mat &image) {
	Mat gray;

	//图像转换
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("灰度图像", gray);

	Mat dst;
	//输入，输出
	equalizeHist(gray, dst);
	imshow("直方图均衡化演示", dst);
}


//图像卷积操作
void QuickDemo::blur_demo(Mat &image) {
	Mat dst;

	//原始图像，卷积之后的图像，卷积的矩阵大小，卷积的起始点
	blur(image, dst, Size(15, 15), Point(-1, -1));

	imshow("图像卷积操作 图像模糊", dst);
}

//高斯模糊
void QuickDemo::gaussian_blur_demo(Mat &image) {
	Mat dst;

	//初始图像,处理后的图像,高斯矩阵大小,sigmaX在X方向上的标准偏差-控制了模糊的程度和模糊的方向
		//较大的sigmaX值会导致更宽的模糊效果，而较小的值则会产生更锐利的模糊效果
	GaussianBlur(image, dst, Size(0, 0), 15);

	imshow("高斯模糊", dst);
}

//高斯双边模糊
void QuickDemo::bifilter_demo(Mat &image) {
	Mat dst;

	//输入图像,输出图像,滤波过程中像素之间的距离,颜色空间中的标准偏差,像素空间中的标准偏差
	bilateralFilter(image, dst, 0, 100, 10);

	imshow("高斯双边模糊", dst);
}


//实时人脸检测
void QuickDemo::face_detection_demo(Mat &image) {
	//自己opencv的face_detector文件夹路径
	std::string root_dir = "D:/OpenCV/opencv/sources/samples/dnn/face_detector/";

	//读取以TensorFlow框架格式存储的网络文件
		//opencv_face_detector_uint8.pb模型		opencv_face_detector.pbtxt配置文件
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	//第一种：对本地视频进行识别
		//自己视频的地址
		VideoCapture capture("F:/images/kunkun.mp4");
	//第二种：摄像头进行人脸检测
		//VideoCapture capture(0);

	// 定义一个Mat对象，用于存储捕获到的视频帧
	Mat frame;
	while (true) {
		// 从摄像头捕获一帧视频，并将捕获到的视频帧传入frame
		capture.read(frame);

		// 如果捕获到的视频帧为空，跳出循环
		if (frame.empty()) {
			break;
		}

		//左右翻转
		//flip(frame, frame, 1);

		//DNN模块从图像创建blob的过程:从给定的图像帧创建一个blob，该blob可以用于深度学习模型的输入
			//参数：输入的图像帧，图像缩放的因子，图像裁剪的大小，图像的色彩空间转换，后面2个参数是确定图像是否需要进行翻转或旋转的标记
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);

		// 设置深度学习模型的输入：将blob作为模型的输入。blob是一个包含了图像数据的矩阵，通常用于模型的输入层
		net.setInput(blob);			

		//是OpenCV中DNN模块的一个函数，用于前向传播计算模型的输出
		Mat probs = net.forward();	//计算模型的预测结果

		//从预测结果中获取人脸检测的矩阵
		//新的Mat对象detectionMat:它的大小是probs的第二维和第三维的大小，数据类型为32位浮点数（对应于OpenCV中的CV_32F）
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
			
		// 解析检测结果，对每一个检测到的人脸进行处理
		for (int i = 0; i < detectionMat.rows; i++) {

			//从detectionMat矩阵中提取第i行、第2列的元素，并将其存储在confidence变量中
			// 获取检测到的人脸的概率（即得分），如果得分大于0.5，则认为检测到了人脸
			float confidence = detectionMat.at<float>(i, 2);	// 第三个值 得分

			if (confidence > 0.5) {
				// 因为预测来的值为[0,1]范围的数，我们还需要*原图像的宽度和长度，得到实际的位置坐标

				//从detectionMat中获取第i行、第3列的元素，也就是每个检测到的对象的置信度（confidence）
				//这是深度学习模型输出的一个值，表示模型对检测结果的信任程度
					//第1个坐标的起始位置
						//表示1个坐标或边界的起始位置的x坐标。
						int x1 = static_cast<int>(detectionMat.at<float>(i, 3)*frame.cols);	//frame.cols帧的列数
						//表示1个坐标或边界的起始位置的y坐标。
						int y1 = static_cast<int>(detectionMat.at<float>(i, 4)*frame.rows);
					//第2个坐标的起始位置
						int x2 = static_cast<int>(detectionMat.at<float>(i, 5)*frame.cols);
						int y2 = static_cast<int>(detectionMat.at<float>(i, 6)*frame.rows);

				// 在原图像上画出检测到的人脸的位置框，并用红色边框显示出来
					//左上角坐标（x1，y1）和右下角坐标（x2，y2）
					Rect box(x1, y1, x2 - x1, y2 - y1);
					//画矩形：原始图像,坐标，红色,线条宽度为2,线条类型为8,没有填充
					rectangle(frame, box, Scalar(0, 0, 255), 2, 8, 0);
			}
		}



		imshow("人脸检测演示", frame);
		int c = waitKey(1);
		if (c == 27) { 
			break;// 退出
		}
	}
	capture.release();	//释放资源
}