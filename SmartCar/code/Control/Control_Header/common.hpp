#pragma once

// #include<windows.data.json.h>
#include <fstream>
#include <iostream>
#include <opencv2/highgui.hpp> //OpenCV终端部署
#include <opencv2/opencv.hpp>  //OpenCV终端部署

using namespace std;
using namespace cv;


void savePicture(Mat &image)
{
    // 存图
    string name = ".png";
    static int counter = 0;
    counter++;
    string img_path = "../res/samples/train/";
    name = img_path + to_string(counter) + ".jpg";
    imwrite(name, image);
}

/********检测开关**************/
bool resuen_area = false;
bool danger_area = false;
bool stopcar_area = false;
bool bridge_area = false;
/********使能开关************/
bool set_resuen_area = true;
bool set_danger_area = true;
bool set_stopcar_area = true;
bool set_bridge_area = true;

string rgb_window_name = "RGB";
string gray_window_name = "Gray";
// int display_window_init() 
// {
//   namedWindow(rgb_window_name, WINDOW_NORMAL);
//   resizeWindow(rgb_window_name, 640, 480);
//   moveWindow(rgb_window_name, 0, 0);
//   return 0;


// }