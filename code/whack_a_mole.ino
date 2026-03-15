#include <LiquidCrystal_I2C.h>
int Startbutton=7;
int redPush=4;      
int greenPush=3;    
int yellowPush=2;   
int bluePush=1;     
int blueLED=9;       //4
int yellowLED=10;   //3 
int greenLED=11;   //2
int redLED=12;   //1
int buzzerPin=6;
LiquidCrystal_I2C lcd(0x27,16,2);
int state=0;   //IDLE->0,Game Running->1, Game Over->2
unsigned long DURATION=30000, MOLE_dur=1000;
unsigned long StartTime;
int score=0;
unsigned long currentTime,prevTime;
bool prevStart=1,prevRed=1,prevGreen=1,prevYellow=1,prevBlue=1;
bool currStart,currRed,currGreen,currYellow,currBlue;
int currentLED;
void setup() {
  pinMode(Startbutton, INPUT_PULLUP);
  pinMode(redPush, INPUT_PULLUP);
  pinMode(greenPush, INPUT_PULLUP);
  pinMode(yellowPush, INPUT_PULLUP);
  pinMode(bluePush, INPUT_PULLUP);
  pinMode(blueLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  randomSeed(analogRead(A0));
 lcd.init();
 lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Game Starts:");
 delay(2000);
 lcd.clear();
}

void loop() {
 if(state==0){
  currStart=digitalRead(Startbutton);
  if(prevStart==0 && currStart==1){
  StartTime=millis();
  prevTime=StartTime;
  lcd.clear();  //game starts
  lcd.print("Score:0");
  //choose a random LED and light it
 pickNewMole();
 state=1; //state goes to game running
 }
 else{
  lcd.setCursor(0,0);
  lcd.print("Press START: ");
  prevStart=currStart;
 }
 }



 if(state==1){
  currentTime=millis();
 if(currentTime-StartTime>=DURATION){
  //game over
  state=2;
 }
 if(currentTime-prevTime>=MOLE_dur){
  //turn current LED off
   turnOFF();
  //choose a random LED and light it
  pickNewMole();
  prevTime=currentTime;
 }
 //detect the button pressed
 currRed=digitalRead(redPush);
 currGreen=digitalRead(greenPush);
 currYellow=digitalRead(yellowPush);
 currBlue=digitalRead(bluePush);
 if(prevRed==0 && currRed==1){
  //red button pressed
  if(digitalRead(redLED)==1){
    score++;  //correct
    lcd.setCursor(7,0);
    lcd.print(score);
    //success buzzer tone
    tone(buzzerPin, 1000, 100);
  }
  else{
    //buzzer tone
    tone(buzzerPin, 200, 200);
  }
 }
 if(prevGreen==0 && currGreen==1){
  //green button pressed
  if(digitalRead(greenLED)==1){
    score++;  //correct
    lcd.setCursor(7,0);
    lcd.print(score);
    //success buzzer tone
    tone(buzzerPin, 1000, 100);
  }
  else{
    //buzzer tone
    tone(buzzerPin, 200, 200);
  }
 }
 if(prevYellow==0 && currYellow==1){
  //yellow button pressed
  if(digitalRead(yellowLED)==1){
    score++;  //correct
    lcd.setCursor(7,0);
    lcd.print(score);
    //success buzzer tone
    tone(buzzerPin, 1000, 100);
  }
  else{
    //buzzer tone
    tone(buzzerPin, 200, 200);
  }
 }
 if(prevBlue==0 && currBlue==1){
  //blue button pressed
  if(digitalRead(blueLED)==1){
    score++;  //correct
    lcd.setCursor(7,0);
    lcd.print(score);
    //success buzzer tone
    tone(buzzerPin, 1000, 100);
  }
  else{
    //buzzer tone
    tone(buzzerPin, 200, 200);
  }
  }
 prevRed=currRed;
 prevGreen=currGreen;
 prevYellow=currYellow;
 prevBlue=currBlue;
 }


if(state==2){
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(blueLED,LOW);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("GAME OVER!");
  lcd.setCursor(0,1);
  lcd.print("FINAL SCORE:");
  lcd.print(score);
  delay(5000);
  score=0;
  state=0;
  prevStart=1;
  lcd.clear();
}
}
void pickNewMole(){
currentLED=random(0,4);
 if(currentLED==0){
  digitalWrite(redLED,HIGH);
 }
 if(currentLED==1){
  digitalWrite(greenLED,HIGH);
 }
 if(currentLED==2){
  digitalWrite(yellowLED,HIGH);
 }
 if(currentLED==3){
  digitalWrite(blueLED,HIGH);
 }
}
void turnOFF(){
if(currentLED==0){
  digitalWrite(redLED,LOW);
 }
 if(currentLED==1){
  digitalWrite(greenLED,LOW);
 }
 if(currentLED==2){
  digitalWrite(yellowLED,LOW);
 }
 if(currentLED==3){
  digitalWrite(blueLED,LOW);
 }
}
