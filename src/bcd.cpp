#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <bcd.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "bcd_node");

  Mat img= imread("/home/exbot/catkin_ws/src/bcd/2");
  if(img.empty()){
    ROS_INFO("Load image failed!");
    return 0;
  }
  Mat img_R;
  cvtColor(img,img_R,CV_BGR2GRAY);//三通道的图转化为1通道的灰度图
  namedWindow("Gray_Window");
  imshow("Gray_Window", img_R);
  Mat img_b;
  threshold(img_R,img_b,0,1,THRESH_BINARY_INV);//通过阈值操作把灰度图变成二值图
  namedWindow("Bin_Window");
  imshow("Bin_Window", img_b);
  int cells=0;
  Mat separate_map=BCD::calc_bcd(img_b,cells);
  ROS_INFO("Separate image sucessed!");
  Mat display_mat=BCD::display_separate_map(separate_map,cells);
  ROS_INFO("Display Separate image sucessed!");
  namedWindow("BCD_Window");
  imshow("BCD_Window", display_mat);
  cvWaitKey(0);
  return 1;
}


