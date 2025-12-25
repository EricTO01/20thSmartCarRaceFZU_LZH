#ifndef __check_line_status_H_
#define __check_line_status_H_
#include <opencv2/opencv.hpp>
#include "zf_common_headfile.h"
using namespace std;
using namespace cv;
extern Mat img;
extern Mat gray;
extern Point2i center_line_long_point;
int find_center_line_long(Mat img);
/*找丢线*/
/*----------------------------------------*/
bool find_left_line_lost(vector<Point2i> line_points);
bool find_right_line_lost(vector<Point2i> line_points);

#endif