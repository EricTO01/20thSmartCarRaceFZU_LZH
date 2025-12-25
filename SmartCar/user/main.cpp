#include<iostream>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <string>
#include "zf_common_headfile.h"
#include "motor.h"
#include "PID.h"
#include "brushless.h"
#include "Fuzzy_PID.h"
#include "servo_control.h"
#include "encoder.h"
#include "right_circle.h"
#include "Zebra_Stripes.h"
#include "button.h"
#include "beep.h"
#include "track.h"
#include "find_special_points.h"
#include "check_line_status.h"
#include "ui.h"
#include "left_circle.h"
#include "cross.h"
//#include "PID.h"
//#include "brushless.h"
using namespace std;
using namespace cv;

enum Left_Flag_e Left_circle_Flag = LEFT_FLAG_0;
enum Flag_e circle_Flag = FLAG_0;
enum Flag_element FLAG_ELEMENT = NONE;
enum Road_Type road_type = None;//偏差值固定权
extern  Zebra_times ZebraT ;
extern  Flag_c CROSS_FLAG ;
Mat img;
Mat gray;

//bool lost_line_right(vector<Point2i> right_line_points);

PID_Struct servoPID;
static PID_Struct motor_Left;
static PID_Struct motor_Right;

float last_error = 0;
float error_temp = 0;
float offset = 0;
int add_offset=0;


/*电机速度*/
// uint16 G_straight_line_speed=230;
// uint16 G_curve_line_speed=200;
// uint16 G_circle_speed=150;

// uint16 G_straight_line_speed=320;
// uint16 G_curve_line_speed=300;
// uint16 G_circle_speed=250;

// uint16 G_straight_line_speed=410;
// uint16 G_curve_line_speed=290;
// uint16 G_circle_speed=330;


uint16 G_straight_line_speed=450;
uint16 G_curve_line_speed=330;
uint16 G_circle_speed=300;

/*差和比阈值*/
uint16 G_cha_he_bi_threshold=13;

/*电机PID*/
float G_motor_Kp=12.5;
float G_motor_Ki=9;
float G_motor_Kd=20;


// float G_cha_su_K=1.5;
// float G_cha_su_K=1.65;
// float G_cha_su_K=1.1;
float G_cha_su_K=1.1;
// enum Flag_element FLAG_ELEMENT;

extern bool ui_state;//注意矢山
extern uint8 func_index;

void sigint_handler(int signum)
{
    printf("收到Ctrl+C，程序即将退出\n");
    exit(0);
}

void cleanup()
{
   printf("程序异常退出，执行清理操作\n");
   // 关闭电机
   pwm_set_duty(MOTOR1_PWM, 0);
   pwm_set_duty(MOTOR2_PWM, 0);
   pwm_set_duty(PWM_1, 0);
   pwm_set_duty(PWM_2, 0);
   pwm_set_duty(SERVO_MOTOR1_PWM, 4850);
}
float calculateOffset(const vector<Point2i>& track_line_points, int img_width, string road_type) {
    if (track_line_points.empty()) return 0.0f;

    // 1. 根据道路类型选择权重
    vector<float> weights;
    if (road_type == "straight") {
        weights = { 0.1, 0.3, 0.6 }; // 直线：远端权重高
    }
    else { // "curve"
        weights = { 0.2, 0.6, 0.2 }; // 弯道：中端权重高
    }

    // 2. 分段计算近、中、远端的平均偏差
    int n = track_line_points.size();
    vector<pair<int, int>> segments = {
        {0, n / 3},           // 近端：0~33%
        {n / 3, 2 * n / 3},   // 中端：33%~66%
        {2 * n / 3, n}        // 远端：66%~100%
    };

    float offset = 0.0f;
    for (int i = 0; i < 3; i++) {
        int start = segments[i].first;
        int end = segments[i].second;
        if (start >= end) continue;

        // 计算当前段的平均x偏差
        float sum = 0.0f;
        for (int j = start; j < end; j++) {
            sum += track_line_points[j].x - img_width / 2;
        }
        float segment_offset = sum / (end - start);

        // 3. 加权累加
        offset += segment_offset * weights[i];
    }

    return offset;
}
int main(int argc, char** argv) {
    
    VideoCapture cap;

    // 2.打开默认相机;
    cap.open(0);

    // 3.判断相机是否打开成功;
    if (!cap.isOpened())
        return -1;

    // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    // double exposureTime = -7; 
    // if (!cap.set(cv::CAP_PROP_EXPOSURE, exposureTime)) {
    //     std::cerr << "无法设置曝光时间！" << std::endl;
    //     return -1;
    // }

    /*-----------------------------------------------------------------------------*/
    atexit(cleanup);
    // 注册SIGINT信号的处理函数
    signal(SIGINT, sigint_handler);
    encoder_Init();
    Servo_Init();
    ips200_init("/dev/fb0");
    //// PID_Init(&motor_Left, 0.15, 0.003, 0.005, 300, 40, -40);
    //// PID_Init(&motor_Right, 0.15, 0.003, 0.005, 300, 40, -40);
    // PID_Init(&motor_Left, 10.5, 0.5, 0, 15000, 5000, -5000);
    // PID_Init(&motor_Right, 10.5, 0.5, 0, 15000, 5000, -5000);
    // PID_Init(&motor_Left, 18.5, 8, 2, 15000, 8000, -8000);
    // PID_Init(&motor_Right, 18.5, 8, 2, 15000, 8000, -8000);
    // PID_Init(&motor_Left, 15.5, 5, 2, 15000, 8000, -8000);
    // PID_Init(&motor_Right, 15.5, 5, 2, 15000, 8000, -8000);
    
    // PID_Init(&motor_Left, 18.5, 8, 0, 15000, 6000, -8000);
    // PID_Init(&motor_Right, 18.5, 8, 0, 15000, 6000, -8000);
    /*-----------------------------------------------------------------------------*/



    // while (true)
    // {
    //     cap >> img;
    //     // if(!gpio_get_level(KEY_1))
    //     // {

    //     // }
    //     if(!gpio_get_level(KEY_0))
    //     {
    //         beep_on();
    //         system_delay_ms(2000);
    //         beep_off();
    //         cout << "发车" << endl;
    //         break;
    //     }
        
    // }

    the_ui:ui();
    PID_Init(&motor_Left, G_motor_Kp, G_motor_Ki, G_motor_Kd, 8000, 6000, -6000);
    PID_Init(&motor_Right, G_motor_Kp, G_motor_Ki, G_motor_Kd, 8000, 6000, -6000);
    while (true)
    {
        double tickStart = (double)getTickCount();
        if (gpio_get_level(SWITCH_0)==0)
        {
            brushless_run(1000);
        }
        else
        {
            brushless_run(0);
        }
        
        
        

        if (key0_Press_down())
        {
            pwm_set_duty(MOTOR1_PWM, 0);
            pwm_set_duty(MOTOR2_PWM, 0);
            pwm_set_duty(PWM_1, 0);
            pwm_set_duty(PWM_2, 0);
            pwm_set_duty(SERVO_MOTOR1_PWM, 4850);
            ui_state=true;
            func_index=0;

            Left_circle_Flag = LEFT_FLAG_0;

            circle_Flag = FLAG_0;
            FLAG_ELEMENT = NONE;
            // Find_Zebra=Zebra_0;
            PID_Init(&motor_Left, 0, 0, 0, 8000, 4000, -4000);
            PID_Init(&motor_Right, 0, 0, 0, 8000, 4000, -4000);
            // motor_Run_Left(PID_Run(&motor_Left, 0, encoder_left_value()));
            // // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
            // motor_Run_Right(PID_Run(&motor_Right, 0, encoder_right_value()));
            goto the_ui;
        }
        

        cap >> img;
        if (img.empty()) {
            cerr << "Error: Captured empty frame!" << endl;
            continue; // 跳过后续处理
        }
        

        
        // find_center_line_long(gray);
        cvtColor(img, gray, COLOR_BGR2GRAY);
        // Canny(gray, gray, 80, 240, 3);

        

        // double mean_val = mean(gray)[0];
        // // Canny(gray, gray, 0.3 * mean_val, 0.6 * mean_val, 3);
        // Canny(gray, gray, 0.4 * mean_val, 0.95 * mean_val, 3);
        // Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

        // double mean_val = mean(gray)[0];
        // Canny(gray, gray, 0.4 * mean_val, 0.95 * mean_val, 3);
        // Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

        // // 执行膨胀操作
        // Mat dst;
        // dilate(gray, gray, kernel, Point(-1, -1), 2);

        // Find_Zebra_Stripes(img);

        int start_col = img.cols / 2 - 1;

        

        left_line_points.clear();
        right_line_points.clear();
        center_line_points.clear();
        // cout<<"此处已执行"<<endl;
        // cout << "运行到1" << endl;
        /*---------------------------------------------------------------------*/
        //找线
        for (int row = img.rows - 10; row > 50; row--)
        {
            if (row != img.rows - 1 && center_line_points.size() > 0)
            {
                start_col = (int)(0.4 * center_line_points.back().x + 0.3 * start_col + 0.1 * img.cols);
            }
            find_left_line(gray, row, start_col);
            find_right_line(gray, row, start_col);
            if (left_line_points.size() > 0 && right_line_points.size() > 0) {
                center_line_points.push_back(Point2i((left_line_points.back().x + right_line_points.back().x) / 2, (left_line_points.back().y + right_line_points.back().y) / 2));
            }
        }
        

        

        //白线
        /*----------------------------------------------------------------------------------------*/
        //角点
        find_the_inflection_point_left_Down(img, left_line_points);
        // find_the_inflection_point_right_UP(img, right_line_points);
        find_the_inflection_point_right_Down(img, right_line_points);
        /*-------------------------------------------------------------------------------------------*/

        Right_ring_state_machine();
        Left_Ring_state_machine();
        CrossCheck_IN();
        Find_Zebra_Stripes(img,motor_Left,motor_Right);

        left_line_points.clear();
        right_line_points.clear();
        center_line_points.clear();
        /*---------------------------------------------------------------------*/
//找线
        for (int row = img.rows - 10; row > 50; row--)
        {
            if (row != img.rows - 1 && center_line_points.size() > 0)
            {
                start_col = (int)(0.4 * center_line_points.back().x + 0.3 * start_col + 0.1 * img.cols);
            }
            find_left_line(gray, row, start_col);
            find_right_line(gray, row, start_col);
            if (left_line_points.size() > 0 && right_line_points.size() > 0) {
                center_line_points.push_back(Point2i((left_line_points.back().x + right_line_points.back().x) / 2, (left_line_points.back().y + right_line_points.back().y) / 2));
            }
        }
        
        // find_ZebraLine_state(gray,motor_Left,motor_Right);

        if (circle_Flag==FLAG_0
            &&Left_circle_Flag==LEFT_FLAG_0
            && CROSS_FLAG ==FLAGc_0)
        {
            track_line_points = center_line_points;
        }
        // offset=center_line_points[center_line_points.size() / 9*4].x- img.cols / 2;
        // offset=center_line_points[center_line_points.size() / 10*6].x- img.cols / 2;
        // cout<<"encoder_distance;" <<encoder_distance<<endl;
        // if (Find_Zebra==Zebra_0)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*3].x- img.cols / 2;
        // }
        // if (Find_Zebra==Zebra_1)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*1].x- img.cols / 2;
        // }
        //  if (Find_Zebra==Zebra_2)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*4].x- img.cols / 2;
        // }
        // if (Find_Zebra==Zebra_3)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*1].x- img.cols / 2;
        // }
        // if (Find_Zebra==Zebra_4)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*3].x- img.cols / 2;
        // }
        if (ZebraT != Zebra_twice)
        {
            //offset=track_line_points[track_line_points.size() / 100*75].x- img.cols / 2;
            offset = calculateOffset(track_line_points, 320, road_type);
        }
        else if(ZebraT == Zebra_twice)
        {
            offset=track_line_points[track_line_points.size() / 100*80].x- img.cols / 2;/* code */
        }
        
        
        // offset=track_line_points[track_line_points.size() / 100*65].x- img.cols / 2;
        // if (CROSS_FLAG==FLAGc_3)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*7].x- img.cols / 2;
        // }
        // if (CROSS_FLAG==FLAGc_3)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*7].x- img.cols / 2;
        // }
        // if (CROSS_FLAG==FLAGc_3)
        // {
        //     offset=track_line_points[track_line_points.size() / 10*7].x- img.cols / 2;
        // }
        // cout<<"offset:"<<offset*1.8<<endl;
        Set_Servo_duty(4850 + pid_servo());
        last_error = offset;
        /*-----------------------------------------------------------------------------*/
        // float k=2;
        // float k=1.3;
        // float k=1.8;
        if(find_center_line_long(gray) > 170
            &&circle_Flag==FLAG_0
            &&Left_circle_Flag==LEFT_FLAG_0)
        {

            motor_Run_Left(PID_Run(&motor_Left, G_straight_line_speed, encoder_left_value()));
            // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
            motor_Run_Right(PID_Run(&motor_Right, G_straight_line_speed, encoder_right_value()));
        }
        if(find_center_line_long(gray) <= 170
            &&circle_Flag==FLAG_0
            &&Left_circle_Flag==LEFT_FLAG_0)//识别成弯道！
        {
            road_type = Curve;
            //右转为正
            if(offset>0)
            {
                motor_Run_Left(PID_Run(&motor_Left, G_curve_line_speed+offset*G_cha_su_K, encoder_left_value()));
                // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
                // motor_Run_Right(PID_Run(&motor_Right, 250-offset*k, encoder_right_value()));
                motor_Run_Right(PID_Run(&motor_Right, G_curve_line_speed-offset*G_cha_su_K, encoder_right_value()));
            }
            else
            {
                motor_Run_Left(PID_Run(&motor_Left, G_curve_line_speed+offset*G_cha_su_K, encoder_left_value()));
                // motor_Run_Left(PID_Run(&motor_Left, 250+offset*k, encoder_left_value()));
                // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
                motor_Run_Right(PID_Run(&motor_Right, G_curve_line_speed-offset*G_cha_su_K, encoder_right_value()));
            }
            
                    
        }
        if(circle_Flag!=FLAG_0||Left_circle_Flag!=LEFT_FLAG_0)
        {
                        //右转为正
            if(offset>0)
            {
                motor_Run_Left(PID_Run(&motor_Left, G_circle_speed+offset*G_cha_su_K, encoder_left_value()));
                // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
                // motor_Run_Right(PID_Run(&motor_Right, 180-offset*k, encoder_right_value()));
                motor_Run_Right(PID_Run(&motor_Right, G_circle_speed-offset*G_cha_su_K, encoder_right_value()));
            }
            else
            {
                motor_Run_Left(PID_Run(&motor_Left, G_circle_speed+offset*G_cha_su_K, encoder_left_value()));
                // motor_Run_Left(PID_Run(&motor_Left, 180+offset*k, encoder_left_value()));
                // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
                motor_Run_Right(PID_Run(&motor_Right, G_circle_speed-offset*G_cha_su_K, encoder_right_value()));
            }
        
            // motor_Run_Left(PID_Run(&motor_Left, 190, encoder_left_value()));
            // // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
            // motor_Run_Right(PID_Run(&motor_Right, 190, encoder_right_value()));
                    
        }
        /*-----------------------------------------------------------------------------*/
        double tickEnd = (double)getTickCount();
        cout << to_string((int)(((tickEnd - tickStart) / (getTickFrequency())) * 1000)) << endl;
    }
    return 0;
}

