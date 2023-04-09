#ifndef MINIMAL_CONTROLLER_CLASS_H_
#define MINIMAL_CONTROLLER_CLASS_H_

//some generically useful stuff to include...

#include <ros/ros.h> //ALWAYS need to include this
//message types used in this example code;  include more message types, as needed
#include<std_msgs/Float64.h> 


// define a class, including a constructor, member variables and member functions
class ExampleRosClass
{
public:
    ExampleRosClass(ros::NodeHandle* nodehandle); //"main" will need to instantiate a ROS nodehandle, then pass it to the constructor
    // may choose to define public methods or public variables, if desired
    std_msgs::Float64 g_velocity;
    std_msgs::Float64 g_vel_cmd;
    std_msgs::Float64 g_force; // this one does not need to be global... 
    ros::Subscriber my_subscriber_object1; //these will be set up within the class constructor, hiding these ugly details
    ros::Subscriber my_subscriber_object2;
    ros::Publisher  my_publisher_object;
private:
    // put private member data here;  "private" data will only be available to member functions of this class;
    ros::NodeHandle nh_; // we will need this, to pass between "main" and constructor
    // some objects to support subscriber, service, and publisher

    

    // member methods as well:
    void initializeSubscribers(); // we will define some helper methods to encapsulate the gory details of initializing subscribers, publishers and services
    void initializePublishers();
    
    void velocity_Callback(const std_msgs::Float64& message_holder);
    void vel_cmd_Callback(const std_msgs::Float64& message_holder); //prototype for callback of example subscriber
}; // note: a class definition requires a semicolon at the end of the definition

#endif  // this closes the header-include trick...ALWAYS need one of these to match #ifndef