#include "quickopencv.h"
#include <opencv2/dnn.hpp>



void QuickDemo::colorSpace_Demo(cv::Mat& image) {
	cv::Mat img_lena_gray, img_lena_hsv;
	cv::cvtColor(image, img_lena_gray, cv::COLOR_BGR2GRAY);
	/*
	H��0 ~ 180  
	S�����Ͷ�
	V������
	*/
	

	cv::cvtColor(image, img_lena_hsv, cv::COLOR_BGR2HSV);

	imshow("img_lena_gray", img_lena_gray);
	imshow("img_lena_hsv", img_lena_hsv);

	cv::imwrite("D:/01AiShenLan/CV/img_lena_gray.png", img_lena_gray);
	cv::imwrite("D:/01AiShenLan/CV/img_lena_hsv.png", img_lena_hsv);
}

void QuickDemo::mat_creation_demo(Mat& image) {
	Mat m1, m2;

	m1 = image.clone(); //���
	image.copyTo(m2);//���

	//�����հ�ͼ��
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

	cout << "��ǰͼƬ��Ϊ:" << width <<"��ǰͼƬ��Ϊ:" << height << endl;
	cout << &image << endl;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (dims == 1)
			{
				//1.��image�е����ص�ͨ��at����ȡ������ʱ���ص����ֽ�����uchar��
				//������ʽת��Ϊint����
				int pv = image.at<uchar>(row, col);

				//2.���߿���ֱ��ͨ��at������image��ֵ
				//����ע��uchar��ȡֵ��Χ��[0-255]�������ϸ��
				image.at<uchar>(row, col) = 255 - pv;

				//ͬʱ-Ҫע�⣬�С��еĶ���
			}
			if (dims == 3)
			{
				//3.��ͨ��ʱ����ɫͼ��Ҳ����ͨ��atȡֵ����ʱ���ص�����ΪVec3b
				//���ͼ����int���ͣ����ص�����ΪVec3i
				//���ͼ����float���ͣ����ص�����ΪVec3f
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
		//�õ����еĵ�һ�����ص��ָ��
		uchar* row_pointer = image.ptr<uchar>(row);
		for (int col = 0; col < width; col++)
		{
			if (dims == 1)
			{
				//�õ����еĵ�һ�����ص��ֵ
				int pixel_value = *row_pointer;

				//��ת��һ�����ص��ֵ
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
	// 1. �ӷ�����255����Ϊ255
	Mat image1 = Scalar(255, 255, 255) + image.clone();
	imshow("111", image1);

	// 2. ����С��0����Ϊ0
	Mat image2 = image.clone() - Scalar(255, 255, 255);
	imshow("222", image2);

	//3.��������
	Mat image3 = image.clone() / Scalar(2, 2, 2);
	imshow("333", image3);

	//4.�˷�����---�������ֹ������ؼ����ڲ��ܳ˾���
	//Mat image4 = image.clone() * Scalar(2, 2, 2);
	//imshow("444", image4);

	//���ڳ˷���opencv�����Լ��ĺ���
	Mat result;
	Mat m_temp = Mat::zeros(image.size(), image.type());
	m_temp = Scalar(2, 2, 2);
	cv::multiply(image, m_temp, result);
	imshow("result", result);


	//�ٷ�api
	Mat dst;

	//��һ�����ڶ�������Ϊ��Ҫ��ӵ�����ͼƬ��
	//����������Ϊ�����Mat
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
//	imshow("���ȵ���", dst);
//}
//
//void QuickDemo::tracking_bar_demo(Mat& image) {
//	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
//	int max_value = 100;
//	int lightness = 50;
//	createTrackbar("Value bar", "���ȵ���", &lightness, max_value, on_track, (void*)(&image));
//	on_track(50, &image); //�ֶ�����һ�Σ���Ȼ��һ�β���ֱ����ʾͼƬ
//}


//���ڿεĺ��ľ���addWeighted(ͼ��1��alpha�� ͼ��2�� beta�� intֵ�����ͼ��)
// ���й�ʽΪ     ���ͼ�� = ͼ��1*alpha + ͼ��2*beta + intֵ
// �˵�alpha���˷��൱�ڵ����Աȶ�
// �ӵ�intֵ���ӷ��൱�ڵ���ͼ������
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat m = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0.0, b, output);  //ԭͼϵ��Ϊ1�����ӶԱȶȵ�mϵ��Ϊ0���������ȵ�Ϊb
	imshow("������Աȶȵ���", output);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat m = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, output);  //ԭͼϵ��Ϊ1�����ӶԱȶȵ�mϵ��Ϊ0���������ȵ�Ϊb
	imshow("������Աȶȵ���", output);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	int lightness = -255;
	int max_value = 255;
	int contrast_value = 100;

	namedWindow("������Աȶȵ���", cv::WINDOW_AUTOSIZE);
	createTrackbar("Lightness bar", "������Աȶȵ���", &lightness, max_value, on_lightness, &image);
	setTrackbarMin("Lightness bar", "������Աȶȵ���", -255);//����tracebar����Сֵ
	createTrackbar("Contrast bar", "������Աȶȵ���", &contrast_value, 200, on_contrast, &image);

	on_lightness(100, &image);
	on_contrast(100, &image);
}


void QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		char c = waitKey(10000);
		cout << "��ǰ������ĸΪ��"<< c << "��ǰ������Ӧ����Ϊ��" << (int)c << endl;

		if ((int)c == 27)  //��Ӧ��������esc   Ҳ����ͨ�� c == /'33'���ж�
		{
			break;
		}

		if ((int)c == 49) //��Ӧ��������1
		{
			cvtColor(image, dst, COLOR_BGR2GRAY);
			imshow("������Ӧ", dst);
		}

		if ((int)c == 50) //��Ӧ��������2
		{
			cvtColor(image, dst, COLOR_BGR2HSV);
			imshow("������Ӧ", dst);
		}

		if ((int)c == 51) //��Ӧ��������3
		{
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
			imshow("������Ӧ", dst);
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
		return "���﷢����һЩ����enumû���ҵ�������";
	}
}

void QuickDemo::color_style_demo(Mat& image) {
	//colormap���飬������ɫ��,һ��18��
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
	//Rect�������Ͻ�����ʹ�С
	//thinckness����0ʱ����ʾ���ƾ��α߿�
	//thincknessС��0ʱ����ʾ���������Σ�������-1
	//lineType���߻������ݣ�
		//������ܾ�ݣ������4������� LINE_4����8������� LINE_8
		//LINE_AA ��ʾ�����   ȱ�㣺�ή�ͷ�Ӧ�ٶ�
	//rectangle���һλshift��ʾ������С����λ��
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);

	imshow("m1", m1);
	imshow("m2", m2);

	Mat output;

	bitwise_xor(m1, m2, output);
	imshow("bitwise_xor", output);
}


void QuickDemo::channels_demo(Mat& image) {

	//��������ͨ�����õ�������b g r��������ͨ���Ҷ�ͼ
	vector<Mat> mat_vector;
	split(image, mat_vector);
	imshow("b", mat_vector[0]);
	imshow("g", mat_vector[1]);
	imshow("r", mat_vector[2]);

	//�õ������b  g  r  ����ͨ����ɫͼ������������ͨ������ֵ����Ϊ0
	Mat blue_channel3;
	vector<Mat> temp_vector = mat_vector;
	temp_vector[1] = 0;
	temp_vector[2] = 0;
	merge(temp_vector, blue_channel3);
	imshow("blue3", blue_channel3);


	//mixChannelsͨ�����
	//https://blog.csdn.net/qq_41741344/article/details/104370450
	//https://blog.csdn.net/w_weixiaotao/article/details/110497732
	Mat output = Mat::zeros(image.size(), image.type());
	//���ȣ���ʱimage��û���޸ġ�

	//�������齻��ͨ����ӳ��
	int from_to[] = { 0, 2, 1, 1, 2, 0 };//����������������һ�Զ�
	//��ʾ����һ��ͼƬ��0ͨ�������ݣ���ֵ���ڶ���ͼƬ��2ͨ��
	//��ʾ����һ��ͼƬ��1ͨ�������ݣ���ֵ���ڶ���ͼƬ��1ͨ��
	//��ʾ����һ��ͼƬ��2ͨ�������ݣ���ֵ���ڶ���ͼƬ��0ͨ��

	mixChannels(&image, 1, &output, 1, from_to, 3);
	//��һ��������ʾ��һ��ͼƬ�����һ��ͼƬ
	//�ڶ���������ʾ��һ���������м���ͼƬ�������һ��ͼƬ����1�������3��ͼƬΪһ���ͼƬ����Ϊ3
	//���һ��������ʾ������ͨ�������м��Զ������������Զ�
	imshow("ͨ�����", output);

}

void QuickDemo::mixchannels_demo(Mat& image) {
	//�˰����������mixChannels
	Mat image2 = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());
	Scalar m = Scalar(255, 0, 0);
	image2 = m;

	imshow("111", image2);

	//��ʱimage2�Ǵ���ɫ��ͼƬ
	//Ŀ�꽫��һ��ͼƬ�ĵ�0��ͨ������ֵ�������ڶ�����Ƭ�ĵ�2��ͨ����Ԥ���Ǵ���ɫ
	int from_to[] = { 0, 2, 1, 1, 2, 0 };
	mixChannels(&image2, 1, &output, 1, from_to, 3);
	imshow("22", output);
}

void QuickDemo::inrange_demo() {
	//������ʵ�����¼�������
	//1.ͨ��hsvɫ�ʿռ䣬��ȡ��������ɫ����������ɫΪ��ɫ��������ɫΪ��ɫ��mask����
	Mat image1 = imread("D:/01AiShenLan/CV/lvmu.jpg");
	imshow("image1", image1);
	Mat image_hsv = Mat::zeros(image1.size(), image1.type()); 
	cvtColor(image1, image_hsv, cv::COLOR_BGR2HSV);//ת����hsvɫ�ʿռ�
	

	Mat mask = Mat::zeros(image1.size(), image1.type());
	inRange(image_hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask); //�������֡���ɫ��Ϊ��ɫ��hsv����ɫ��Χ���ʼ�ͼƬ
	//copyTo  ������mask��������ͼ��copy����ͼ��ʱ��ֻ��mask��Ϊ0�ĵ���ܱ�Ǩ�ƹ�����Ϊ0�ĺ�ɫ��Ͳ�Ҫ��

	//2.������ɫ�������������ƶ�����ɫ������
	Mat image_red  = Mat::zeros(image1.size(), image1.type());
	Scalar red = Scalar(0, 0, 255);
	image_red = red;

	//3.��maskȡ����ʹ�������ǰ�ɫ�������Ǻ�ɫ
	bitwise_not(mask, mask);
	imshow("mask", mask);

	//4.�ϲ�����ͼƬʹ��copyTo,��ԭͼ������image_red�У���ʹ��mask���ɰ�
	copyTo(image1, image_red, mask);
	imshow("red", image_red);
}

void QuickDemo::pixel_statistic_demo(Mat& image) {

	//�õ���ֵ��ע�⣺minMaxLocҪ������ǵ�ͨ��
	vector<Mat> mat_vector;
	split(image, mat_vector);
	for (int i = 0; i < mat_vector.size(); i++)
	{
		double minVal, maxVal;
		Point minLoc, maxLoc;
		minMaxLoc(mat_vector[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		cout << "��ǰ��С����ֵ��" << minVal << endl;
		cout << "��ǰ�������ֵ��" << maxVal << endl;
		cout << "��ǰ��С����ֵλ�ã�" << minLoc << endl;
		cout << "��ǰ�������ֵλ�ã�" << maxLoc << endl;
	}

	//�õ������׼��
	Mat mean, stddev;
	meanStdDev(image, mean, stddev, Mat());
	cout << "��ֵmeanΪ��"<< "/n" << mean << endl;
	cout << "��׼��stddevΪ��" << "/n" << stddev << endl;

	//��ȡ�����׼���ֵ
	cout << "��һ��ͨ���ľ�ֵ��" << mean.at<double>(0) << endl;
	cout << "�ڶ���ͨ���ľ�ֵ��" << mean.at<double>(1) << endl;
	cout << "������ͨ���ľ�ֵ��" << mean.at<double>(2) << endl;

	//����ͨ������Ϊ0��˵��ͼƬ��ɫ������Ϊ1��2��˵��ͼƬ���ص���Ϣ����û�С�����������
}

void QuickDemo::drawing_demo(Mat& image){
	//1Rect���ʵ������x  y   width  height4�����ԡ�
	Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 100;
	rect.height = 200;
	rectangle(image, rect, Scalar(255, 0, 0), 2, LINE_8, 0);
	//ע��thinckness����Ǹ�������ʾ������
	//LINE_8�ǵ�ȥ��LINE_TYPE������йء�

	//2��Բ
	circle(image, Point(300, 300), 20, Scalar(0, 255, 0), -1, LINE_8, 0);
	//ԭͼ�����ĵ㣬�뾶����ɫ���߿�/��䣬�������ͣ�shiftֵ
	imshow("rectangle", image);

	//3ͨ��addWeightʵ�ְ�͸��Բ
	Mat background = Mat::zeros(image.size(), image.type());
	Mat output = Mat::zeros(image.size(), image.type());

	circle(background, Point(300, 300), 50, Scalar(0, 255, 0), -1, LINE_8, 0);
	addWeighted(background, 0.3, image, 1, 0, output);
	imshow("circle", output);
	
	//4. ������
	line(image, Point(0, 0), Point(400, 400), Scalar(0, 0, 255), 2, LINE_8, 0);
	imshow("line", image);

	//5.������Բ
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

		int y1 = rng.uniform(0, height); //�������һ��0~row֮�������
		int x1 = rng.uniform(0, width);
		int y2 = rng.uniform(0, height); 
		int x2 = rng.uniform(0, width);

		//���������ɫ
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		//����������ָ��ֻһ���ߣ���Ҫ�ѻ���������
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
	//ע�⣬polylines�У�thincknessΪ�����Ǵ򲻵����Ч����
	imshow("polylines", canvas);

	//��Ҫʹ��fillPoly������䡣����ע�����͡�����8����LINE_8�����ܻᵼ����������δ���û���ĵط�
	fillPoly(canvas, point_vector, Scalar(255, 0, 0), 8, 0);

	imshow("fillPoly", canvas);
}

void QuickDemo::polyline_drawing_demo2(Mat& image) {
	Mat canvas = Mat::zeros(Size(512, 512), image.type());

	// 1.��������ε�ĺϼ�point_vector
	vector<Point> point_vector;
	Point p1 = Point(0, 0);
	Point p2 = Point(100, 10);
	Point p3 = Point(500, 500);
	point_vector.push_back(p1);
	point_vector.push_back(p2);
	point_vector.push_back(p3);

	// 2.��������ε�ĺϼ��ĺϼ�
	vector<vector<Point>> contours_vector;
	contours_vector.push_back(point_vector);
	drawContours(canvas, contours_vector, 0, Scalar(0, 0, 255), -1, 8);
	//����thinckness�����ø����������
	//�ڶ�����������contours�����ļ���
	//�����������������contours�ļ����У��ڼ�������������contours_vector��ֻ��һ�����������Ի��Ƶ�0��

	imshow("drawContours", canvas);
}


//static string draw_func = "None";
////���������㣬�������������Ϣ
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
//		cout <<"��ʼ����" << x << "/t" << y << endl;
//	}
//	else if (event == EVENT_LBUTTONUP)
//	{
//		end_point.x = x;
//		end_point.y = y;
//		cout << "��������" << x << "/t" << y << endl;
//		cout << draw_func << endl;
//
//		//����ִ�л�ͼ����
//		if (draw_func == "circle")
//		{
//			int radius = sqrtf(powf((end_point.x - start_point.x), 2) + powf((end_point.y - start_point.y), 2));
//			cout << "�뾶Ϊ" << radius << endl;
//			cout << "��ʼ����2" << x << "/t" << y << endl;
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
//	//����ԭͼ
//	temp = image.clone();
//
//	//�������ڣ�������ʾͼƬ���ͻ���
//	namedWindow("111", WINDOW_AUTOSIZE);
//	resizeWindow("111", Size(512, 512));
//
//	//��������¼�
//	setMouseCallback("111", mouseCallBack, (void*)&image);
//
//	//����ѭ������ʩ��ؼ����¼�
//	while (true)
//	{
//		char c = waitKey(0);
//		if ((int)c == 27)
//		{
//			//����esc�˳�����
//			break;
//		}
//		else if ((int)c == 99)
//		{
//			//����c����Բ
//			cout << "c�Ѿ�����" << endl;
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
	Mat image = *((Mat*)userdata); //��void*ת���� Mat*����������ݵ�ͼƬ��Ϣ

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
				//�������shift���򵥶���ʾѡ����ͼ��
				imshow("22", image(rec));
			}
			rectangle(image, rec, Scalar(0, 255, 0), 2, 8, 0);
			imshow("winname", image);

			break;
		}

		//̧��ȡ������
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
	//��������
	namedWindow("winname", WINDOW_AUTOSIZE);
	resizeWindow("winname", Size(512, 512));
	imshow("winname", image);
	//���������¼�
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
			cout << "����c�Ѿ����£�����Բ��" << endl;
			draw_mode = 0;
		}
		if ((int)c == 114)
		{
			cout << "����r�Ѿ����£����ƾ��Σ��������shift���Ὣ��ѡ���ڵ������" << endl;
			draw_mode = 1;
		}
	}
}

void QuickDemo::norm_demo(Mat& image) {
	cout << "ԭ����image����������" << image.type() << endl;
	Mat dst;
	image.convertTo(image, CV_32F);
	normalize(image, dst, 1.0, 0.0, NORM_MINMAX);
	imshow("11", dst);
	cout << "��ǰ�ĵ���������" << dst.type() << endl;
	cout << dst << endl;

	//��ת��8UC3������ *255

	Mat res;
	Scalar m = Scalar(255, 255, 255);
	multiply(res, m, res);
	dst.convertTo(res, CV_8UC3);
	imshow("22", dst);
	cout << "ת�ɺ�res������" << res.type() << endl;
}

void QuickDemo::scale_resize_demo(Mat& image) {
	int h = image.rows;
	int w = image.cols;
	Mat zoomin, zoomout;
	resize(image, zoomin, Size(h / 2.0, w / 2.0), 0.0, 0.0, INTER_NEAREST);
	//�����ڶ����͵����������������ڴ˻����ϴ�ֱ�����ˮƽ�����Ƿ���Ҫ����һ���������ӡ�һ�㲻��
	resize(image, zoomout, Size(h * 1.5, w * 1.5), 0.0, 0.0, INTER_NEAREST);
	imshow("zoomin", zoomin);
	imshow("zoomout", zoomout);
}

void QuickDemo::flip_demo(Mat& image) {
	Mat dst0, dst1, dst11;
	flip(image, dst0, 0); //xΪ�ᷭת
	flip(image, dst1, 1); //yΪ�ᷭת
	flip(image, dst11, -1); //x,y�ᷭת
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
	float scale = 1.0; //ͼƬ��������

	//1.����M
	M = getRotationMatrix2D(center_point, angle, scale);

	//2.������ת��ͼƬSize
	double cos = M.at<double>(0, 0); //�任�����0�е�0�б�ʾ����ֵ
	double sin = M.at<double>(0, 1); //�任�����0�е�1�б�ʾ����ֵ

	int new_w = w * cos + h * sin;
	int new_h = w * sin + h * cos;

	//3. �ı�M��(0, 2)��(1, 2)������ƽ�ƾ����ԭ����ƽ��Ч��
	M.at<double>(0, 2) += (new_w - w) / 2;
	M.at<double>(1, 2) += (new_h - h) / 2;

	//4.������ת
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
	//1.ʵ�����࣬�����Ƕ�ȡ����ͷ������Ƶ
	VideoCapture capture("D:/01AiShenLan/CV/drawcontours.avi");
	
	//���ǿ��Դ�capture�ϣ��õ�һЩ����
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	VideoWriter writer("D:/01AiShenLan/CV/CvideoSave.avi", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height),true);

	cout << "frame�Ŀ�ȣ�" << frame_width << endl;
	cout << "frame�ĸ߶ȣ�" << frame_height << endl;
	cout << "frame����֡����" << count << endl;
	cout << "frame��fps��" << fps << endl;

	//2.���ñ������������ն�ȡ�Ļ���
	Mat frame;
	
	//3.����ѭ��
	while (true)
	{
		//3.1 ���϶�ȡ��Ƶ�����ϴ��
		capture.read(frame); //����ȡ����֡����frame��

		//3.2 �������Ϊ�أ���break��
		if (frame.empty())
		{
			break;
		}

		//3.3 ������Ƶ
		imshow("111", frame);

		// 3.4 ���ñ�����Ƶ
		writer.write(frame);

		//�˳�ѭ���Ĵ���
		char c = waitKey(10);

		if ((int)c == 27)
		{
			break;
		}
	}

	//4.����ͷŵ�capture
	capture.release();
}


void QuickDemo::showHistogram(Mat& image) {
	cout << "��ǰͼƬ���Ϊ" << image.cols << "/t" << image.rows << endl; //512, 512
	//��ͨ������
	vector<Mat> bgr_plane_vector;
	split(image, bgr_plane_vector);
	//�����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 }; // �Ҷȼ���256������
	float hranges[2] = { 0, 255 }; //����ֱ��ͼ��Χ 0 - 255
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//����Blue��green��Redͨ����ֱ��ͼ
	//�ڶ�������1����ʾ��һ�������д����ͼƬ�����������ʾ������һ��
	//����������0��������ͼƬͨ�����ĺ� ��һ�����뵥��ͼƬ��������ͼƬֻ��һ��ͨ��������ֵΪ 1 - 1 = 0
		//������뵥��ͼƬ�����ͼƬ������ͨ��������ֵΪ 3 - 1 = 2
		//�����ͼ����ͼƬ��ͼƬ���ǵ�ͨ���ģ�����ֵΪ 1 + 1 - 1 = 1
		//�����ͼ����ͼƬ��ͼƬ������ͨ���ģ�����ֵΪ 3 + 3 - 1 = 5
		// ����Ϊ�Լ�������п��ܲ���
	//���ĸ�������������
	//�������������ֱ��ͼ���
	//����������1���������ֱ��ͼ��ά�ȡ�
	//���߸�����bins��bins��һ�����飬Ԫ������������в���һ�£�����������1άֱ��ͼ������������ֻ��һ��Ԫ�أ���ʾ���ά�ȵĻҶȼ���
	//�ڰ˸�����ranges��ranges��һ�����飬Ԫ������������в���һ�£�ÿ��Ԫ����һ������Ϊ2�����飬��ʾֱ��ͼ����ȡֵ��Χ��
	calcHist(&bgr_plane_vector[0], 1, 0, Mat(), b_hist, 1, bins, ranges); 
	calcHist(&bgr_plane_vector[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane_vector[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 512;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3); //�൱�ڴ�������
	//��һ��ֱ��ͼ����
	//��һ����ȡֵ��ΧΪ  1.0  -  histImage.rows   Ϊ�˻��Ʋ�����ͼƬ�߶ȡ�
	normalize(b_hist, b_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat()); 
	normalize(g_hist, g_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 1.0, histImage.rows, NORM_MINMAX, -1, Mat());
	//����ֱ��ͼ����
	for (int i = 0; i < bins[0]; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);

		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);

		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

void QuickDemo::histogram_2d_demo(Mat& image) {
	//2D ֱ��ͼ
	Mat hsv, hs_hit;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hbins = 30, sbins = 32; 
	//hsv�У�hȡֵ��0-180��������Ϊ���ð�181Ϊ30��
	//hsv�У�sȡֵ��0-255��������Ϊ���ð�256Ϊ32��
	int hist_bins[] = { hbins, sbins };
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 256 };
	const float* hs_ranges[] = { h_range, s_range };
	int hs_channels[] = { 0, 1 };//
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hit, 2, hist_bins, hs_ranges, true, false);

	//��һ��
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
	Mat gray; //ֱ��ͼ���⻯�����ǵ�ͨ����ͼ��
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(gray, dst);

	imshow("gray", gray);
	imshow("dst", dst);
}

void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1));
	//����������Ϊ����˴�С
	//���ĸ�����Ϊ��������������Ĭ�Ͼ���Point(-1, -1)
	//���������Ϊ��Ե��δ�������û��д�õ���Ĭ�ϵ�
	imshow("111", dst);
}

void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(33, 33), 15.0, 15.0);
	//ע�����˱���������
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
	// 1.��ȡȨ���ļ�ģ��
	string root_dir = "D:/opencv4.5.1/opencv/sources/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	// 2.������Ƶ
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

		//3. opencv��dnn���ṩ��blobFromImage��ת�� ת�����Mat�Ǹ�����������
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		//scalefactor  Ĭ��1.0��ʾͼ�񱣳���0-255��ɫ�ʿռ��С�  
		// Size  ģ��Ҫ��������С����־��ʹ�õ���300*300��
		// Scalar mean : ģ�͵ľ�ֵ����D:\opencv4.5.1\opencv\sources\samples\dnn\models.yml��opencv_fd:����
		// bool swapRB:�Ƿ񽻻�RGB�е�RB����ͨ����Ҳ�ǿ������models.yml�ļ�  rgb: false��ʾͨ��ΪBGR��
				// opencv�������ľ���BGR�����Բ��ý���
		// bool crop :�Ƿ���Ҫ���� 

		//4 ��������
		net.setInput(blob); //����NCHW�Ľ����  blob����NCH

		//5 ��ȡ����
		Mat probs = net.forward(); 
		//������  
		// ��һ��ά����ͼ���� 
		// �ڶ���ά���ǵڼ������εڼ���ͼ
		// ������ά�ȱ�ʾ�ж��ٸ���
		// ���ĸ�ά�ȱ�ʾ�������(��7�б�ʾ)

		// 6 �������
		//	6.1 �����ݽ������ȡ�Լ���Ҫ���У����¹���һ��Mat����
		//		ȡprobs�е��������ά�ȡ�probs.size[2], probs.size[3]
		//		�����Ǹ����͡�     ������Ҫָ��probs��ָ�롣
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//  6.2 ѭ������6.1�й�����Mat����
		for (int i = 0; i < detectionMat.rows; i++)
		{
			//��һ��ѭ������������Ԥ��򡣵õ����п��7��ֵ��
			//	��7��ֵ��ǰ������Ԥ���Ԥ��� ���͡��Լ�index��������ֵ�����Ŷȡ�������ֵ�����ϽǺ����½�����
			float confidence = detectionMat.at<float>(i, 2); // ȡ��i���߿�� ������ֵ�����Ŷ�
			if (confidence > 0.5) //�������0.5Ĭ��Ϊ������
			{
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols); 
				//at<float>(i, 3)��ʾ���Ͻ�x���꣬��Ϊ����һ���ˣ�����widtd��cols������������x1����
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect = Rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);

			}
		}

		imshow("���������ʾ", frame);

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