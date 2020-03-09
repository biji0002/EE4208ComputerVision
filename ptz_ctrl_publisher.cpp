#include "scout_msgs/PTZ.h"
#include "ros/ros.h"
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <ncurses.h>


void counter_clockwise(ros::Publisher pb,scout_msgs::PTZ call1,scout_msgs::PTZ call4);

void clockwise(ros::Publisher pb,scout_msgs::PTZ call0,scout_msgs::PTZ call4);

void going_up(ros::Publisher pb,scout_msgs::PTZ call2,scout_msgs::PTZ call4);

void going_down(ros::Publisher pb,scout_msgs::PTZ call3,scout_msgs::PTZ call4);



int main(int argc, char **argv)
{
    ros::init(argc, argv, "ptz_ctrl_publisher");

    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<scout_msgs::PTZ>("ptz_ctrl_pub",1000);

	scout_msgs::PTZ msg0;//clockwise
	msg0.ptz_cmd = 8;
	msg0.param1 = 2;
	msg0.param2 = 0;

	scout_msgs::PTZ msg1;//counter clockwise
	msg1.ptz_cmd = 9;
	msg1.param1 = 2;
	msg1.param2 = 0;

	scout_msgs::PTZ msg2;//up
	msg2.ptz_cmd = 6;
	msg2.param1 = 0;
	msg2.param2 = 2;

	scout_msgs::PTZ msg3;//down
	msg3.ptz_cmd = 7;
	msg3.param1 = 0;
	msg3.param2 = 2;

	scout_msgs::PTZ msg4;//stop
	msg4.ptz_cmd = 0;
	msg4.param1 = 0;
	msg4.param2 = 0;


	//ros::Rate loop_rate(10);
	//int cnt = 0;
	ROS_INFO("publisher ready");
	while(ros::ok())
	{
		ROS_INFO("ROS OK, waiting for command..");
		/*
		turning_right(pub,msg0,msg1,msg2,msg3,msg4);
		turning_left(pub,msg0,msg1,msg2,msg3,msg4);*/

		char i = getchar();
		switch(i)
		{
			case 'd':ROS_INFO("counter_clockwise");counter_clockwise(pub,msg1,msg4);break;
			case 'a':ROS_INFO("clockwise");clockwise(pub,msg0,msg4);break;
			case 'w':ROS_INFO("going_up");going_up(pub,msg2,msg4);break;
			case 's':ROS_INFO("going_down");going_down(pub,msg3,msg4);break;

		}
	}

	
	
	ros::spinOnce();
	
    return 0;
}

void counter_clockwise(ros::Publisher pb,scout_msgs::PTZ call1,scout_msgs::PTZ call4)
{

	int cnt = 0;
	ros::Rate loop_rate(10);
	ROS_INFO("counter clockwise");
	while (cnt<100)
	{
		pb.publish(call1);		
		cnt++;
		loop_rate.sleep();
	}

	ROS_INFO("stay at right");
	while (cnt>=100 && cnt <110)
	{
	    pb.publish(call4);
		cnt++;		
	}

}

void clockwise(ros::Publisher pb,scout_msgs::PTZ call0,scout_msgs::PTZ call4)
{

	int cnt = 0;
	ros::Rate loop_rate(10);
	ROS_INFO("clockwise");
	while (cnt<100)
	{
		pb.publish(call0);		
		cnt++;
		loop_rate.sleep();
	}

	ROS_INFO("stay at left");
	while (cnt>=100 && cnt <110)
	{
	    pb.publish(call4);
		cnt++;		
	}

}

void going_up(ros::Publisher pb,scout_msgs::PTZ call2,scout_msgs::PTZ call4)
{

	int cnt = 0;
	ros::Rate loop_rate(10);
	ROS_INFO("up");
	while (cnt<80)
	{
		pb.publish(call2);		
		cnt++;
		loop_rate.sleep();
	}

	ROS_INFO("stay up");
	while (cnt>=80 && cnt <90)
	{
	    pb.publish(call4);
		cnt++;		
	}

}

void going_down(ros::Publisher pb,scout_msgs::PTZ call3,scout_msgs::PTZ call4)
{

	int cnt = 0;
	ros::Rate loop_rate(10);
	ROS_INFO("down");
	while (cnt<74)
	{
		pb.publish(call3);		
		cnt++;
		loop_rate.sleep();
	}

	ROS_INFO("stay down");
	while (cnt>=74 && cnt <84)
	{
	    pb.publish(call4);
		cnt++;		
	}

}
/*
void turning_right(ros::Publisher pb,scout_msgs::PTZ call0,scout_msgs::PTZ call1,scout_msgs::PTZ call2,scout_msgs::PTZ call3,scout_msgs::PTZ call4)
{

	int cnt = 0;
	ros::Rate loop_rate(10);
	ROS_INFO("counter clockwise");
	while (cnt<100)
	{
		pb.publish(call1);		
		cnt++;
		loop_rate.sleep();
	}
	ROS_INFO("up");
	while (cnt>=100 && cnt<180)
	{
		pb.publish(call2);		
		cnt++;
		loop_rate.sleep();
	}

	ROS_INFO("stay at right");
	while (cnt>=180 && cnt <190)
	{
	    pb.publish(call4);
		cnt++;		
	}

}
*/
