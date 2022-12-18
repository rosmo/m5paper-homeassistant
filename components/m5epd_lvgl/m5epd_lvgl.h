#ifndef __M5EPD_H
#define __M5EPD_H
#define LGFX_M5PAPER
#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <stdio.h>
#include <inttypes.h>

#include <lvgl.h>
#include <LovyanGFX.hpp>
#include <lgfx/v1_init.hpp>

#define M5EPD_PANEL_W 960
#define M5EPD_PANEL_H 540

// Thanks to: https://gist.github.com/hollyhockberry/492282526896c84b04adc2974ca7affb
class M5_LVGL {
    public:
        LGFX *gfx = NULL;
        static bool initialized;

        M5_LVGL() { };
        bool initialize(int rotation = 0);
        void timer(bool delay = false);

    private:
        lv_disp_draw_buf_t drawBuffer;
        lv_color_t buf[M5EPD_PANEL_H * 10];
        lv_disp_drv_t disp_drv;
        lv_indev_drv_t indev_drv;
};

extern M5_LVGL LVGL;

#endif