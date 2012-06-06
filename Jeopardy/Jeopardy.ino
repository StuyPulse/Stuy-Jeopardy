unsigned int contest_pin[] = {4,5,6,7}; // GPIO pins on buzzer #s 0-3
unsigned int light_pin[] = {0,1,2,3}; // GPIO pins on light #s 0-3
unsigned int moderator_pin = 11; // GPIO pin on the moderator button
unsigned int claxon_pin = 12; // GPIO pin on the speaker
int i; // iterator

void setup() {
  Serial.begin(9600);
  
  for (i = 0; i < 4; i++)  {
    pinMode(contest_pin[i], INPUT); // allocate and configure contestant input lines
    pinMode(light_pin[i], OUTPUT); // allocate and configure contestant output lines
  }
  pinMode(moderator_pin, OUTPUT); // allocate and configure moderator input
  pinMode(claxon_pin, OUTPUT); // allocate and configure speaker line
  
  i = 0; // initialize iterator
}

void loop() {
  if (isPressed(contest_pin[i])) {
    int start = millis();
    
    digitalWrite(light_pin[i], HIGH); // turn the light on
    tone(claxon_pin, 150, 200); //------ pulse the speaker on
    
    while (millis() - start <= 5000 && digitalRead(moderator_pin));
    // give contestant 5 seconds to respond
    
    soundEnd(claxon_pin);
    // signal that the waiting period is over or question has been answered
  }
}

boolean isPressed(unsigned int pin) { // All the switches are pulled up
  if (digitalRead(pin)) //-------------- meaning that it is HIGH by 
    return false; //-------------------- default and has an active LOW
  else 
    return true;
}

void soundEnd(unsigned int speaker_line) {
  //pulses the speaker twice in quick succession
  
  int frequency = 300; // in Hz
  int duration = 75; //in msec
  
  tone(speaker_line, frequency, duration);
  noTone(speaker_line);
  delay(50);
  tone(speaker_line, frequency, duration);
  noTone(speaker_line);
}
