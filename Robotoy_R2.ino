#include <StandardCplusplus.h>
#include <vector>
#include <Servo.h>
#include <iostream>
#include <string>


// ** For Loop Instructions ** //
//0x00 = break
//0x10 = fwd
//0x20 = turn L
//0x30 = turn R

//0x90 = for
//0xA0 = end


[[maybe_unused]] const int del_istr = 0;
[[maybe_unused]] const int next_istr = 1;
[[maybe_unused]] const int all_istr = 2;

using namespace std;

/*
 * TECHNICAL DIRECTORS:
 * PAOLO STEGAGNO
 * CAMERON AMARAL
 * 
 * CONTRIBUTORS OF THE ROBOTOY PROJECT:

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
int main_list[12]; //main instruction list.
int *ptr = main_list; // keeps count on array content.
vector<int>forlist; // for - loop list that will archive contents within the FOR and END block.
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

  ForLoop();
  
   Serial.begin(9600);
   
  //Button Array Pins:
   pinMode(34,OUTPUT);//1
   pinMode(36,OUTPUT);//2
   pinMode(38,OUTPUT);//3
   pinMode(40,OUTPUT); //4
   pinMode(33,OUTPUT);//5
   pinMode(31,OUTPUT);//6
   pinMode(30,OUTPUT);//7
   pinMode(32,OUTPUT);//8   
   pinMode(41,OUTPUT);//9
   pinMode(39,OUTPUT);//10
   pinMode(37,OUTPUT);//11
   pinMode(35,OUTPUT);//12

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

int ForLoop() {
	int mode = all_istr;
	
	//simulate for block
	[[maybe_unused]]int iter_fur1 = 3;
	[[maybe_unused]]int fur1 = (0x90 + iter_fur1 - 1);

	//simulate for block
	[[maybe_unused]]int iter_fur2 = 2;
	[[maybe_unused]]int fur2 = (0x90 + iter_fur2 - 1);
	
	vector<int> v = {0x10, 0x40, fur2, 0x20, fur1, 0x40, 0x70, 0x10, 0xA0, 0x30, 0x50, 0xA0};
	//vector<int> v = {0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x00, 0x00, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0};
	//cout << v.size();

	//vector<int> v = {0x00, 0x10, 0x20, 0x92, 0x40, 0x50, 0x60};

	

	//find last occurence of 'for' in the istr vector 
	//(guarantees this only runs an amount of times equal to the number of 'for' commands
	// and eliminates needing to deal with the istr vector being resized)
	for (int i = v.size() - 1; i >= 0; i--){
		if (v[i] >> 4 == 0x90 >> 4){

			//grab index of 'for' in the vector and the num of occurences of said 'for' in the last 4 bits of the 'for' istr
			//cout << i << endl;
			int iterations = v[i] & 0x0F;
			
			//find closest occurence of 'end' after the 'for'
			for (int j = i; j <= v.size() - 1; j++){
				if (v[j] == 0xA0){
					//cout << "size of v: " << v.size() << endl;
					//cout << "position of 'end': " << j << endl;

					//print
					/*
					for (int k = 0; k < v.size(); k++){
						cout << hex << v[k] << ' ';
					}
					cout << endl;
					*/
					
					//replace the found 'for', 'end', and the values in between 
					//with a repetiton of the values in between specified by iter
					vector<int>::iterator start = v.begin() + i;
					vector<int>::iterator end = v.begin() + j;
					vector<int> v2(start + 1, end);

					v.erase(start); 
					v.erase(end - 1);
					
					for (int k = 0; k < iterations; k++){
						v.insert(v.begin() + i, v2.begin(), v2.end());
					}
					
					//print
					for (int k = 0; k < v.size(); k++){
						cout << hex << v[k] << ' ';
					}
					cout << endl;
					break;
				}

				// Eliminates extra 'for's
				if (j == v.size() - 1){
					cout << "mode: " << mode << endl;

					for (int k = 0; k < v.size(); k++){
						cout << hex << v[k] << ' ';
					}
					cout << endl << i << endl;

					cout << v[i] << endl;
					v.erase(v.begin() + i);
					cout << v[i] << endl;
					
					switch (mode) {
						case 0: {break;}
						case 1: {
							int istr_temp = v[i];
							for (int k = 0; k < iterations; k++) {
								v.insert(v.begin() + i + 1, istr_temp);
							}
							break;
						}
						case 2: {
							vector<int>::iterator start = v.begin() + i;
							vector<int>::iterator end = v.end();
							vector<int> v2(start, end);

							for (int k = 0; k < iterations; k++){
								v.insert(v.begin() + i, v2.begin(), v2.end());
							}
							break;
						}
						default: {
							;;
						}	
					}
					break;
					for (int k = 0; k < v.size(); k++){
						cout << hex << v[k] << ' ';
					}
					cout << endl;
					break;
				}	
				// More options are to only repeat the istr after the 'for' or all istr up until the end of the list
			}
		}
	}
	//print
	for (int k = 0; k < v.size(); k++){
		cout << hex << v[k] << ' ';
	}
	cout << endl;
}
