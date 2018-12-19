#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>

int trig_pin = A1;
int echo_pin = A0;
int light_senzor_1 = A2;
int light_senzor_2 = A3;
int max_dist =200; //distanta maxima pentru NewPing
int servo_pin =3;
 int distanceRight,distanceLeft,distanceFront;
int in1=12; //stanga
int in2=13;
int in3=11; //dreapta
int in4=10;

int distance;


NewPing sonar(trig_pin,echo_pin,max_dist);
Servo myServo;


void servoFront(){
  myServo.write(80);
  Serial.print("Servo Orientation :FRONT\t");
  delay(1000);
} // miscare servo
void servoLeft(){
  Serial.print("Servo Orientation :LEFT\t");
  myServo.write(150);
  delay(1000);
}  // miscare servo
void servoRight(){
  Serial.print("Servo Orientation :RIGHT\t");
  myServo.write(10);
  delay(1000);
}  // miscare servo

int readPing(){
  int sum=0;
  int j=0;
  int distance[10];
  for(int i=0;i<10;i++){
    distance[i]=sonar.ping_cm();
    sum=sum+distance[i];
    delay(50);
    if(distance[i]>0) j++;}
  if((sum/j)>250 || (sum==0)){
    Serial.println("Am citit 250");
    return 250;
  }
  else{
    Serial.print("Am citit (sum/j=) ");
    Serial.println(sum/j);
     return sum/j;
  }
}//citirea distantei
int readFront(){
  servoFront();
  distanceFront=readPing();
  Serial.print("DistanceFront = ");
  Serial.println(distanceFront);
  return distanceFront;
} //citirea distantei si miscare servo
int readRight(){
  servoRight();
  distanceRight=readPing();
  Serial.print("distanceRight = ");
  Serial.println(distanceRight);
  return distanceRight;
}//citirea distantei si miscare servo
int readLeft(){
  servoLeft();
  distanceLeft=readPing();
  Serial.print("distanceLeft = ");
  Serial.println(distanceLeft);
  return distanceLeft;
}//citirea distanteisi miscare servo

void afisare_pini(){
  if((digitalRead(in1)==1)&&(digitalRead(in2)==0)&&(digitalRead(in3)==1)&&(digitalRead(in4)==0)){
    Serial.print("INAINTE MARS \n" );
  }
  if((digitalRead(in1)==0)&&(digitalRead(in2)==1)&&(digitalRead(in3)==0)&&(digitalRead(in4)==1)){
    Serial.print("Retragerea \n");
  }
  if((digitalRead(in1)==0)&&(digitalRead(in2)==0)&&(digitalRead(in3)==1)&&(digitalRead(in4)==0)){
    Serial.print("Stanga \n" );
  }
  if((digitalRead(in1)==1)&&(digitalRead(in2)==0)&&(digitalRead(in3)==0)&&(digitalRead(in4)==0)){
    Serial.print("Dreapta \n" );
  }
  if((digitalRead(in1)==0)&&(digitalRead(in2)==0)&&(digitalRead(in3)==0)&&(digitalRead(in4)==0)){
    Serial.print("STOP \n");
  }
}
//functia pentru afisarea pinilor activi, ajuta la testarea motoarelor
void move_front(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);


  afisare_pini();
}
//functia pentru deplasarea masinii inainte
void move_right(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);

  afisare_pini();
}
//functia pentru orientarea masinii in partea dreapta
void move_left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  delay(300);
  afisare_pini();
}
//functia pentru orientarea masinii in partea stanga
void move_back(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

  delay(300);
  afisare_pini();
}
//functia plentru deplasarea masii
void move_stop(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
//funcite pentru opriprea masinii





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servo_pin);
  delay(100);
  servoFront();
  distanceFront=readFront();
  delay(100);
}

 void loop() {

  if(readFront()>=20){
    move_front();
    Serial.println("\n\n");
  }else {
    move_stop();
    delay(100);
    distanceLeft=readLeft();
    delay(100);
    distanceRight=readRight();
    delay(100);
    if(distanceLeft>=distanceRight )
      {
      Serial.println("Luam Stanga");
      move_left();
      delay(400); //delay pentru intoarcerea masinii la 90 de grade la stanga
      }else if(distanceLeft<distanceRight)
            {
              move_right();
              Serial.println("Luam Dreapta");
              delay(400); //delay pentru intoarcerea masinii la 90 de grade la dreapta
            }
    Serial.println("\n\n");
  }
}
