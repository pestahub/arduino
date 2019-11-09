/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */
#include <NewPing.h>

#include <ros.h>
#include <rospy_tutorials/Floats.h>
#include <std_msgs/Float32.h>


#define TRIGGER_PIN  6
#define ECHO_PIN     9
#define MAX_DISTANCE 20

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

ros::NodeHandle  nh;

int IN1 = 5; // Input1 подключен к выводу 5 
int IN2 = 4;
int IN3 = 13;
int IN4 = 12;
int ENA = 3;
int ENB = 11;
int i;
byte flag;
void messageCb( const rospy_tutorials::Floats& vel_msg){
  
  if (vel_msg.data[0] == 1 and flag == 0){
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH); 
  
    analogWrite(ENB, 180);
    analogWrite(ENA, 180);
    delay(1000);
    analogWrite(ENB, 180);
    analogWrite(ENA, 30);
    delay(1000);
    flag = 1;
  }
  else {
     digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW); 
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW); 
  
    analogWrite(ENB, 100);
    analogWrite(ENA, 100);
  }
  
  
     // blink the led
}

std_msgs::Float32 float_msg;

ros::Subscriber<rospy_tutorials::Floats> sub("direction", &messageCb );
ros::Publisher distance("distance", &float_msg);
void setup()
{ 
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(distance);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
}

void loop()
{  
  float n = sonar.ping_cm();
  nh.loginfo("Цикл луп");
  float_msg.data = n;
  distance.publish( &float_msg );
  flag = 0;
  nh.spinOnce();
  delay(300);
}
