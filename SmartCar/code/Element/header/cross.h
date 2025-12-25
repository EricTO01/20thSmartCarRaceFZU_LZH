#ifndef __CROSS_H_
#define __CROSS_H_
#include "element.h"
#include <opencv2/opencv.hpp>
#include "check_line_status.h"
#include "find_special_points.h"
#include "check_line_status.h"
#include "track.h"
using namespace std;
using namespace cv;
// std::chrono::time_point<std::chrono::steady_clock> crossDetectTime; // 记录首次检测到十字的时间
// bool crossFirstDetected = false; // 标记是否首次检测到十字
// int crossDetectionDuration = 4000; // 检测到十字后的保持时间（毫秒）
typedef unsigned char uint8;

void CrossCheck_IN();//GGGGGGGGGG 元素锁纯十字检测，无状态机

extern Point2i point_right_UP;

extern Point2i point_left_UP;
#endif