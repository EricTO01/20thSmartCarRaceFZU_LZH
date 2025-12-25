#include "check_line_status.h"
extern uint16 G_cha_he_bi_threshold;
int find_center_line_long(Mat img)
{
    float sum, dif, sar; //和，差，比
    unsigned char mov = 3;
    for (int y = img.rows - 1; y > mov + 1; y -= mov)
    {
        dif = (float)((((img.at<uchar>(y, (img.cols - 1) / 2)) - img.at<uchar>(y - mov - 1, (img.cols - 1) / 2))) << 8);
        sum = (float)(((img.at<uchar>(y, (img.cols - 1) / 2)) + img.at<uchar>(y - mov - 1, (img.cols - 1) / 2)));
        sar = fabs(dif / sum);
        if (sar > G_cha_he_bi_threshold)
        { //差比和大于阈值代表深浅色突变
            cout << "最长白线为：" << img.rows - y << endl;
            center_line_long_point.x = (img.cols - 1) / 2;
            center_line_long_point.y = y;
            return img.rows - y;
        }
    }
    return img.rows;
}
bool find_left_line_lost(vector<Point2i> line_points)
{
    int line_points_num = 0;
    for (int i = 0; i < line_points.size() - 1; i++)
    {
        if (line_points[i].x < img.cols / 2
            && line_points[i].y > img.rows / 2)
        {
            if (line_points[i].x > 10)
            {
                line_points_num++;
                if (line_points_num > 60)
                {
                    return true;
                }
            }

        }
    }
    cout << "左丢线" << endl;
    return false;
}
bool find_right_line_lost(vector<Point2i> line_points)//找右是否丢线
{
    int line_points_num = 0;
    // cout << "3-1" << endl;
    for (int i = 0; i < line_points.size() - 1; i++)
    {
        if (line_points[i].x > img.cols / 2
            && line_points[i].y > img.rows / 2)
        {
            if (line_points[i].x < img.cols - 10)
            {
                line_points_num++;
                if (line_points_num > 60)
                {
                    return true;
                }
            }
        }
    }
    cout << "右丢线" << endl;
    return false;
}