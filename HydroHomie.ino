#define trigPin 5
#define echoPin 18

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
}

const int MEASURE_TIMES = 30;
const int SOUND_SPEED = 34300; //cm/second
const int bottle_height = 20;
const int bottle_area = 35;
void loop() {
  int water_volume = measureWater(bottle_height, bottle_area);
  Serial.println("Water Volume: " + String(water_volume));
  delay(1000);
}


//takes in bottle parameters, returns amount of water in bottle (in mL)
//returns -1 if the cap has been removed
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
