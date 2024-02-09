#include <Arduino.h>
// import des fonctions utiles pour le moteur
# include "motor.h"

// déclaration des fonctions de test
void test1();
void test2();

// capteurs
#define CAPTEUR_LEFT 13
#define CAPTEUR_RIGHT 12

// ----------------- Initialisation -----------------
void setup() {
  // Configuration des ports en mode "sortie"
  pinMode(CAPTEUR_LEFT, INPUT);
  pinMode(CAPTEUR_RIGHT, INPUT);
  initMotor();

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
  if (digitalRead(CAPTEUR_LEFT) == LOW) {
    smoothStartMotor1(1);
  } else {
    smoothStopMotor1();
  }
  // si le capteur droit est actif allumer moteur 2
  if (digitalRead(CAPTEUR_RIGHT) == LOW) {
    smoothStartMotor2(1);
  } else {
    smoothStopMotor2();
  }
}

void test2() {
  // ce test allume les moteurs de manière "brutale", c'est à dire que la vitesse augmente directement à la vitesse maximale
  // et ceci en fonction du capteur activé

  if (digitalRead(CAPTEUR_LEFT) == LOW) {
    forwardMotor1();
    speedMotor1(255);
  } else {
    stopMotor1();
  }
  if (digitalRead(CAPTEUR_RIGHT) == LOW) {
    forwardMotor2();
    speedMotor2(255);
  } else {
    stopMotor2();
  }
}