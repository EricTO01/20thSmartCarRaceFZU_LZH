#ifndef __find_special_points_H_
#define __find_special_points_H_
#include <opencv2/opencv.hpp>
#include "track.h"
using namespace cv;
using namespace std;
/*-------------------------------------------------*/
//找拐点
extern bool find_inflection_point_left_Down;
extern bool find_inflection_point_right_Down;

extern Point2i inflection_point_left_Down;
extern Point2i inflection_point_right_Down;
extern Point2i left_Down_bu_xian_begin;

extern Point2i point_right_circle_UP;
extern bool find_point_right_circle_UP;

// extern vector <Point2i> left_line_points;
// extern vector<Point2i> right_line_points;

void find_the_inflection_point_left_Down(Mat img, vector<Point2i> left_line_points);
void find_the_inflection_point_right_Down(Mat img, vector<Point2i> right_line_points);

bool find_the_inflection_point_left_UP(Mat img, vector<Point2i> left_line_points);
bool find_the_inflection_point_right_UP(Mat img,vector<Point2i> right_line_points);
// bool find_the_inflection_point_right_UP(Mat img, vector<Point2i> right_line_points);
#endif