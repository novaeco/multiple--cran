#!/bin/bash
# Script d'installation minimal pour ESP-IDF
set -e

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
