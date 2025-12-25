#include "left_circle.h"
extern uint64_t encoder_distance;
// void find_the_inflection_point_right_Down(Mat img ,vector<Point2i> right_line_points)
// {
//     /*int point_num = 0;*/
//     find_inflection_point_right_Down = false;
//     int temp_x = 0;
//     int temp_y = 0;
    
//     for (int i = 0; i < right_line_points.size()-15; i++)
//     {
//         if (right_line_points[i].x > (img.cols / 2) && (right_line_points[i].y > img.rows / 2))
//         {
//             if (abs(right_line_points[i].x- right_line_points[i + 1].x)>20
//                 &&abs(right_line_points[i].x - right_line_points[i + 2].x) > 20
//                 &&abs(right_line_points[i].x - right_line_points[i + 3].x) > 20
//                 &&abs(right_line_points[i].x - right_line_points[i + 4].x) > 20
//                 &&abs(right_line_points[i].x - right_line_points[i + 5].x) > 20
//                 )
//             {
//                 find_inflection_point_right_Down = true;
//                 cout << "找到右下" << endl;
//                 inflection_point_right_Down.x = right_line_points[i].x;
//                 inflection_point_right_Down.y = right_line_points[i].y;
//             }
//         }
//     }
// }
void find_left_circle_FLAG_1()
{
    if  (FLAG_ELEMENT == NONE
        && find_inflection_point_left_Down//找到左下角点
        && !find_inflection_point_right_Down//但未找到右下角点
        // && check_left_straight_line(left_line_points)
        // && !find_the_inflection_point_right_UP(img, right_line_points)
        && find_right_line_lost(right_line_points)
        && !find_left_line_lost(left_line_points)//右正常左丢线
        && find_center_line_long(gray) > 155
        

        )
    {
        Left_circle_Flag = LEFT_FLAG_1;
        FLAG_ELEMENT = CIRCLE_L;
    }
    // else
    // {
    //     Left_circle_Flag = LEFT_FLAG_0;
    // }
}
void find_left_circle_FLAG_2()
{
    if (//左侧丢线
        !find_left_line_lost(left_line_points) &&
        find_right_line_lost(right_line_points)//但右侧保持
        /*&& !find_inflection_point_right_Down*///未找到右下角点
        // && !find_inflection_point_right_Down//未找到右下角点
        // && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        /*&& find_left_line(left_line_points)
        && find_right_line(right_line_points)*/
        )
    {
        //circle_direction = FLAG_LEFT;
        Left_circle_Flag = LEFT_FLAG_2;
        //circle_direction = FLAG_LEFT;

    }
    // else if(encoder_distance>10000)
    // {
    //     Left_circle_Flag = LEFT_FLAG_0;
    // }
    
    else
    {
        Left_circle_Flag = LEFT_FLAG_1;
        //circle_direction = FLAG_NO;
    }
}
void find_left_circle_FLAG_3()
{
    if (find_left_line_lost(left_line_points)   //左右巡线保持
        && find_right_line_lost(right_line_points)
        )
    {
        Left_circle_Flag = LEFT_FLAG_3;
    }
    else
    {
        Left_circle_Flag = LEFT_FLAG_2;
    }
}
void find_left_circle_FLAG_4()
{
    //find_the_inflection_point_right_UP(img, right_line_points);
    if (
        !find_left_line_lost(left_line_points)//左侧再次丢线
        // && find_right_line_lost(right_line_points)//但右侧保持
        )
    {
        Left_circle_Flag = LEFT_FLAG_4;
    }
}
void find_left_circle_FLAG_5()
{
    if (/*!find_inflection_point_right_Down*///未找到右下角点
        //&& !find_inflection_point_left_Down//未找到左下角点

        //&& !find_right_line(right_line_points)//右侧再次丢线
        //&& !find_left_line(left_line_points)//但左侧丢线
        // && Slope_Calculate(left_line_points)<0
        find_center_line_long(gray) < 130
        
        )
    {
        Left_circle_Flag = LEFT_FLAG_5;
    }
}
void find_left_circle_FLAG_6()
{
    if (
        // !find_inflection_point_left_Down//未找到左下角点
         find_inflection_point_right_Down//找到右下角点
        && find_center_line_long(gray) > 130
        ||encoder_distance>160000

        )
    {
        Left_circle_Flag = LEFT_FLAG_6;
    }
}
void find_left_circle_FLAG_7()
{
    if (
        // find_center_line_long(gray) > 124
        // &&
        // !find_inflection_point_right_Down//未找到右下角点
        // find_inflection_point_right_Down//找到右下角点
        // && find_inflection_point_left_Down//找到左下角点
        // && find_center_line_long(gray)<150
        true
        )
    {
        Left_circle_Flag = LEFT_FLAG_7;
    }
}
void find_left_circle_FLAG_8()
{
    if (/*!find_inflection_point_right_Down//未找到右下角点
        && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        && find_left_line(left_line_points)*/
        find_right_line_lost(right_line_points)
        // &&check_left_straight_line(left_line_points)
        && find_center_line_long(gray) > 155
        ||encoder_distance>180000
        )
    {
        Left_circle_Flag = LEFT_FLAG_8;
    }
}
void find_left_circle_FLAG_9()
{
    if (!find_inflection_point_right_Down//未找到右下角点
        && !find_inflection_point_left_Down//未找到左下角点，就是左右巡线恢复
        && find_left_line_lost(left_line_points)
        && find_right_line_lost(right_line_points)
        && find_center_line_long(gray) > 168
        )
    {
        FLAG_ELEMENT = NONE;
        Left_circle_Flag = LEFT_FLAG_0;
    }
}

void Left_Ring_state_machine()
{
    switch (Left_circle_Flag)
    {
    case LEFT_FLAG_0:
        //find_right_circle_FLAG_1();
        find_left_circle_FLAG_1();
        break;
    case LEFT_FLAG_1:
        //find_right_circle_FLAG_2();
        change_track_line(right_line_points,-img.cols/4);
        find_left_circle_FLAG_2();
        encoder_distance=0;
        cout << "找到左圆环状态一，已将状态机置为FLAG_1" << endl;
        break;
    case LEFT_FLAG_2:
        change_track_line(right_line_points,-img.cols/4);
        find_left_circle_FLAG_3();
        //find_right_circle_FLAG_3();
        cout << "找到左圆环状态二，已将状态机置为FLAG_2" << endl;
        break;
    case LEFT_FLAG_3:

        //find_right_circle_FLAG_4();
        find_left_circle_FLAG_4();
        change_track_line(right_line_points,-img.cols/4);
        cout << "找到左圆环状态三，已将状态机置为FLAG_3" << endl;
        break;
    case LEFT_FLAG_4:
        // change_track_line(left_line_points,img.cols/20*6);
        change_track_line(left_line_points,img.cols/100*35);
        find_left_circle_FLAG_5();
        encoder_distance=0;
        cout << "找到左圆环状态四，已将状态机置为FLAG_4" << endl;
        break;
    case LEFT_FLAG_5:
        // change_track_line(left_line_points,img.cols/3);
        // change_track_line(right_line_points,-img.cols/20*7);
        // change_track_line(left_line_points,img.cols/20*6);
        change_track_line(left_line_points,img.cols/100*35);
        // change_track_line(left_line_points,img.cols/20*6);
        find_left_circle_FLAG_6();
        cout << "找到左圆环状态五，已将状态机置为FLAG_5" << endl;
        break;
    case LEFT_FLAG_6:

        // change_track_line(left_line_points,img.cols/3);
        // change_track_line(left_line_points,img.cols/20*6);
        change_track_line(left_line_points,img.cols/100*35);
        find_left_circle_FLAG_7();
        cout << "找到左圆环状态六，已将状态机置为FLAG_6" << endl;
        break;
    case LEFT_FLAG_7:
        //if (circle_direction == FLAG_RIGHT) {
        // change_track_line(left_line_points, img.cols / 3);
        change_track_line(left_line_points,img.cols/20*6);
        find_left_circle_FLAG_8();
        cout << "找到左圆环状态七，已将状态机置为FLAG_7" << endl;
        break;
    case LEFT_FLAG_8:
        // change_track_line(right_line_points, -img.cols / 4);
        change_track_line(right_line_points,-img.cols/100*33);
        find_left_circle_FLAG_9();
        //find_right_circle_FLAG_9();
        cout << "找到左圆环状态八，已将状态机置为FLAG_8" << endl;
        break;
    default:
        break;
    }
}