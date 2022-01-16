

#include <BluetoothSerial.h>

#define trigPin 5
#define powerPin 21
#define echoPin 18

int duration;
int readDuration;
int readDurationAvg = 0;
int avgDistance;
BluetoothSerial SerialBT;
byte BTData;

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
  readDurationAvg = 0;
  for(int i = 0; i < 30; i++)
  {
    readDurationAvg += getSensorReading();
    delay(10);
  }
  readDuration = readDurationAvg / 30;
  avgDistance = 

  if(readDuration) > 
  
   
}
