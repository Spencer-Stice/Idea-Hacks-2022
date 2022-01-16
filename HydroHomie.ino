#define trigPin 5
#define echoPin 18

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
}

const int MEASURE_TIMES = 30;
const int SOUND_SPEED = 34300; //cm/second
const int CALIBRATION_VOLUME = 100; //volume, in mL, that is used for calibration
int bottle_height = 20;
int bottle_area = 35;

void loop() {
  /*int water_volume = measureWater();
  Serial.println("Water Volume: " + String(water_volume));*/

  calibrateHeight();
  Serial.println(String(bottle_height));
  delay(1000);
}


//takes in bottle parameters, returns amount of water in bottle (in mL)
//returns -1 if the cap has been removed
int measureWater() {
  int average_time = measureTime();

  //water_height in cm
  int water_height = bottle_height - SOUND_SPEED * average_time / 2000000;

  if (water_height < 0)
    return -1;
  
  int volume = bottle_area * water_height;
  return volume;
}

//uses ultrasonic sensor, returns average value over MEASURE_TIMES trials
int measureTime() {
  int sum = 0;
  for (int i=0;i<MEASURE_TIMES; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    sum += pulseIn(echoPin, HIGH);
  }
  return sum / MEASURE_TIMES;
}

//sets the bottle height, used when the bottle is empty
void calibrateHeight() {
  int average_time = measureTime();
  bottle_height = SOUND_SPEED * average_time / 2000000;
  
  return;
}

//sets the bottle area, used when the bottle has CALIBRATION_VOLUME water inside
void calibrateArea() {
  int average_time = measureTime();
  int water_height = bottle_height - SOUND_SPEED * average_time / 2000000;
  
  //CALIBRATION_VOLUME (in mL) / height (in cm) = area (in cm^2)
  bottle_area = CALIBRATION_VOLUME / water_height;
  
  return;
}
