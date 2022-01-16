//Code for ESP-32 MCU for Hydrate Mate

#include <BluetoothSerial.h>

#define trigPin 5
#define powerPin 21
#define echoPin 18

BluetoothSerial SerialBT;
byte BTData;

int currentVolumeML;
int bottlesConsumed = 0;
int prevVolumeML;
int startBit = 1;
uint32_t prevTime;
uint32_t curTime;

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

int getSensorReading()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
//   SerialBT.println(duration);
  return duration;
  
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
  curTime = millis();
  if ( curTime - prevTime >= 24*60*60*1000UL || startBit == 1;)
  {
    startBit = 0;
    

    // do things every 24h here
  }
  
  //1)Read sensor value every ~2 secs
  prevVolume
  currentVolumeML = NICKSFUNCTION();
  
  //2)If cap is on, send value to app. If cap is off, tell the app that
  if(currentVolumeML != -1)
  {
    SerialBT.write(currentVolumeML);
  }
  else
  {
    SerialBT.write(-1);
  }
  
  //3)If the water level gets low enough, count it as a bottle consumed
  if(currentVolumeML < 10 && prevVolumeML > 10)
  {
    bottlesConsumed++;
  }





   
}
