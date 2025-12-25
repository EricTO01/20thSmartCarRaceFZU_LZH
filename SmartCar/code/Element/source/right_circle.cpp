#include "right_circle.h"
#include <opencv2/opencv.hpp>
// Point2i left_Down_bu_xian_begin;

// extern enum Flag_e circle_Flag = FLAG_0;
// extern enum Flag_element FLAG_ELEMENT ;
extern uint64_t encoder_distance;
Point2i center_line_long_point;
/*最小二乘法*/
void find_the_inflection_point_right_Down_Of_FLAG_7(Mat img, vector<Point2i> right_line_points)
{
    /*int point_num = 0;*/
    find_inflection_point_right_Down = false;
    int temp_x = 0;
    int temp_y = 0;

    for (int i = 0; i < right_line_points.size() - 15; i++)
    {
        if (right_line_points[i].x > (img.cols / 2) && (right_line_points[i].y > img.rows / 3))
        {
            if (right_line_points[i].x< img.cols - 15
                && right_line_points[i + 1].x >img.cols - 15//出现边界撕裂
                && right_line_points[i + 2].x > img.cols - 15
                && right_line_points[i + 3].x > img.cols - 15
                && right_line_points[i + 4].x > img.cols - 15
                // && right_line_points[i + 5].x > img.cols - 15
                )
            {
                temp_x = right_line_points[i].x;
                temp_y = right_line_points[i].y;
                for (; i < right_line_points.size() - 15; i++)
                {
                    if (right_line_points[i].x > img.cols - 15
                        && right_line_points[i + 1].x < img.cols - 15
                        && right_line_points[i + 2].x < img.cols - 15
                        && right_line_points[i + 3].x < img.cols - 15
                        && right_line_points[i + 4].x < img.cols - 15
                        // && right_line_points[i + 5].x < img.cols - 15)//边界撕裂恢复
                    )
                    {
                        find_inflection_point_right_Down = true;
                        cout << "找到右下" << endl;
                        inflection_point_right_Down.x = temp_x;
                        inflection_point_right_Down.y = temp_y;
                        break;
                    }

                }
            }


        }
    }

}

float Slope_Calculate(vector<Point2i> line_point)
{
    float xsum = 0, ysum = 0, xysum = 0, x2sum = 0;
    signed short i = 0;
    float result = 0;
    static float resultlast;
    int points_count = 0;
    for (i = 0; i < line_point.size() - 1; i++)
    {
        if (line_point[i].x < 15
            || line_point[i].y<img.rows / 2
            || line_point[i].x >img.cols - 15)
        {
            continue;
        }
        xsum += line_point[i].x;
        ysum += line_point[i].y;
        xysum += line_point[i].x * line_point[i].y;
        x2sum += line_point[i].x * line_point[i].x;
        points_count++;
    }

    if ((points_count - 0) * x2sum - xsum * xsum) // 判断除数是否为零
    {
        result = ((points_count - 0) * xysum - xsum * ysum) / ((points_count - 0) * x2sum - xsum * xsum);
        resultlast = result;
    }
    else
    {
        result = resultlast;
    }
    return result;
}


void Right_ring_state_machine()
{
    switch (circle_Flag)
    {
    case FLAG_0:
        find_right_circle_FLAG_1();
        // skip_to_circle_FLAG_4();
        break;
    case FLAG_1:
        find_right_circle_FLAG_2();
        change_track_line(left_line_points,img.cols/100*30);
        encoder_distance=0;
        //line(img, inflection_point_right_Down, point_right_circle_UP, Scalar(0, 0, 0), 5);
        cout << "找到圆环状态一，已将状态机置为FLAG_1" << endl;
        break;
    case FLAG_2:
        // line(img, Point(img.cols/8*6, img.rows), find_leftmost_point(right_line_points), Scalar(0, 0, 0), 5);
        // line(img, Point(img.cols / 15 * 2, img.rows), Point(img.cols / 15 * 5, 0), Scalar(0, 0, 0), 5);
        change_track_line(left_line_points,img.cols/100*30);
        find_right_circle_FLAG_3();
        cout << "找到圆环状态二，已将状态机置为FLAG_2" << endl;
        break;
    case FLAG_3:
        find_right_circle_FLAG_4();
        // line(img, Point(0, img.rows/8*7), Point(img.cols / 8 * 8, 0), Scalar(0, 0, 0), 5);
        // line(img, Point(img.cols / 8 * 6, img.rows), Point(img.cols / 8 * 7, 0), Scalar(0, 0, 0), 5);
        change_track_line(left_line_points,img.cols/100*30);
        cout << "找到圆环状态三，已将状态机置为FLAG_3" << endl;
        break;
    case FLAG_4:
        // line(img, Point(0,(img.rows/6)*6), point_right_circle_UP, Scalar(0, 0, 0), 5);
        // change_track_line(right_line_points, -img.cols / 10*3);
        change_track_line(right_line_points,-img.cols/100*33);
        find_right_circle_FLAG_5();
        cout << "找到圆环状态四，已将状态机置为FLAG_4" << endl;
        encoder_distance=0;
        break;
    case FLAG_5:
        // line(img, Point(0, (img.rows/8)*7) , Point(img.cols, img.rows/8*0 ), Scalar(0, 0, 0), 5);
        //  change_track_line(right_line_points, -img.cols / 3);
        // change_track_line(right_line_points, -img.cols / 20*6);
        change_track_line(right_line_points, -img.cols / 100*33);
         find_the_inflection_point_right_Down_Of_FLAG_7(img,right_line_points);
        find_right_circle_FLAG_6();
        cout << "找到圆环状态五，已将状态机置为FLAG_5" << endl;
        break;
    case FLAG_6:
        // line(img, Point(0, (img.rows/8)*7) , Point(img.cols, img.rows/8*0 ), Scalar(0, 0, 0), 5);
        // change_track_line(right_line_points, -img.cols / 3);
        // change_track_line(right_line_points, -img.cols / 20*6);
        change_track_line(right_line_points, -img.cols / 100*33);
        find_the_inflection_point_right_Down_Of_FLAG_7(img,right_line_points);
        find_right_circle_FLAG_7();
        cout << "找到圆环状态六，已将状态机置为FLAG_6" << endl;
        break;
    case FLAG_7:
        // line(img, Point(0, (img.rows/8)*7 ), Point(img.cols, img.rows/10 ), Scalar (0, 0, 0), 5);
        // change_track_line(right_line_points, -img.cols / 3);
        change_track_line(right_line_points, -img.cols / 20*6);
       // line(img, Point(img.cols/8*6, img.rows), point_right_circle_UP, Scalar(0, 0, 0), 5);
        // change_track_line(left_line_points, img.cols / 3);
        find_right_circle_FLAG_8();
        cout << "找到圆环状态七，已将状态机置为FLAG_7" << endl;
        break;
    case FLAG_8:
        // line(img, Point(img.cols/8*6, img.rows), point_right_circle_UP, Scalar(0, 0, 0), 5);
        change_track_line(left_line_points, img.cols / 4);
        find_right_circle_FLAG_9();
        cout << "找到圆环状态八，已将状态机置为FLAG_8" << endl;
        break;
    default:
        break;
    }
}
void skip_to_circle_FLAG_4()
{
    if (
        find_left_line_lost(left_line_points)
        && !find_right_line_lost(right_line_points)
        && find_center_line_long(gray) > 165

        )
    {
        circle_Flag = FLAG_4;
    }
    else
    {
        circle_Flag = FLAG_0;
    }
}
// void find_right_circle_FLAG_1()
// {
//     if (FLAG_ELEMENT == NONE
//         &&find_inflection_point_right_Down//找到右下角点
//         && !find_inflection_point_left_Down//但未找到左下角点
//         // && check_left_straight_line(left_line_points)pow 
//         // && !find_the_inflection_point_right_UP(img, right_line_points)
//         && find_left_line_lost(left_line_points)
//         && !find_right_line_lost(right_line_points)
//         && find_center_line_long(gray) > 150
//         )
//     {
//         circle_Flag = FLAG_1;
//         FLAG_ELEMENT = CIRCLE_R;
//     }
//     else
//     {
//         circle_Flag = FLAG_0;
//     }
// }
std::chrono::time_point<std::chrono::high_resolution_clock> rightCircleFlagStartTime;
bool rightCircleFlagTimerStarted = false;
const int RIGHT_CIRCLE_FLAG_DURATION_MS = 800; // 右圆环状态1维持1.2秒，可根据需要调整

void find_right_circle_FLAG_1()
{
    if (FLAG_ELEMENT == NONE
        && find_inflection_point_right_Down //找到右下角点
        && !find_inflection_point_left_Down //但未找到左下角点
        // && check_left_straight_line(left_line_points)pow 
        // && !find_the_inflection_point_right_UP(img, right_line_points)
        && find_left_line_lost(left_line_points)
        && !find_right_line_lost(right_line_points)
        && find_center_line_long(gray) > 155
        )
    {
        circle_Flag = FLAG_1;
        FLAG_ELEMENT = CIRCLE_R;

        
    }
    
}
void find_right_circle_FLAG_2()
{
    if (!find_right_line_lost(right_line_points)//右侧丢线
        && find_left_line_lost(left_line_points)//但左侧保持
        // && !find_inflection_point_right_Down//未找到右下角点
        // && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        /*&& find_left_line(left_line_points)
        && find_right_line(right_line_points)*/
        )
    {
        circle_Flag = FLAG_2;
    }
    // else if (encoder_distance>40000)
    // {
    //     circle_Flag = FLAG_0;
    // }
    
}
void find_right_circle_FLAG_3()
{
    if (find_left_line_lost(left_line_points)
        && find_right_line_lost(right_line_points)
        )
    {
        circle_Flag = FLAG_3;
    }
    else
    {
        circle_Flag = FLAG_2;
    }
}
void find_right_circle_FLAG_4()
{
    //find_the_inflection_point_right_UP(img, right_line_points);
    if (!find_right_line_lost(right_line_points)//右侧再次丢线
        // && find_left_line(left_line_points)//但左侧保持
        )
    {
        circle_Flag = FLAG_4;
    }
}
void find_right_circle_FLAG_5()
{
    if (//!find_inflection_point_right_Down//未找到右下角点
        // && !find_inflection_point_left_Down//未找到左下角点

        // && !find_right_line(right_line_points)//右侧再次丢线
        // && !find_left_line(left_line_points)//但左侧丢线
        find_center_line_long(gray) < 130
        
        // && Slope_Calculate(left_line_points)<0
        )
    {
        circle_Flag = FLAG_5;
    }
}
void find_right_circle_FLAG_6()
{
    if (
        // !find_inflection_point_right_Down//未找到右下角点
        find_inflection_point_left_Down//找到左下角点
        && find_center_line_long(gray) > 130
        ||encoder_distance>160000
        )
    {
        circle_Flag = FLAG_6;
    }
}
void find_right_circle_FLAG_7()
{
    if (//find_center_line_long(gray) > 150
        // !find_inflection_point_right_Down//未找到右下角点
        // find_inflection_point_left_Down//找到左下角点
        true
        // && find_center_line_long(gray)<150
        )
    {
        circle_Flag = FLAG_7;
    }
}
void find_right_circle_FLAG_8()
{
    if (/*!find_inflection_point_right_Down//未找到右下角点
        && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        && find_left_line(left_line_points)*/
        find_left_line_lost(left_line_points)
        // &&find_right_line(right_line_points)
        // &&check_left_straight_line(left_line_points)
        && find_center_line_long(gray) > 155
        ||encoder_distance>180000
        )
    {
        circle_Flag = FLAG_8;
    }
}
void find_right_circle_FLAG_9()
{
    if (!find_inflection_point_right_Down//未找到右下角点
        && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        && find_left_line_lost(left_line_points)
        && find_right_line_lost(right_line_points)
        && find_center_line_long(gray) > 165
        )
    {
        circle_Flag = FLAG_0;
        FLAG_ELEMENT = NONE;
    }
}
