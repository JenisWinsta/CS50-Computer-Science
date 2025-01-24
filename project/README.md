# Car Parking Model
#### Video Demo:  [Car parking project](https://youtu.be/OvjpOdmlAog)
#### Description:

##### Overview
One of the most prevalent and quickly expanding needs of a developing smart city is
parking management. Thus, the need for an efficient parking system arises. An
IOT-based parking management system makes parking resources more effectively
accessible for parking managers and drivers alike.

The car parking system built by our group has the following features:
1. automatic opening and closing of the barriers using servo motor and IR sensors
2. displays the available number of parking slots before the car enters the parking space
3. leds assist the driver in searching for open spaces.
4. after a vehicle has left the parking space, updates the number of slots
5. if all of the slots are occupied, does not open the entry barriers.

##### Components Used
1. Arduino UNO : The microcontroller
2. IR Sensors : Object detection
3. Servo Motors : Barrier control
4. I2C LCD display : Displays the number of available parking slots
5. Breadboard and Jumper Wires : Connection purpose
6. Arduino IDE : Upload the codes

##### Tinkercad
https://www.tinkercad.com/things/krmSHCmQzB5-csproject/editel?returnTo=%2Fthings%2FkrmSHCmQzB5-csproject%3Fsharecode%3DeKNASMkwGfPoay37&sharecode=iKKvRtwmCdRLqKIfYle7WMWxigF400zkJSAwTaK2CAw

##### Prototype Testing
![prototype img](https://i.ibb.co/2kQy8ZV/prototype-img.jpg)

##### Actual model
![actual model img1](https://i.ibb.co/gS38Lmk/actual-model-1.jpg)
![actual model img2](https://i.ibb.co/YP7w2wb/actual-model-2.jpg)
![actual model img3](https://i.ibb.co/DzMQXRw/actual-model-3.jpg)

##### Code Snippets
```
#include <Wire.h>                       /required header files
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo1; /entry
int IR1 = 2; /entry 1
int IR2 = 4; /entry 2

Servo myservo2; /exit
int IR7 = A0; /exit 1
int IR8 = A1; /exit 2

/parking slots
int IR3 = 5; /IR slot 1
int IR4 = 9; /IR slot 2
int IR5 = 7; /IR slot 3
int IR6 = 8; /IR slot 4

int L1 =10; /led slot 1
int L2 =11; /led slot 2
int L3 =12; /led slot 3
int L4 =13; /led slot 4


int Slot = 4; /Total number of parking Slots

int flag1 = 0; /entry
int flag2 = 0; /entry

int flag3 = 0; /exit
int flag4 = 0; /exit

void setup() {
Wire.begin();

    lcd.begin(16,2);
    lcd.backlight();
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(IR3, INPUT);
    pinMode(IR4, INPUT);
    pinMode(IR5, INPUT);
    pinMode(IR6, INPUT);
    pinMode(IR7, INPUT);
    pinMode(IR8, INPUT);
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(L4, OUTPUT);

    myservo1.attach(3); /servo for entry
    myservo1.write(100); /default position

    myservo2.attach(A2); /servo for exit
    myservo2.write(100); /default position

    lcd.setCursor (0,0);
    lcd.print(" CAR ");
    lcd.setCursor (0,1);
    lcd.print(" PARKING SYSTEM ");
    delay (3000);
    lcd.clear();
}


void loop(){
    /entry detection --------------------------------------------------
    if(digitalRead (IR1) = LOW & flag1 =0){ if(Slot>0)
        {flag1=1;
            if(flag2 =0){myservo1.write(0); Slot = Slot-1;}
        }
        else{
            lcd.setCursor (0,0);
            lcd.print(" SORRY :( ");
            lcd.setCursor (0,1);
            lcd.print(" Parking Full ");
            delay (3000);
            lcd.clear();
        }
    }
    if(digitalRead (IR2) = LOW & flag2 =0) {flag2=1;}
    if(flag1 =1 & flag2 =1){
    delay (500);
    myservo1.write(100);
    flag1=0, flag2=0;
    }

/exit detection-------------------------------------------------------
    if(digitalRead (IR7) = LOW & flag3 =0) {
        flag3=1;
        if(flag4 =0)
            {myservo2.write(0); Slot = Slot+1;}
    }
    if(digitalRead (IR8) = LOW & flag4 =0) {
        flag4=1;
    }
    if(flag3 =1 & flag4 =1){
        delay (500);
        myservo2.write(100);
        flag3=0, flag4=0;
    }

/CAR DETECTION FOR PARKING
SLOTS----------------------------------------------------------------
if(digitalRead(IR3) = LOW){
    digitalWrite(L1,LOW);
    delay(1000);}
else{
    digitalWrite(L1,HIGH);
    delay(400);
}
if(digitalRead(IR4) = LOW){
    digitalWrite(L2,LOW);
}
else{
    digitalWrite(L2,HIGH);
    delay(400);
}
if(digitalRead(IR5) = LOW){
    digitalWrite(L3,LOW);
}
else{
    digitalWrite(L3,HIGH);
    delay(400);
}
if(digitalRead(IR6) = LOW){
    digitalWrite(L4,LOW);
}
else{
    digitalWrite(L4,HIGH);
    delay(400);
}
/LCD DISPLAY--------------------------------------------------------
    lcd.setCursor (0,0);
    lcd.print(" WELCOME! ");
    lcd.setCursor (0,1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);
}
```
