#include "m5epd_lvgl.h"

bool M5_LVGL::initialized = false;
lgfx::Panel_IT8951 *p = new lgfx::Panel_IT8951();
lgfx::Touch_GT911 *t = new lgfx::Touch_GT911();

void displayFlush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    LGFX *_gfx = (LGFX *)disp->user_data;

    const u_long w = area->x2 - area->x1 + 1;
    const u_long h = area->y2 - area->y1 + 1;
    _gfx->startWrite();
    _gfx->setAddrWindow(area->x1, area->y1, w, h);
    _gfx->writePixels(static_cast<uint16_t *>(&color_p->full), w * h, true);
    _gfx->endWrite();

    ::lv_disp_flush_ready(disp);
}


void touchInput(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    LGFX *_gfx = (LGFX *)drv->user_data;
    lgfx::touch_point_t tp;
    std::uint8_t count;
    static std::int32_t x, y;
    
    count = _gfx->getTouch(&tp);
    //printf("Touch screen results: count=%d, tx=%d, ty=%d, id=%d, size=%d\n", count, tp.x, tp.y, tp.id, tp.size);
    if (count > 0)
    {
        data->point.x = tp.x;
        data->point.y = tp.y;
        data->state = LV_INDEV_STATE_PR;
        x = tp.x;
        y = tp.y;
    } else {
        data->point.x = x;
        data->point.y = y;
        data->state = LV_INDEV_STATE_REL;
    }
}

void M5_LVGL::timer(bool delay) {
    ::lv_task_handler();
    ::lv_timer_handler();
    if (delay) {
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

void vApplicationTickHook() {
    ::lv_tick_inc(1000 / CONFIG_FREERTOS_HZ);
}


bool M5_LVGL::initialize(int rotation) {
    gfx = new LGFX();
    if (!gfx->init()) {
        printf("LovyanGFX initialization failed!\n");
        return false;
    }
    gfx->touch()->wakeup();
    gfx->setEpdMode(epd_mode_t::epd_quality);  
    // gfx->setRotation(rotation);

    ::lv_init();
    ::lv_disp_draw_buf_init(&drawBuffer, buf, NULL, M5EPD_PANEL_H * 10);

    // Initial screen
    ::lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = M5EPD_PANEL_H;
    disp_drv.ver_res = M5EPD_PANEL_W;
    disp_drv.flush_cb = displayFlush;
    disp_drv.draw_buf = &drawBuffer;
    disp_drv.user_data = (void *)gfx; 
    ::lv_disp_drv_register(&disp_drv);

    // Initialize touch screen input
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchInput;
    indev_drv.user_data = (void *)gfx;
    ::lv_indev_drv_register(&indev_drv);

    initialized = true;
    return initialized;
}

M5_LVGL LVGL;