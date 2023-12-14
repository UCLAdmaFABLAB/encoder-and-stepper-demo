#include <Encoder.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"

int const MODE_LED = 11;
int const MOTOR_HOME_LED = 6;
int const ENCODER_HOME_LED = 7;

int const REED_SWITCH_PIN = 4;

int const RESET_BUTTON_PIN = 10;

String state = "HOMING MOTOR";
bool buttonReady = true;

long SerialTimerFire = 0;
long SerialTimerInterval = 30;
int const DRIVER_M0_PIN = 12;
int const DRIVER_M1_PIN = 13;

float const MOTOR_DEGREES_PER_STEP = 1.8;

int const ENCODER_HOME_PIN = 5;
int const ENCODER_A_PIN = 2;
int const ENCODER_B_PIN = 3;

int const ENCODER_STEPS = 4096;
float const ENCODER_DEGREES_PER_STEP = 360.0 / float(ENCODER_STEPS);
float const ENCODER_STEPS_PER_DEGREE = float(ENCODER_STEPS) / 360.0;

long encoderStepAcum = 0;
long encoderAcumRelativeToHome = 0;
long encoderPositionDegrees = 0;
long encoderDegreesAbsolute = 0;
long encoderTrackAcum = 0;

int const encoderHomeOffset = 93;  // in degerees
int const encoderHomeMargin = 2;

bool motorIsHome = false;

bool encoderIsHome = false;
bool encoderIsZeroed = false;
bool buttonHasBeenPressed = false;

long lastKnownEncoderZero = 0;
bool encoderHasZeroed = false;

long CWEncoderHome = 0;
long CCWEncoderHome = 0;


float motorMovementAcum = 0.0;


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(ENCODER_B_PIN, ENCODER_A_PIN);

// sketchy encoder library stuff
long oldEncoderPosition = -999;
long encoderAcumDebug = 0;


// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
int const MOTOR_STEPS = 200;
int const RPM = 200;

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
int const MICROSTEPS = 1;

// All the wires needed for full functionality
int const DIR = 8;
int const STEP = 9;
//Uncomment line to use enable/disable functionality
//#define SLEEP 13


// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

// LED blinking
long const ledInterval = 50;
long lastLedSwitch = 0;
bool modeLedState = false;

// util timer

long timerInterval = 2000;
long timerFire = 0;
long timerIsRunning = false;

float encoderDeltaAcum = 0;

int speedLimit = 3;

//---------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:

  pinMode(DRIVER_M0_PIN, OUTPUT);
  pinMode(DRIVER_M1_PIN, OUTPUT);
  digitalWrite(DRIVER_M0_PIN, LOW);
  digitalWrite(DRIVER_M1_PIN, LOW);
  stepper.begin(RPM, MICROSTEPS);

  Serial.begin(9600);
  delay(2000);
  pinMode(MOTOR_HOME_LED, OUTPUT);
  pinMode(ENCODER_HOME_LED, OUTPUT);
  pinMode(MODE_LED, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(MODE_LED, LOW);

  reportState();

}

//---------------------------------------------------------------------

void loop() {

  readEncoder();
  checkButton();
  checkEncoderZ();
  checkEncoderHome();
  checkMotorHome();
  handleLEDs();

  if (state.equals("HOMING MOTOR")) {
    if (!motorIsHome) {
      stepper.rotate(-2);
      delay(10);
    } else {
      changeState("WAITING FOR Z");
    }
  } else if (state.equals("WAITING FOR Z")) {
    if (encoderHasZeroed) {
      changeState("WAITING FOR HOME");
    }
  } else if (state.equals("WAITING FOR HOME")) {
    if (encoderIsHome) {
      changeState("HOME");
    }
  } else if (state.equals("HOME")) {
    if (!encoderIsHome) {
      encoderDeltaAcum = 0;
      encoderDegreesAbsolute = 0;
      encoderTrackAcum = 0;
      changeState("TRACKING");
    }
  } else if (state.equals("TRACKING")) {
    encoderPositionDegrees = encoderAcumRelativeToHome * (1.0) / ENCODER_STEPS_PER_DEGREE;
    encoderDegreesAbsolute = encoderTrackAcum * 1.0 / ENCODER_STEPS_PER_DEGREE;

    if (encoderPositionDegrees < 0) {
      encoderPositionDegrees = 360 + encoderPositionDegrees;
    }

    if (encoderPositionDegrees > 360) {
      encoderPositionDegrees = encoderPositionDegrees % 360;
    }

    float deltaThreshold = MOTOR_DEGREES_PER_STEP;
    float angleDelta = encoderDegreesAbsolute - encoderDeltaAcum;

    if (abs(angleDelta) > speedLimit) {
      changeState("TOO FAST");
    }
    if (angleDelta >= deltaThreshold || angleDelta <= -deltaThreshold) {
      int steps = int(angleDelta / MOTOR_DEGREES_PER_STEP);
      stepper.move(-steps);
      float remain = angleDelta - (steps * MOTOR_DEGREES_PER_STEP);
      encoderDeltaAcum = encoderDegreesAbsolute - remain;
    }
  } else if (state.equals("TOO FAST")) {
    setTimer(2000);
    changeState("WAITING TO RESET");
  } else if (state.equals("WAITING TO RESET")) {
    blinkLED();
    if (checkTimer()) {
      resetToStart();
    }
  }
}

//---------------------------------------------------------------------

void changeState(String s) {
  state = s;
  reportState();
}

//---------------------------------------------------------------------

void checkButton() {
  if (digitalRead(RESET_BUTTON_PIN)) {
    buttonReady = true;
  } else if (digitalRead(RESET_BUTTON_PIN) == LOW && buttonReady) {
    //reportAngle();
    setTimer(500);
    changeState("WAITING TO RESET");
    buttonReady = false;
  }
}

//---------------------------------------------------------------------


void resetToStart() {
  encoderHasZeroed = false;
  encoderIsZeroed = false;
  changeState("HOMING MOTOR");
}