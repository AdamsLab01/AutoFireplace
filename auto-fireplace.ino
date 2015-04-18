const int OnOffDetect = 0;
const int PowerSW = 3;
const int PIR = 4;

unsigned long OnTimer = 1800000; // How long (in milliseconds) we want the fireplace to stay on (30 min in this case).
unsigned long OnTimerCount = 0;
unsigned long CurrMills = 0;
unsigned long TimerPreMills = 0;

void setup() {
  pinMode(OnOffDetect, INPUT);
  pinMode(PowerSW, OUTPUT);
  pinMode(PIR, INPUT);

  digitalWrite(OnOffDetect, HIGH); // Enable internal resistor.

  OnTimerCount = OnTimer;
  
  delay(60000); // Give the PIR it's calibration time on boot.
}

void loop() {
  if (millis() - CurrMills > 1000) { // If a second has passed, subtract that from OnTimerCount. 
    OnTimerCount = OnTimerCount - 1000;
    CurrMills = millis();
  }

  if (OnTimerCount <= 0 && digitalRead(OnOffDetect) == LOW) { // If the timer runs out and the fireplace is on.
    digitalWrite(PowerSW, HIGH); // "Press" the fireplace power button to turn it off.
    delay(500);
    digitalWrite(PowerSW, LOW); // Stop pressing the fireplace power button.
    OnTimerCount = OnTimer; // Reset the timer.
  }

  if (OnTimerCount <= 0 && digitalRead(OnOffDetect) == HIGH) { // If the timer runs out and the fireplace is off.
    OnTimerCount = OnTimer; // Reset the timer.
  }

  if (digitalRead(PIR) == HIGH && digitalRead(OnOffDetect) == HIGH) { // If motion is detected and the fireplace is off.
    digitalWrite(PowerSW, HIGH); // "Press" the fireplace power button to turn it on.
    delay(500);
    digitalWrite(PowerSW, LOW); // Stop pressing the fireplace power button.
  }

  else if (digitalRead(PIR) == HIGH && digitalRead(OnOffDetect) == LOW) { // If motion is detected and the fireplace is on.
    OnTimerCount = OnTimer; // Reset the timer.
  }
}
