#include "application.hpp"

bool HelloWorldApplication::init() {
    LVGL.initialize();
    return true;
}

bool HelloWorldApplication::setup() {
    createScreen();

    lv_obj_t *rootContainer = lv_obj_create(screen);
    lv_obj_align(rootContainer, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_size(rootContainer, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(rootContainer, LV_FLEX_FLOW_COLUMN);

    static lv_style_t st;
    ::lv_style_set_text_color(&st, ::lv_color_black());
    ::lv_style_set_text_font(&st, &lv_font_montserrat_38);
    ::lv_obj_add_style(screen, &st, 0);

    lv_obj_t *label = ::lv_label_create(rootContainer);
    ::lv_label_set_text(label, "Hello World from LVGL!");
    ::lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *slider = ::lv_slider_create(rootContainer);
    ::lv_obj_set_width(slider, LV_PCT(95));
    ::lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);
//    lv_obj_add_event_cb(slider1, slider_event_cb, LV_EVENT_ALL, NULL);
    //::lv_obj_refresh_ext_draw_size(slider);

    return true;
}

void HelloWorldApplication::run() {
    show();
    printf("Tick period MS: %d\n", portTICK_PERIOD_MS);
    while (true) {
        LVGL.timer(false);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}