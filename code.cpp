
#define BLYNK_TEMPLATE_ID "TMPL2XwR4EOjv"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "pFgqJTbW3W7jjG1kK89U4ekstncklgcg"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// === WiFi ===
char ssid[] = "hlc";
char pass[] = "09876543211";

// === OLED ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// === Pins ===
const int Gas34 = 34;
const int ledPin = 25;

// === Variables ===
const int warmupTime = 60000; // 60 sec
const int baselineSamples = 50;
const int detectionThresholdOffset = 200;
const int hysteresis = 50;
const int numReadings = 10;

int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

int baseline = 0;
int gasDetected = 0;

unsigned long lastMeasureTime = 0;
unsigned long interval = 1000;

void setup() {

Serial.begin(9600);
pinMode(Gas34, INPUT);
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);

if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

Serial.println(F("SSD1306 failed"));
while (true);
}

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);

// Phase de chauffe avec countdown
for (int i = warmupTime / 1000; i >= 0; i--) {

display.clearDisplay();
display.setCursor(0, 10);
display.println(F("Sensor Warmup"));
display.setCursor(20, 35);
display.print(i);
display.print(F(" sec"));
display.display();
delay(1000);
}

// Calcul automatique baseline
long sumBaseline = 0;
for (int i = 0; i < baselineSamples; i++) {

int val = analogRead(Gas34);
sumBaseline += val;
display.clearDisplay();
display.setCursor(0, 10);
display.println(F("Calibrating..."));
display.setCursor(0, 35);
display.print("Read: ");
display.print(val);
display.display();
delay(500);
}
baseline = sumBaseline / baselineSamples;
Serial.print(F("Baseline established: "));
Serial.println(baseline);

display.clearDisplay();
display.setCursor(0, 10);
display.println(F("Baseline OK"));
display.setCursor(0, 35);
display.print(F("Value: "));
display.print(baseline);
display.display();
delay(2000);

// Initialisation tableau
for (int i = 0; i < numReadings; i++) {

readings[i] = baseline;
}

WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED) {

delay(1000);
Serial.println(F("Connecting WiFi..."));
}
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {

Blynk.run();
unsigned long currentMillis = millis();
if (currentMillis - lastMeasureTime >= interval) {

lastMeasureTime = currentMillis;

// Moyenne glissante
total -= readings[readIndex];
readings[readIndex] = analogRead(Gas34);
total += readings[readIndex];
readIndex = (readIndex + 1) % numReadings;
average = total / numReadings;

int threshold = baseline + detectionThresholdOffset;

display.clearDisplay();
display.setTextSize(1);
display.setCursor(0, 0);
display.print("Gas: ");
display.println(average);
display.setCursor(0, 15);
display.print("Baseline: ");
display.println(baseline);
display.setCursor(0, 30);
display.print("Seuil: ");
display.println(threshold);

if (!gasDetected && average > threshold) {

gasDetected = 1;
display.setCursor(0, 50);
display.println("GAS Detected!");
Blynk.virtualWrite(V1, 1);
Blynk.logEvent("gas_alert", "ALERTE: Gaz détecté !");
digitalWrite(ledPin, HIGH);
} else if (gasDetected && average < (threshold - hysteresis)) {

gasDetected = 0;
display.setCursor(0, 50);
display.println("Safe Air");
Blynk.virtualWrite(V1, 0);
digitalWrite(ledPin, LOW);
} else {

display.setCursor(0, 50);
display.println(gasDetected ? "GAS Alert ON" : "Safe Air");
}

display.display();

// Envoyer valeurs sur Blynk
Blynk.virtualWrite(V4, average);
}
}