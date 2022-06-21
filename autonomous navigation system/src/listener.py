#!/usr/bin/env python
import rospy
from std_msgs.msg import String
 
def callback(data):
 
    # Print the data that is heard from the ROS topic
    rospy.loginfo(
        rospy.get_caller_id() + " I heard %s", data.data)
     
def listener():
 
    # Initialize the node
    rospy.init_node('listener', anonymous=True)
 
    # Subscribe to the obstacle_distance topic
    rospy.Subscriber("obstacle_distance", String, callback)
 
    # keeps python from exiting until this node is stopped
    rospy.spin()
 
if __name__ == '__main__':
    listener()
