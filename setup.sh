#!/bin/bash
# Script d'installation minimal pour ESP-IDF
set -e

if [ -z "$IDF_PATH" ]; then
  echo "Clonage de l'ESP-IDF dans \$HOME/esp-idf" >&2
  git clone --depth 1 https://github.com/espressif/esp-idf.git "$HOME/esp-idf"
  export IDF_PATH="$HOME/esp-idf"
  "$IDF_PATH/install.sh"
fi

source "$IDF_PATH/export.sh"
