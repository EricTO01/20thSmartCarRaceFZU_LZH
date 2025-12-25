#include "track.h"
vector <Point2i> left_line_points;
vector<Point2i> right_line_points;
vector<Point2i> center_line_points;
vector<Point2i> track_line_points;
extern uint16 G_cha_he_bi_threshold;
void find_left_line(Mat img, int y, int x)
{
    float sum, dif, sar; //和，差，比
    unsigned char mov = 3;
    Point2i find_point;
    for (int col = x; col > mov + 1; col -= mov)
    {
        find_point.x = col;
        find_point.y = y;
        dif = (float)((img.at<uchar>(y, col) - img.at<uchar>(y, col - mov - 1)) << 8);
        sum = (float)((img.at<uchar>(y, col) + img.at<uchar>(y, col - mov - 1)));
        sar = fabs(dif / sum);
        if (sar > G_cha_he_bi_threshold)
        { //差比和大于阈值代表深浅色突变
            find_point.x = col;
            find_point.y = y;
            break; //找到边界后退出
        }
    }
    left_line_points.push_back(find_point);
}

void find_right_line(Mat img, int y, int x)
{
    float sum, dif, sar; //和，差，比
    unsigned char mov = 3;
    Point2i find_point;
    for (int col = x; col < img.cols - mov - 1; col += mov)
    {
        find_point.x = col;
        find_point.y = y;
        dif = (float)((img.at<uchar>(y, col) - img.at<uchar>(y, col + mov + 1)) << 8);
        sum = (float)((img.at<uchar>(y, col) + img.at<uchar>(y, col + mov + 1)));
        sar = fabs(dif / sum);
        if (sar > G_cha_he_bi_threshold)
        { //差比和大于阈值代表深浅色突变
            find_point.x = col;
            find_point.y = y;
            break; //找到边界后退出
        }
    }
    right_line_points.push_back(find_point);
}
void change_track_line(vector <Point2i> line_points,int offset)
{
    track_line_points = line_points;
    for (int i = 0; i < line_points.size(); i++)
    {
        track_line_points[i].x = line_points[i].x+offset;
    }
}