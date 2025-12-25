#ifndef __CIRCLE_H_
#define __CIRCLE_H_
#include <opencv2/opencv.hpp>
#include "element.h"
#include "track.h"
#include "find_special_points.h"
#include "check_line_status.h"
extern uint64_t encoder_distance;
using namespace std;
using namespace cv;
extern Mat img;
extern Mat gray;
/*------------------------------------------------*/
/*最远白线*/
// int find_stop_line_distance(vector<Point2i> line_points);

extern Point2i center_line_long_point;
/*----------------------------------------------*/

/*---------------------------------------------*/


// extern int serial_number_of_point_right_Down;
/*最小二乘法*/
float Slope_Calculate(vector<Point2i> line_point);
/*左线为直线时为1-1.4之间*/
void find_right_circle_FLAG_1();
void find_right_circle_FLAG_2();
void find_right_circle_FLAG_3();
void find_right_circle_FLAG_4();
void find_right_circle_FLAG_5();
void find_right_circle_FLAG_6();
void find_right_circle_FLAG_7();
void find_right_circle_FLAG_8();
void find_right_circle_FLAG_9();

void Right_ring_state_machine();

void skip_to_circle_FLAG_4();
extern bool find_inflection_point_left_Down ;
extern bool find_inflection_point_right_Down ;
extern bool find_inflection_point_right_UP ;
extern bool find_inflection_point_left_UP ;
extern Point2i inflection_point_left_Down;
extern Point2i inflection_point_right_Down;
extern enum Flag_e circle_Flag ;
extern enum Flag_element FLAG_ELEMENT;
#endif
