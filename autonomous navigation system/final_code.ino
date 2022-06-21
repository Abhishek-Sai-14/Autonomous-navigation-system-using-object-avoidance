#include <SoftwareSerial.h>
SoftwareSerial EEBlue(2, 3);

void Setup_Serial(int baud_rate)
{
 
  Serial.begin(9600);  
  EEBlue.begin(9600);  //Default Baud for communications
   
}

void Read_From_Serial()
{
  // Read data from Serial terminal of Arduino IDE
  while(Serial.available() > 0)
    {      
     EEBlue.write(Serial.read());        
    } 
 
 
}

void Update_all()
{
  Read_From_Serial();
}

int trigPin = 9;      // trig pin of HC-SR04
int echoPin = 10;     // Echo pin of HC-SR04

int revleft4 = 4;       //REVerse motion of Left motor
int fwdleft5 = 5;       //ForWarD motion of Left motor
int revright6 = 6;      //REVerse motion of Right motor
int fwdright7 = 7;      //ForWarD motion of Right motor

long duration, distance;

void setup() {
  
  delay(random(500,2000));   // delay for random time
  Serial.begin(9600);
  pinMode(revleft4, OUTPUT);      // set Motor pins as output
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);
  
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
    // If you dont get proper movements of your robot then alter the pin numbers
  if (distance > 19)            
  {
    digitalWrite(fwdright7, HIGH);                    // move forward
    digitalWrite(revriHIGH)ght6, LOW);
    digitalWrite(fwdleft5, ;                                
    digitalWrite(revleft4, LOW);                                                       
  }

  if (distance < 19)
  {
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
    delay(500);
    digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
    delay(500);
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);  
    delay(100);  
    digitalWrite(fwdright7, HIGH);       
    digitalWrite(revright6, LOW);   
    digitalWrite(revleft4, LOW);                                 
    digitalWrite(fwdleft5, LOW);  
    delay(500);
  }
  Update_all();

}
