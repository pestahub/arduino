#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
from rospy_tutorials.msg import Floats

class dist:
    def __init__(self):
        self.distan = [0, 0]

a = dist()
def manager():
    #rospy.loginfo(a.distan)
    return a.distan
 
def callback(data):
    rospy.loginfo(data.data)
    #rospy.loginfo(type(data))
    
    if data.data == 0.0:
        a.distan = [0, 0] 
        rospy.loginfo("0")
    else:
        a.distan = [1, 0]
        rospy.loginfo("1")


def talker_listener():
    
    
    pub = rospy.Publisher('direction', Floats, queue_size=100)
    rospy.init_node('manager', anonymous=True)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        direction = manager()
        
        pub.publish(direction)
        rate.sleep()
        rospy.Subscriber("distance", Float32, callback)
        



if __name__ == '__main__':
    try:
        talker_listener()
    except rospy.ROSInterruptException:
        pass
