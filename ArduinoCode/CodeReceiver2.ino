#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <LiquidCrystal_I2C.h>








RF24 radio (7, 8); //CE, CSN
const byte address[10] = "ADDRESS02";
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adjust to (0x27,20,4) for 20x4 LCD
int txt = 0;
int wirelessInput = 0;
int gateA = 1;
int gateB = 1;








int motor1pin1 = 5;
int motor1pin2 = 6;
int motor1speed = 9;




int motor2pin1 = 2;
int motor2pin2 = 4;
int motor2speed = 3;








void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  lcd.init();          // Initiate the LCD module
  lcd.backlight();     // Turn on the backlight




  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1speed, OUTPUT);




  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor2speed, OUTPUT);




  analogWrite(motor1speed, 100);
  analogWrite(motor2speed, 150);
 
}








void loop() {
  recieveThings();
  Serial.println(wirelessInput);




 
  if(wirelessInput == -1 && gateA == 1)
  {
    gateA = 0;
    Serial.println("what in the what");
    totalBlock();
    restState();
   
  }
  else if (wirelessInput == 1 && gateB == 1)
  {
    gateB = 0;
    Serial.println("what in the");
    punch();
    restState();
   
  }
  else
  {
    delay(500);
    gateA = 1;
    gateB = 1;
  }




}




void recieveThings()
{
  if (radio.available()) {
    radio.read(&txt, sizeof(txt));
    if (txt == -1) {
      //Serial.println("block up");
      wirelessInput = -1;
      //totalBlock();
   
    }
    else if (txt == 1) {
      //Serial.println("hit hooray");
      wirelessInput = 1;
      //punch();


    }
    else {
      //Serial.println("huh nothing lame");
      wirelessInput = 0;
     
    }
  }
}




void restState()
{
  analogWrite(motor1speed, 0);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  analogWrite(motor2speed, 0);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);




}
void moveForward()
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
}








void moveBackward()
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);




}




void punch()
{
  //punch forward
  analogWrite(motor1speed, 100);
  moveForward();
  delay(300);
  moveBackward();
  delay(300);
  restState();
}




void blockUp()
{
  analogWrite(motor2speed, 100);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}




void blockLow()
{
  analogWrite(motor2speed, 100);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);




}




void totalBlock()
{
  analogWrite(motor2speed, 100);
  blockUp();
  delay(150);
  restState();
  delay(1000);
  blockLow();
  delay(150);
  restState();
}


