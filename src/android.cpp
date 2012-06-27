#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "tf/tf.h"
#include "sparkV_msg/velocity.h"
#include <cmath>
double x_acc, y_acc, z_acc;

void quaternion_fun(const sensor_msgs::Imu::ConstPtr& msg)
{
x_acc=msg->linear_acceleration.x;
y_acc=msg->linear_acceleration.y;
z_acc=msg->linear_acceleration.z;
  // Convert quaternion to RPY.
    ROS_INFO(" %lf %lf %lf ",x_acc,y_acc,z_acc);

}


	

int main(int argc, char **argv)
{	
  ros::init(argc, argv, "android");

  ros::NodeHandle n;

  ros::Subscriber quaternion_sub = n.subscribe("android/imu", 1, quaternion_fun);
  ros::Publisher motor_pub = n.advertise<sparkV_msg::velocity>("motor", 1000);

  

  ros::Rate r(10);
  while (ros::ok())
  {	
   
sparkV_msg::velocity msg;

	if ( (x_acc>=8)) 
		msg.start=false;
	else if (x_acc>=7)
		{msg.left=true;msg.right=true;msg.start=true;msg.s2L=false;msg.s1L=false; 			msg.s0L=true;msg.s2R=false;msg.s1R=false; msg.s0R=true;} 
   	else if (x_acc>=6)
		{ msg.left=true;msg.right=true;msg.start=true;msg.s2L=false;msg.s1L=true; 			msg.s0L=false;msg.s2R=false;msg.s1R=true; msg.s0R=false;} 
	else if (x_acc>=5)
		{msg.left=true;msg.right=true;msg.start=true;msg.s2L=false;msg.s1L=true; 			msg.s0L=true;msg.s2R=false;msg.s1R=true; msg.s0R=true;} 
	else if (x_acc>=4)
		{ msg.left=true;msg.right=true;msg.start=true;msg.s2L=true;msg.s1L=false; 			msg.s0L=false;msg.s2R=true;msg.s1R=false; msg.s0R=false;} 
	else if (x_acc>=3)
		{ msg.left=true;msg.right=true;msg.start=true;msg.s2L=true;msg.s1L=false; 			msg.s0L=true;msg.s2R=true;msg.s1R=false; msg.s0R=true;}
	else if (x_acc>=2)
		{ msg.left=true;msg.right=true;msg.start=true;msg.s2L=true;msg.s1L=true; 			msg.s0L=false;msg.s2R=true;msg.s1R=true; msg.s0R=false;} 
	else 
		{ msg.left=true;msg.right=true;msg.start=true;msg.s2L=true;msg.s1L=true; 			msg.s0L=true;msg.s2R=true;msg.s1R=true; msg.s0R=true;} 

	if(y_acc<-6)
		{ msg.left=false;} 
	else if (y_acc<-3)
		{ msg.s0L=false;msg.s1L=false;msg.s2L=false;}
        else if(y_acc<3)
		{ ;;} 
 	else if (y_acc<6)
		{ msg.s0R=false;msg.s1R=false;msg.s2R=false;}		
	else 
	{ msg.right=false;} 			

    motor_pub.publish(msg);

	
    r.sleep();
ros::spinOnce();
    
  }
  

}
