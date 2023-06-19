#include <opencv2/opencv.hpp>
#include <iostream>
#include "quickopencv.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	/*
	
	*/

	//普通加载
	Mat img_lena = imread("C:/Users/Tingfeng/Desktop/Xiyi.jpg");
	//namedWindow("img_lena", WINDOW_FREERATIO);
	//imshow("img_lena", img_lena);

	QuickDemo qd;
	//测试色彩空间转换
	//qd.colorSpace_Demo(img_lena);

	//测试创建Mat对象
	//qd.mat_creation_demo(img_lena);

	//测试通过数组访问像素点值
	//qd.pixel_visit_demo(img_lena);
	//测试通过指针访问像素点值
	//qd.pixel_visit_demo_pointer(img_lena);

	//测试像素点值运算
	//qd.operators_demo(img_lena);
 
	//滚动条测试
	//qd.tracking_bar_demo(img_lena);

	//键盘按键测试
	//qd.key_demo(img_lena);

	//LUT表测试
	//qd.color_style_demo(img_lena);

	//像素位运算
	//qd.bitwise_demo(img_lena);

	//通道分离和合并
	//qd.channels_demo(img_lena);

	//我自己的进一步理解mixChannel
	//qd.mixchannels_demo(img_lena);

	//理解色彩空间
	//qd.inrange_demo();

	//统计像素信息
	//qd.pixel_statistic_demo(img_lena);

	//绘制图像
	//qd.drawing_demo(img_lena);

	//随机颜色
	//qd.random_color(img_lena);

	//绘制多边形
	//qd.polyline_drawing_demo2(img_lena);

	//鼠标操作与相应
	//qd.mouse_drawing_demo(img_lena);

	//归一化
	//qd.norm_demo(img_lena);

	//resize
	//qd.scale_resize_demo(img_lena);

	//flip
	//qd.flip_demo(img_lena);

	//rotate
	//qd.rotate_demo(img_lena);

	//videl
	//qd.video_demo(img_lena);

	//video save
	//qd.video_demo2(img_lena);

	//直方图
	//qd.showHistogram(img_lena);

	//二维直方图
	//qd.histogram_2d_demo(img_lena);

	//直方图均衡化
	//qd.histogram_eq_demo(img_lena);

	//卷积blur
	//qd.blur_demo(img_lena);

	//gaosi模糊
	//qd.gaussian_blur_demo(img_lena);

	//高斯双边模糊
	//qd.bilateral_gaussian_blur_demo();

	//深度学习模型人脸检测
	//qd.face_detection_demo();

	//后期cuda学习期间的opencv代码
	qd.cuda_test(img_lena);
	
	waitKey(0);
	destroyAllWindows();
	//print
	return 0;
}
