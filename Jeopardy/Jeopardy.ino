/**
* Stuyvesant Jeopardy System
* @author FRC694
*
* This system is a replica of Jeopardy and works as follows:
* - There are 4 "contestants": 1 parent, 1 teacher, 1 alumnus, 1 team of students
*   - The team of students consists of 4 students
* - The moderator asks a question.
* - The contestants buzz to answer the question
*   - The buzzer sounds to indicate that the answering period has begun
*   - The contestant has 5 seconds to answer the question
*     - If the constestant answers correctly, the moderator presses his button, after which any contestant may buzz to answer again.
*     - If the contestant answers falsely (or doesn't answer), everyone must wait until his questioning period is up, at which point the buzzer sounds twice and anyone else may answer.
* - If any student answers falsely, the entire team of students is seen as having answered falsely.
* - A contestant has 5 seconds to answer a question after buzzing and being selected to answer.
*/

unsigned int contest_pin[] = {9,10,11,12}; // GPIO pins on buzzer #s 0-3
unsigned int moderator_pin = 5; // GPIO pin on the moderator button

unsigned int contest_light[] = {0,1,2,0,1,2,3,4}; // GPIO pins on light #s 0-3
unsigned int moderator_light = 3;

boolean correct_answer = false;

unsigned int claxon_pin = 4; // GPIO pin on the speaker
int i; // iterator

boolean answers[] = {false, false, false, false};


boolean hasAnswered(int contestant) {
  if (contestant > 2) {
    return answers[3];
  }
  else {
    return answers[contestant];
  }
}

void setAnswer(int contestant, boolean set) {
  if (contestant > 2) {
    answers[3] = set;
  }
  else {
    answers[contestant] = set;
  }
}
void setup() {
  Serial.begin(9600);
  
  for (i = 0; i < 4; i++)  {
    pinMode(contest_pin[i], INPUT); // allocate and configure contestant input lines
    pinMode(contest_light[i], OUTPUT); // allocate and configure contestant output lines
  }
  pinMode(moderator_pin, INPUT); // allocate and configure moderator input
  pinMode(moderator_light, OUTPUT);
  pinMode(claxon_pin, OUTPUT); // allocate and configure speaker line
  
  i = 0; // initialize iterator
}

void lightOn(int pin) {
  //turn on correct pin
}
void loop() {
  if (isPressed(i) && !hasAnswered(i)) {
    // if contestant who *can* answer questions...
    int start = millis();
    
    lightOn(i); //enable that light
    //signalStart(); //Sound the claxon!
    
    digitalWrite(contest_light[i], HIGH); // turn the light on
    tone(claxon_pin, 150, 200); //------ pulse the speaker on
    
    while (millis() - start < 5000) {
      if (isPressed(moderator_pin)) {
       correct_answer = true;
        break;
      }
    }
    // give contestant 5 seconds to respond
    
    if (!correct_answer) {
      setAnswer(i, true);
    }
    soundEnd(claxon_pin);
    digitalWrite(contest_light[i], LOW); //light off
    // signalEnd();
    // signal that the waiting period is over or question has been answered
  }
  
  i = (i +1) % 4; //
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
