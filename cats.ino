#include <PololuLedStrip.h>

/*********************
* connect the COIN wire to digital 2
* set the side switches to "FAST" "NC"
**********************/

// include the library code:
#include <Wire.h>
#include <Servo.h>


// attach coin wire to digital 2
#define COIN 2
#define SERVO_1_PIN 11
#define SERVO_2_PIN 10
#define SERVO_3_PIN 9
#define SERVO_4_PIN 8



//wine configuration
#define WINE_PIN 3
#define WINE_SERVING_TIME 15000

//LED PIN

#define LED_PIN 12
PololuLedStrip<LED_PIN> ledStrip;

// Create a buffer for holding 60 colors.  Takes 180 bytes.
#define LED_COUNT 30
rgb_color colors[LED_COUNT];
rgb_color colorstby;

#define NFLASHES 500
int coins;
Servo myservo1,myservo2,myservo3,myservo4;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

void setup() {
   
  // Debugging output
  Serial.begin(9600);
  
  //init servo
  myservo1.attach(SERVO_1_PIN);
  myservo2.attach(SERVO_2_PIN);
  myservo3.attach(SERVO_3_PIN);
  myservo4.attach(SERVO_4_PIN);
  
  //init COIN
  pinMode(COIN, INPUT);
  digitalWrite(COIN, HIGH); // pull up
  coins = 0;
  
  //init Wine
  pinMode(WINE_PIN, OUTPUT);
  digitalWrite(WINE_PIN,HIGH);
  
}

void WriteAllServos(int position)
{
  myservo1.write(position);
  myservo2.write(position);
  myservo3.write(position);
  myservo4.write(position);
}

void MoveServos(void)
{ WriteAllServos(90);
  delay(150);
  WriteAllServos(180);
  delay(150);
  WriteAllServos(90);
  delay(150);
  WriteAllServos(180);
  delay(150);
  WriteAllServos(90);
  delay(150);
  WriteAllServos(180);
  delay(150);
  WriteAllServos(90);
  delay(150);
  WriteAllServos(180);
  delay(150);
  WriteAllServos(90);
  delay(150);
  WriteAllServos(0);
  delay(150);
  //lights
    rgb_color color;
    color.red = random(256);
    color.green = random(256);
    color.blue = random(256);
    // Update the colors buffer.
    for(byte i = 0; i < LED_COUNT; i++)
    {
      colors[i] = color;
    }
    // Write to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  #if 0
  for(pos = 90; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 90; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  }
   
  for(pos = 90; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
  } 
  #endif
}

void WaitForCoin(void)
{
  rgb_color color;
    color.red = random(256);
    color.green = random(256);
    color.blue = random(256);
    // Update the colors buffer.
    for(byte i = 0; i < LED_COUNT; i++)
    {
      colors[i] = color;
    }
    // Write to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  // while the coin pin is low (no coin detected), do nothing
  while (! digitalRead(COIN)) {
    delay(1);
  }

  // while the pin is high, we'll track the length with a counter
  uint8_t counter = 0;
  while (digitalRead(COIN)) {
    delay(1);
    counter++;
  }
  Serial.print(counter);
  Serial.println(" ms long pulse");
  
  /*if ((counter > 60) || (counter < 20))
      return;*/
      
  coins++;
  Serial.print(coins);
  Serial.println(" monedas"); 
}

void GiveTheWine(void){
  rgb_color color;
    color.red = random(256);
    color.green = random(256);
    color.blue = random(256);
    // Update the colors buffer.
    for(byte i = 0; i < LED_COUNT; i++)
    {
      colors[i] = color;
    }
    // Write to the LED strip.
    ledStrip.write(colors, LED_COUNT);
    
  //turn pump on
  digitalWrite(WINE_PIN, LOW);
  
  //wait for the glass to be full
  delay(WINE_SERVING_TIME);
  
  //turn pump off
  digitalWrite(WINE_PIN, HIGH);
}

void loop() {
  
  /*Wait for a coin
  The code gets stuck here until a coin is inserted
  */
  WaitForCoin();
  /* move the servos now */
  for (int i=0;i<5;i++)
    MoveServos();

  GiveTheWine();
}
