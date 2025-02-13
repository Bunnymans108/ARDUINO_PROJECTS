#define buzzer 5 // this pin use for Alarm
#define echopin 7 // echo pin
#define trigpin 8 // Trigger pin
int Alarm=1; 
int cm; // Duration used to calculate distance
void setup(){ // put your setup code here, to run once 
Serial.begin(9600);// initialize serial communication at 9600 bits per second:
pinMode(buzzer, OUTPUT); //declare buzzer as output
pinMode(trigpin, OUTPUT); // declare ultrasonic sensor Echo pin as input
pinMode(echopin, INPUT);  // declare ultrasonic sensor Trigger pin as Output 
delay(100);
}
 
void loop(){  
// Write a pulse to the HC-SR04 Trigger Pin
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
// Measure the response from the HC-SR04 Echo Pin
long ultra_time = pulseIn (echopin, HIGH);
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
cm =  ultra_time / 29 / 2; 
Serial.print("cm:");Serial.println(cm);
if(cm>=10 && cm<=100){
int d = map(cm, 10, 100, 20, 2000); 
if(Alarm==1)digitalWrite(buzzer, HIGH);   // Turn on Buzzer 
delay(100);  
digitalWrite(buzzer, LOW); // Turn off Buzzer 
delay(d);    
}
if(cm<10){
if(Alarm==1)digitalWrite(buzzer, HIGH);   // Turn on Buzzer 
}
if(cm>100){
digitalWrite(buzzer, LOW); // Turn off Buzzer 
}
delay(10); 
}