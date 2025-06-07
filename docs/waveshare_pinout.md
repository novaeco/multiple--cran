# Brochage et caractéristiques des cartes Waveshare ESP32-S3 Touch LCD

Cette page regroupe les caractéristiques principales et le brochage des modèles 7" et 5B.
## Caractéristiques communes

- Processeur double cœur Xtensa LX7 à 240 MHz
- Wi‑Fi 2,4 GHz (802.11 b/g/n) et Bluetooth 5
- 16 Mo de flash et 8 Mo de PSRAM
- 512 Ko de SRAM interne et 384 Ko de ROM
- Interfaces CAN, RS485, I²C, USB pleine vitesse et lecteur de carte TF
## ESP32-S3-Touch-LCD-7
Écran LCD IPS 7 pouces 800×480 avec interface tactile capacitive (GT911).

| GPIO | Fonction | Description |
|------|----------|-------------|
|0 | G3 | Donn\xC3\xA9es vertes 3e bit |
|1 | R3 | Donn\xC3\xA9es rouges 3e bit |
|2 | R4 | Donn\xC3\xA9es rouges 4e bit |
|3 | VSYNC | Synchronisation verticale |
|5 | DE | Activation des donn\xC3\xA9es |
|7 | PCLK | Horloge pixel |
|10| B7 | Donn\xC3\xA9es bleues 7e bit |
|14| B3 | Donn\xC3\xA9es bleues 3e bit |
|17| B6 | Donn\xC3\xA9es bleues 6e bit |
|18| B5 | Donn\xC3\xA9es bleues 5e bit |
|21| G7 | Donn\xC3\xA9es vertes 7e bit |
|38| B4 | Donn\xC3\xA9es bleues 4e bit |
|39| G2 | Donn\xC3\xA9es vertes 2e bit |
|40| R7 | Donn\xC3\xA9es rouges 7e bit |
|41| R6 | Donn\xC3\xA9es rouges 6e bit |
|42| R5 | Donn\xC3\xA9es rouges 5e bit |
|45| G4 | Donn\xC3\xA9es vertes 4e bit |
|46| HSYNC | Synchronisation horizontale |
|47| G6 | Donn\xC3\xA9es vertes 6e bit |
|48| G5 | Donn\xC3\xA9es vertes 5e bit |

Broches suppl\xC3\xA9mentaires :
- **TP_IRQ** sur GPIO4
- **TP_SDA** sur GPIO8
- **TP_SCL** sur GPIO9
- **TP_RST** via EXIO1
- **DISP** via EXIO2 (contr\xC3\xB4le du r\xC3\xA9tro\xC3\xA9clairage)
- **USB_SEL/CAN_SEL** via EXIO5

## ESP32-S3-Touch-LCD-5B
Écran IPS 5 pouces (800×480 ou 1024×600) avec alimentation large 7–36 V et RTC intégré.

| GPIO | Fonction |
|------|----------|
|0 | G3 |
|1 | R3 |
|2 | R4 |
|3 | VSYNC |
|4 | TP_IRQ |
|5 | DE |
|7 | PCLK |
|8 | TP_SDA |
|9 | TP_SCL |
|10| B7 |
|14| B3 |
|17| B6 |
|18| B5 |
|21| G7 |
|38| B4 |
|39| G2 |
|40| R7 |
|41| R6 |
|42| R5 |
|45| G4 |
|46| HSYNC |
|47| G6 |
|48| G5 |

Broches suppl\xC3\xA9mentaires :
- **TP_RST** via EXIO1
- **DISP** via EXIO2
- **LCD_RST** via EXIO3
- **RS485_RXD** sur GPIO43
- **RS485_TXD** sur GPIO44
- **CANTX** sur GPIO15
- **CANRX** sur GPIO16

Le pilote `lcd_panel_waveshare.c` s'appuie sur les définitions de `drivers/waveshare_pins.h`.
Les signaux `DISP` et `LCD_RST` peuvent être activés via ces macros et
modifiés à l'aide de `PIN_NUM_DISP` et `PIN_NUM_LCD_RST` pour correspondre à votre câblage,
ou laissés à `-1` afin d'ignorer ces broches. Dans ce projet, `PIN_NUM_DISP` vaut `6`
et `PIN_NUM_LCD_RST` vaut `11`, valeurs adaptées au modèle 5B.

Depuis la mise à jour du pilote `lcd_panel_waveshare.c`, la fréquence `pclk` et
les temporisations de synchronisation (fronts et retards HSYNC/VSYNC) sont
déterminées automatiquement selon la résolution détectée (800×480 ou 1024×600).
Veillez donc à compiler avec la dernière version des sources pour bénéficier de
ces réglages.

Ces informations peuvent servir de r\xC3\xA9f\xC3\xA9rence pour ajuster les pilotes et la configuration selon la carte utilis\xC3\xA9e.



Pour pr\xC3\xA9parer l\x27environnement et compiler le projet, ex\xC3\xA9cutez `python3 tools/orchestrator.py` (ou `./setup.sh`),
puis chargez l\x27ESP‑IDF avec :

source "$HOME/esp-idf/export.sh"

Pour de bonnes performances d\'affichage, ajoutez dans `sdkconfig.defaults` :
```
CONFIG_FREERTOS_HZ=1000
CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_240=y
CONFIG_ESPTOOLPY_FLASHMODE_QIO=y
CONFIG_ESPTOOLPY_FLASHFREQ_120M=y
CONFIG_SPIRAM_MODE_OCT=y
```

Reportez-vous \xC3\xA9galement au fichier [README.md](../README.md) pour plus de d\xC3\xA9tails.

