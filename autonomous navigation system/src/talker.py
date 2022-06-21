#!/usr/bin/env python
 
import rospy # ROS Python library
from std_msgs.msg import String
 
import bluetooth # Import the python-bluez library
 
##################################################
# Bluetooth parameters
 
robot_bluetooth_mac_address = '98:D3:B1:FD:48:FF'
port = 1
pc_bluetooth_handle = None
data_size = 300
 
##################################################
# Publisher List
 
# Ultrasonic distance sensor data will 
# be published to a ROS topic named
# obstacle_distance using the message 
# type String. Other data types like
# Float32, Int64, etc. are possible in other 
# applications. Here we use String.
ultrasonic_handle = rospy.Publisher(
         'obstacle_distance', String, queue_size=10)
 
####################################################
# Launch the ROS node
 
rospy.init_node('talker', anonymous=True)
rospy.loginfo("Starting Talker Node")
 
 
#####################################################
# Connect the PC's Bluetooth to the robot's Bluetooth
 
def connect():
  global pc_bluetooth_handle    
   
  while(True):    
    try:
      pc_bluetooth_handle = bluetooth.BluetoothSocket(
                                 bluetooth.RFCOMM)
      pc_bluetooth_handle.connect((
                    robot_bluetooth_mac_address, port))
      break;
    except bluetooth.btcommon.BluetoothError as error:
      pc_bluetooth_handle.close()
      rospy.logwarn(
       "Could not connect: ", error, "; Retrying in 10s...")
      rospy.sleep(10)
   
  return pc_bluetooth_handle
   
pc_bluetooth_handle = connect() # Connect to robot's Bluetooth
  
#############################################################
# Main code
 
# If this file is the main (driver) program you are executing
if __name__ == '__main__': 
 
  while not rospy.is_shutdown():
    try:
      # Keep reading data from the robot
      incoming_data_from_robot = pc_bluetooth_handle.recv(
                              data_size)
      rospy.loginfo(incoming_data_from_robot)
      ultrasonic_handle.publish(incoming_data_from_robot)
      rospy.sleep(0.05)
 
    except bluetooth.btcommon.BluetoothError as error:
      rospy.logerr("Caught BluetoothError: ", error)
      time.sleep(5)
      pc_bluetooth_handle = connect()
      pass
 
  pc_bluetooth_handle.close()
