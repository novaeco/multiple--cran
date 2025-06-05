idf_component_register(
    SRCS
        "screen_detect.c"
        "sd_card.c"
        "battery.c"
    INCLUDE_DIRS "."
    REQUIRES drivers
)
