#include <ros/ros.h>
#include<visualization_msgs/Marker.h>


int main(int argc,char**argv)
{
//初始化ros，发布话题visualization_marker

ros::init(argc, argv, "display1");
ros::NodeHandle n;
ros::Rate r(1);
ros::Publisher marker_pub=n.advertise<visualization_msgs::Marker>("visualization_marker",1);

uint32_t shape=visualization_msgs::Marker::CUBE;

while(ros::ok())
{
    //实例化Marker
    visualization_msgs::Marker marker;

    marker.header.frame_id="/map";//指定参考框架
    marker.header.stamp=ros::Time::now();

    marker.ns="xy";
    marker.id=0;

    marker.type=shape;
    

    marker.action=visualization_msgs::Marker::ADD;

    marker.pose.position.x=0;
    marker.pose.position.y=0;
    marker.pose.position.z=1;
    marker.pose.orientation.x=0.0;
    marker.pose.orientation.y=0.0;
    marker.pose.orientation.z=1.0;


    //size of the cube
    marker.scale.x=1;
    marker.scale.y=1;
    marker.scale.z=1;

    //set color
    marker.color.r=0.0;
    marker.color.g=1.0;
    marker.color.b=0.0;
    marker.color.a=1.0;


    //取消自动删除
    marker.lifetime=ros::Duration();


    //有订阅者再发布信息
    while(marker_pub.getNumSubscribers()<1)
    {
        if(!ros::ok())
        {
            return 0;
        }

        //ROS_INFO("")
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);


    }

    marker_pub.publish(marker);


    //change the shapes
    switch(shape)
    {
        case visualization_msgs::Marker::CUBE:
        shape=visualization_msgs::Marker::ARROW;
        break;

        case visualization_msgs::Marker::ARROW:
        shape=visualization_msgs::Marker::CYLINDER;
        break;

        case visualization_msgs::Marker::CYLINDER:
        shape=visualization_msgs::Marker::CUBE;
        break;
    }

    r.sleep();


}

}