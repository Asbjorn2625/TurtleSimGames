#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"

#define triplength 20
/*
typedef struct {
    float  x,y;
} postype;

postype cordinater[triplength];

void randompos(postype *value) {
    *value.x=rand() & 10 + 1;
    *value.y=rand() & 10 + 1;
}

for (int i=0; i<triplength; i++ ) {
    randompos(&cordinater[i]);
}*/
#define sizeCoordA 5
#define sizeCoordB 2
float coordinates[sizeCoordA][sizeCoordB];
float Sorted_coordinates[sizeCoordA][sizeCoordB];

void RandomCordinates()
{
    //num = (rand() % (upper – lower + 1)) + lower ref https://www.geeksforgeeks.org/generating-random-number-range-c/
    srand(time(NULL));

    for (int j = 0; j < (sizeCoordA - 1); j++)
    {

        coordinates[j][0] = rand() % 11 + 1;
        coordinates[j][1] = rand() % 11 + 1;
    }
}
void sort_cor(){
    RandomCordinates()
    if (coordinates[j][0]<coordinates[j][1]);
        
}

void startstop() {
    coordinates[0][0] = 5.544445; ///start
    coordinates[0][1] = 5.544445;
    coordinates[sizeCoordA - 1][0] = coordinates[0][0]; //slutpunkt
    coordinates[sizeCoordA - 1][1] = coordinates[0][1];
}

void initTurtlePosition(float x, float y, ros::ServiceClient teleport_client, ros::ServiceClient pen_client, turtlesim::TeleportAbsolute srv, turtlesim::SetPen pen_srv)
{
    pen_srv.request.off = true;
    pen_client.call(pen_srv);
    srv.request.x = x;
    srv.request.y = y;
    teleport_client.call(srv);
    pen_srv.request.off = false;
    pen_srv.request.width = 2;
    pen_client.call(pen_srv);
}

void moveTurtle(float x, float y, ros::ServiceClient teleport_client, turtlesim::TeleportAbsolute srv)
{
    srv.request.x = x;
    srv.request.y = y;
    teleport_client.call(srv);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Draw_turtle");
    ros::NodeHandle nh;
    ros::service::waitForService("/turtle1/teleport_absolute", -1);
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    turtlesim::TeleportAbsolute srv;
    ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    turtlesim::SetPen pen_srv;
    ros::Rate loop_rate(10);

    float startX = 5.544445, startY = 5.544445;
    if (argc > 1)
    {
        startX = atof(argv[1]);
        startY = atof(argv[2]);
    }

    initTurtlePosition(startX, startY, teleport_client, pen_client, srv, pen_srv);
    loop_rate.sleep();
    RandomCordinates();
    startstop();

    for (int j = 0; j < sizeCoordA; j++)
        std::cout << "x: " << coordinates[j][0] << " y: " << coordinates[j][1] << std::endl;
    //https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/

    for (int i = 0; i < sizeCoordA; i++)
    {
        moveTurtle(coordinates[i][0], coordinates[i][1], teleport_client, srv);
        loop_rate.sleep();
    }



}