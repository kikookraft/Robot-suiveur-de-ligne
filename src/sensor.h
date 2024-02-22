#include <Arduino.h>

// Definition des pins
#define CAPTEUR_LEFT 11
#define CAPTEUR_MIDDLE 12
#define CAPTEUR_RIGHT 13


// Initialisation des capteurs
void initSensor() {
    pinMode(CAPTEUR_LEFT, INPUT);
    pinMode(CAPTEUR_RIGHT, INPUT);
    pinMode(CAPTEUR_MIDDLE, INPUT); 
}

// ----------------- Fonctions de base -----------------
// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_LEFT() {
    if (digitalRead(CAPTEUR_LEFT) == HIGH) {
        return 1;
    } else {
        return 0;
    }
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_MIDDLE() {
    if (digitalRead(CAPTEUR_MIDDLE) == HIGH) {
        return 1;
    } else {
        return 0;
    }
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_RIGHT() {
    if (digitalRead(CAPTEUR_RIGHT) == HIGH) {
        return 1;
    } else {
        return 0;
    }
}