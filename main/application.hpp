
#include "m5epd_lvgl.h"

#ifndef __APPLICATION_H
#define __APPLICATION_H

class Application {
    public:
        Application() { 
        };
        ~Application() {
            if (screen != NULL) {
                lv_obj_del(screen);
            }
        };

        virtual bool init() { return false; };
        virtual bool setup() { return false; }
        virtual void run() { };
        
        void createScreen() {
             screen = lv_obj_create(NULL);
        };
        void show() {
            ::lv_scr_load(screen);
        };
    protected:
        lv_obj_t *screen = NULL;
};

class HelloWorldApplication : Application {
    public:
        bool init();
        bool setup();
        void run();
};
#endif