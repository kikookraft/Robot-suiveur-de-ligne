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

// fonction test
void test1();

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

// gestions du moteur (temporaire)
int state = MIN_PWM; // evite de demarrer a 0 car le moteur ne demarre pas
int down = 0;
int dir = 1; // 1 = avance, 0 = recule

int test = 0;

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
}

// ----------------- Boucle principale -----------------
void loop() {
  test1();
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


// ----------------- Fonctions de tests random -----------------
void test1() {
  
}