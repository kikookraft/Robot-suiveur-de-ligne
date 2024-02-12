#include <Arduino.h>

//Ports de commande du pont en H (pour les deux moteurs)
#define motorIN1 7
#define motorIN2 6
#define motorIN3 5
#define motorIN4 4
#define ENB 9
#define ENA 10

// vitesse minimale du moteur pour eviter de caler (utilisé pour les fonction smooth...)
#define MIN_PWM 50
#define MAX_SPEED 255

// lissage du démarrage / arret des moteurs
#define SMOOTHING 1 // valeur à ajouter ou retirer à la vitesse
#define SMOOTHING_DELAY 1 // temps d'attente entre chaque ajout ou retrait de vitesse

// TODO: intégrer ces variables dans une structure ou dans des classes pour éviter les variables globales
int PWM1 = 0; // vitesse moteur 1
int PWM2 = 0; // vitesse moteur 2

// ----------------- Initialisation des moteurs -----------------
void initMotor() {
  // tout est en sortie
  pinMode(ENA, OUTPUT); // moteur 1
  pinMode(motorIN1, OUTPUT); // moteur 1
  pinMode(motorIN2, OUTPUT); // moteur 1

  pinMode(ENB, OUTPUT); // moteur 2
  pinMode(motorIN3, OUTPUT); // moteur 2
  pinMode(motorIN4, OUTPUT); // moteur 2
}


// ----------------- Moteur 1 -----------------
// avancer moteur 1
void forwardMotor1() {
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
}

// reculer moteur 1
void backwardMotor1() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, HIGH);
}

// arreter moteur 1
void stopMotor1() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, LOW);
}

// vitesse moteur 1
void speedMotor1(int vitesse) {
  analogWrite(ENA, vitesse);
}


// ----------------- Moteur 2 -----------------
// avancer moteur 2
void forwardMotor2() {
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}

// reculer moteur 2
void backwardMotor2() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}

// arreter moteur 2
void stopMotor2() {
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, LOW);
}

// vitesse moteur 2
void speedMotor2(int vitesse) {
  analogWrite(ENB, vitesse);
}


// ----------------- démarage / arret classique des moteurs -----------------
// démarage moteur 1
void startMotor1(int direction, int vitesse) {
  if (direction == 1) {
    forwardMotor1();
  } else {
    backwardMotor1();
  }
  speedMotor1(vitesse);
}

// démarage moteur 2
void startMotor2(int direction, int vitesse) {
  if (direction == 1) {
    forwardMotor2();
  } else {
    backwardMotor2();
  }
  speedMotor2(vitesse);
}

// ----------------- smooth le démarrage / arret des moteurs -----------------
// fonction qui necessite d'être appelée plusieures fois (explication de ce choix dans la doc partie #moteurs)
// démarage fluide moteur 1
void smoothStartMotor1(int direction) {
  if (PWM1 < MIN_PWM) {
    PWM1 = MIN_PWM;
  } else if (PWM1 + SMOOTHING < MAX_SPEED) {
    PWM1 += SMOOTHING;
  } else if (PWM1 + SMOOTHING > MAX_SPEED) {
    PWM1 = MAX_SPEED;
  }
  
  // si direction = 1 alors avancer, sinon reculer
  // TODO: faire en sorte que cette partie ne soit pas éxécutée à chaque appel de la fonction
  if (direction == 1) {
    forwardMotor1();
  } else {
    backwardMotor1();
  }

  // appliquer la vitesse
  speedMotor1(PWM1);
  delay(SMOOTHING_DELAY);
}

// arret fluide moteur 1
void smoothStopMotor1() {
  if (PWM1 > MIN_PWM) {
    PWM1 -= SMOOTHING;
  } else {
    // si la vitesse est inférieure à la vitesse minimale alors on arrete le moteur directement
    PWM1 = 0;
    stopMotor1();
  }

  // appliquer la vitesse
  speedMotor1(PWM1);
  delay(SMOOTHING_DELAY);
}

// --- la même chose pour le moteur 2 ---
// démarage fluide moteur 2
void smoothStartMotor2(int direction) {
  if (PWM2 < MIN_PWM) {
    PWM2 = MIN_PWM;
  } else if (PWM2 + SMOOTHING < MAX_SPEED) {
    PWM2 += SMOOTHING;
  } else if (PWM2 + SMOOTHING > MAX_SPEED) {
    PWM2 = MAX_SPEED;
  }

  // si direction = 1 alors avancer, sinon reculer
  // TODO: faire en sorte que cette partie ne soit pas éxécutée à chaque appel de la fonction
  if (direction == 1) {
    forwardMotor2();
  } else {
    backwardMotor2();
  }

  // appliquer la vitesse
  speedMotor2(PWM2);
  delay(SMOOTHING_DELAY);
}

// arret fluide moteur 2
void smoothStopMotor2() {
  if (PWM2 > MIN_PWM) {
    PWM2 -= SMOOTHING;
  } else {
    // si la vitesse est inférieure à la vitesse minimale alors on arrete le moteur directement
    PWM2 = 0;
    stopMotor2();
  }

  // appliquer la vitesse
  speedMotor2(PWM2);
  delay(SMOOTHING_DELAY);
}


// ----------------- ralentissement fluide des moteurs -----------------
// ralentir moteur 1
void slowDownMotor1(int vitesse) {
  if (PWM1 > vitesse) {
    PWM1 -= SMOOTHING;
  } else {
    PWM1 = vitesse;
  }
  speedMotor1(PWM1);
  delay(SMOOTHING_DELAY);
}

// ralentir moteur 2
void slowDownMotor2(int vitesse) {
  if (PWM2 > vitesse) {
    PWM2 -= SMOOTHING;
  } else {
    PWM2 = vitesse;
  }
  speedMotor2(PWM2);
  delay(SMOOTHING_DELAY);
}