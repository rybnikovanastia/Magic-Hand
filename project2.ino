
#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;

#define sensorA_Pin A4
#define sensorA_firstNeopixel 0
#define sensorA_lastNeopixel 9

#define sensorB_Pin A7
#define sensorB_firstNeopixel 0
#define sensorB_lastNeopixel 9

#define sensorC_Pin A0

int sensorA_low = 0;
int sensorA_high = 1023;

int sensorB_low = 100;
int sensorB_high = 300;

int sensorA_constrained;
int sensorB_constrained;

int sensorA_mapped;
int sensorB_mapped;

int sensorA_value;
int sensorB_value;

int sensorC_pressed;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  pinMode(sensorC_Pin, INPUT);
}

void loop() {
  CircuitPlayground.clearPixels();
  sensorA_value = analogRead(sensorA_Pin);
  sensorA_constrained = constrain(sensorA_value, sensorA_low, sensorA_high);
  sensorA_mapped = map(sensorA_constrained, sensorA_low, sensorA_high, sensorA_firstNeopixel, sensorA_lastNeopixel+1);

  sensorB_value = analogRead(sensorB_Pin);
  sensorB_constrained = constrain(sensorB_value, sensorB_low, sensorB_high);
  sensorB_mapped = map(sensorB_constrained, sensorB_low, sensorB_high, sensorB_firstNeopixel, sensorB_lastNeopixel+1);

  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);

  Serial.print("Sensor A: ");
  Serial.print(sensorA_value);
  Serial.print("\t");

  Serial.print("Sensor B: ");
  Serial.print(sensorB_value);
  Serial.println("\t");

  sensorC_pressed = digitalRead(sensorC_Pin);
  Serial.print("Sensor C: ");
  Serial.print(sensorC_pressed);

if (sensorA_value > sensorB_value) {
for (int i = sensorA_firstNeopixel; i < sensorA_mapped; i++) {
    CircuitPlayground.setPixelColor(i, abs(X)*20, 0, 255);
  }
} else if (sensorB_value > sensorA_value) {
for (int i = sensorB_firstNeopixel; i < sensorB_mapped; i++) {
    CircuitPlayground.setPixelColor(i, abs(Y)*20, 255, 0);
  }
}

if (sensorC_pressed == HIGH) {
    CircuitPlayground.playTone(abs(Z)*50, 200);
  }

  delay(100);
}