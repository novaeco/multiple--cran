#pragma once
#include <stdbool.h>

// Gestion de la carte SD pour la lecture et l'écriture de fichiers
void sd_card_init(void);
void sd_card_unmount(void);
bool sd_card_is_mounted(void);
