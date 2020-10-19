#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "move_turtle");
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1);
  ros::Rate loop_rate(10);

  geometry_msgs::Twist twist;
//  int count = 0;
  int userInput = 1;

  while(ros::ok() && userInput!=0){

    int ans = 0;
    std::cout<<"hey makker skriv lige et tal fra 1 til 3";
    std::cin >> ans;
  
    switch (ans)
    {
    case 1:
        for(int i=0;i<10;i++){
      twist.linear.x = 4.0;
      twist.angular.z= 4.0;
      vel_pub.publish(twist);
          loop_rate.sleep();
        }
        break;
    case 2:
        { 
        int bae = 0;
        std::cout << "hej tøsen, giv mig de kanter du vil have" << std::endl;
        std::cin >> bae;
    for(int i=0;i<bae;i++)
    {
      twist.linear.x = 4.0;
      twist.angular.z=0;
      vel_pub.publish(twist);
      ros::Duration(1).sleep();
      
      twist.linear.x = 0;
      twist.angular.z=1.57079632679;
        vel_pub.publish(twist);
        ros::Duration(1).sleep();
          loop_rate.sleep();

     }
        }
        break;

      case 3:
      for(int i=0;i<20;i++){
        twist.linear.x=4.0;
        twist.angular.z=0;
        ros::Duration(1).sleep();

        twist.linear.x=0;
        twist.angular.z=1.570796;
        ros::Duration(1).sleep();
        vel_pub.publish(twist);
        loop_rate.sleep();
       }
      break;

    default:
        std::cout<< "hey fister forkert tal" << std::endl;
    break;
    }

/*
    while (count<10){
      twist.linear.x = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
      count++;
    }
    */
    std::cout << "continue (yes=1/no=0)? ";
    std::cin >> userInput;

  }

  return 0;
}