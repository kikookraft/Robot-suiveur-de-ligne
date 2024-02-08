
## Info importante
Le projet à été créé avec PlatformIO avec VSCode.
Pour plus d'info sur PlatformIO : [PlatformIO](https://platformio.org/)  
  
Sinon pour juste voir le code, tout se situe dans le dossier `src` et le fichier `main.cpp` est le point d'entrée du programme.

## CAPTEURS
Quand le capteur infrarouge est a `LOW` c'est qu'il détecte le sol blanc.
Sinon c'est qu'il détecte le sol noir.
> Le capteurs renvoi un `HIGH` quand il detecte la ligne noire.

Liens utiles : 
- [Utilisation module infrarouge](https://www.instructables.com/How-to-Use-TCRT5000-IR-Sensor-Module-With-Arduino-/)  
   Doit être a moin de 4.5cm du sol sinon il ne détecte pas correctement le sol.
- [Utilisation module Pont en H](https://arduino.blaisepascal.fr/pont-en-h-l298n/)