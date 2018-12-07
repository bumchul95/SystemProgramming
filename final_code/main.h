#ifndef __MAIN_H__
#define __MAIN_H__

#define BED_TOUCH_DEV_PATH "/dev/bed_touch_dev"
#define PIL_TOUCH_DEV_PATH "/dev/pil_touch_dev"
#define BUZZER_DEV_PATH "/dev/buzzer_dev"
#define SOUND_DEV_PATH "/dev/sound_dev"
#define BUTTON_DEV_PATH "/dev/button_dev"
#define MOTOR_DEV_PATH "/dev/motor_dev"
#define LED_DEV_PATH "/dev/led_dev"

pthread_t thread;
pthread_t btn_thread;

static int touch_flag = 0;
static int sleep_flag = 0;
static int wakeup_flag = 0;
static int window_flag = 1;
static int button_flag = 0;
static int moodlight_flag = 1;

char s1[10] = "off";
char s2[10] = "on";

#endif
