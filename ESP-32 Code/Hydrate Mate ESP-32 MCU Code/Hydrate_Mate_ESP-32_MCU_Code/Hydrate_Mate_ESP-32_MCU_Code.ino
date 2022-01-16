//Code for ESP-32 MCU for Hydrate Mate

#include <BluetoothSerial.h>

#define trigPin 5
#define powerPin 21
#define echoPin 18
const int MEASURE_TIMES = 30;
const int SOUND_SPEED = 34300; //cm/second

BluetoothSerial SerialBT;
byte BTData;

int currentVolumeML;
int bottlesConsumed = 0;
int prevVolumeML;
int startBit = 1;
uint32_t prevTime;
uint32_t curTime;
uint32_t tempTime;

 /*Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(powerPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
  digitalWrite(powerPin, HIGH);
  delay(10000);
}

int measureWater(int bottle_height, int bottle_area) {
  int sum = 0;
  for (int i=0;i<MEASURE_TIMES; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    sum += pulseIn(echoPin, HIGH);
  }
  int average_time = sum / MEASURE_TIMES;

  //water_height in cm
  int water_height = bottle_height - SOUND_SPEED * average_time / 2000000;

  if (water_height < 0)
    return -1;
  
  int volume = bottle_area * water_height;
  return volume;
}

void sendCurrentVolume()
{
  if(currentVolumeML != -1)
  {
    SerialBT.write(currentVolumeML);
  }
  else
  {
    SerialBT.write(-1);
  }
}

void checkBottlesConsumed(int currentVolumeML)
{
  if(currentVolumeML < 10 && prevVolumeML > 10)
  {
    bottlesConsumed++;
  }
}


void loop()

{
 /*  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
  */
  tempTime = curTime;
  curTime = millis();
  if ( curTime - prevTime >= 24*60*60*1000UL || startBit == 1;)
  {
    startBit = 0;
    bottlesConsumed = 0;
    prevTime = tempTime;
  }
  
  //1)Read sensor value every ~2 secs
  prevVolumeML = currentVolumeML;
  currentVolumeML = measureWater();
  
  //2)If cap is on, send value to app. If cap is off, tell the app that
  sendCurrentVolume(currentVolumeML);
  
  //3)If the water level gets low enough, count it as a bottle consumed
  if(currentVolumeML < 10 && prevVolumeML > 10)
  {
    bottlesConsumed++;
  }





   
}
