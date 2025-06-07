Ce dossier contiendra LVGL une fois `setup.sh` exécuté. La variable `LVGL_TAG`
permet de choisir la version souhaitée lors de l'installation.

Après l'installation, chargez l'environnement ESP‑IDF :

source "$HOME/esp-idf/export.sh"

(ou `source "$IDF_PATH/export.sh"` si la variable est déjà définie)

Ceci permet d'utiliser la commande `idf.py` pour compiler le projet.
