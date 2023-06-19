#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class QuickDemo {
public:
	void colorSpace_Demo(cv::Mat& image);
	void mat_creation_demo(Mat& image);
	void pixel_visit_demo(Mat& image);
	void pixel_visit_demo_pointer(Mat& image);
	void operators_demo(Mat& image);
	void tracking_bar_demo(Mat& image);
	void key_demo(Mat& image);
	void color_style_demo(Mat& image);
	void bitwise_demo(Mat& image);
	void channels_demo(Mat& image);
	void mixchannels_demo(Mat& image);
	void inrange_demo();
	void pixel_statistic_demo(Mat& image);
	void drawing_demo(Mat& image);
	void random_color(Mat& image);
	void polyline_drawing_demo(Mat& image);
	void polyline_drawing_demo2(Mat& image);
	void mouse_drawing_demo(Mat& image);
	void norm_demo(Mat& image);
	void scale_resize_demo(Mat& image);
	void flip_demo(Mat& image);
	void rotate_demo(Mat& image);
	void video_demo(Mat& image);
	void video_demo2(Mat& image);
	void zhifangtu_demo(Mat& image);
	void showHistogram(Mat& image);
	void histogram_2d_demo(Mat& image);
	void histogram_eq_demo(Mat& image);
	void blur_demo(Mat& image);
	void gaussian_blur_demo(Mat& image);
	void bilateral_gaussian_blur_demo();
	void face_detection_demo();

	void cuda_test(Mat& image);
};

