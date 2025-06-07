# Projet ESP-IDF pour écrans Waveshare ESP32-S3 Touch LCD

Ce projet fournit un squelette modulaire pour développer un firmware compatible avec les écrans Waveshare 5B (1024x600) et 7" (800x480) équipés du contrôleur tactile GT911.

## Compilation et flashage

1. Installer l'ESP-IDF conformément à la documentation officielle.
2. Exécuter `./setup.sh` pour préparer l'environnement (dépendances APT
   incluses).


3. Initialiser l'environnement ESP‑IDF :
   ```bash
   source "$HOME/esp-idf/export.sh"
   ```
   (ou `source "$IDF_PATH/export.sh"` si la variable est déjà définie)

4. Vérifier que `idf.py` est disponible :
   ```bash
   idf.py --version
   ```
   La commande doit renvoyer un numéro de version (ex. `ESP-IDF v6.0.0`).
5. Compiler le projet :
   ```bash
   idf.py build
   ```
6. Flasher sur la carte :
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```
7. Le fichier `partitions.csv` définit une partition `factory` de 2 Mo. Prévoyez donc une carte avec au moins 4 Mo de flash et activez cette table via `sdkconfig.defaults`.
   Si vous aviez déjà un fichier `sdkconfig` généré, exécutez `idf.py fullclean` pour prendre en compte cette nouvelle configuration.

## Architecture

- `main/` : point d'entrée du firmware et initialisation LVGL.
- `drivers/` : pilotes de communication (UART, Wi-Fi, BLE, I2C, CAN, RS485).
- `modules/` : fonctionnalités haut niveau (détection d'écran, carte SD, gestion batterie).
- `battery.c` utilise l'API ADC *oneshot* avec une atténuation `ADC_ATTEN_DB_12`.
- `sd_card.c` démonte la carte avec `esp_vfs_fat_sdcard_unmount("/sdcard")`.
- `ui/` : interface graphique LVGL adaptative.
- `components/` : contient LVGL après exécution de `./setup.sh`.

Chaque composant est livré sous forme de squelette commenté en français afin de faciliter son extension.

> **Note :** les pilotes et modules fournis sont des exemples à compléter pour obtenir un firmware opérationnel. Le pilote `drivers/lcd_panel_waveshare.c` contrôle désormais les broches `DISP` et `LCD_RST` pour allumer l'écran. Ajustez les numéros de GPIO via les macros `PIN_NUM_DISP` et `PIN_NUM_LCD_RST` ou laissez-les à `-1` pour désactiver leur gestion.

>


> La fiche de caractéristiques et le brochage détaillé sont disponibles dans
> [`docs/waveshare_pinout.md`](docs/waveshare_pinout.md).

## Licence

Ce projet est distribué sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## Bonnes pratiques de commit

- Utilisez un message court et impératif décrivant la modification.
- Ajoutez des explications plus longues dans le corps du message si nécessaire.

## Agents spécialisés
- **Agent Orchestrateur Principal (Orchestrator)** : pilote l'écosystème et coordonne les autres agents.
- **Agent de Provisioning & Setup (Provisioner)** : installe et met à jour les outils de développement.
- **Agents de Développement Par Langage (DevAgent[Lang])** : fournissent l'expertise pour chaque technologie.
- **Agent Build & CI (Builder)** : centralise la compilation et la CI/CD.
- **Agent de Test & Qualité (Tester)** : automatise les tests et le lint.
- **Agent Déploiement & Infrastructure (Deployer)** : gère le déploiement et l'infrastructure.
- **Agent d’Observabilité & Monitoring (Observer)** : agrège logs et métriques.
- **Agent de Documentation & Assistance (DocAgent)** : génère et maintient la documentation.
- **Agent de Collaboration (CollabAgent)** : facilite la gestion de branches et tickets.
