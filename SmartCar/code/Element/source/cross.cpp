#include "cross.h"
#include "right_circle.h"

extern Flag_element FLAG_ELEMENT ;
// extern enum Flag_c CROSS_FLAG;
enum Flag_c CROSS_FLAG = FLAGc_0;
extern float offset;

void find_cross_flag1() {
    if (
        // (find_inflection_point_right_Down || find_inflection_point_left_Down)
        !find_right_line_lost(right_line_points)
        && !find_left_line_lost(left_line_points)
        && FLAG_ELEMENT == NONE
        ) {
        //cout << "Crossflag1" << endl;
        //putText(img, "Cross_Flag1", Point(50, 40), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
        FLAG_ELEMENT = CROSS; //十字状态1：找到左下角点和右下角点并且最长中线大于170 (待调整)
        CROSS_FLAG = FLAGc_1;
    }
    else if(find_inflection_point_left_Down&&!find_inflection_point_right_Down&&!find_right_line_lost(right_line_points)){
        FLAG_ELEMENT=CROSS;
        CROSS_FLAG=FLAGr_Left1;
    }
    else if(find_inflection_point_right_Down&&!find_inflection_point_left_Down&&!find_left_line_lost(left_line_points)){
        FLAG_ELEMENT=CROSS;
        CROSS_FLAG=FLAGr_Right1;
    }
    //else {
    //    CROSS_FLAG = FLAGc_0;
    //    FLAG_ELEMENT = NONE;
    //}
}
void find_cross_flag2() {
    if (find_center_line_long(gray) < 110 && CROSS_FLAG == FLAGc_1 && FLAG_ELEMENT == CROSS) 
    {
        CROSS_FLAG = FLAGc_2; //十字状态2：找到左上角和右上角点
        //cout << "Crossflag2" << endl;

    }
    else {
        CROSS_FLAG = FLAGc_1;
    }
}

void find_cross_flag3() {
    if (find_inflection_point_left_Down && find_inflection_point_right_Down && CROSS_FLAG == FLAGc_2 && find_center_line_long(gray) > 150 && FLAG_ELEMENT == CROSS
        )
     {
        CROSS_FLAG = FLAGc_3; //3再次找到左右下角点且找到最长中线值170(待改！!!)--状态4
        //putText(img, "Cross_Flag3", Point(130, 40), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
    }
    else if (find_inflection_point_left_Down && !find_right_line_lost(right_line_points) && CROSS_FLAG == FLAGc_2
            &&find_center_line_long(gray) > 150 
            ) {
        CROSS_FLAG = FLAGx_Left_3;//找到左上角点且右丢线 判定为左斜出十字
        //putText(img, "Cross_Flag3(左斜)", Point(130, 40), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
    }
    else if (find_inflection_point_right_Down && !find_left_line_lost(left_line_points) && CROSS_FLAG == FLAGc_2
            &&find_center_line_long(gray) > 150
            ) {
        CROSS_FLAG = FLAGx_Right_3;//找到左上角点且右丢线 判定为右斜出十字
        //putText(img, "Cross_Flag3(右斜)", Point(130, 40), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
    }
    else if(encoder_distance>90000)
                             
    {
        CROSS_FLAG = FLAGc_0;
        FLAG_ELEMENT = NONE;
        cout << "出十字" << endl;
    }
    
    else {
        CROSS_FLAG = FLAGc_2;
    }

}
void find_cross_flag4() {
    if (
        find_left_line_lost(left_line_points) 
        && find_right_line_lost(right_line_points) 
        && find_center_line_long(gray) > 120
        && FLAG_ELEMENT == CROSS
        || encoder_distance>90000) 
        {
        FLAG_ELEMENT = NONE;
        CROSS_FLAG = FLAGc_0;
        cout << "出十字" << endl;
    }
}
void CrossCheck_IN() {


    switch (CROSS_FLAG)
    {

    case FLAGc_0:
        //cout << "12" << endl;
        find_cross_flag1();
        break;
    case FLAGc_1:
        cout << "十字状态1" << endl;
        find_cross_flag2();
        //切换巡中线
        encoder_distance=0;
        track_line_points = center_line_points;
        // line(img, Point(img.cols / 8 * 2, img.rows), Point(img.cols / 8 * 2, 0), Scalar(0, 0, 0), 4);
        // line(img, Point(img.cols / 8 * 6, img.rows), Point(img.cols / 8 * 6, 0), Scalar(0, 0, 0), 4); //初步十字补线--没有试过待完善！！！
        break;
    case FLAGr_Left1:
    cout<<"左斜入十字"<<endl;
    line(img,inflection_point_left_Down,point_left_UP,Scalar(0,0,0),5);//左上角连线左下角
    break;
    case FLAGr_Right1:
    cout<<"右斜入十字"<<endl;
    line(img,inflection_point_right_Down,point_right_UP,Scalar(0,0,0),5);//右上角连线右下角
    find_cross_flag2();
            //切换巡中线
        encoder_distance=0;
        track_line_points = center_line_points;
    case FLAGc_2:
        find_cross_flag3();
        track_line_points = center_line_points;
        cout << "十字状态2" << endl;
        // if(offset>0)
        // {
        //     change_track_line(right_line_points, -img.cols / 3);
        // }
        
        break;
    case FLAGc_3:
        find_cross_flag4();
        cout << "十字状态3" << endl;
        // line(img, Point(img.cols / 8 * 2, img.rows), Point(img.cols / 8 * 2, 0), Scalar(0, 0, 0), 4);
        // line(img, Point(img.cols / 8 * 6, img.rows), Point(img.cols / 8 * 6, 0), Scalar(0, 0, 0), 4); //初步十字补线--没有试过待完善！！！
        find_the_inflection_point_left_UP(img, left_line_points);
        find_the_inflection_point_right_UP(img,right_line_points);
        line(img, Point((img.cols / 8) * 1, img.rows), point_left_UP, Scalar(0, 0, 0), 5);
        line(img, Point((img.cols / 8) * 7, img.rows), point_right_UP, Scalar(0, 0, 0), 5);
        track_line_points = center_line_points;
        break;
    case FLAGx_Left_3:
        find_cross_flag4();
        cout << "左斜出十字" << endl;
        // change_track_line(right_line_points,-img.cols/3);
                find_the_inflection_point_left_UP(img, left_line_points);
        find_the_inflection_point_right_UP(img,right_line_points);
        line(img, Point((img.cols / 8) * 1, img.rows), point_left_UP, Scalar(0, 0, 0), 5);
        line(img, Point((img.cols / 8) * 7, img.rows), point_right_UP, Scalar(0, 0, 0), 5);
        track_line_points = center_line_points;
        //  track_line_points = right_line_points;
        // line(img, Point(img.cols / 4 * 3, 0), Point(img.cols / 4 * 1, img.rows), Scalar(0, 0, 0), 4);
        break;
    case FLAGx_Right_3:
        find_cross_flag4();
        cout << "右斜出十字" << endl;
        // line(img, Point(img.cols / 4 * 4, img.rows), Point(img.cols / 4 * 1, 0), Scalar(0, 0, 0), 4);
        // change_track_line(left_line_points,img.cols/3);
        find_the_inflection_point_left_UP(img, left_line_points);
        find_the_inflection_point_right_UP(img,right_line_points);
        line(img, Point((img.cols / 8) * 1, img.rows), point_left_UP, Scalar(0, 0, 0), 5);
        line(img, Point((img.cols / 8) * 7, img.rows), point_right_UP, Scalar(0, 0, 0), 5);
        track_line_points = center_line_points;
        // track_line_points = left_line_points;
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }
}