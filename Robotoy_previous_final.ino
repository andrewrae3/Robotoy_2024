#include <StandardCplusplus.h>
#include <vector>
#include <Servo.h>
/*
 * TECHNICAL DIRECTORS:
 * PAOLO STEGAGNO
 * CAMERON AMARAL
 * 
 * CONTRIBUTORS OF THE ROBOTOY PROJECT:
 * KYLE DASILVA
 * LUIS MEDRANO
 * CHRIS GLEBUS
 * NOAH DOAK
*/

/* INSTRUCTION SET:
 * UP = 01
 * DOWN = 02
 * LEFT = 03
 * RIGHT = 04
 * FOR = 05
 * END = 06
 * ROBOTIC ARM = 07 
 * ULTRASONIC SENSOR = 08 
 * BUZZER = 09
 * SENSOR & ARM = 10 
 * SENSOR & BEEP = 11
 * WIGGLE = 12
*/

//INSTRUCTION BLOCKS RELEVANT VARIALBLES:
byte var1;
int main_list[16]; //main instruction list.
int *ptr = main_list; // keeps count on array content.
std::vector<int>forlist; // for - loop list that will archive contents within the FOR and END block.
int ArrayLength = 16; //array length block
int i;
int forNum;
int opCode = 0;
int immediate = 0;


//ROBOTIC ARM SERVO PINS:

Servo myservo; //hand
Servo myservo2;//right side
Servo myservo3;//left side

//DC MOTOR PINS:
int APolar = 12;
int BPolar = 13;
int Brake_A = 9;
int Brake_B = 8;
int A_PWM = 3;
int B_PWM = 11;


//ULTRASONIC PINS:
int echo = 6;
int trig = 2;
int vcc = 7;
//Sensor variables:
const unsigned int MAX_DIST = 23200;
unsigned long t1;
unsigned long t2;
unsigned long pulse_width;
bool ObsticleAhead = false;
float cm;

//PUSH BUTTON & BUMPER PINS:
int inPin  =  4;
int bumperPin = 5;
int buttonON = 0;
int buttonON2 = 0;
int var;
int var2;
int state = LOW;

//BUZZER PINS:
int buzzerPin = 47;

//verification boolean:
bool verify = true;

void setup() {
  // put your setup code here, to run once:
  
   DDRC = 0; // set PORTC to input
   Serial.begin(9600);
   
  //Button Array Pins:
   pinMode(22,OUTPUT);//1
   pinMode(23,OUTPUT);//2
   pinMode(24,OUTPUT);//3
   pinMode(25,OUTPUT); //4
   pinMode(26,OUTPUT);//5
   pinMode(27,OUTPUT);//6
   pinMode(28,OUTPUT);//7
   pinMode(29,OUTPUT);//8
   
   //30 - 37: 7 bit PORTC
   //44 belongs to arm
   
   pinMode(38,OUTPUT);//9
   pinMode(39,OUTPUT);//10
   pinMode(40,OUTPUT);//11
   pinMode(41,OUTPUT);//12
   pinMode(42,OUTPUT);//13
   pinMode(43,OUTPUT);//14
   pinMode(45,OUTPUT);//15
   pinMode(46,OUTPUT);//16

  //motorshield pins:
  pinMode(APolar, OUTPUT);
  pinMode(BPolar, OUTPUT);
  pinMode(Brake_A, OUTPUT);
  pinMode(Brake_B, OUTPUT);
  
  //PWM SET
  analogWrite(B_PWM,75);
  analogWrite(A_PWM,75);
  
  //enable button settings:
  pinMode(inPin,INPUT);
  pinMode(bumperPin,INPUT);

  //Keeps motors idle from the start:
  digitalWrite(Brake_A,HIGH);
  digitalWrite(Brake_B,HIGH);
  
  //sensor pins setup:
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(vcc,OUTPUT);

  //buzzer enabled:
  pinMode(buzzerPin,OUTPUT);

  //robotic arm pins:
  myservo.attach(50);
  myservo2.attach(51);
  myservo3.attach(49);
}

void loop() {
  // put your main code here, to run repeatedly:

  enButton();
  delay(50);
  while(state == HIGH){
    //SCANNING INSTRUCTIONS:
    
    //line 1:
  digitalWrite(22,HIGH);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[0] = var1; //store in array
  delay(100);
  Serial.println("Line 1");
  Serial.println(var1,BIN);
  delay(500);

  //line 2:
  digitalWrite(22,LOW);//1
  digitalWrite(23,HIGH); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16
  
  delay(500);

  var1 = PINC; // get PORTA valued
  main_list[1] = var1; //store in array

  delay(100);
  Serial.println("Line 2");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 3
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,HIGH); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16
  delay(1000);

  var1 = PINC; // get PORTA valued
  main_list[2] = var1; //store in array
  delay(100);
  Serial.println("Line 3");
  Serial.println(var1,BIN);
  delay(500);
 
  //line 4:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  delay(1000);
  digitalWrite(25,HIGH); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16
  delay(500);

  var1 = PINC; // get PORTA valued
  main_list[3] = var1; //store in array

  delay(100);
  Serial.println("Line 4");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 5:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,HIGH);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16
  
  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[4] = var1; //store in array

  delay(100);
  Serial.println("Line 5");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 6:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,HIGH);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

    delay(100);

  var1 = PINC; // get PORTA valued
  main_list[5] = var1; //store in array

  delay(100);
  Serial.println("Line 6");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 7:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,HIGH);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

    delay(100);

  var1 = PINC; // get PORTA valued
  main_list[6] = var1; //store in array

  delay(100);
  Serial.println("Line 7");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 8:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,HIGH);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

      delay(100);

  var1 = PINC; // get PORTA valued
  main_list[7] = var1; //store in array

  delay(100);
  Serial.println("Line 8");
  Serial.println(var1,BIN);
  delay(500);
  
  
  //line 9:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,HIGH);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  
  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[8] = var1; //store in array

  delay(100);
  Serial.println("Line 9");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 10:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,HIGH);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[9] = var1; //store in array

  delay(100);
  Serial.println("Line 10");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 11:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,HIGH);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[10] = var1; //store in array

  delay(100);
  Serial.println("Line 11");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 12:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,HIGH);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16


  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[11] = var1; //store in array

  delay(100);
  Serial.println("Line 12");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 13:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,HIGH);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[12] = var1; //store in array

  delay(100);
  Serial.println("Line 13");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 14:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,HIGH);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[13] = var1; //store in array

  delay(100);
  Serial.println("Line 14");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 15:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,HIGH);//15
  digitalWrite(46,LOW);//16

  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[14] = var1; //store in array

  delay(100);
  Serial.println("Line 15");
  Serial.println(var1,BIN);
  delay(500);
  
  //line 16:
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW); //2
  digitalWrite(24,LOW); //3
  digitalWrite(25,LOW); //4
  digitalWrite(26,LOW);//5
  digitalWrite(27,LOW);//6
  digitalWrite(28,LOW);//7
  digitalWrite(29,LOW);//8
  digitalWrite(38,LOW);//9
  digitalWrite(39,LOW);//10
  digitalWrite(40,LOW);//11
  digitalWrite(41,LOW);//12
  digitalWrite(42,LOW);//13
  digitalWrite(43,LOW);//14
  digitalWrite(45,LOW);//15
  digitalWrite(46,HIGH);//16


  delay(100);

  var1 = PINC; // get PORTA valued
  main_list[15] = var1; //store in array

  delay(100);
  Serial.println("Line 16");
  Serial.println(var1,BIN);
  delay(500);
  
  Serial.println("Printing Array:");
  
 for (i = 0; i < ArrayLength; ++i){
    opCode = ptr[i] >> 4;
    immediate = ptr[i] % 16;
    if(opCode == 05){
      forNum = immediate;
      }

        opCode = ptr[i] >> 4;
        immediate = ptr[i] % 16;
      Serial.print(opCode);
      Serial.print(" ");
      Serial.println(immediate);
      Command();
      delay(50);
    }
    Serial.println("Done!");
    forlist.clear();
    delay(50);
    state = LOW;
    
    }
  //stasis loop
  while(state == LOW){
    digitalWrite(Brake_A,HIGH);
    digitalWrite(Brake_B, HIGH);
    delay(50);
    enButton(); // rechecks state condition
    }
}


//command switch case program:

void Command(){
  switch(opCode){
    case 0://Brake
      digitalWrite(Brake_A,HIGH);
      digitalWrite(Brake_B,HIGH);
      delay(500);
      break;
      
    case 1://Forward
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(BPolar,HIGH);
      digitalWrite(APolar,LOW);
      delay(immediate*1000);
      break;
      
    case 2://Backward
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(BPolar,LOW);
      digitalWrite(APolar,HIGH);
      delay(immediate*1000);
      break;

    case 3://TurnLeft
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(APolar,LOW);
      digitalWrite(BPolar,LOW);
      delay(immediate*1000);
      break;
      
    case 4://TurnRight
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(APolar,HIGH);
      digitalWrite(BPolar,HIGH);
      delay(immediate*1000);
      break;
      
    case 5://For Loop
      i++;
      while(ptr[i]>>4 != 6){
        forlist.push_back(ptr[i]);
        i++;
        }
        if(ptr[i]>>4 == 6){
          i++;
          for(int j = 0; j < forNum; j++){
            for(unsigned int b = 0; b != forlist.size(); ++b){
              opCode = forlist[b] >> 4;
              immediate = forlist[b] % 16;
              Command();
              delay(50);
              } 
            }
          }
      break;

    case 7:// Robotic Arm
      RoboticArm();
      break;
      
    case 8: //Ultrasonic Sensor
      SensorStop();
      verify = true;
      break;
      
    case 9: //Buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(immediate*1000);
      digitalWrite(buzzerPin, LOW);
      delay(50);
      
      break;
      
    case 10: //Sensor and Arm
      SensorArm();
      verify = true;
      break;
      
    case 11: //Sensor and Buzzer
      SensorBuzz();
      verify = true;
      break;
      
    case 12: //Wiggle
      Wiggle();
      break;
      
     default:
      Serial.println("Default.");
      digitalWrite(Brake_B, HIGH);
      digitalWrite(Brake_A, HIGH); 
      break;
    }
  }
  
//surbourtine programs:


//enable button subroutine:
void enButton(){
  var = digitalRead(inPin);
  delay(50);
  var2 = digitalRead(bumperPin);
  if((var != buttonON)|| (var2 != buttonON2)){
    if(var == HIGH || var2 == HIGH){
      if(state == LOW){
        state = HIGH;
        }
        else{state = LOW;}
        //digitalWrite(pin22,state);
        Serial.println(state);
      }
      delay(50);
    } 
   buttonON = var;
   buttonON2 = var2;
  }


 //ultrasonic sensor function:
   void checkDistance(){
    //trigger toggles between on and off:
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      while (digitalRead(echo) == 0);
      t1 = micros();
      while( digitalRead(echo) == 1);
      t2 = micros();
      //calculates difference between t2 and t1 to quantify distance:
      pulse_width = t2-t1;
      //converts pulse width value into cm:
      cm = pulse_width / 58.0;
      //checking if length exceeds the max detection length:
      if(pulse_width > MAX_DIST){
        Serial.println("OUT OF RANGE");
        }
      else{
        Serial.println(cm);
        }
        //delay for a bit:
        delay(60);

       if(cm <= 10){
          ObsticleAhead = true;
        }
       else{
          ObsticleAhead = false;
        }
      
    }
    
    //Buzzer:
    void Buzzer(){
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      delay(50);
     }
     
    //Robotic Arm:
    void RoboticArm(){

      /*myservo.write(90);
      delay(500);
      myservo2.write(90);
      delay(500);
      myservo3.write(90); //180
      delay(500);
      
    
      myservo.write(0);
      delay(500);
      
      myservo3.write(-90);
      delay(500);
      myservo2.write(-90);
      delay(1000);*/

      myservo3.write(-90);
      delay(500);
      myservo2.write(-90);
      delay(500);
      myservo.write(0);
      delay(500);
      myservo.write(90);
      delay(500);
      myservo2.write(90);
      delay(500);
      myservo3.write(90);
      delay(1000);
      }
      
    //Wiggle:
    void Wiggle(){
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(APolar,HIGH);
      digitalWrite(BPolar,LOW);
      delay(500);
      digitalWrite(Brake_A,LOW);
      digitalWrite(Brake_B,LOW);
      digitalWrite(APolar,HIGH);
      digitalWrite(BPolar,HIGH);
      delay(500);
      
      }
      
    //Sensor & Arm:
    void SensorArm(){
      while(verify == true){
        digitalWrite(Brake_A,LOW);
        digitalWrite(Brake_B,LOW);
        digitalWrite(APolar,HIGH);
        digitalWrite(BPolar,HIGH);
        delay(50);
        checkDistance();  
        delay(5);
        if(ObsticleAhead == true && cm > 1){
          digitalWrite(Brake_A,HIGH);
          digitalWrite(Brake_B,HIGH);
          delay(50);
          RoboticArm();
          delay(50);
          verify = false;          
          }
          else{
          digitalWrite(Brake_A,LOW);
          digitalWrite(Brake_B,LOW);
          delay(50);
            }
        }      
      }
      
    //Sensor and Buzzer:
    void SensorBuzz(){
      while(verify == true){
        digitalWrite(Brake_A,LOW);
        digitalWrite(Brake_B,LOW);
        digitalWrite(APolar,HIGH);
        digitalWrite(BPolar,HIGH);
        delay(50);
        checkDistance();
        delay(5);
        if(ObsticleAhead == true && cm > 1){
          digitalWrite(Brake_A,HIGH);
          digitalWrite(Brake_B,HIGH);
          digitalWrite(buzzerPin, HIGH);
          delay(500);
          digitalWrite(buzzerPin, LOW);
          delay(50);
          verify = false;
          }
        else{
          digitalWrite(buzzerPin, LOW); 
          delay(5);
          }
        }
      }
      
    //Sensor Stop:
    void SensorStop(){
      while(verify == true){
        digitalWrite(Brake_A,LOW);
        digitalWrite(Brake_B,LOW);
        digitalWrite(APolar,HIGH);
        digitalWrite(BPolar,HIGH);
        delay(50);
        checkDistance();  
        delay(5);
        if(ObsticleAhead == true && cm > 1){
          digitalWrite(Brake_A,HIGH);
          digitalWrite(Brake_B,HIGH);
          delay(50);
          verify = false;          
          }
          else{
          digitalWrite(Brake_A,HIGH);
          digitalWrite(Brake_B,HIGH);
          delay(50);
            }
        }
      }
