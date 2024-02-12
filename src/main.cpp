#include <Arduino.h>
// import des fonctions utiles pour le moteur
# include "motor.h"
# include "sensor.h"

// ----------------- Variables globales -----------------
#define SWLOWING_MULTIPLIER 1.8

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
  if (triggered_left) {
    slowDownMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    smoothStopMotor2();
    if (SENSOR_MIDDLE()) {
      triggered_left = 0;
    }
  // Si le capteur droit est actif
  } else if (triggered_right) {
    smoothStopMotor1();
    slowDownMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
    if (SENSOR_MIDDLE()) {
      triggered_right = 0;
    }
  } else {
    smoothStartMotor1(1);
    smoothStartMotor2(1);
  }
}

// ----------------- Initialisation (setup) -----------------
void setup() {
  // Initialisation des elements
  initMotor();
  initSensor();

  // Initialisation de la communication série (utile pour debug)
  Serial.begin(9600);
}

// ----------------- Boucle principale (loop) -----------------
void loop() {
  update_trigger();
  driveRobot();
}
