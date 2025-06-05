# Projet ESP-IDF pour écrans Waveshare ESP32-S3 Touch LCD

Ce projet fournit une structure de base modulaire compatible avec les écrans Waveshare 5B (1024x600) et 7 (800x480) équipés d'un contrôleur tactile GT911.

## Compilation et flashage

1. Installer l'ESP-IDF conformément à la documentation officielle.
2. Initialiser l'environnement : `source $IDF_PATH/export.sh`.
3. Compiler le projet :
   ```bash
   idf.py build
   ```
4. Flasher sur la carte :
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

## Structure

- `drivers/` : pilotes UART, Wi-Fi, BLE, I2C, CAN, RS485.
- `modules/` : détection d'écran, carte SD, gestion batterie.
- `ui/` : interface graphique LVGL adaptative.
- `main/` : point d'entrée du firmware.

Chaque fichier contient des commentaires détaillés en français pour faciliter l'extension du projet.

> **Note :** les pilotes et modules fournis sont des *squelettes* à compléter pour obtenir un firmware fonctionnel.

## Licence

Ce projet est distribué sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## Bonnes pratiques de commit

- Utilisez un message court et impératif décrivant la modification.
- Ajoutez des explications plus longues dans le corps du message si nécessaire.

Ce projet fournit une structure de base modulaire compatible avec les écrans Waveshare 5B (1024x600) et 7 (800x480) équipés d'un contrôleur tactile GT911.

## Compilation et flashage

1. Installer l'ESP-IDF conformément à la documentation officielle.
2. Initialiser l'environnement : `source $IDF_PATH/export.sh`.
3. Compiler le projet :
   ```bash
   idf.py build
   ```
4. Flasher sur la carte :
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

## Structure

- `drivers/` : pilotes UART, Wi-Fi, BLE, I2C, CAN, RS485.
- `modules/` : détection d'écran, carte SD, gestion batterie.
- `ui/` : interface graphique LVGL adaptative.
- `main/` : point d'entrée du firmware.

Chaque fichier contient des commentaires détaillés en français pour faciliter l'extension du projet.


> **Note :** les pilotes et modules fournis sont des *squelettes* à compléter pour obtenir un firmware fonctionnel.

## Licence

Ce projet est distribué sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## Bonnes pratiques de commit

- Utilisez un message court et impératif décrivant la modification.
- Ajoutez des explications plus longues dans le corps du message si nécessaire.
