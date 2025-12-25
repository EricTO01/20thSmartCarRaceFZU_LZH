#include "find_special_points.h"
Point2i inflection_point_left_Down;
Point2i inflection_point_right_Down;
bool find_inflection_point_left_Down = false;
bool find_inflection_point_right_Down = false;
Point2i point_right_UP;
bool find_point_right_circle_UP;
extern vector <Point2i> left_line_points;
extern vector<Point2i> right_line_points;

Point2i point_left_UP;

void find_the_inflection_point_left_Down(Mat img, vector<Point2i> left_line_points)
{
    find_inflection_point_left_Down = false;
    int temp_x = 0;
    int temp_y = 0;

    for (int i = 2; i < left_line_points.size() - 15; i++)
    {
        if (i + 5 >= left_line_points.size()) break;
        if (left_line_points[i].x < (img.cols / 3*2) && (left_line_points[i].y > img.rows / 2))
        {
            if (left_line_points[i].x > 15
                && left_line_points[i + 1].x < 15//出现边界撕裂
                && left_line_points[i + 2].x < 15
                && left_line_points[i + 3].x < 15
                && left_line_points[i + 4].x < 15
                && left_line_points[i + 5].x < 15
                && abs(left_line_points[i].x - left_line_points[i + 1].x)>  20
                && abs(left_line_points[i].x - left_line_points[i + 2].x)>  20
                && abs(left_line_points[i].x - left_line_points[i + 3].x)>  20
                && abs(left_line_points[i].x - left_line_points[i + 4].x)>  20
                && abs(left_line_points[i].x - left_line_points[i + 5].x)>  20
                && abs(left_line_points[i+1].x - right_line_points[i+1].x)> img.cols / 20*13
                )
            {
                temp_x = left_line_points[i].x;
                temp_y = left_line_points[i].y;
                for (; i < left_line_points.size() - 15; i++)
                {
                    if (left_line_points[i].x > 15
                        && left_line_points[i + 1].x < 15
                        && left_line_points[i + 2].x < 15
                        && left_line_points[i + 3].x < 15
                        && left_line_points[i + 4].x < 15
                        && left_line_points[i + 5].x < 15)//边界撕裂恢复
                    {
                        /*cout << "找到左下" << endl;*/
                        find_inflection_point_left_Down = true;
                        inflection_point_left_Down.x = temp_x;
                        inflection_point_left_Down.y = temp_y;

                        break;
                    }
                }
            }
        }

    }

}

void find_the_inflection_point_right_Down(Mat img, vector<Point2i> right_line_points)
{
    /*int point_num = 0;*/
    find_inflection_point_right_Down = false;
    int temp_x = 0;
    int temp_y = 0;

    for (int i = 0; i < right_line_points.size() - 15; i++)
    {
        if (right_line_points[i].x > (img.cols / 3) && (right_line_points[i].y > img.rows / 2))
        {
            if (right_line_points[i].x< img.cols - 15
                && right_line_points[i + 1].x >img.cols - 15//出现边界撕裂
                && right_line_points[i + 2].x > img.cols - 15
                && right_line_points[i + 3].x > img.cols - 15
                && right_line_points[i + 4].x > img.cols - 15
                && abs(right_line_points[i].x - right_line_points[i + 1].x)>  20
                && abs(right_line_points[i].x - right_line_points[i + 2].x)>  20
                && abs(right_line_points[i].x - right_line_points[i + 3].x)>  20
                && abs(right_line_points[i].x - right_line_points[i + 4].x)>  20
                && abs(right_line_points[i].x - right_line_points[i + 5].x)>  20
                && abs(left_line_points[i+1].x - right_line_points[i+1].x) > img.cols / 20*13
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
                        //cout << "找到右下" << endl;
                        inflection_point_right_Down.x = temp_x;
                        inflection_point_right_Down.y = temp_y;
                        break;
                    }

                }
            }


        }
    }

}
bool find_the_inflection_point_left_UP(Mat img, vector<Point2i> left_line_points)
{
    //find_point_right_circle_UP = false;
    for (int i = 5; i < left_line_points.size() - 15; i++)
    {
        if (left_line_points[i].x < (img.cols / 2)
            && (left_line_points[i].y > img.rows / 5) * 1
            && (left_line_points[i].y < (img.rows / 5) * 4))
        {

            if (left_line_points[i - 3].x < 15
                &&left_line_points[i - 2].x <  15
                && left_line_points[i - 1].x <  15
                && left_line_points[i].x >  15
                && left_line_points[i + 1].x >  15//出现边界撕裂
                && left_line_points[i + 2].x >  15
                && left_line_points[i + 3].x >  15
                && left_line_points[i + 4].x >  15
                && left_line_points[i + 5].x >  15
                //&& right_line_points[i - 2].x - left_line_points[i - 2].x > img.cols / 10 * 7
                && abs(left_line_points[i].x- left_line_points[i + 1].x) <  8
                && abs(left_line_points[i+2].x - left_line_points[i + 3].x) < 8
                && abs(left_line_points[i+4].x - left_line_points[i + 5].x) < 8
                && abs(left_line_points[i+5].x - left_line_points[i + 6].x) < 8

                && abs(left_line_points[i].y - left_line_points[i + 1].y) < 8
                && abs(left_line_points[i+2].y - left_line_points[i + 3].y) < 8
                && abs(left_line_points[i+3].y - left_line_points[i + 4].y) < 8
                && abs(left_line_points[i+5].y - left_line_points[i + 6].y)  < 8
            )
                
            {
                //find_point_right_circle_UP = true;
                point_left_UP.x = left_line_points[i ].x;
                point_left_UP.y = left_line_points[i ].y;
                //break;
                return true;
            }
        }
    }
    return false;
}
bool find_the_inflection_point_right_UP(Mat img,vector<Point2i> right_line_points)
{
    //find_point_right_circle_UP = false;
    for (int i = 5; i < right_line_points.size() - 15; i++)
    {
        if (right_line_points[i].x > (img.cols / 2) 
            && (right_line_points[i].y > img.rows / 5)*1
            && (right_line_points[i].y < (img.rows / 5)*4))
        {

            if (right_line_points[i - 3].x > img.cols - 15
                &&right_line_points[i-2].x > img.cols - 15
                &&right_line_points[i-1].x > img.cols - 15
                &&right_line_points[i].x< img.cols - 15
                && right_line_points[i + 1].x <img.cols - 15//出现边界撕裂
                && right_line_points[i + 2].x < img.cols - 15
                && right_line_points[i + 3].x < img.cols - 15
                && right_line_points[i + 4].x < img.cols - 15
                && right_line_points[i + 5].x < img.cols - 15
                //&& right_line_points[i - 2].x-left_line_points[i - 2].x > img.cols/10*7

                && abs(right_line_points[i].x - right_line_points[i + 1].x) < 8
                && abs(right_line_points[i + 2].x - right_line_points[i + 3].x) < 8
                && abs(right_line_points[i + 4].x - right_line_points[i + 5].x) < 8
                && abs(right_line_points[i + 5].x - right_line_points[i + 6].x) < 8

                && abs(right_line_points[i].y - right_line_points[i + 1].y) < 8
                && abs(right_line_points[i + 2].y - right_line_points[i + 3].y) < 8
                && abs(right_line_points[i + 3].y - right_line_points[i + 4].y) < 8
                && abs(right_line_points[i + 5].y - right_line_points[i + 6].y) < 8
                )
            {
                //find_point_right_circle_UP = true;
                point_right_UP.x = right_line_points[i + 1].x;
                point_right_UP.y = right_line_points[i + 1].y;
                //break;
                return true;
            }
        }
    }
    return false;
}
