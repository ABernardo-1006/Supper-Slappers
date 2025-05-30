#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>








RF24 radio (7, 8); //CE, CSN
const byte address[10] = "ADDRESS01";
int A0pin = A0;
int A1pin = A1;
int val0 = 0;
int val1 = 0;
















void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}








void loop() {
  int txt = inputSorter(flexInputRead(A0pin, val0, 930), flexInputRead(A1pin, val1, 935));
  radio.write(&txt, sizeof(txt));
  Serial.println(txt);
  //flexDebug(1);
}








int flexInputRead(int AnalogPin, int val, int tolerance){
  int output = 0;
  val = analogRead (AnalogPin);
  //Serial.println(val);
  if (val >= tolerance){
    output = 1;
    return output;
  }
  else {
    output = 0;
    return output;
  }
}








int inputSorter(int block, int hit){
  if(block == 0){
    return -1;
  }
  else if(hit == 0){
    return 1;
  }
  else{
    return 0;
  }
}




void flexDebug(int val)
{
  if (val == 0)
  {
    Serial.println(analogRead(A0));
  }
  else
  {
    Serial.println(analogRead(A1));
  }
}




