#include <Arduino.h>

// declaration des fonctions
void avance();
void arriere();
void stop();
void vitesse(int vitesse);

//Ports de commande du moteur B
int motorIN3 = 9;
int motorIN4 = 8;
int ENB = 5;
 
// gestions du moteur
int state = 0;
int down = 0;
int avant = 1;
int cycle = 0;

void setup() {
    // Configuration des ports en mode "sortie"
    pinMode(motorIN3, OUTPUT);
    pinMode(motorIN4, OUTPUT);
    pinMode(ENB, OUTPUT);
    Serial.begin(9600);
    avance();
}
 
void loop() {
  // gestion de la vitesse et de la direction
  if (state < 255 && down == 0) {
    state++;
  } else {
    down = 1;
  }
  if (state > 0 && down == 1) {
    state--;
  } else {
    down = 0;
    if (avant == 1) {
      avant = 0;
    } else {
      avant = 1;
    }
  }

  // // envoi des commandes
  // if (avant == 1) {
  //   avance();
  // } else {
  //   arriere();
  // }
  vitesse(state);
  delay(1);

  // affichage de la vitesse
  Serial.print("Vitesse : ");
  Serial.print(state);
  Serial.print(" -- Direction : ");
  if (avant == 1) {
    Serial.println("Avant");
  } else {
    Serial.println("Arriere");
  }
}

void avance() {
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}

void arriere() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}

void stop() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, LOW);
}

void vitesse(int vitesse) {
  analogWrite(ENB, vitesse);
}