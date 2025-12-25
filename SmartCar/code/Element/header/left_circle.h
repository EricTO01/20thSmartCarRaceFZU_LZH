#ifndef __LEFT_CIRCLE_H_
#define __LEFT_CIRCLE_H_
#include <opencv2/opencv.hpp>
#include "check_line_status.h"
#include "track.h"
#include "element.h"
#include "find_special_points.h"
using namespace std;
using namespace cv;

extern Mat img;
extern Mat gray;

extern Point2i center_line_long_point;

void find_left_circle_FLAG_1();
void find_left_circle_FLAG_2();
void find_left_circle_FLAG_3();
void find_left_circle_FLAG_4();
void find_left_circle_FLAG_5();
void find_left_circle_FLAG_6();
void find_left_circle_FLAG_7();
void find_left_circle_FLAG_8();
void find_left_circle_FLAG_9();
extern bool find_inflection_point_left_Down ;
extern bool find_inflection_point_right_Down ;
extern bool find_inflection_point_right_UP ;
extern bool find_inflection_point_left_UP ;
extern Point2i inflection_point_left_Down;
extern Point2i inflection_point_right_Down;
extern enum Flag_e circle_Flag ;
extern enum Flag_element FLAG_ELEMENT;
extern enum Left_Flag_e Left_circle_Flag ;
void Left_Ring_state_machine();

#endif