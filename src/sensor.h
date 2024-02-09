#include <Arduino.h>

// Definition des pins
#define CAPTEUR_LEFT 13
#define CAPTEUR_MIDDLE 12
#define CAPTEUR_RIGHT 11

#define TROIS_CAPTEURS 0 // permet de switch les fonctions de test entre 3 capteurs et 2 capteurs

// Initialisation des capteurs
void initSensor() {
    pinMode(CAPTEUR_LEFT, INPUT);
    pinMode(CAPTEUR_RIGHT, INPUT);

    #if TROIS_CAPTEURS
    pinMode(CAPTEUR_MIDDLE, INPUT); 
    #endif
}

// ----------------- Fonctions de base -----------------
// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_LEFT() {
    if (digitalRead(CAPTEUR_LEFT) == LOW) {
        return 1;
    } else {
        return 0;
    }
}

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
#if TROIS_CAPTEURS
int SENSOR_MIDDLE() {
    if (digitalRead(CAPTEUR_MIDDLE) == LOW) {
        return 1;
    } else {
        return 0;
    }
}
#endif

// Renvoi 1 si le capteur detecte la ligne, 0 sinon
int SENSOR_RIGHT() {
    if (digitalRead(CAPTEUR_RIGHT) == LOW) {
        return 1;
    } else {
        return 0;
    }
}

// ----------------- Fonctions avancées -----------------
#if TROIS_CAPTEURS // fonctions pour 3 capteurs
// renvoie 1 si le capteur gauche et du milieu sont actifs
int lineToLeft() {
    if (SENSOR_LEFT() && SENSOR_MIDDLE()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si seul le capteur gauche est actif
int extremeLeft() {
    if (SENSOR_LEFT() && !SENSOR_MIDDLE() && !SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si le capteur droit et du milieu sont actifs
int lineToRight() {
    if (SENSOR_RIGHT() && SENSOR_MIDDLE()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si seul le capteur droit est actif
int extremeRight() {
    if (!SENSOR_LEFT() && !SENSOR_MIDDLE() && SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}


// renvoie 1 si les 3 capteurs sont actifs
int lineToCenter() {
    if (SENSOR_LEFT() && SENSOR_MIDDLE() && SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si aucun capteur n'est actif
int noLine() {
    if (!SENSOR_LEFT() && !SENSOR_MIDDLE() && !SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si un seul capteur est actif
int only1ActiveSensor() {
    if ((SENSOR_LEFT() && !SENSOR_MIDDLE() && !SENSOR_RIGHT()) || (!SENSOR_LEFT() && SENSOR_MIDDLE() && !SENSOR_RIGHT()) || (!SENSOR_LEFT() && !SENSOR_MIDDLE() && SENSOR_RIGHT())) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1, 2 ou 3 en fonction du capteur actif (1 = gauche, 2 = milieu, 3 = droit, 0 = aucun)
int whichLine() {
    if (!only1ActiveSensor()) {
        return -1;
    } else if (SENSOR_LEFT()) {
        return 1;
    } else if (SENSOR_MIDDLE()) {
        return 2;
    } else if (SENSOR_RIGHT()) {
        return 3;
    } else {
        return 0;
    }
}

// renvoie un entier entre -2 et 2 en fonction de la position de la ligne (0 = centre, -2 = extreme gauche, 2 = extreme droite, 1 = milieu gauche, -1 = milieu droite)
int linePosition() {
    if (lineToCenter()) {
        return 0;
    } else if (lineToLeft()) {
        return -1;
    } else if (lineToRight()) {
        return 1;
    } else if (extremeLeft()) {
        return -2;
    } else if (extremeRight()) {
        return 2;
    } else {
        // si aucun capteur n'est actif
        return -3;
    }
}

#else // fonctions pour 2 capteurs


// renvoie 1 si seul le capteur gauche est actif
int extremeLeft() {
    if (SENSOR_LEFT() && !SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si seul le capteur droit est actif
int extremeRight() {
    if (!SENSOR_LEFT() && SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si les 2 capteurs sont actifs
int lineToCenter() {
    if (SENSOR_LEFT() && SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

// renvoie 1 si aucun capteur n'est actif
int noLine() {
    if (!SENSOR_LEFT() && !SENSOR_RIGHT()) {
        return 1;
    } else {
        return 0;
    }
}

//renvoi un int entre -1 et 1 en fonction de la position de la ligne (0 = centre, -1 = gauche, 1 = droite)
int linePosition() {
    if (lineToCenter()) {
        return 0;
    } else if (extremeLeft()) {
        return -1;
    } else if (extremeRight()) {
        return 1;
    } else {
        // si aucun capteur n'est actif
        return -2;
    }
}
#endif