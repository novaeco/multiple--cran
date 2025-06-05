#include "ui.h"
#include "lvgl.h"
#include "battery.h"

static lv_obj_t *bar_batt;

static void battery_timer_cb(lv_timer_t *t)
{
    lv_bar_set_value(bar_batt, battery_get_percent(), LV_ANIM_OFF);
}

void ui_init(void) {
    /* Conteneur principal adaptatif */
    lv_obj_t *cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    /* Label de bienvenue */
    lv_obj_t *label = lv_label_create(cont);
    lv_label_set_text(label, "Interface prête");

    /* Slider d'exemple */
    lv_obj_t *slider = lv_slider_create(cont);
    lv_obj_set_width(slider, LV_PCT(80));

    /* Bouton simple */
    lv_obj_t *btn = lv_btn_create(cont);
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "OK");

    /* Barre de niveau batterie */
    bar_batt = lv_bar_create(cont);
    lv_obj_set_width(bar_batt, LV_PCT(80));
    lv_bar_set_range(bar_batt, 0, 100);
    lv_bar_set_value(bar_batt, battery_get_percent(), LV_ANIM_OFF);

    /* Rafraîchissement périodique du niveau batterie */
    lv_timer_create(battery_timer_cb, 2000, NULL);
}
