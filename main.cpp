#include <opencv2/opencv.hpp>
#include <iostream>
#include "quickopencv.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	/*
	
	*/

	//��ͨ����
	Mat img_lena = imread("C:/Users/Tingfeng/Desktop/Xiyi.jpg");
	//namedWindow("img_lena", WINDOW_FREERATIO);
	//imshow("img_lena", img_lena);

	QuickDemo qd;
	//����ɫ�ʿռ�ת��
	//qd.colorSpace_Demo(img_lena);

	//���Դ���Mat����
	//qd.mat_creation_demo(img_lena);

	//����ͨ������������ص�ֵ
	//qd.pixel_visit_demo(img_lena);
	//����ͨ��ָ��������ص�ֵ
	//qd.pixel_visit_demo_pointer(img_lena);

	//�������ص�ֵ����
	//qd.operators_demo(img_lena);
 
	//����������
	//qd.tracking_bar_demo(img_lena);

	//���̰�������
	//qd.key_demo(img_lena);

	//LUT�����
	//qd.color_style_demo(img_lena);

	//����λ����
	//qd.bitwise_demo(img_lena);

	//ͨ������ͺϲ�
	//qd.channels_demo(img_lena);

	//���Լ��Ľ�һ�����mixChannel
	//qd.mixchannels_demo(img_lena);

	//���ɫ�ʿռ�
	//qd.inrange_demo();

	//ͳ��������Ϣ
	//qd.pixel_statistic_demo(img_lena);

	//����ͼ��
	//qd.drawing_demo(img_lena);

	//�����ɫ
	//qd.random_color(img_lena);

	//���ƶ����
	//qd.polyline_drawing_demo2(img_lena);

	//����������Ӧ
	//qd.mouse_drawing_demo(img_lena);

	//��һ��
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

	//ֱ��ͼ
	//qd.showHistogram(img_lena);

	//��άֱ��ͼ
	//qd.histogram_2d_demo(img_lena);

	//ֱ��ͼ���⻯
	//qd.histogram_eq_demo(img_lena);

	//���blur
	//qd.blur_demo(img_lena);

	//gaosiģ��
	//qd.gaussian_blur_demo(img_lena);

	//��˹˫��ģ��
	//qd.bilateral_gaussian_blur_demo();

	//���ѧϰģ���������
	//qd.face_detection_demo();

	//����cudaѧϰ�ڼ��opencv����
	qd.cuda_test(img_lena);
	
	waitKey(0);
	destroyAllWindows();
	//print
	return 0;
}
