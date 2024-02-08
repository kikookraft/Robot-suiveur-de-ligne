#include <Arduino.h>

// declaration des fonctions
void avance();
void arriere();
void stop();
void vitesse(int vitesse);
void test1();
void test2();
void test3();

//Ports de commande du moteur B
#define motorIN1 7
#define motorIN2 6
#define motorIN3 5
#define motorIN4 4
#define ENB 10
#define ENA 11
#define MIN_PWM 50

#define capteur 13
 
// gestions du moteur
int state = MIN_PWM; // evite de demarrer a 0 car le moteur ne demarre pas
int down = 0;
int dir = 1; // 1 = avance, 0 = recule

int test = 0;

void setup() {
    // Configuration des ports en mode "sortie"
    pinMode(motorIN3, OUTPUT);
    pinMode(motorIN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(capteur, INPUT);
    avance();
}
 
void loop() {
  test3();
  //test2();
  //test1();
}

void test3() {
  if (digitalRead(capteur) == LOW) {
    stop();
  } else {
    avance();
    vitesse(255);
  }
  delay(5);

}

void test2() {
   avance();
  vitesse(255);
  delay(2000);
  stop();
  delay(1000);
  arriere();
  vitesse(255);
  delay(2000);
  stop();
  delay(1000);
}

void test1() {
  // gestion de la vitesse
  if (state < 255 && down == 0) {
    state++;
  } else {
    down = 1;
  }
  if (state > MIN_PWM && down == 1) {
    state--;
  } else {
    down = 0;
  }

  // gestion de la direction
  if (state == MIN_PWM && down == 1) {
    if (dir == 1) {
      arriere();
      dir = 0;
    } else {
      avance();
      dir = 1;
    }
    state = MIN_PWM;
  }

  vitesse(state);
  delay(5);

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