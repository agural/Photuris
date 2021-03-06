/*
 * photuris.cpp
 *
 * AVR Studio: 2011/08/26 10:00:00 PM
 * To Arduino: 2011/12/25 01:00:00 PM
 * AGMF03v0.1: 2013/03/05 06:00:00 AM
 * Photuris v0.3: 2013/08/07 09:30:00 AM
 *
 * Author: Albert Gural
 * e: ag@albertgural.com
 * w: http://albertgural.com
 */

#include <math.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Wire.h>

#include "Arduino.h"
#include "photuris.h"
#include <photuris_utilities.h>
#include <photuris_interface.h>

// Global Variables
long displayLED = 0;
int  mode = 0;

/********** CAPACITIVE TOUCH SENSORS **********/
/*
double main_switch(int samples) {
    long total = 0;
    for(int i = 0; i < samples; i++) {
        // Inner Switch
        pinMode(slide_MA, INPUT);
        pinMode(slide_MB, OUTPUT);
        total += csM0.capacitiveSensor(10);
        delay_us(5);

        // Outer Switch
        pinMode(slide_MB, INPUT);
        pinMode(slide_MA, OUTPUT);
        total += csM1.capacitiveSensor(10);
        delay_us(5);
    }
    return total;
}

// Returns 0 for none, 1 for S0, 2 for S1, 3 for S0 and S1.
int button09(int samples, int threshold) {
    long total1 = 0, total2 = 0;
    for(int i = 0; i < samples; i++) {
        // Slide 0
        pinMode(slide_S0, INPUT);
        pinMode(slide_S9, OUTPUT);
        total1 += csS0.capacitiveSensor(10);
        delay_us(5);

        // Slide 9
        pinMode(slide_S9, INPUT);
        pinMode(slide_S0, OUTPUT);
        total2 += csS9.capacitiveSensor(10);
        delay_us(5);
    }
    int result = 0;
    if(total1 >= threshold * samples) sbi(result, 0);
    if(total2 >= threshold * samples) sbi(result, 1);
    return result;
}

// Returns best guess of pressed slider buttons
int sliderButtons(int samples, int threshold) {
    // TODO
    return 0;
}

// Returns best guess of slider position; -1 if no touch detected
double slider(int samples, int threshold) {
    // TODO
    return -1;
}
*/
/*
// Outputs position of slider touch (0 <= x < 32) or -1 if there is no touch
double slider() {
    long total1 = 0, total2 = 0;
    for(int i = 0; i < csSample; i++) {
        pinMode(slide_A, OUTPUT);
        pinMode(slide_B, INPUT);
        total1 += csr.capSense(10);
        delay_us(10);
        pinMode(slide_A, INPUT);
        pinMode(slide_B, OUTPUT);
        total2 += csl.capSense(10);
    }
    if(total1 < csThresh * csSample) return -1;
    double frac = 256.0 * (double)total1 / (total1 + total2);
    return ((frac - 96) / 4);
}
*/


/********** CREE XM-L2 U2 LED DRIVING **********/

#define POT_ADDRESS 0x2A // Address 0b0010101, write 0b0
byte POT_wiper_0 = 0x00; // Address 0b0000, write 0b00, data MSB 0b00
byte POT_wiper_1 = 0x10; // Address 0b0001, write 0b00, data MSB 0b00
byte POT_TCONrs1 = 0x41; // Address 0b0100, write 0b00, data MSB 0b00
byte POT_TCONrs2 = 0xFF; // TCON Data LSB 0b11111111
byte POT_TCONrc1 = 0x40; // Address 0b0100, write 0b00, data MSB 0b00
byte POT_TCONrc2 = 0x00; // TCON Data LSB 0b11111111

void setup_POT() {
    Wire.begin();
    delay(1);
}

void on( byte wipe0,  byte wipe1) {
    Wire.beginTransmission(POT_ADDRESS);
    Wire.write(POT_wiper_0);
    Wire.write(wipe0);
    Wire.write(POT_wiper_1);
    Wire.write(wipe1);
    Wire.write(POT_TCONrs1);
    Wire.write(POT_TCONrs2);
    Wire.endTransmission();
    delay(1);
    pinMode(A3, OUTPUT);
    digitalWrite(A3, 1);
}

void off() {
    Wire.beginTransmission(POT_ADDRESS);
    Wire.write(POT_wiper_0);
    Wire.write(0x00);
    Wire.write(POT_wiper_1);
    Wire.write(0x00);
    Wire.write(POT_TCONrc1);
    Wire.write(POT_TCONrc2);
    Wire.endTransmission();
    digitalWrite(A3, 0);
    delay(1);
    pinMode(A3, INPUT);
}

/********** CONTROL BOARD LED DISPLAY **********/

void led_off(int time) {
    cbi(PORTB, 1);
    cbi(PORTB, 2);
    cbi(PORTD, 3);
    cbi(PORTD, 5);
    cbi(PORTD, 6);
    delay_us(time);
    cbi(DDRB,  1);
    cbi(DDRB,  2);
    cbi(DDRD,  3);
    cbi(DDRD,  5);
    cbi(DDRD,  6);
}

// Turn on control board LEDs.
// Bits 00 - 09: Slider LEDs 0 - 9
// Bits 10 - 10: Main switch LED
// Bits 11 - 14: Main switch surround LEDs
// Bits 15 - 15: IR LED
// Bits 16 - 16: UV LED
// Bits 17 - 19: RGB LEDs
void display_led(unsigned long led, int time, int p) {
    if(time > 1000) time = 1000;  // Limit max time to 1s
    if(p < 0) p = 0;
    if(p > 100) p = 100;
    p /= 2; // Allow input in terms of percentage 0 - 100, convert to 0 - 50us

    for(int i = 0; i < time; i++) {
        wdt_reset();
        if(gbi(led,0)) {
            sbi(DDRD,  3);
            sbi(DDRD,  5);
            sbi(PORTD, 3);
            cbi(PORTD, 5);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,1)) {
            sbi(DDRD,  5);
            sbi(DDRD,  3);
            sbi(PORTD, 5);
            cbi(PORTD, 3);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,2)) {
            sbi(DDRD,  5);
            sbi(DDRB,  2);
            sbi(PORTD, 5);
            cbi(PORTB, 2);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,3)) {
            sbi(DDRD,  5);
            sbi(DDRB,  1);
            sbi(PORTD, 5);
            cbi(PORTB, 1);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,4)) {
            sbi(DDRD,  5);
            sbi(DDRD,  6);
            sbi(PORTD, 5);
            cbi(PORTD, 6);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,5)) {
            sbi(DDRD,  6);
            sbi(DDRD,  5);
            sbi(PORTD, 6);
            cbi(PORTD, 5);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,6)) {
            sbi(DDRD,  6);
            sbi(DDRB,  1);
            sbi(PORTD, 6);
            cbi(PORTB, 1);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,7)) {
            sbi(DDRD,  6);
            sbi(DDRB,  2);
            sbi(PORTD, 6);
            cbi(PORTB, 2);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,8)) {
            sbi(DDRD,  6);
            sbi(DDRD,  3);
            sbi(PORTD, 6);
            cbi(PORTD, 3);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,9)) {
            sbi(DDRD,  3);
            sbi(DDRD,  6);
            sbi(PORTD, 3);
            cbi(PORTD, 6);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,10)) {
            sbi(DDRB,  2);
            sbi(DDRB,  1);
            sbi(PORTB, 2);
            cbi(PORTB, 1);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,11)) {
            sbi(DDRB,  1);
            sbi(DDRB,  2);
            sbi(PORTB, 1);
            cbi(PORTB, 2);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,12)) {
            sbi(DDRB,  1);
            sbi(DDRD,  3);
            sbi(PORTB, 1);
            cbi(PORTD, 3);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,13)) {
            sbi(DDRB,  1);
            sbi(DDRD,  5);
            sbi(PORTB, 1);
            cbi(PORTD, 5);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,14)) {
            sbi(DDRB,  1);
            sbi(DDRD,  6);
            sbi(PORTB, 1);
            cbi(PORTD, 6);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,15)) {
            sbi(DDRD,  3);
            sbi(DDRB,  2);
            sbi(PORTD, 3);
            cbi(PORTB, 2);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,16)) {
            sbi(DDRD,  3);
            sbi(DDRB,  1);
            sbi(PORTD, 3);
            cbi(PORTB, 1);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);

        if(gbi(led,17)) {
            sbi(DDRB,  2);
            sbi(DDRD,  3);
            sbi(PORTB, 2);
            cbi(PORTD, 3);
            delay_us(p/2);
            led_off(50-p/2);
        }
        else led_off(50);

        if(gbi(led,18)) {
            sbi(DDRB,  2);
            sbi(DDRD,  5);
            sbi(PORTB, 2);
            cbi(PORTD, 5);
            delay_us(p/4);
            led_off(50-p/4);
        }
        else led_off(50);

        if(gbi(led,19)) {
            sbi(DDRB,  2);
            sbi(DDRD,  6);
            sbi(PORTB, 2);
            cbi(PORTD, 6);
            delay_us(p);
            led_off(50-p);
        }
        else led_off(50);
    }
}

void setup() {
    cli();

    //WDT
    wdt_enable(WDTO_8S);
    wdt_reset();

    DDRB  = 0b00000000;
    DDRC  = 0b00000000;
    DDRD  = 0b00000000;
    PORTB = 0b00100000;
    PORTC = 0b01110000;
    PORTD = 0b00000000;

    setup_POT();

    //Test: PWM
    //setup_pwm1();
    //pwm1_on();
    //OCR1A = 0x0100;
    //_delay_ms(500);
    //pwm1_off();

    //TCCR2A = 0b00000000;
    //TCCR2B = 0b00000111;
    //TIMSK2 = 0b00000000;

    // Pin-Change Interrupts
    //sbi(PCICR, 0);
    //sbi(PCMSK0, 0);
    //sbi(PCICR, 1);
    //sbi(PCMSK1, 3);

    // Power Saving
    //power_spi_disable();
    //power_timer0_disable();
    //power_twi_disable();
    //power_usart0_disable();

    randomSeed(analogRead(A3));

    sei();
}

void loop() {
    wdt_reset();
    if(analogRead(A3) < 50 && gbi(PINB, 5) && getMainSwitchState(5)) {
        display_led(513, 500, 10);
        startBootloader();
    }

    //int cur_val;
    //int ctr = 0;
    /*while(true) {
        wdt_reset();
        //if(ctr % 10 == 0) cur_val = (int)main_switch_0(20);
        //if(cur_val < 0) cur_val = 0;
        display_led((int)main_switch_0(20) + (1 << 10), 10, 10);
        //ctr++;
    }*/

    /*while(true) {
        wdt_reset();
        for(byte i = 0x20; i <= 0x2F; i += 1) {
            wdt_reset();
            Wire.beginTransmission(i);
            Wire.write(0x00);
            Wire.write(i);
            Wire.write(0x10);
            Wire.write(i);
            //Wire.write(0x40);
            //Wire.write(0xFF);
            Wire.endTransmission();
            display_led(i << 1, 1000, 10);
        }
    }*/

    while(true) {
        wdt_reset();
        //display_led(getSlideRaw(0) << 1, 50, 10);
        display_led((0x5000) | (getMainSwitchFrontRaw() << 1), 50, 10);
        display_led((0x2800) | (getMainSwitchBackRaw() << 1), 50, 10);
    }

    while(true) {
        wdt_reset();
        for(byte brightness = 0; brightness < 201; brightness++) {
            wdt_reset();
            on(brightness, brightness);
            //display_led(1 << batteryLevel(), 10, 10);
            display_led(brightness << 1, 5, 10);
        }
        for(byte brightness = 200; brightness > 0; brightness--) {
            wdt_reset();
            on(brightness, brightness);
            //display_led(1 << batteryLevel(), 10, 10);
            display_led(brightness << 1, 5, 10);
        }
        on(0,0);
        display_led(-1, 500, 25);
        /*display_led(512, 250, 10);
        display_led(((int)(10 * getBatteryVoltage())) << 1, 500, 10);
        display_led(1, 250, 10);
        display_led(getBatteryPercent() << 1, 500, 10);
        display_led(getTemperature() << 1, 500, 10);
        display_led(1023, 100, 10);*/
        for(byte brightness = 0; brightness < 255; brightness++) {
            wdt_reset();
            on(brightness, 0);
            display_led(512 + (brightness << 1), 10, 10);
        }
        for(byte brightness = 255; brightness > 0; brightness--) {
            wdt_reset();
            on(brightness, 0);
            display_led(1 + (brightness << 1), 10, 10);
        }
        off();
        display_led((0x5000) | (getTemperature() << 1), 500, 10);
        display_led((0x2800) | (getBatteryPercent() << 1), 500, 10);
        display_led(1023, 500, 10);
        if(getBatteryPercent() < 50) {
            while(getBatteryPercent() < 60) {
                display_led(1023, 250, 10);
                display_led(getBatteryPercent(), 250, 10);
            }
        }
    }
    /*
    while(true) {
        wdt_reset();
        display_led(1 << batteryLevel(), 50, 10);
    }

    int leds = 0;
    int rbit = 0;
    while(true) {
        wdt_reset();
        rbit = random(10);
        gbi(leds, rbit) ? cbi(leds, rbit) : sbi(leds, rbit);
        display_led(leds, 100, 10);
    }*/

    int j = 0;
    unsigned long i = 1;
    while(true) {
        wdt_reset();
        j %= 20;
        display_led(i << j, 50, 10);
        j++;
    }

    //pwm1_on();

    /* Test: ADC
    int adcIN = analogRead(A0);
    OCR1B = fmax(0, fmin(65535, (square((adcIN + 1) / 32.0) + pow(2.0, (adcIN + 1) / 64.0) - 1 - M_SQRT2)));
    PORTD = OCR1B >> 8;
    */


    //OCR1A = 0x0100;
    /*
    int ctrled = 0;

    while(1) {
        wdt_reset();
        ctrled += 1;
        sbi(PORTB, wxml_u2); // Woops... this maps to burst mode ><
        if(ctrled % 100 < 10) sbi(PORTC, xml_pwr);
        else cbi(PORTC, xml_pwr);

        //OCR1A = 0x0100;
        //OCR1B = 0x1000;
        // Test: CapSense
        double sVal = slider();
        //PORTD = sVal;
        if(sVal >= 16) OCR1B = 0xFFFF;
        else if(sVal != -1) OCR1B = (uint16_t)pow(2,sVal);

        if(ctrled % 100 < 80) {
            if(sVal == -1) {
                // OCR1B = 0x0000;
                cbi(PORTD, rgbl_rl);
                sbi(PORTD, rgbl_gl);
            }
            else {
                cbi(PORTD, rgbl_gl);
                sbi(PORTD, rgbl_rl);
            }
        }
        else {
            sbi(PORTD, rgbl_rl);
            sbi(PORTD, rgbl_gl);
            cbi(PORTD, rgbl_bl);
        }

        if(ctrled % 100 < 20) {
            sbi(PORTC, irl_pos);
            cbi(PORTC, irl_neg);
            sbi(PORTD, rgbl_bl);
        }
        else if(ctrled % 100 < 40) {
            cbi(PORTC, irl_pos);
            sbi(PORTC, uvl_pos);
        }
        else if(ctrled % 100 < 80) {
            cbi(PORTC, uvl_pos);
        }

    }
    */
}

