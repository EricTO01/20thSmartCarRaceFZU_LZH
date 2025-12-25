#ifndef __TRACK_H_
#define __TRACK_H_
#include <opencv2/opencv.hpp>
#include <vector>
#include "zf_common_headfile.h"
using namespace std;
using namespace cv;
extern vector<Point2i> left_line_points;
extern vector<Point2i> right_line_points;
extern vector<Point2i> center_line_points;
extern vector<Point2i> track_line_points;
void find_left_line(Mat img, int y, int x);
void find_right_line(Mat img, int y, int x);
void change_track_line(vector <Point2i> line_points,int offset);
#endif