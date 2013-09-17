/***********************************************************
 * photuris_interface.cpp
 *
 * For getting information from the input devicee:
 *    - capacitive switch
 *    - capacitive slider
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/30 - 2013/09/14
 **********************************************************/

#include "photuris_interface.h"

#include "Arduino.h"
#include <photuris_utilities.h>

/*** Sensor Setup ***/
#define slide_MA A2
#define slide_MB A1
#define slide_S0 8
#define slide_S1 1
#define slide_S3 2
#define slide_S6 4
#define slide_S8 1
#define slide_S9 1

CapacitiveSensor csM0 = CapacitiveSensor(slide_MB, slide_MA);
CapacitiveSensor csM1 = CapacitiveSensor(slide_MA, slide_MB);
CapacitiveSensor csS0 = CapacitiveSensor(slide_S9, slide_S0);
CapacitiveSensor csS9 = CapacitiveSensor(slide_S0, slide_S9);
CapacitiveSensor csLL = CapacitiveSensor(slide_S6, slide_S8);
CapacitiveSensor csLR = CapacitiveSensor(slide_S8, slide_S6);
CapacitiveSensor csML = CapacitiveSensor(slide_S3, slide_S6);
CapacitiveSensor csMR = CapacitiveSensor(slide_S6, slide_S3);
CapacitiveSensor csRL = CapacitiveSensor(slide_S1, slide_S3);
CapacitiveSensor csRR = CapacitiveSensor(slide_S3, slide_S1);

/*** Main Switch ***/

// Returns the main switch capacitive sensor (0 - front) analog value.
// @samples - number of times to poll for the main capacitive sensor value.
int getMainSwitchFrontRaw(int samples) {
    int total = 0;
    for(int i = 0; i < samples; i++) {
        pinMode(slide_MA, INPUT);
        pinMode(slide_MB, OUTPUT);
        total += csM0.capacitiveSensor(10);
        delay_us(5);
    }
    return total;
}

// Returns the main switch capacitive sensor (1 - back) analog value.
// @samples - number of times to poll for the main capacitive sensor value.
int getMainSwitchBackRaw(int samples) {
    int total = 0;
    for(int i = 0; i < samples; i++) {
        pinMode(slide_MB, INPUT);
        pinMode(slide_MA, OUTPUT);
        total += csM1.capacitiveSensor(10);
        delay_us(5);
    }
    return total;
}

// Returns the main switch output state (on or off).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which the switch should read logical 1.
bool getMainSwitchState(int threshold, int samples) {
    int front_total = getMainSwitchFrontRaw(samples);
    int back_total = getMainSwitchBackRaw(samples);
    return (front_total > threshold * samples &&
            back_total > threshold * samples);
}

/*** Capacitive Slider ***/

int getSlide0Raw(int samples) {
    int total = 0;
    for(int i = 0; i < samples; i++) {
        pinMode(slide_S0, INPUT);
        pinMode(slide_S9, OUTPUT);
        total += csS0.capacitiveSensor(10);
        delay_us(5);
    }
    return total;
}

int getSlide1Raw(int samples) {
    int total_pos = 0, total_neg;
    for(int i = 0; i < samples; i++) {
        pinMode(slide_S1, INPUT);
        pinMode(slide_S3, OUTPUT);
        total_pos += csRR.capacitiveSensor(10);
        delay_us(5);

        pinMode(slide_S3, INPUT);
        pinMode(slide_S1, OUTPUT);
        total_neg += csLL.capacitiveSensor(10);
        delay_us(5);
    }
    return max(0, total_pos - total_neg);
}

int getSlide9Raw(int samples) {
    int total = 0;
    for(int i = 0; i < samples; i++) {
        pinMode(slide_S9, INPUT);
        pinMode(slide_S0, OUTPUT);
        total += csS9.capacitiveSensor(10);
        delay_us(5);
    }
    return total;
}

int getSlideRaw(char key, int samples) {
    switch(key) {
        case 9:
            return getSlide9Raw(samples);
        case 8:
//            return getSlide8Raw(samples);
        case 7:
//            return getSlide7Raw(samples);
        case 6:
//            return getSlide6Raw(samples);
        case 5:
//            return getSlide5Raw(samples);
        case 4:
//            return getSlide4Raw(samples);
        case 3:
//            return getSlide3Raw(samples);
        case 2:
//            return getSlide2Raw(samples);
        case 1:
            return getSlide1Raw(samples);
        case 0:
            return getSlide0Raw(samples);
        default:
            break;
    }
    return -1;
}

/*
char getActiveSliders(int samples = DEFAULT_SAMPLES) {
  return 0;
}

// Returns which key of slider 0 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition0(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 1 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition1(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 2 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition2(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 3 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition3(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of all sliders is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}
*/

