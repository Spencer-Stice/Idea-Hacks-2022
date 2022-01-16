#define LMotor_1 8
#define LMotor_2 7
#define LMotor_S 5
#define RMotor_1 2
#define RMotor_2 4
#define RMotor_S 3
#define ARP 0
#define echoPin 12
#define trigPin 10

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(LMotor_1,OUTPUT);
  pinMode(LMotor_2, OUTPUT);
  pinMode(LMotor_S, OUTPUT);
  pinMode(RMotor_1,OUTPUT);
  pinMode(RMotor_2, OUTPUT);
  pinMode(RMotor_S, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
    {
      int currByte = Serial.read();
      if(currByte == 1)//forwards
        {
          digitalWrite(LMotor_1, HIGH);//both go forwards
          digitalWrite(LMotor_2, LOW);
          analogWrite(LMotor_S, 255);
          digitalWrite(RMotor_1, HIGH);
          digitalWrite(RMotor_2, LOW);
          analogWrite(RMotor_S, 255);
          Serial.println("FORWARDS");
         }
      else if(currByte == 2)//backwards
         {
          digitalWrite(LMotor_1, LOW);//both go backwards
          digitalWrite(LMotor_2, HIGH);
          analogWrite(LMotor_S, 255);
          digitalWrite(RMotor_1, LOW);
          digitalWrite(RMotor_2, HIGH);
          analogWrite(RMotor_S, 255);
          Serial.println("BACKWARDS");
         }
      else if(currByte ==3)//stop
        {
          digitalWrite(LMotor_1, LOW);//both go backwards
          digitalWrite(LMotor_2, LOW);
          analogWrite(LMotor_S, 255);
          digitalWrite(RMotor_1, LOW);
          digitalWrite(RMotor_2, LOW);
          analogWrite(RMotor_S, 255);
          Serial.println("STOP");
        }
      else if(currByte ==4)//turn
        {
          digitalWrite(LMotor_1, HIGH);//both go backwards
          digitalWrite(LMotor_2, LOW);
          analogWrite(LMotor_S, 255);
          digitalWrite(RMotor_1, LOW);
          digitalWrite(RMotor_2, LOW);
          analogWrite(RMotor_S, 0);
          Serial.println("LEFT");
        }
      else if(currByte ==5)//turn
        {
          digitalWrite(LMotor_1, HIGH);//both go backwards
          digitalWrite(LMotor_2, LOW);
          analogWrite(LMotor_S, 0);
          digitalWrite(RMotor_1, HIGH);
          digitalWrite(RMotor_2, LOW);
          analogWrite(RMotor_S, 255);
          Serial.println("RIGHT");
         }
  }
}
