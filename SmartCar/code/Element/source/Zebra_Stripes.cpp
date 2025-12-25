#include "Zebra_Stripes.h"
#include <math.h>
#include <stdint.h>
// #include "image.h"
#include "element.h"
#include <chrono>
#include <thread> //Include计时器 斑马线和十字检测都要用！ 十字模块就不再Include一遍了！



// enum Flag_element {
//     NONE, CIRCLE_L, Zebra, CROSS, CIRCLE_R,
// };//元素锁标志位！！！
extern  Flag_element FLAG_ELEMENT ;
enum Zebra_times ZebraT = Zebra_0;
// 定义时间常量（单位：毫秒）
const int ZEBRA_ONCE_DURATION = 2000; // 维持Zebra_once状态4秒
const int FLAG_ZEBRA_DURATION = 2000; // 维持FLAG_ELEMENT=Zebra状态4秒
const int ZEBRA_TWICE_DURATION = 100; // 新增：维持Zebra_twice状态0.5秒后输出1
// enum Zebra_times {
//     Zebra_0, Zebra_once, Zebra_twice,
// };
// enum Zebra_times ZebraT = Zebra_0;
// 记录首次检测到斑马线的时间点
std::chrono::time_point<std::chrono::steady_clock> firstDetectionTime;
// 新增：记录第二次检测到斑马线的时间点
std::chrono::time_point<std::chrono::steady_clock> secondDetectionTime;

// 新增：标记是否已经输出过1
bool hasOutputOne = false;


void Find_Zebra_Stripes(Mat img);//函数声明！



int zs = 0;
int zebra_num = 8; // 可以根据实际情况调整
int min_stripe_width = 5; // 最小条纹宽度，可调整
int min_continuous_stripes = 5; // 最小连续条纹数量，可调整
void Find_Zebra_Stripes(Mat img,PID_Struct &motor_Left,PID_Struct &motor_Right) {
    int img_width = img.cols;
    int img_height = img.rows;

    // 限定在图像中间区域
    int start_row = (img_height / 4) * 3;//row:行
    int end_row = img_height;
    int start_col = img_width / 4;//col:列
    int end_col = img_width * 3 / 4;

    int valid_rows = 0;
    int row_count = 4; // 检查的行数

    // 定义局部变量
    static bool isInCooldown = false;
    static std::chrono::time_point<std::chrono::steady_clock> cooldownStartTime;

    // 新增：FLAG_ELEMENT=Zebra状态维持计时器
    static bool isInFlagZebraState = false;
    static std::chrono::time_point<std::chrono::steady_clock> flagZebraStartTime;

    // 检查FLAG_ELEMENT=Zebra状态维持时间
    if (isInFlagZebraState) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - flagZebraStartTime).count();

        if (elapsedTime >= FLAG_ZEBRA_DURATION) {
            // 维持时间已过，重置FLAG_ELEMENT
            isInFlagZebraState = false;
            FLAG_ELEMENT = NONE;
            cout << "FLAG_ELEMENT=Zebra状态维持时间结束，重置为NONE" << endl;
        }
    }

    // 如果处于冷却期，检查是否已过冷却时间
    if (isInCooldown) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - cooldownStartTime).count();

        if (elapsedTime >= ZEBRA_ONCE_DURATION) {
            isInCooldown = false;
            cout << "斑马线检测冷却期结束，恢复检测" << endl;
        }
        else {
            // 仍在冷却期，直接返回
            return;
        }
    }

    if (FLAG_ELEMENT == NONE) {
        for (int y = start_row; y < end_row; y += (end_row - start_row) / (row_count - 1)) {
            int stripe_count = 0;
            int current_stripe_width = 0;
            int continuous_stripes = 0;

            for (int x = start_col; x < end_col - 1; x++) {
                // 考虑一定的像素差值范围来判断条纹边界
                if (abs(gray.at<uchar>(y, x) - gray.at<uchar>(y, x + 1)) > 20) {
                    if (current_stripe_width >= min_stripe_width) {
                        stripe_count++;
                        if (++continuous_stripes >= min_continuous_stripes) {
                            break;
                        }
                    }
                    current_stripe_width = 0;
                }
                else {
                    current_stripe_width++;
                }
            }

            if (continuous_stripes >= min_continuous_stripes) {
                valid_rows++;
            }
        }

        //cout << valid_rows << std::endl;
        if (valid_rows >= row_count / 2 && FLAG_ELEMENT == NONE && ZebraT == Zebra_0) 
        {
            FLAG_ELEMENT = Zebra;
            ZebraT = Zebra_once;
            firstDetectionTime = std::chrono::steady_clock::now();
            cout << "第一次检测到斑马线！起步！" << endl;
            //Set_Servo_duty(4850);
            //motor_Run_Left(PID_Run(&motor_Left, 0, encoder_left_value()));
            //motor_Run_Right(PID_Run(&motor_Right, 0, encoder_right_value()));

            // 设置冷却期开始
            isInCooldown = true;
            cooldownStartTime = std::chrono::steady_clock::now();

            // 设置FLAG_ELEMENT=Zebra状态开始
            isInFlagZebraState = true;
            flagZebraStartTime = std::chrono::steady_clock::now();

            // 重置输出标记
            hasOutputOne = false;
        }
        else if (valid_rows >= row_count / 2 
            // && FLAG_ELEMENT == NONE 
            && ZebraT == Zebra_once && !isInCooldown) 
            {
            ZebraT = Zebra_twice;
            FLAG_ELEMENT = Zebra;
            secondDetectionTime = std::chrono::steady_clock::now(); // 记录第二次检测时间
            pwm_set_duty(SERVO_MOTOR1_PWM, 4850);
            cout << "第二次检测到斑马线！停止！";
        }
    }

    // 新增：检查Zebra_twice状态持续时间
    if (ZebraT == Zebra_twice && !hasOutputOne) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - secondDetectionTime).count();

        if (elapsedTime >= ZEBRA_TWICE_DURATION) {

            pwm_set_duty(SERVO_MOTOR1_PWM, 4850);
            motor_Run_Left(PID_Run(&motor_Left, 0, encoder_left_value()));
            // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
            motor_Run_Right(PID_Run(&motor_Right, 0, encoder_right_value()));
            
            auto stopTime = std::chrono::steady_clock::now();
            while (true)
            {
                auto currentTime = std::chrono::steady_clock::now();
                elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - stopTime).count();
                motor_Run_Left(PID_Run(&motor_Left, 0, encoder_left_value()));
            // motor_Run_Right(PID_Run(&motor_Right, -150, encoder_right_value()));
                motor_Run_Right(PID_Run(&motor_Right, 0, encoder_right_value()));
                if (elapsedTime >= 1000)
                {
                    exit(0);
                }
                
            }
            // exit(0);
            cout << "Zebra_twice状态维持时间结束,停止！！！" << endl;
            //cout << "1" << endl; // 输出1
            hasOutputOne = true; // 标记已输出，避免重复输出
        }
    }
}
