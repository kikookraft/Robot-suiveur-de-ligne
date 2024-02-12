#include <Arduino.h>
// import des fonctions utiles pour le moteur
# include "motor.h"
# include "sensor.h"

#define SWLOWING_MULTIPLIER 2
// déclaration des fonctions de test
void test1();
void test2();
void test3();
void test4();


// ----------------- Initialisation -----------------
void setup() {
  // Initialisation des elements
  initMotor();
  initSensor();

  // Initialisation de la communication série (utile pour debug)
  Serial.begin(9600);
}

// ----------------- Boucle principale -----------------
void loop() {
  // test1();
  // test2();
  // test3();
  test4();
}


// ----------------- Fonctions de tests random -----------------
void test1() {
  // ce test allume les moteurs de manière "fluide", c'est à dire que la vitesse augmente progressivement et décroit progressivement
  // et ceci en fonction du capteur activé

  // si le capteur gauche est actif allumer moteur 1
  if (SENSOR_LEFT()) {
    smoothStartMotor1(1);
  } else {
    smoothStopMotor1();
  }
  // si le capteur droit est actif allumer moteur 2
  if (SENSOR_RIGHT()) {
    smoothStartMotor2(1);
  } else {
    smoothStopMotor2();
  }
}

void test2() {
  // ce test allume les moteurs de manière "brutale", c'est à dire que la vitesse augmente directement à la vitesse maximale
  // et ceci en fonction du capteur activé

  if (SENSOR_LEFT()) {
    forwardMotor1();
    speedMotor1(255);
  } else {
    stopMotor1();
  }
  if (SENSOR_RIGHT()) {
    forwardMotor2();
    speedMotor2(255);
  } else {
    stopMotor2();
  }
}

void test3() {
  #if TROIS_CAPTEURS
  // fonctionne dans le scénario 3 capteurs
  // ce test utilise les deux méthode en fonction de la position du capteur

  #else
  // fonctionne dans le scénario 2 capteurs
  // ce test utilise les deux méthode en fonction de la position du capteur
  if (SENSOR_LEFT()) {
    slowDownMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    smoothStopMotor2();
  } else if (SENSOR_RIGHT()) {
    smoothStopMotor1();
    slowDownMotor2(MAX_SPEED/SWLOWING_MULTIPLIER);
  } else {
    smoothStartMotor1(1);
    smoothStartMotor2(1);
  }
  #endif
}

int triggered_left = 0;
int triggered_right = 0;
int allow_trigger_left = 1;
int allow_trigger_right = 1;

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


void test4() {
  update_trigger();

  if (triggered_left) {
    slowDownMotor1(MAX_SPEED/SWLOWING_MULTIPLIER);
    smoothStopMotor2();
    if (SENSOR_MIDDLE()) {
      triggered_left = 0;
    }
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