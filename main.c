// stepper 1 - left
const int dir1 = 2;
const int step1 = 3;

// stepper 2 - right
const int dir2 = 5;
const int step2 = 6;

//button
const int button = 7;

const int turnover = 400; // 360 deg / 0.9 deg per step = 400 steps
const int rotateSpeed = 500; // 500 microseconds
const int flipDelay = 2 * 60 * 1000; // second motor will activate 2 minutes after the first one

void setup() {
  Serial.begin(9600);

  pinMode(dir1, OUTPUT); // dir stepper 1
  pinMode(step1, OUTPUT); // step stepper 1

  pinMode(dir2, OUTPUT); // dir stepper 2
  pinMode(step2, OUTPUT); // step stepper 2

  pinMode(button, INPUT);

  // wait for button press. The button should be pressed when the first serving of batter is poured on the first pan
  while (1) {
    if (digitalRead(button) == HIGH) {
      Serial.println("Button state = " + digitalRead(button));
      Serial.println("Entering the mainloop");
      break;
    }
    else {
      Serial.println("Waiting for button press = batter on pan 1");
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
  for (int i = 0; i < steps; i++) {
    digitalWrite(step, HIGH);
    delayMicroseconds(rotateSpeed); // rotate
    digitalWrite(step, LOW);
    delayMicroseconds(rotateSpeed); // rotate
  }
}

void flip(const int stepperIndex) {
  Serial.print("Flipping stepper ");
  Serial.println(stepperIndex);

  makeSteps(stepperIndex, turnover / 2, 1);
  delay(500);
  makeSteps(stepperIndex, turnover / 2, 0);

  Serial.print("Flipped stepper ");
  Serial.println(stepperIndex);
}

void loop() {
  // the batter is poured. wait
  delay(1000);
  // the first side is done cooking. flip
  flip(1);
  // wait for the second side
  delay(1000);
  // flip onto the plate.
  flip(2);
  // wait for the user to press the button (that means that he has poured the batter)
  while (1) {
    if (digitalRead(button) == HIGH) {
      Serial.println("Button state = " + digitalRead(button));
      break;
    }
    else {
      Serial.println("Waiting for button press = batter on pan 1");
    }
  }
}
