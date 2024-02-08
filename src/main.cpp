#include <Arduino.h>

// avancer moteur 1
void forwardMotor1();
// reculer moteur 1
void backwardMotor1();
// arreter moteur 1
void stopMotor1();
// regler la vitesse du moteur 1 (0-255)
void speedMotor1(int vitesse);
// avancer moteur 2
void forwardMotor2();
// reculer moteur 2
void backwardMotor2();
// arreter moteur 2
void stopMotor2();
// regler la vitesse du moteur 2 (0-255)
void speedMotor2(int vitesse);

// smooth le démarrage / arret des moteurs
void smoothStartMotor1();
void smoothStopMotor1();
void smoothStartMotor2();
void smoothStopMotor2();



// fonction test
void test1();
void test2();

//Ports de commande des moteurs
#define motorIN1 7
#define motorIN2 6
#define motorIN3 5
#define motorIN4 4
#define ENB 10
#define ENA 11

#define MIN_PWM 50 // vitesse minimale du moteur pour eviter de caler

// capteurs
#define CAPTEUR_LEFT 13
#define CAPTEUR_RIGHT 12

// lissage du démarrage / arret des moteurs
#define SMOOTHING 1
// gestions du moteur (temporaire)
int PWM1 = 0; // vitesse moteur 1
int PWM2 = 0; // vitesse moteur 2

void setup() {
    // Configuration des ports en mode "sortie"
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(CAPTEUR_LEFT, INPUT);
  pinMode(CAPTEUR_RIGHT, INPUT);
  // Initialisation des moteurs
  stopMotor1();
  stopMotor2();
  speedMotor1(0);
  speedMotor2(0);

  Serial.begin(9600);
}

// ----------------- Boucle principale -----------------
void loop() {
  test1();
  // test2();
}



// ----------------- Moteur 1 -----------------
void forwardMotor1() {
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}

void backwardMotor1() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}

void stopMotor1() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, LOW);
}

void speedMotor1(int vitesse) {
  analogWrite(ENB, vitesse);
}

// ----------------- Moteur 2 -----------------
void forwardMotor2() {
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
}

void backwardMotor2() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, HIGH);
}

void stopMotor2() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, LOW);
}

void speedMotor2(int vitesse) {
  analogWrite(ENA, vitesse);
}

// ----------------- smooth le démarrage / arret des moteurs -----------------
// ces fonctions ne doivent pas etre bloquantes
void smoothStartMotor1(int direction) {
  if (PWM1 < MIN_PWM) {
    PWM1 = MIN_PWM;
  } else if (PWM1 + SMOOTHING < 255) {
    PWM1 += SMOOTHING;
  } else if (PWM1 + SMOOTHING > 255) {
    PWM1 = 255;
  }
  
  if (direction == 1) {
    forwardMotor1();
  } else {
    backwardMotor1();
  }
  speedMotor1(PWM1);
  delay(1);
}

void smoothStopMotor1() {
  if (PWM1 > MIN_PWM) {
    PWM1 -= SMOOTHING;
  } else {
    PWM1 = 0;
    stopMotor1();
  }
  speedMotor1(PWM1);
  delay(1);
}

//moteur 2
void smoothStartMotor2(int direction) {
  if (PWM2 < MIN_PWM) {
    PWM2 = MIN_PWM;
  } else if (PWM2 + SMOOTHING < 255) {
    PWM2 += SMOOTHING;
  } else if (PWM2 + SMOOTHING > 255) {
    PWM2 = 255;
  }

  if (direction == 1) {
    forwardMotor2();
  } else {
    backwardMotor2();
  }
  speedMotor2(PWM2);
  delay(1);
}

void smoothStopMotor2() {
  if (PWM2 > MIN_PWM) {
    PWM2 -= SMOOTHING;
  } else {
    PWM2 = 0;
    stopMotor2();
  }
  speedMotor2(PWM2);
  delay(1);
}

// ----------------- Fonctions de tests random -----------------
void test1() {
  // si le capteur gauche est actif allumer moteur 1
  if (digitalRead(CAPTEUR_LEFT) == LOW) {
    smoothStartMotor1(1);
    // Serial.println(PWM1);
  } else {
    smoothStopMotor1();
  }
  // si le capteur droit est actif allumer moteur 2
  if (digitalRead(CAPTEUR_RIGHT) == LOW) {
    smoothStartMotor2(1);
    // Serial.println(PWM2);
  } else {
    smoothStopMotor2();
  }
}

void test2() {
  // comme test 1 mais sans la fluidité
  if (digitalRead(CAPTEUR_LEFT) == LOW) {
    forwardMotor1();
    Serial.println("capteur gauche");
    speedMotor1(255);
  } else {
    stopMotor1();
  }
  if (digitalRead(CAPTEUR_RIGHT) == LOW) {
    forwardMotor2();
    Serial.println("capteur droit");
    speedMotor2(255);
  } else {
    stopMotor2();
  }
}