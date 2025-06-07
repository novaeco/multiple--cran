# Projet ESP-IDF pour écrans Waveshare ESP32-S3 Touch LCD

Ce projet fournit un squelette modulaire pour développer un firmware compatible avec les écrans Waveshare 5B (1024x600) et 7" (800x480) équipés du contrôleur tactile GT911.

## Compilation et flashage

1. Installer l'ESP-IDF conformément à la documentation officielle.
2. Lancer `python3 tools/orchestrator.py` pour préparer l'environnement via le
   Provisioner (ou exécuter `./setup.sh` manuellement). Ce script télécharge
   l'ESP‑IDF complet et peut prendre plusieurs minutes. Définissez la variable
   `IDF_VERSION` pour choisir une version spécifique :

   ```bash
   IDF_VERSION=v6.0 ./setup.sh
   ```

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
8. Pour de bonnes performances d'affichage, ajoutez également dans `sdkconfig.defaults` :
   ```
   CONFIG_FREERTOS_HZ=1000
   CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_240=y
   CONFIG_ESPTOOLPY_FLASHMODE_QIO=y
   CONFIG_ESPTOOLPY_FLASHFREQ_120M=y
   CONFIG_SPIRAM_MODE_OCT=y
   ```

## Architecture

- `main/` : point d'entrée du firmware et initialisation LVGL.
- `drivers/` : pilotes de communication (UART, Wi-Fi, BLE, I2C, CAN, RS485).
- `modules/` : fonctionnalités haut niveau (détection d'écran, carte SD, gestion batterie).
- `battery.c` utilise l'API ADC *oneshot* avec une atténuation `ADC_ATTEN_DB_12`.
- `sd_card.c` démonte la carte avec `esp_vfs_fat_sdcard_unmount("/sdcard")`.
- `ui/` : interface graphique LVGL adaptative.
- `components/` : contient LVGL une fois la Provision exécutée (via
  `tools/orchestrator.py`).

Chaque composant est livré sous forme de squelette commenté en français afin de faciliter son extension.

> **Note :** les pilotes et modules fournis sont des exemples à compléter pour obtenir un firmware opérationnel. Le pilote `drivers/lcd_panel_waveshare.c` utilise la table de brochage définie dans `drivers/waveshare_pins.h` et contrôle optionnellement les broches `DISP` et `LCD_RST`. Ajustez ces numéros via les macros `PIN_NUM_DISP` et `PIN_NUM_LCD_RST` (valeur `-1` pour ignorer la broche) selon votre câblage.
> Dans la configuration actuelle, `PIN_NUM_DISP` vaut `6` et `PIN_NUM_LCD_RST` vaut `11`.
> Depuis la version actuelle, ce pilote règle également automatiquement la fréquence
> `pclk` et les temporisations de synchronisation selon la résolution détectée (800×480
> ou 1024×600). Pensez à mettre à jour vos sources avant de compiler.
>


> La fiche de caractéristiques et le brochage détaillé sont disponibles dans
> [`docs/waveshare_pinout.md`](docs/waveshare_pinout.md).

## Licence

Ce projet est distribué sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## Bonnes pratiques de commit

- Utilisez un message court et impératif décrivant la modification.
- Ajoutez des explications plus longues dans le corps du message si nécessaire.

## Agents spécialisés
- **Agent Orchestrateur Principal (Orchestrator)** : pilote l'écosystème, planifie les tâches et coordonne les autres agents.
- **Agent de Provisioning & Setup (Provisioner)** : installe et met à jour les outils de développement et vérifie la disponibilité de l'ESP‑IDF.
- **Agents de Développement Par Langage (DevAgent[Lang])** : fournissent l'expertise pour chaque technologie et proposent de bonnes pratiques.
- **DevAgent UI/UX Full Stack** : conçoit des interfaces esthétiques, fonctionnelles et accessibles en mêlant design et développement front‑end/back‑end.
- **DevAgent LVGL Full Stack** : réalise des interfaces graphiques avancées pour l'embarqué et l'IoT tout en tenant compte des contraintes matérielles.
- **DevAgent JS/TS Full Stack** : développe des applications Web complètes avec l'écosystème JavaScript/TypeScript, du frontend au backend.
- **DevAgent Python Full Stack** : couvre le développement Web, la science des données et l'IA jusqu'au déploiement de modèles de machine learning.
- **DevAgent Go Full Stack** : crée des services cloud‑native et des microservices performants pour des architectures distribuées.
- **DevAgent Rust Full Stack** : fournit des solutions sûres et performantes pour la programmation système et le WebAssembly.
- **DevAgent Java Full Stack** : conçoit des applications d'entreprise évolutives et maintenables dans l'écosystème Java.
- **DevAgent C/C++ Full Stack** : se spécialise dans les systèmes embarqués et les logiciels hautes performances.
- **DevAgent C#/.NET Full Stack** : offre des solutions complètes pour les applications et services basés sur l'écosystème Microsoft .NET.
- **DevAgent PHP Full Stack** : propose des plateformes Web et e‑commerce complètes avec PHP et ses frameworks.
- **DevAgent Ruby Full Stack** : privilégie le développement Web rapide et maintenable avec Ruby et Rails.
- **DevAgent Assembly Full Stack** : optimise le code au plus bas niveau pour un contrôle matériel et des performances maximales.
- **Agent Build & CI (Builder)** : centralise la compilation et la CI/CD en appliquant les options de `sdkconfig.defaults`.
- **Agent de Test & Qualité (Tester)** : automatise les tests et le lint pour garantir un firmware stable.
- **Agent Déploiement & Infrastructure (Deployer)** : gère le déploiement et l'infrastructure en tenant compte des écrans cibles.
- **Agent d’Observabilité & Monitoring (Observer)** : agrège logs et métriques pour faciliter le diagnostic.
- **Agent de Documentation & Assistance (DocAgent)** : génère et maintient la documentation, y compris ce fichier.
- **Agent de Collaboration (CollabAgent)** : facilite la gestion de branches et tickets et suit l'avancement global.
