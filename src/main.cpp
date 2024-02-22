#include <Arduino.h>
// import des fonctions utiles pour le moteur
# include "motor.h"
# include "sensor.h"

// ----------------- Variables globales -----------------
#define SWLOWING_MULTIPLIER 1.2

int triggered_left = 0;
int triggered_right = 0;
int allow_trigger_left = 1;
int allow_trigger_right = 1;

// ----------------- Fonctions -----------------
// Mise à jour des triggers pour les capteurs
void update_trigger() {
  if (SENSOR_LEFT()) {
    if (allow_trigger_left) {
      triggered_left = 1;
      allow_trigger_left = 0;
    }
  } else {
    allow_trigger_left = 1;
  }
  if (SENSOR_RIGHT()) {
    if (allow_trigger_right) {
      triggered_right = 1;
      allow_trigger_right = 0;
    }
  } else {
    allow_trigger_right = 1;
  }
}

// Déplacement du robot
// Si un capteur est actif, le robot ralentit le moteur correspondant jusqu'à ce que le capteur central soit actif
void driveRobot() {
  // Si le capteur gauche est actif
  if (triggered_left && triggered_right) {
    // backwardMotor1();
    // backwardMotor2();
    forwardMotor1();
    forwardMotor2();
    slowDownMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    slowDownMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
    if (SENSOR_MIDDLE()) {
      triggered_left = 0;
      triggered_right = 0;
    }
  } else if (triggered_left) {
    speedMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    forwardMotor1();
    speedMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
    backwardMotor2();
    // stopMotor2();
    if (SENSOR_MIDDLE()) {
      triggered_left = 0;
    } else if (SENSOR_RIGHT()) {
      triggered_right = 1;
      triggered_left = 0;
    }
  // Si le capteur droit est actif
  } else if (triggered_right) {
    speedMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    backwardMotor1();
    // stopMotor1();
    speedMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
    forwardMotor2();
    if (SENSOR_MIDDLE()) {
      triggered_right = 0;
    } else if (SENSOR_LEFT()) {
      triggered_left = 1;
      triggered_right = 0;
    }
  } else {
    forwardMotor1();
    forwardMotor2();
    speedMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    speedMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
  }
}

// ----------------- Initialisation (setup) -----------------
void setup() {
  // Initialisation des elements
  initMotor();
  initSensor();

  // Initialisation de la communication série (utile pour debug)
  // Serial.begin(9600);


  //indiquer le démarrage du robot en reculant pendant 0.3 secondes
  backwardMotor1();
  backwardMotor2();
  speedMotor1(MAX_SPEED);
  speedMotor2(MAX_SPEED);
  delay(200);
  forwardMotor1();
  forwardMotor2();
  delay(200);
  stopMotor1();
  stopMotor2();
  delay(500);
}

// ----------------- Boucle principale (loop) -----------------
void loop() {
  update_trigger();
  driveRobot();
}
