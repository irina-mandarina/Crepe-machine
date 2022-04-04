// stepper 1 - left
const int dir1 = 1;
const int step1 = 2;

// stepper 2 - right
const int dir2 = 3;
const int step2 = 4;

//button
const int button = 5;

const int turnover = 400; // 360 deg / 0.9 deg per step = 400 steps
const int rotateSpeed = 500; // 500 microseconds
const int flipDelay = 2*60*1000; // second motor will activate 2 minutes after the first one

void setup() {
  Serial.begin(9600);
  
  pinMode(dir1, OUTPUT); // dir stepper 1
  pinMode(step1, OUTPUT); // step stepper 1
  
  pinMode(dir2, OUTPUT); // dir stepper 2
  pinMode(step2, OUTPUT); // step stepper 2
  
  pinMode(button, INPUT);
  
  while(1) {
    if (button == LOW) {
      Serial.println("Waiting for button press = batter on pan 1");
    }
    else {
      Serial.println("Button state = " + button);
      Serial.println("Entering the mainloop");
      break;
    }
  }
}

void makeSteps(const int stepperIndex, const int steps, const int left) {
  int dir, step;
  if (stepperIndex == 1) {
    dir = dir1;
    step = step1;
  }
  else if (stepperIndex == 2) {
    dir = dir2;
    step = step2;
  }
  
  // set direction
  if (left == 1) {
    digitalWrite(dir, HIGH);
  }
  else {
    digitalWrite(dir, LOW);
  }
  
  // make steps
  for(int i = 0; i < steps; i++){
    digitalWrite(step, HIGH);
    delayMicroseconds(rotateSpeed); // rotate
    digitalWrite(step, LOW);
    delayMicroseconds(rotateSpeed); // rotate
  }
}

void flip(const int stepperIndex) {
  Serial.print("Flipping stepper ");
  Serial.println(stepperIndex);
  
  makeSteps(stepperIndex, turnover/2, 1);
  
  Serial.print("Flipped stepper ");
  Serial.println(stepperIndex);
}

void loop() {
  flip(1);
  delay(1000);
  makeSteps(1, 200, 1);
  flip(2);
}
