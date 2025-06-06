# Projet ESP-IDF pour écrans Waveshare ESP32-S3 Touch LCD

Ce projet fournit un squelette modulaire pour développer un firmware compatible avec les écrans Waveshare 5B (1024x600) et 7" (800x480) équipés du contrôleur tactile GT911.

## Compilation et flashage

1. Installer l'ESP-IDF conformément à la documentation officielle.
2. Exécuter `./setup.sh` pour préparer l'environnement.
3. Initialiser l'environnement : `source $IDF_PATH/export.sh`.
4. Compiler le projet :
   ```bash
   idf.py build
   ```
5. Flasher sur la carte :
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```
6. Le fichier `partitions.csv` définit une partition `factory` de 2 Mo. Prévoyez donc une carte avec au moins 4 Mo de flash et activez cette table via `sdkconfig.defaults`.
   Si vous aviez déjà un fichier `sdkconfig` généré, exécutez `idf.py fullclean` pour prendre en compte cette nouvelle configuration.

## Architecture

- `main/` : point d'entrée du firmware et initialisation LVGL.
- `drivers/` : pilotes de communication (UART, Wi-Fi, BLE, I2C, CAN, RS485).
- `modules/` : fonctionnalités haut niveau (détection d'écran, carte SD, gestion batterie).
- `ui/` : interface graphique LVGL adaptative.

Chaque composant est livré sous forme de squelette commenté en français afin de faciliter son extension.

> **Note :** les pilotes et modules fournis sont des exemples à compléter pour obtenir un firmware opérationnel.

## Licence

Ce projet est distribué sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## Bonnes pratiques de commit

- Utilisez un message court et impératif décrivant la modification.
- Ajoutez des explications plus longues dans le corps du message si nécessaire.
