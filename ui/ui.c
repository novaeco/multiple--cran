#include "ui.h"
#include <lvgl.h>
#include "battery.h"

static lv_obj_t *bar_batt;

static void btn_event_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_label_set_text(lv_obj_get_child(btn, 0), "Pressé");
}

static void battery_timer_cb(lv_timer_t *t)
{
    battery_update();
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
    lv_coord_t w = lv_disp_get_hor_res(NULL);
    lv_obj_t *slider = lv_slider_create(cont);
    lv_obj_set_width(slider, w - 40);

    /* Bouton simple */
    lv_obj_t *btn = lv_btn_create(cont);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "OK");

    /* Barre de niveau batterie */
    bar_batt = lv_bar_create(cont);
    lv_obj_set_width(bar_batt, w - 40);
    lv_bar_set_range(bar_batt, 0, 100);
    lv_bar_set_value(bar_batt, battery_get_percent(), LV_ANIM_OFF);

    /* Rafraîchissement périodique du niveau batterie */
    lv_timer_create(battery_timer_cb, 2000, NULL);

}
