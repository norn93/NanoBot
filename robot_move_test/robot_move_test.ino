//ultrasonic
//ashwin is right, these need to be moved to avoid future conflicts
#define TRIG 11
#define ECHO 12

//Motor A
#define EN1 5 //Speed control blue
#define IN1 2 //Direction green
#define IN2 3 //Direction yellow

//Motor B
#define EN2 6 //Speed control blue
#define IN3 7 //Direction green
#define IN4 8 //Direction yellow

//set this to true to always be roaming
//if you have connected up the BT module (RX to TX, TX to RX), then leave this false and watch my video
int roaming = false;

void setup() {
  initialiseUltrasonic();
  initialiseMotors();
  Serial.begin(9600);
}

void serialEvent() {
  //gets the serial input from the BT module
  //does this once per loop automatically
  //(read arduino docs for serialEvent() )
  roaming = false;
  while (Serial.available()) {
    char inChar =  (char)Serial.read();
    if (inChar == 'w') {
      stepForward();
    }
    if (inChar == 's') {
      stepBackward();
    }
    if (inChar == 'a') {
      turn(1, 45);
    }
    if (inChar == 'd') {
      turn(0, 45);
    }
    if (inChar == 'r') {
      roaming = true;
    }
  }
}

void loop() {
  if (roaming == true) { //then roam, bouncing off walls
    forward();
    delay(10);
    long distance = measureDistance();
    if (distance < 40) { //we are close to something
      backward();
      delay(350);
      turn(random(0, 2), 90);
    }
  }
}

void forward() {
  move(1, 255, 1);
  move(0, 255, 1);
}

void backward() {
  move(1, 255, 0);
  move(0, 255, 0);
}

void stopMoving() {
  move(1, 0, 0);
  move(0, 0, 0);
}

void stepForward() {
  //moves forward for 500ms
  forward();
  delay(500);
  stopMoving();
}

void stepBackward() {
  //moves backward for 500ms
  backward();
  delay(500);
  stopMoving();
}

void turn(int direction, int angle) {
  //turn by approximately 'angle' degrees
  if (direction == 0) { //left
    move(1, 255, 1);
    move(0, 255, 0);
  } else { //right
    move(1, 255, 0);
    move(0, 255, 1);
  }
  delay(angle*2.5);
  stopMoving();
}

void initialiseUltrasonic() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void initialiseMotors() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

long measureDistance() {
  //measures distance in front of the ultrasonic sensor
  //returns the distance in cm as a log float
  
  long duration, distance;
  digitalWrite(TRIG, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIG, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;
}


void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(IN1, inPin1);
    digitalWrite(IN2, inPin2);
    analogWrite(EN1, speed);
  }
  if (motor == 0) {
    digitalWrite(IN3, inPin1);
    digitalWrite(IN4, inPin2);
    analogWrite(EN2, speed);
  }
}
