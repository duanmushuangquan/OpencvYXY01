#include "quickopencv.h"
#include <opencv2/dnn.hpp>



void QuickDemo::colorSpace_Demo(cv::Mat& image) {
	cv::Mat img_lena_gray, img_lena_hsv;
	cv::cvtColor(image, img_lena_gray, cv::COLOR_BGR2GRAY);
	/*
	H：0 ~ 180  
	S：饱和度
	V：明度
	*/
	

	cv::cvtColor(image, img_lena_hsv, cv::COLOR_BGR2HSV);

	imshow("img_lena_gray", img_lena_gray);
	imshow("img_lena_hsv", img_lena_hsv);

	cv::imwrite("D:/01AiShenLan/CV/img_lena_gray.png", img_lena_gray);
	cv::imwrite("D:/01AiShenLan/CV/img_lena_hsv.png", img_lena_hsv);
}

void QuickDemo::mat_creation_demo(Mat& image) {
	Mat m1, m2;

	m1 = image.clone(); //深拷贝
	image.copyTo(m2);//深拷贝

	//创建空白图像
	Mat m3;
	m3 = Mat::ones(Size(200, 200), CV_8UC3);
	m3 = cv::Scalar(127, 127, 127);

	Mat m4;
	m3.copyTo(m4);
	m4 = cv::Scalar(0, 255, 255);
	imshow("m3", m3);
	imshow("m4", m4);
}


void QuickDemo::pixel_visit_demo(Mat& image) {
	int height = image.rows;
	int width = image.cols;
	int dims = image.channels();

	cout << "当前图片宽为:" << width <<"当前图片高为:" << height << endl;
	cout << &image << endl;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (dims == 1)
			{
				//1.将image中的像素点通过at方法取出，此时像素点是字节类型uchar。
				//最终隐式转换为int类型
				int pv = image.at<uchar>(row, col);

				//2.或者可以直接通过at方法给image赋值
				//这里注意uchar的取值范围在[0-255]，后面会细讲
				image.at<uchar>(row, col) = 255 - pv;

				//同时-要注意，行、列的定义
			}
			if (dims == 3)
			{
				//3.三通道时，彩色图像也可以通过at取值，此时像素点类型为Vec3b
				//如果图像是int类型，像素点类型为Vec3i
				//如果图像是float类型，像素点类型为Vec3f
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}

	imshow("111", image);
}

void QuickDemo::pixel_visit_demo_pointer(Mat& image) {
	int height = image.rows;
	int width = image.cols;
	int dims = image.channels();

	for (int row = 0; row < height; row++)
	{
		//得到该行的第一个像素店的指针
		uchar* row_pointer = image.ptr<uchar>(row);
		for (int col = 0; col < width; col++)
		{
			if (dims == 1)
			{
				//得到改行的第一个像素点的值
				int pixel_value = *row_pointer;

				//翻转第一个像素点的值
				*(row_pointer++) = 255 - pixel_value;
			}

			if (dims == 3)
			{
				*(row_pointer++) = 255 - *row_pointer;
				*(row_pointer++) = 255 - *row_pointer;
				*(row_pointer++) = 255 - *row_pointer;
			}
		}
	}
	cout << "dims=" << dims << endl;
	imshow("11111", image);
}

void QuickDemo::operators_demo(Mat& image) {
	// 1. 加法超过255，则为255
	Mat image1 = Scalar(255, 255, 255) + image.clone();
	imshow("111", image1);

	// 2. 减法小于0，则为0
	Mat image2 = image.clone() - Scalar(255, 255, 255);
	imshow("222", image2);

	//3.除法操作
	Mat image3 = image.clone() / Scalar(2, 2, 2);
	imshow("333", image3);

	//4.乘法操作---下面这种过报错，关键在于不能乘矩阵
	//Mat image4 = image.clone() * Scalar(2, 2, 2);
	//imshow("444", image4);

	//对于乘法，opencv中有自己的函数
	Mat result;
	Mat m_temp = Mat::zeros(image.size(), image.type());
	m_temp = Scalar(2, 2, 2);
	cv::multiply(image, m_temp, result);
	imshow("result", result);


	//官方api
	Mat dst;

	//第一个、第二个参数为需要相加的两个图片。
	//第三个参数为输出的Mat
	add(image, m_temp, result);
	subtract(image, m_temp, result);
	divide(image, m_temp, result);
	multiply(image, m_temp, result);

}

//static void on_track(int b, void* userdata) {
//	Mat image = *((Mat*)userdata);
//	Mat dst = Mat::zeros(image.size(), image.type());
//	Mat m = Mat::zeros(image.size(), image.type());
//	m = Scalar(b, b, b);
//	add(image, m, dst);
//	imshow("亮度调整", dst);
//}
//
//void QuickDemo::tracking_bar_demo(Mat& image) {
//	namedWindow("亮度调整", WINDOW_AUTOSIZE);
//	int max_value = 100;
//	int lightness = 50;
//	createTrackbar("Value bar", "亮度调整", &lightness, max_value, on_track, (void*)(&image));
//	on_track(50, &image); //手动调用一次，不然第一次不会直接显示图片
//}


//本节课的核心就是addWeighted(图像1，alpha， 图像2， beta， int值，输出图像)
// 其中公式为     输出图像 = 图像1*alpha + 图像2*beta + int值
// 乘的alpha，乘法相当于调整对比度
// 加的int值，加法相当于调整图像亮度
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat m = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0.0, b, output);  //原图系数为1，增加对比度的m系数为0，增加亮度的为b
	imshow("亮度与对比度调整", output);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat m = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, output);  //原图系数为1，增加对比度的m系数为0，增加亮度的为b
	imshow("亮度与对比度调整", output);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	int lightness = -255;
	int max_value = 255;
	int contrast_value = 100;

	namedWindow("亮度与对比度调整", cv::WINDOW_AUTOSIZE);
	createTrackbar("Lightness bar", "亮度与对比度调整", &lightness, max_value, on_lightness, &image);
	setTrackbarMin("Lightness bar", "亮度与对比度调整", -255);//设置tracebar的最小值
	createTrackbar("Contrast bar", "亮度与对比度调整", &contrast_value, 200, on_contrast, &image);

	on_lightness(100, &image);
	on_contrast(100, &image);
}


void QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		char c = waitKey(10000);
		cout << "当前按键字母为："<< c << "当前按键对应数字为：" << (int)c << endl;

		if ((int)c == 27)  //对应键盘输入esc   也可以通过 c == /'33'来判断
		{
			break;
		}

		if ((int)c == 49) //对应键盘输入1
		{
			cvtColor(image, dst, COLOR_BGR2GRAY);
			imshow("键盘响应", dst);
		}

		if ((int)c == 50) //对应键盘输入2
		{
			cvtColor(image, dst, COLOR_BGR2HSV);
			imshow("键盘响应", dst);
		}

		if ((int)c == 51) //对应键盘输入3
		{
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
			imshow("键盘响应", dst);
		}
	}
}


string getString(int color) {
	switch (color)
	{
	case cv::COLORMAP_AUTUMN:
		return "COLORMAP_AUTUMN";
	case cv::COLORMAP_BONE:
		return "COLORMAP_BONE";
	case cv::COLORMAP_JET:
		return "COLORMAP_JET";
	case cv::COLORMAP_WINTER:
		return "COLORMAP_WINTER";
	case cv::COLORMAP_RAINBOW:
		return "COLORMAP_RAINBOW";
	case cv::COLORMAP_OCEAN:
		return "COLORMAP_OCEAN";
	case cv::COLORMAP_SUMMER:
		return "COLORMAP_SUMMER";
	case cv::COLORMAP_SPRING:
		return "COLORMAP_SPRING";
	case cv::COLORMAP_COOL:
		return "COLORMAP_COOL";
	case cv::COLORMAP_HSV:
		return "COLORMAP_HSV";
	case cv::COLORMAP_PINK:
		return "COLORMAP_PINK";
	case cv::COLORMAP_HOT:
		return "COLORMAP_HOT";
	case cv::COLORMAP_PARULA:
		return "COLORMAP_PARULA";
	case cv::COLORMAP_MAGMA:
		return "COLORMAP_MAGMA";
	case cv::COLORMAP_INFERNO:
		return "COLORMAP_INFERNO";
	case cv::COLORMAP_PLASMA:
		return "COLORMAP_PLASMA";
	case cv::COLORMAP_VIRIDIS:
		return "COLORMAP_VIRIDIS";
	case cv::COLORMAP_CIVIDIS:
		return "COLORMAP_CIVIDIS";
	case cv::COLORMAP_TWILIGHT:
		return "COLORMAP_TWILIGHT";
	case cv::COLORMAP_TWILIGHT_SHIFTED:
		return "COLORMAP_TWILIGHT_SHIFTED";
	case cv::COLORMAP_TURBO:
		return "COLORMAP_TURBO";
	case cv::COLORMAP_DEEPGREEN:
		return "COLORMAP_DEEPGREEN";
	default:
		return "这里发生了一些错误，enum没有找到该类型";
	}
}

void QuickDemo::color_style_demo(Mat& image) {
	//colormap数组，里面是色彩,一共18个
	int colormap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_HSV,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED,
	};

	Mat dst;
	int index = 0;
	while (true)
	{
		int c = waitKey(2000);
		if (c == 27)
		{
			break;
		}

		applyColorMap(image, dst, colormap[index % 19]);
		index++;

		putText(dst, 
			getString(colormap[index % 19]),
			Point(100, 100), 
			FONT_HERSHEY_SIMPLEX,
			1.0,
			Scalar(255, 0, 0),
			5);

		imshow("111", dst);
	}
}

void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	//Rect中是左上角坐标和大小
	//thinckness大于0时，表示绘制矩形边框
	//thinckness小于0时，表示填充这个矩形，这里是-1
	//lineType：线会产生锯齿，
		//如果不管锯齿，则叫做4临域绘制 LINE_4或者8临域绘制 LINE_8
		//LINE_AA 表示反锯齿   缺点：会降低反应速度
	//rectangle最后一位shift表示坐标点的小数点位数
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);

	imshow("m1", m1);
	imshow("m2", m2);

	Mat output;

	bitwise_xor(m1, m2, output);
	imshow("bitwise_xor", output);
}


void QuickDemo::channels_demo(Mat& image) {

	//分离三个通道，得到单独的b g r的三个单通道灰度图
	vector<Mat> mat_vector;
	split(image, mat_vector);
	imshow("b", mat_vector[0]);
	imshow("g", mat_vector[1]);
	imshow("r", mat_vector[2]);

	//得到分离后b  g  r  的三通道彩色图。即其他两个通道像素值设置为0
	Mat blue_channel3;
	vector<Mat> temp_vector = mat_vector;
	temp_vector[1] = 0;
	temp_vector[2] = 0;
	merge(temp_vector, blue_channel3);
	imshow("blue3", blue_channel3);


	//mixChannels通道混合
	//https://blog.csdn.net/qq_41741344/article/details/104370450
	//https://blog.csdn.net/w_weixiaotao/article/details/110497732
	Mat output = Mat::zeros(image.size(), image.type());
	//首先，此时image并没有修改。

	//设置两组交换通道的映射
	int from_to[] = { 0, 2, 1, 1, 2, 0 };//此六个字两两看成一对儿
	//表示将第一个图片的0通道的数据，赋值给第二个图片的2通道
	//表示将第一个图片的1通道的数据，赋值给第二个图片的1通道
	//表示将第一个图片的2通道的数据，赋值给第二个图片的0通道

	mixChannels(&image, 1, &output, 1, from_to, 3);
	//第一个参数表示第一个图片，或第一组图片
	//第二个参数表示第一个参数中有几个图片。如果有一张图片就是1，如果是3张图片为一组的图片，则为3
	//最后一个参数表示这样的通道交换有几对儿，这里是三对儿
	imshow("通道混合", output);

}

void QuickDemo::mixchannels_demo(Mat& image) {
	//此案例用来理解mixChannels
	Mat image2 = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	Scalar m = Scalar(255, 0, 0);
	image2 = m;

	imshow("111", image2);

	//此时image2是纯蓝色的图片
	//目标将第一张图片的第0个通道的数值交换给第二章照片的第2个通道，预期是纯红色
	int from_to[] = { 0, 2, 1, 1, 2, 0 };
	mixChannels(&image2, 1, &output, 1, from_to, 3);
	imshow("22", output);
}

void QuickDemo::inrange_demo() {
	//本案例实现以下几个功能
	//1.通过hsv色彩空间，提取出所有绿色，并生成绿色为白色，其他颜色为黑色的mask遮罩
	Mat image1 = imread("D:/01AiShenLan/CV/lvmu.jpg");
	imshow("image1", image1);
	Mat image_hsv = Mat::zeros(image1.size(), image1.type()); 
	cvtColor(image1, image_hsv, cv::COLOR_BGR2HSV);//转换成hsv色彩空间
	

	Mat mask = Mat::zeros(image1.size(), image1.type());
	inRange(image_hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask); //生成遮罩。绿色变为白色。hsv中绿色范围见笔记图片
	//copyTo  其中有mask参数，将图像copy到新图像时，只有mask不为0的点才能被迁移过来。为0的黑色点就不要了

	//2.创建红色背景，将人物移动到红色背景中
	Mat image_red  = Mat::zeros(image1.size(), image1.type());
	Scalar red = Scalar(0, 0, 255);
	image_red = red;

	//3.对mask取反，使得人像是白色，背景是黑色
	bitwise_not(mask, mask);
	imshow("mask", mask);

	//4.合并两张图片使用copyTo,将原图拷贝至image_red中，并使用mask做蒙版
	copyTo(image1, image_red, mask);
	imshow("red", image_red);
}

void QuickDemo::pixel_statistic_demo(Mat& image) {

	//得到均值：注意：minMaxLoc要求必须是单通道
	vector<Mat> mat_vector;
	split(image, mat_vector);
	for (int i = 0; i < mat_vector.size(); i++)
	{
		double minVal, maxVal;
		Point minLoc, maxLoc;
		minMaxLoc(mat_vector[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		cout << "当前最小像素值：" << minVal << endl;
		cout << "当前最大像素值：" << maxVal << endl;
		cout << "当前最小像素值位置：" << minLoc << endl;
		cout << "当前最大像素值位置：" << maxLoc << endl;
	}

	//得到方差标准差
	Mat mean, stddev;
	meanStdDev(image, mean, stddev, Mat());
	cout << "均值mean为："<< "/n" << mean << endl;
	cout << "标准差stddev为：" << "/n" << stddev << endl;

	//获取方差标准差的值
	cout << "第一个通道的均值：" << mean.at<double>(0) << endl;
	cout << "第二个通道的均值：" << mean.at<double>(1) << endl;
	cout << "第三个通道的均值：" << mean.at<double>(2) << endl;

	//所有通道方差为0，说明图片纯色。方差为1、2，说明图片承载的信息基本没有。或者有噪声
}

void QuickDemo::drawing_demo(Mat& image){
	//1Rect类的实例包含x  y   width  height4个属性。
	Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 100;
	rect.height = 200;
	rectangle(image, rect, Scalar(255, 0, 0), 2, LINE_8, 0);
	//注意thinckness如果是负数，表示填充矩形
	//LINE_8记得去看LINE_TYPE跟锯齿有关。

	//2画圆
	circle(image, Point(300, 300), 20, Scalar(0, 255, 0), -1, LINE_8, 0);
	//原图，中心点，半径，颜色，线宽/填充，线条类型，shift值
	imshow("rectangle", image);

	//3通过addWeight实现半透明圆
	Mat background = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());

	circle(background, Point(300, 300), 50, Scalar(0, 255, 0), -1, LINE_8, 0);
	addWeighted(background, 0.3, image, 1, 0, output);
	imshow("circle", output);
	
	//4. 绘制线
	line(image, Point(0, 0), Point(400, 400), Scalar(0, 0, 255), 2, LINE_8, 0);
	imshow("line", image);

	//5.绘制椭圆
	RotatedRect rrt;
	rrt.center = Point(100, 100);
	rrt.size = Size(100, 200);
	rrt.angle = 90.0;

	ellipse(image, rrt, Scalar(0, 255, 255), 2, 8);
	imshow("ellipse", image);
}


void QuickDemo::random_color(Mat& image) {
	Mat canvas = Mat::zeros(image.size(), image.type());
	int height = canvas.rows;
	int width = canvas.cols;
	RNG rng(12345); //
	while (true)
	{
		char c = waitKey(50);
		if ((int)c == 27)
		{
			break;
		}

		int y1 = rng.uniform(0, height); //随机生成一个0~row之间的数字
		int x1 = rng.uniform(0, width);
		int y2 = rng.uniform(0, height); 
		int x2 = rng.uniform(0, width);

		//随机生成颜色
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		//如果随机绘制指挥只一条线，需要把画布重置下
		canvas = Scalar(0, 0, 0);

		Scalar color = Scalar(b, g, r);
		line(canvas, Point(x1, y1), Point(x2, y2), color, 1, LINE_AA, 0);
		imshow("111", canvas);
	}
}

void QuickDemo::polyline_drawing_demo(Mat& image) {
	Mat canvas = Mat::zeros(Size(512, 512), image.type());

	vector<Point> point_vector;
	Point p1 = Point(0, 0);
	Point p2 = Point(100, 10);
	Point p3 = Point(500, 500);
	point_vector.push_back(p1);
	point_vector.push_back(p2);
	point_vector.push_back(p3);

	polylines(canvas, point_vector, true, Scalar(0, 0, 255), 2, 8, 0);
	//注意，polylines中，thinckness为负数是打不到填充效果的
	imshow("polylines", canvas);

	//需要使用fillPoly进行填充。但是注意线型。这里8代表LINE_8。可能会导致填充与多边形存在没填充的地方
	fillPoly(canvas, point_vector, Scalar(255, 0, 0), 8, 0);

	imshow("fillPoly", canvas);
}

void QuickDemo::polyline_drawing_demo2(Mat& image) {
	Mat canvas = Mat::zeros(Size(512, 512), image.type());

	// 1.创建多边形点的合集point_vector
	vector<Point> point_vector;
	Point p1 = Point(0, 0);
	Point p2 = Point(100, 10);
	Point p3 = Point(500, 500);
	point_vector.push_back(p1);
	point_vector.push_back(p2);
	point_vector.push_back(p3);

	// 2.创建多边形点的合集的合集
	vector<vector<Point>> contours_vector;
	contours_vector.push_back(point_vector);
	drawContours(canvas, contours_vector, 0, Scalar(0, 0, 255), -1, 8);
	//这里thinckness可以用负数代表填充
	//第二个参数代表contours轮廓的集合
	//第三个参数代表绘制contours的集合中，第几个轮廓，这里contours_vector中只有一个轮廓，所以绘制第0个

	imshow("drawContours", canvas);
}


//static string draw_func = "None";
////设置两个点，用来储存鼠标信息
//Point start_point(-1, -1);
//Point end_point;
//Point moveing_point;
//Mat temp;

//static void mouseCallBack(int event, int x, int y, int flags, void* userdata) {
//	Mat image = *((Mat*)userdata);
//	
//	if (event == EVENT_LBUTTONDOWN)
//	{
//		start_point.x = x;
//		start_point.y = y;
//		cout <<"起始坐标" << x << "/t" << y << endl;
//	}
//	else if (event == EVENT_LBUTTONUP)
//	{
//		end_point.x = x;
//		end_point.y = y;
//		cout << "结束坐标" << x << "/t" << y << endl;
//		cout << draw_func << endl;
//
//		//具体执行画图程序
//		if (draw_func == "circle")
//		{
//			int radius = sqrtf(powf((end_point.x - start_point.x), 2) + powf((end_point.y - start_point.y), 2));
//			cout << "半径为" << radius << endl;
//			cout << "起始坐标2" << x << "/t" << y << endl;
//			circle(image, start_point, radius, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("111", image);
//			start_point.x = -1;
//			start_point.y = -1;
//		}
//	}
//	else if (event == EVENT_MOUSEMOVE  && start_point.x > 0) {
//		moveing_point.x = x;
//		moveing_point.y = y;
//		if (draw_func == "circle")
//		{
//			int radius = sqrtf(powf((moveing_point.x - start_point.x), 2) + powf((moveing_point.y - start_point.y), 2));
//			temp.copyTo(image);
//			circle(image, start_point, radius, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("111", image);
//		}
//	}
//
//
//}
//
//void QuickDemo::mouse_drawing_demo(Mat& image) {
//	//保存原图
//	temp = image.clone();
//
//	//创建窗口，用于显示图片，和绘制
//	namedWindow("111", WINDOW_AUTOSIZE);
//	resizeWindow("111", Size(512, 512));
//
//	//创建鼠标事件
//	setMouseCallback("111", mouseCallBack, (void*)&image);
//
//	//创建循环，设施监控键盘事件
//	while (true)
//	{
//		char c = waitKey(0);
//		if ((int)c == 27)
//		{
//			//按下esc退出程序
//			break;
//		}
//		else if ((int)c == 99)
//		{
//			//按下c，画圆
//			cout << "c已经按下" << endl;
//			draw_func = "circle";
//		}
//	}
//}

static int draw_mode = -1;
Point start_point(-1, -1);
Point end_point;
Point move_point;
Mat temp;


static void mouseCallBack(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata); //将void*转换成 Mat*，最后解出传递的图片信息

	if (event == cv::EVENT_LBUTTONDOWN)
	{
		start_point.x = x;
		start_point.y = y;
	}
	else if (event == cv::EVENT_LBUTTONUP)
	{
		end_point.x = x;
		end_point.y = y;

		int dx = end_point.x - start_point.x;
		int dy = end_point.y - start_point.y;

		int radius = sqrtf(powf(end_point.x - start_point.x, 2) + powf(end_point.y - start_point.y, 2));

		switch (draw_mode)
		{
		case 0:
			circle(image, start_point, radius, Scalar(0, 0, 255), 2, 8, 0);
			imshow("winname", image);
			break;
		case 1:
			Rect rec;
			rec.width = abs(dx);
			rec.height = abs(dy);
			if (dx > 0)
			{
				rec.x = start_point.x;
				rec.y = start_point.y;
			}
			if (dx < 0)
			{
				rec.x = end_point.x;
				rec.y = end_point.y;
			}
			if (flags == 16)
			{
				temp.copyTo(image);
				//如果按下shift，则单独显示选框内图像。
				imshow("22", image(rec));
			}
			rectangle(image, rec, Scalar(0, 255, 0), 2, 8, 0);
			imshow("winname", image);

			break;
		}

		//抬起取消绘制
		start_point.x = -1;
		start_point.y = -1;
	}
	else if (event == cv::EVENT_MOUSEMOVE && start_point.x > 0) {
		move_point.x = x;
		move_point.y = y;

		if (draw_mode == 0) {
			int radius_temp = sqrtf(powf(move_point.x - start_point.x, 2) + powf(move_point.y - start_point.y, 2));
			temp.copyTo(image);
			circle(image, start_point, radius_temp, Scalar(0, 0, 255), 2, 8, 0);
			imshow("winname", image);
		}
		if (draw_mode == 1)
		{
			int dx_temp = move_point.x - start_point.x;
			int dy_temp = move_point.y - start_point.y;

			Rect rec;
			rec.width = abs(dx_temp);
			rec.height = abs(dy_temp);
			if (dx_temp > 0 && dy_temp > 0)
			{
				rec.x = start_point.x;
				rec.y = start_point.y;
			}
			if (dx_temp < 0 && dy_temp < 0)
			{
				rec.x = move_point.x;
				rec.y = move_point.y;
			}

			temp.copyTo(image);
			rectangle(image, rec, Scalar(0, 255, 0), 2, 8, 0);
			imshow("winname", image);
		}
	}
}


void QuickDemo::mouse_drawing_demo(Mat& image) {
	temp = image.clone();
	//创建窗口
	namedWindow("winname", WINDOW_AUTOSIZE);
	resizeWindow("winname", Size(512, 512));
	imshow("winname", image);
	//创建监听事件
	setMouseCallback("winname", mouseCallBack, (void*)&image);

	while (true)
	{
		char c = waitKey(0);
		if ((int)c == 27)
		{
			break;
		}
		if ((int)c == 99)
		{
			cout << "按键c已经按下，绘制圆形" << endl;
			draw_mode = 0;
		}
		if ((int)c == 114)
		{
			cout << "按键r已经按下，绘制矩形，如果按下shift，会将框选窗口单独提出" << endl;
			draw_mode = 1;
		}
	}
}

void QuickDemo::norm_demo(Mat& image) {
	cout << "原来的image的数据类型" << image.type() << endl;
	Mat dst;
	image.convertTo(image, CV_32F);
	normalize(image, dst, 1.0, 0.0, NORM_MINMAX);
	imshow("11", dst);
	cout << "当前的的数据类型" << dst.type() << endl;
	cout << dst << endl;

	//再转成8UC3，数据 *255

	Mat res;
	Scalar m = Scalar(255, 255, 255);
	multiply(res, m, res);
	dst.convertTo(res, CV_8UC3);
	imshow("22", dst);
	cout << "转成后res的类型" << res.type() << endl;
}

void QuickDemo::scale_resize_demo(Mat& image) {
	int h = image.rows;
	int w = image.cols;
	Mat zoomin, zoomout;
	resize(image, zoomin, Size(h / 2.0, w / 2.0), 0.0, 0.0, INTER_NEAREST);
	//倒数第二个和倒数第三个，代表在此基础上垂直方向和水平方向是否需要乘上一个缩放因子。一般不用
	resize(image, zoomout, Size(h * 1.5, w * 1.5), 0.0, 0.0, INTER_NEAREST);
	imshow("zoomin", zoomin);
	imshow("zoomout", zoomout);
}

void QuickDemo::flip_demo(Mat& image) {
	Mat dst0, dst1, dst11;
	flip(image, dst0, 0); //x为轴翻转
	flip(image, dst1, 1); //y为轴翻转
	flip(image, dst11, -1); //x,y轴翻转
	imshow("0", dst0);
	imshow("1", dst1);
	imshow("-1", dst11);
}

void QuickDemo::rotate_demo(Mat& image) {
	Mat output, M;
	int w = image.cols;
	int h = image.rows;
	Point2f center_point = Point2f(w / 2, h / 2);
	float angle = 45.0;
	float scale = 1.0; //图片放缩倍数

	//1.计算M
	M = getRotationMatrix2D(center_point, angle, scale);

	//2.计算旋转后图片Size
	double cos = M.at<double>(0, 0); //变换矩阵第0行第0列表示余弦值
	double sin = M.at<double>(0, 1); //变换矩阵第0行第1列表示正弦值

	int new_w = w * cos + h * sin;
	int new_h = w * sin + h * cos;

	//3. 改变M的(0, 2)、(1, 2)，利用平移矩阵的原理，起到平移效果
	M.at<double>(0, 2) += (new_w - w) / 2;
	M.at<double>(1, 2) += (new_h - h) / 2;

	//4.进行旋转
	warpAffine(image, output, M, Size(new_w, new_h), INTER_NEAREST, BORDER_CONSTANT, Scalar(0, 0, 255));
	cout << M << endl;

	imshow("warpAffine", output);
}

void QuickDemo::video_demo(Mat& image) {
	VideoCapture video_capture("D:/01AiShenLan/CV/drawcontours.avi");
	Mat frame;

	while (true)
	{
		video_capture.read(frame);
		if (frame.empty())
		{
			break;
		}
		flip(frame, frame, 1);
		imshow("111", frame);
		char c = waitKey(1);
		if ((int)c == 27)
		{
			break;
		}
	}

	video_capture.release();
}

void QuickDemo::video_demo2(Mat& image) {
	//1.实例化类，设置是读取摄像头还是视频
	VideoCapture capture("D:/01AiShenLan/CV/drawcontours.avi");
	
	//我们可以从capture上，得到一些属性
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	VideoWriter writer("D:/01AiShenLan/CV/CvideoSave.avi", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height),true);

	cout << "frame的宽度：" << frame_width << endl;
	cout << "frame的高度：" << frame_height << endl;
	cout << "frame的总帧数：" << count << endl;
	cout << "frame的fps：" << fps << endl;

	//2.设置变量，用来接收读取的画面
	Mat frame;
	
	//3.设置循环
	while (true)
	{
		//3.1 不断读取视频，不断存放
		capture.read(frame); //将读取到的帧放入frame中

		//3.2 如果画面为控，则break掉
		if (frame.empty())
		{
			break;
		}

		//3.3 播放视频
		imshow("111", frame);

		// 3.4 设置保存视频
		writer.write(frame);

		//退出循环的代码
		char c = waitKey(10);

		if ((int)c == 27)
		{
			break;
		}
	}

	//4.最后释放掉capture
	capture.release();
}


void QuickDemo::showHistogram(Mat& image) {
	cout << "当前图片宽高为" << image.cols << "/t" << image.rows << endl; //512, 512
	//三通道分离
	vector<Mat> bgr_plane_vector;
	split(image, bgr_plane_vector);
	//定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 }; // 灰度级别。256个级别
	float hranges[2] = { 0, 255 }; //像素直方图范围 0 - 255
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//计算Blue，green，Red通道的直方图
	//第二个参数1，表示第一个参数中传入的图片数量。这里表示输入是一张
	//第三个参数0，是所有图片通道数的和 减一。传入单张图片，如果这个图片只有一个通道。则数值为 1 - 1 = 0
		//如果传入单张图片，这个图片有三个通道，则数值为 3 - 1 = 2
		//如果传图两张图片，图片都是单通道的，则数值为 1 + 1 - 1 = 1
		//如果传图两张图片，图片都是三通道的，则数值为 3 + 3 - 1 = 5
		// 以上为自己的理解有可能不对
	//第四个参数，是掩码
	//第五个参数，是直方图输出
	//第六个参数1，是输出的直方图的维度。
	//第七个参数bins，bins是一个数组，元素数量与第六感参数一致，本案例绘制1维直方图，所以数组中只有一个元素，表示这个维度的灰度级别
	//第八个参数ranges，ranges是一个数组，元素数量与第六感参数一致，每个元素是一个长度为2的数组，表示直方图像素取值范围。
	calcHist(&bgr_plane_vector[0], 1, 0, Mat(), b_hist, 1, bins, ranges); 
	calcHist(&bgr_plane_vector[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane_vector[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//显示直方图
	int hist_w = 512;
	int hist_h = 512;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3); //相当于创建画布
	//归一化直方图数据
	//归一化后取值范围为  1.0  -  histImage.rows   为了绘制不超过图片高度。
	normalize(b_hist, b_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat()); 
	normalize(g_hist, g_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat());
	//绘制直方图曲线
	for (int i = 0; i < bins[0]; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);

		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);

		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

void QuickDemo::histogram_2d_demo(Mat& image) {
	//2D 直方图
	Mat hsv, hs_hit;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hbins = 30, sbins = 32; 
	//hsv中，h取值是0-180。我们人为设置把181为30份
	//hsv中，s取值是0-255。我们人为设置把256为32份
	int hist_bins[] = { hbins, sbins };
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 256 };
	const float* hs_ranges[] = { h_range, s_range };
	int hs_channels[] = { 0, 1 };//
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hit, 2, hist_bins, hs_ranges, true, false);

	//归一化
	double maxVal = 0;
	minMaxLoc(hs_hit, 0, &maxVal, 0, 0);
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);
	for (int h = 0; h < hbins; h++)
	{
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hs_hit.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h * scale, s * scale),
				Point((h + 1) * scale, (s + 1) * scale - 1),
				Scalar::all(intensity),
				-1);
		}
	}
	//applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
}


void QuickDemo::histogram_eq_demo(Mat& image) {
	Mat gray; //直方图均衡化必须是单通道的图像
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(gray, dst);

	imshow("gray", gray);
	imshow("dst", dst);
}

void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1));
	//第三个参数为卷积核大小
	//第四个参数为卷积核中心在哪里，默认就是Point(-1, -1)
	//第五个参数为边缘如何处理，这里没有写用的是默认的
	imshow("111", dst);
}

void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(33, 33), 15.0, 15.0);
	//注意卷积核必须是奇数
	imshow("111", dst);
}

void QuickDemo::bilateral_gaussian_blur_demo() {
	Mat image;
	Mat output;
	image= imread("D:/01AiShenLan/CV/meiyan.jpg");
	bilateralFilter(image, output, 3, 100, 10);
	imshow("111", image);
	imshow("222", output);
}

void QuickDemo::face_detection_demo() {
	// 1.读取权重文件模型
	string root_dir = "D:/opencv4.5.1/opencv/sources/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	// 2.加载视频
	//VideoCapture capture = VideoCapture("D:/01AiShenLan/CV/05JiaZhiGang/testVideoAndPicture/example_dsh.mp4");
	VideoCapture capture = VideoCapture(0);
	Mat frame;

	while (true)
	{
		capture.read(frame);
		flip(frame, frame, 1);
		if (frame.empty())
		{
			break;
		}

		//3. opencv的dnn中提供了blobFromImage，转换 转换后的Mat是浮点数的数据
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		//scalefactor  默认1.0表示图像保持在0-255的色彩空间中。  
		// Size  模型要求的输入大小。贾志刚使用的是300*300的
		// Scalar mean : 模型的均值。见D:\opencv4.5.1\opencv\sources\samples\dnn\models.yml中opencv_fd:配置
		// bool swapRB:是否交换RGB中的RB两个通道。也是看上面的models.yml文件  rgb: false表示通道为BGR，
				// opencv读进来的就是BGR，所以不用交换
		// bool crop :是否需要剪切 

		//4 输入数据
		net.setInput(blob); //输入NCHW的结果。  blob就是NCH

		//5 获取数据
		Mat probs = net.forward(); 
		//输出结果  
		// 第一个维度是图像编号 
		// 第二个维度是第几个批次第几个图
		// 第三个维度表示有多少个框
		// 第四个维度表示框的坐标(由7列表示)

		// 6 解析结果
		//	6.1 将数据结果，提取自己想要的列，从新构建一个Mat对象
		//		取probs中的最后两个维度。probs.size[2], probs.size[3]
		//		类型是浮点型。     而且需要指向probs的指针。
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//  6.2 循环解析6.1中构建的Mat对象
		for (int i = 0; i < detectionMat.rows; i++)
		{
			//第一层循环，遍历所有预测框。得到所有框的7个值。
			//	这7个值，前两个是预测框预测的 类型、以及index。第三个值是置信度。后三个值是左上角和右下角坐标
			float confidence = detectionMat.at<float>(i, 2); // 取第i个边框的 第三个值即置信度
			if (confidence > 0.5) //如果大于0.5默认为是人脸
			{
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols); 
				//at<float>(i, 3)表示左上角x坐标，因为被归一化了，乘上widtd（cols）才是真正的x1坐标
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect = Rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);

			}
		}

		imshow("人脸检测演示", frame);

		char c = waitKey(10);
		if ((int)c == 27)
		{
			break;
		}
	}
}

void QuickDemo::cuda_test(Mat& image) {
	cout << image.step.p[0] << endl;
	cout << image.size << endl;
}