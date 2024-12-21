#include <AFMotor.h>
#include <avr/wdt.h>

// Motor definitions for L293D shield
AF_DCMotor motor1(1);  // Left front
AF_DCMotor motor2(2);  // Right front
AF_DCMotor motor3(3);  // Left rear
AF_DCMotor motor4(4);  // Right rear

// Control variables
char receivedChar;
int currentSpeed = 255;  // Default speed
const int SPEED_STEP = 25;  // Speed increment/decrement step

// Basic safety parameters for Uno
const unsigned long COMMAND_TIMEOUT = 1000;  // Stop if no command received for 1 second
unsigned long lastCommandTime = 0;
bool isMoving = false;

void setup() {
  // Initialize serial for HC-05 (default baud rate)
  Serial.begin(9600);
  
  // Enable watchdog with 2-second timeout
  wdt_enable(WDTO_2S);
  
  // Initialize motors
  setAllSpeeds(currentSpeed);
  stopMotors();
  
  // Small delay to ensure stable startup
  delay(100);
}

void loop() {
  // Reset watchdog
  wdt_reset();
  
  // Basic timeout safety check
  if(isMoving && (millis() - lastCommandTime > COMMAND_TIMEOUT)) {
    stopMotors();
    isMoving = false;
  }
  
  // Check for commands from HC-05
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    lastCommandTime = millis();
    processCommand(receivedChar);
  }
}

void processCommand(char command) {
  switch (command) {
    case 'F': startMovement(); moveForward(); break;
    case 'B': startMovement(); moveBackward(); break;
    case 'L': startMovement(); turnLeft(); break;
    case 'R': startMovement(); turnRight(); break;
    case 'FL': startMovement(); moveForwardLeft(); break;
    case 'FR': startMovement(); moveForwardRight(); break;
    case 'DR': startMovement(); moveDownRight(); break;
    case 'DL': startMovement(); moveDownLeft(); break;
    case 'S': stopMotors(); isMoving = false; break;
    case '+': increaseSpeed(); break;
    case '-': decreaseSpeed(); break;
    default: stopMotors(); isMoving = false; break;
  }
}

void startMovement() {
  isMoving = true;
  lastCommandTime = millis();
}

void setAllSpeeds(int speed) {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void increaseSpeed() {
  if (currentSpeed <= 255 - SPEED_STEP) {
    currentSpeed += SPEED_STEP;
    setAllSpeeds(currentSpeed);
  }
}

void decreaseSpeed() {
  if (currentSpeed >= SPEED_STEP) {
    currentSpeed -= SPEED_STEP;
    setAllSpeeds(currentSpeed);
  }
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);  // Left side backward
  motor2.run(FORWARD);   // Right side forward
  motor3.run(BACKWARD);  // Left side backward
  motor4.run(FORWARD);   // Right side forward
}

void turnRight() {
  motor1.run(FORWARD);   // Left side forward
  motor2.run(BACKWARD);  // Right side backward
  motor3.run(FORWARD);   // Left side forward
  motor4.run(BACKWARD);  // Right side backward
}

void moveForwardLeft() {
  // Reduced speed on left side for gradual turn
  motor1.setSpeed(currentSpeed / 2);
  motor3.setSpeed(currentSpeed / 2);
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  // Restore normal speed
  motor1.setSpeed(currentSpeed);
  motor3.setSpeed(currentSpeed);
}

void moveForwardRight() {
  // Reduced speed on right side for gradual turn
  motor2.setSpeed(currentSpeed / 2);
  motor4.setSpeed(currentSpeed / 2);
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  // Restore normal speed
  motor2.setSpeed(currentSpeed);
  motor4.setSpeed(currentSpeed);
}

void moveDownRight() {
  motor1.run(FORWARD);   // Left side forward
  motor2.run(RELEASE);   // Right side stop
  motor3.run(FORWARD);   // Left side forward
  motor4.run(RELEASE);   // Right side stop
}

void moveDownLeft() {
  motor1.run(RELEASE);   // Left side stop
  motor2.run(FORWARD);   // Right side forward
  motor3.run(RELEASE);   // Left side stop
  motor4.run(FORWARD);   // Right side forward
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
