#include <Servo.h>

Servo gate;

// IR pins
const int irEntry = 2;
const int irExit = 3;

// Parking count
int carCount = 0;
const int maxSlots = 4;

// State tracking
int lastEntryState = HIGH;
int lastExitState = HIGH;

void setup() {
  pinMode(irEntry, INPUT);
  pinMode(irExit, INPUT);

  gate.attach(9);
  gate.write(0); // Gate closed

  Serial.begin(9600);
  Serial.println("Smart Parking System Started");
}

void loop() {

  int entryState = digitalRead(irEntry);
  int exitState = digitalRead(irExit);

  // ENTRY
  if (entryState == LOW && lastEntryState == HIGH) {

    if (carCount < maxSlots) {
      Serial.println("Car Entering...");

      gate.write(90); // Open gate
      delay(2500);

      gate.write(0); // Close gate
      delay(1000);

      carCount++;
      Serial.print("Cars inside: ");
      Serial.println(carCount);
    }
    else {
      Serial.println("Parking FULL");
    }
  }

  // EXIT
  if (exitState == LOW && lastExitState == HIGH) {

    Serial.println("Car Exiting...");

    gate.write(90);
    delay(2500);

    gate.write(0);
    delay(1000);

    if (carCount > 0) {
      carCount--;
    }

    Serial.print("Cars inside: ");
    Serial.println(carCount);
  }

  // Save states
  lastEntryState = entryState;
  lastExitState = exitState;

  delay(100);
}
