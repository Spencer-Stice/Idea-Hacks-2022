//#include <BluetoothSerial.h>

/*#define trigPin D12
#define echoPin D13
#define ledPIN 2
*/
#define powerPin 20

long int duration;
//BluetoothSerial SerialBT;
//byte BTData;

/* Check if Bluetooth configurations are enabled in the SDK */
/*#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
*/

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
 // SerialBT.begin();
 // Serial.println("Bluetooth Started! Ready to pair...");
  digitalWrite(powerPin, HIGH);
}

void loop()
{
 /* if(SerialBT.available())
  {
    BTData = SerialBT.read();
    Serial.write(BTData);
  }
  */
  digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

   duration = pulseIn(echoPin, HIGH);
   Serial.println(duration);

   delay(20);

}
