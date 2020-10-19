#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>



int main(int argc, char *argv[]) {
  ros::init(argc, argv, "move_turtlesim");
srand(time(NULL));

int RandomNumber = rand() % 10 + 1;


  float box_size = ros::param::param("~box_size", RandomNumber);

  ros::NodeHandle nh;

  ros::service::waitForService("/turtle1/teleport_absolute", -1);

  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");

  ros::Duration(2.0).sleep();

  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  turtlesim::TeleportAbsolute srv;
 
  int ans =0;
  std::cout<< "hey fister kom og sæt et tal";
  std::cin >> ans;

  if(ans==1){
  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = RandomNumber;
  pen_srv.request.r = RandomNumber*10;
  pen_srv.request.g = RandomNumber*10;
  pen_client.call(pen_srv);

  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5+box_size/2;
  srv.request.y = 5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5+box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  srv.request.x = 5.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 4;
  pen_srv.request.r = 10;
  pen_srv.request.g = 130;
  pen_srv.request.b = 200;
  pen_client.call(pen_srv);
  }

  return 0;
}