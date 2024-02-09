#include <Arduino.h>
// import des fonctions utiles pour le moteur
# include "motor.h"
# include "sensor.h"

#define MAX_SPEED 255
// déclaration des fonctions de test
void test1();
void test2();


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
  test1();
  // test2();
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
  // ce test utilise les deux méthode en fonction de la position du capteur
  switch (linePosition()) {
  case -2:
    // si la ligne est à l'extreme gauche alors on arrete le moteur 1 et on démarre le moteur 2
    stopMotor1();
    startMotor2(1, MAX_SPEED);
    break;
  
  case -1:
    // si la ligne est à gauche alors on ralentis le moteur 1 et on laisse le moteur 2 à la vitesse maximale
    smoothStopMotor1();
    startMotor2(1, MAX_SPEED);
    break;
  
  case 0:
    // si la ligne est au centre alors on accélère a nouveau
    smoothStartMotor1(1);
    smoothStartMotor2(1);
    break;

  case 1:
    // si la ligne est à droite alors on laisse le moteur 1 à la vitesse maximale et on ralentis le moteur 2
    startMotor1(1, MAX_SPEED);
    smoothStopMotor2();
    break;

  case 2:
    // si la ligne est à l'extreme droite alors on démarre le moteur 1 et on arrete le moteur 2
    startMotor1(1, MAX_SPEED);
    stopMotor2();
    break;

  default:
    // si aucun capteur n'est actif alors on arrete les deux moteurs
    stopMotor1();
    stopMotor2();
    break;
  }
}