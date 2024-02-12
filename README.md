
## Info importante
Le projet à été créé avec PlatformIO avec VSCode.
Pour plus d'info sur PlatformIO : [PlatformIO](https://platformio.org/)  
  
Sinon pour juste voir le code, tout se situe dans le dossier `src` et le fichier `main.cpp` est le point d'entrée du programme.

## CAPTEURS
Quand le capteur infrarouge est a `LOW` c'est qu'il détecte le sol blanc.
Sinon c'est qu'il détecte le sol noir.
> Le capteurs renvoi un `HIGH` quand il detecte la ligne noire.

Si nous avons 3 capteurs infrarouges pour détecter les lignes noires:
- `CAPTEUR_LEFT` : est + a gauche de la ligne (ne la detecte pas par defaut), branché sur la pin 13
- `CAPTEUR_MIDDLE` : est au milieu de la ligne (capte au maximum la ligne), branché sur la pin 12
- `CAPTEUR_RIGHT` : est + a droite de la ligne (ne la detecte pas par defaut), branché sur la pin 11


Lien utile : [Utilisation module infrarouge](https://www.instructables.com/How-to-Use-TCRT5000-IR-Sensor-Module-With-Arduino-/)  

> ! Petit tip !  
> Le capteur doit être a moin de 4.5cm du sol *(4cm pour être safe)* sinon il detecte plus rien.

## MOTEURS
Les moteurs sont controlés par un [module pont en H](https://arduino.blaisepascal.fr/pont-en-h-l298n/) 
- Moteur gauche : `motorIN1` et `motorIN2`, activé par `ENA`
- Moteur droit : `motorIN3` et `motorIN4`, activé par `ENB`

Le code qui controle les moteurs est dans le fichier `src/motors.h`. Il inclut les definitions des pins et les fonctions pour controler les moteurs.

### Fonctions de controle des moteurs
Il y a actuellement deux moyens de controller les moteurs: 
- Manière simple (et brute) : `forwardMotor1`, `backwardMotor1`, `stopMotor1`, `speedMotor1` *(et pareil pour le moteur 2)*.  
  Ces fonctions sont utilisées pour controler les moteurs de manière simple.  
  Les trois premières fonction ont la signature `void fn();` et la dernière `void speedMotorX(int speed);` ou `speed` est la vitesse PWM du moteur *(entre 0 et 255)*.  
  Elles permettent respectivement de faire avancer, reculer et arrêter le moteur.  

- Manière plus complexe (qui ne sera peut être pas utile mais qui est là au cas ou) mais plus fluide: `smoothStartMotor1` et `smoothStopMotor1` *(et pareil pour le moteur 2)*.    
  Ces fonctions permettent de faire démarrer et arrêter les moteurs de manière plus fluide.    
  Le smoothStart fait démarrer le moteur de manière progressive et le smoothStop l'arrête de manière progressive.  
  Les fonctions `smoothStartMotorX` ont la signature `void fn(int direction);` ou `direction` est la direction du moteur *(1 pour avancer, 0 pour reculer)*.  
   Les fonctions `smoothStopMotorX` ont la signature `void fn();`.

#### Pourquois la manière fluide ?
La manière fluide peut potentiellement faire gagner du temps sur les lignes droites.  
Exemple: si en ligne droite le robot est legèrement décalé (ce qui arrivera forcement en fin de virage) au lieu de completement arrêter le moteur puis le démarer, on peut **faire déccelerer lentement le 1er moteur pendant que l'autre tourne a fond** pour repartir droit sans perdre trop de temps.  
Car **si on arrête le moteur completement, le robot va perdre plus d'inertie et donc mettre plus de temps a redémarrer**. De plus si un coté est arrêté et l'autre non, le robot va tourner beaucoup plus brusquement et va donc se mettre a faire des zigzags en ligne droite (donc pas ouf).
  
Cependant la fluiditée peut faire perde beaucoup de temps dans les virages (a verifier).  
Donc soit on prend une des deux méthodes, soit on fait un mix des deux en faisant un système de détection de virage pour switcher entre les deux.


## TODO
- [ ] Tester les deux méthode (simple et fluide) pour voir laquelle est la plus efficace en **ligne droite** puis **en virage**
- [ ] Faire un système de détection de virage pour switcher entre les deux méthodes
- [ ] Refactorer le code pour le rendre orienté objet.  
Parce que actuellement avoir plusieures fonctions similaires pour chaque moteur avec juste 2 variable qui changent, c'est pas ouf.
