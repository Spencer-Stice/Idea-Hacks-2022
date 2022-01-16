#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define echoPin 18
#define trigPin 5
#define LED_Pin 2

const int MEASURE_TIMES = 30;
const float SOUND_SPEED = 34300; //cm/second
const float CALIBRATION_VOLUME = 100; //volume, in mL, that is used for calibration
float bottle_height = 20;
float bottle_area = 35;

BluetoothSerial SerialBT;

float currentVolumeML;
float bottlesConsumed = 0;
float prevVolumeML;
float startBit = 1;
uint32_t prevTime;
uint32_t curTime;
uint32_t tempTime;
uint32_t timeSinceLastDrink = 0;
uint32_t lastDrankTime;

long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement
float percent_full;
char val;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  //calibrateHeight();
  //Serial.print(bottle_height);
  calibrateArea();
//  Serial.print("Area: ");
//  Serial.println(bottle_area);
}

float measureTime() {
  float sum = 0;
  for (int i=0;i<MEASURE_TIMES; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    //Serial.println(pulseIn(echoPin, HIGH));
    sum += pulseIn(echoPin, HIGH);
  }
  return sum / MEASURE_TIMES;
}

float measureWater(float bottle_height, float bottle_area) {
  float average_time = measureTime();

  //water_height in cm
  float water_height = bottle_height - SOUND_SPEED * average_time / 2000000;

  if (water_height < 0)
    return -1;
  
  float volume = bottle_area * water_height;
  return volume;
}

void sendCurrentVolume()
{
  if(currentVolumeML != -1 && prevVolumeML == -1)
  {
    SerialBT.write(1);
    SerialBT.write(currentVolumeML);
  }
}

void checkBottlesConsumed()
{
  if(currentVolumeML < 10 && prevVolumeML > 10)
  {
    bottlesConsumed++;
    sendBottlesConsumed();
  }
}

void sendBottlesConsumed()
{
  SerialBT.write(2);
  SerialBT.write(bottlesConsumed);
}

void sendTimeSinceLastDrink()
{
  timeSinceLastDrink = timeSinceLastDrink / 1000 / 60;
  SerialBT.write(3);
  SerialBT.write(timeSinceLastDrink);
  if(timeSinceLastDrink > 60)
  {
    SerialBT.write(4);
  }
}

void calibrateHeight() {
  float average_time = measureTime();
  Serial.println(average_time);
  bottle_height = SOUND_SPEED * average_time / 2000000;
  
  return;
}

void calibrateArea() {
  float average_time = measureTime();
  float water_height = bottle_height - (SOUND_SPEED * average_time / 2000000);
  Serial.println(water_height);
  //CALIBRATION_VOLUME (in mL) / height (in cm) = area (in cm^2)
  bottle_area = CALIBRATION_VOLUME / water_height;
  
  return;
}

void loop() {
  //Serial.println(measureTime());
  //measureTime();
  //return;

  calibrateArea();
  delay(10);
  /*
  tempTime = curTime;
  curTime = millis();
  if ( curTime - prevTime >= 24*60*60*1000UL || startBit == 1)
  {
    startBit = 0;
    bottlesConsumed = 0;
    prevTime = tempTime;
  }

  // 1)Read sensor value every ~2 secs
  prevVolumeML = currentVolumeML;
  currentVolumeML = measureWater(bottle_height, bottle_area);

  if(currentVolumeML < prevVolumeML)
  {
    lastDrankTime = millis();
  }
  
  timeSinceLastDrink = millis() - lastDrankTime;
  sendTimeSinceLastDrink();

  delay(250);
  // 2)If cap is on, send value to app. If cap is off, tell the app that
  sendCurrentVolume();

  delay(250);
  // 3)If the water level gets low enough, count it as a bottle consumed
  checkBottlesConsumed();
  
  delay(2000); 

  /*if (SerialBT.available() > 0)
    {
    val = SerialBT.read();
    //Serial.print(val);
    if (val == '1')
    {
      duration = getSensorReading();
      distance = duration * 0.034 / 2; // Distance in cm. Speed of sound wave divided by 2 (go and back)
      percent_full = 100 * (1 - (distance / 20.0));
      SerialBT.write(percent_full); // send water level
    }
    }
*/
}
