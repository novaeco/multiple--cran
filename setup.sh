#!/usr/bin/env bash
# Script d'installation de l'ESP-IDF avec options configurables
set -euo pipefail

# Permet de choisir la version d'ESP-IDF et celle de LVGL via des variables
IDF_VERSION="${IDF_VERSION:-v6.0}"
IDF_PATH="${IDF_PATH:-$HOME/esp-idf}"
LVGL_TAG="${LVGL_TAG:-v8.3.0}"

log() { echo "[setup] $*" >&2; }

if command -v apt-get >/dev/null; then
  log "Installation des paquets requis via apt-get"
  apt-get update -y && apt-get install -y --no-install-recommends libusb-1.0-0 git ca-certificates python3 python3-pip ninja-build cmake >/dev/null
else
  log "Veuillez installer libusb-1.0-0, git, ca-certificates, python3, python3-pip, ninja-build et cmake via votre gestionnaire de paquets"
fi

for cmd in git python3 cmake; do
  if ! command -v "$cmd" >/dev/null; then
    echo "Erreur: $cmd manquant" >&2
    exit 1
  fi
done

if [ ! -d "$IDF_PATH" ]; then
  log "Clonage de l'ESP-IDF ($IDF_VERSION) dans $IDF_PATH"
  git clone --depth 1 --branch "$IDF_VERSION" https://github.com/espressif/esp-idf.git "$IDF_PATH"
  "$IDF_PATH/install.sh"
else
  log "ESP-IDF deja present dans $IDF_PATH"
fi

source "$IDF_PATH/export.sh"

# Vérifie la disponibilité d'idf.py
if ! command -v idf.py >/dev/null; then
  echo "Erreur: idf.py introuvable. Vérifiez l'installation ESP-IDF." >&2
  exit 1
fi
idf.py --version >&2

# Récupère LVGL complet si absent
if [ ! -d "components/lvgl" ]; then
  log "Clonage de LVGL ($LVGL_TAG)"
  mkdir -p components
  git clone --depth 1 --branch "$LVGL_TAG" https://github.com/lvgl/lvgl.git components/lvgl
else
  log "LVGL deja present"
fi
