#include <Arduino.h>

// Definition des pins
#define CAPTEUR_LEFT 13
#define CAPTEUR_MIDDLE 12
#define CAPTEUR_RIGHT 11

// Initialisation des capteurs
void initSensor() {
    pinMode(CAPTEUR_LEFT, INPUT);
    pinMode(CAPTEUR_MIDDLE, INPUT);
    pinMode(CAPTEUR_RIGHT, INPUT);
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_LEFT() {
    if (digitalRead(CAPTEUR_LEFT) == LOW) {
        return 1;
    } else {
        return 0;
    }
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_MIDDLE() {
    if (digitalRead(CAPTEUR_MIDDLE) == LOW) {
        return 1;
    } else {
        return 0;
    }
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_RIGHT() {
    if (digitalRead(CAPTEUR_RIGHT) == LOW) {
        return 1;
    } else {
        return 0;
    }
}
