#ifndef __Zebra_Stripes_H_
#define __Zebra_Stripes_H_
#include <opencv2/opencv.hpp>
#include "element.h"
#include "PID.h"
#include "encoder.h"
#include "motor.h"
#include "servo_control.h"
#include "track.h"
#include <math.h>
#include <stdint.h>
#include "check_line_status.h"
// #include "image.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace cv;
extern Mat img;
extern Mat gray;
// extern PID_Struct motor_Left;
// extern PID_Struct motor_Right;
bool detectZebraLine(Mat& frame, int scan_line_count ) ;
void find_ZebraLine_state(Mat& frame,PID_Struct &motor_Left,PID_Struct &motor_Right);
void Find_Zebra_Stripes(Mat img,PID_Struct &motor_Left,PID_Struct &motor_Right);
// void Find_Zebra_Stripes(Mat img);

#endif