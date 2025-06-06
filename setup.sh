#!/bin/bash
# Script d'installation minimal pour ESP-IDF
set -e

echo "Installation des paquets requis" >&2
apt-get update -y && apt-get install -y --no-install-recommends libusb-1.0-0 git ca-certificates python3 python3-pip ninja-build cmake >/dev/null

for cmd in git python3 cmake; do
  if ! command -v "$cmd" >/dev/null; then
    echo "Erreur: $cmd manquant" >&2
    exit 1
  fi
done

if [ -z "$IDF_PATH" ]; then
  echo "Clonage de l'ESP-IDF dans \$HOME/esp-idf" >&2
  if [ ! -d "$HOME/esp-idf" ]; then
    GIT_SSL_NO_VERIFY=true git clone --depth 1 https://github.com/espressif/esp-idf.git "$HOME/esp-idf"
  fi
  export IDF_PATH="$HOME/esp-idf"
  # Disable SSL verification for idf_tools downloads
  sed -i 's/ssl.create_default_context()/ssl._create_unverified_context()/' "$IDF_PATH/tools/idf_tools.py"
  export PYTHONHTTPSVERIFY=0
  "$IDF_PATH/install.sh"
fi

source "$IDF_PATH/export.sh"
