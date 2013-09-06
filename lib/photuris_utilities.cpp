/***********************************************************
 * photuris_utilities.cpp
 *
 * For getting information from Photuris utility sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/07 - 2013/09/04
 **********************************************************/

#include <math.h>
#include <avr/io.h>

#include "Arduino.h"
#include "photuris.h"
#include "photuris_utilities.h"

/*** Useful Functions ***/

void delay_us(int count) {
    while(count > 100) {
        _delay_us(100);
        count -= 100;
    }
    while(count > 10) {
        _delay_us(10);
        count -= 10;
    }
    while(count > 0) {
        _delay_us(1);
        count -= 1;
    }
}

void delay_ms(int count) {
    while(count > 100) {
        _delay_us(100);
        count -= 100;
    }
    while(count > 10) {
        _delay_ms(10);
        count -= 10;
    }
    while(count > 0) {
        _delay_ms(1);
        count -= 1;
    }
}

/*** Bootloading ***/

void (*jump_to_bootloader)(void) = (void (*)())0x1C00; __attribute__ ((unused))

void startBootloader(void) {
    cbi(TIMSK0, TOIE0);
    cbi(ADCSRA, ADIE);
    cbi(ADCSRA, ADEN);
    cli();
    wdt_disable();

    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    jump_to_bootloader();
}

/*** Battery Utilities ***/

// Returns the current battery voltage in volts.
// Fully charged: 4.2V
// Nominal voltage: 3.3V - 3.7V
// Fully discharged: 2.7V
// Connected to charger: -1V
float getBatteryVoltage() {
    cbi(DDRC, 3);

    // 238.14 = 1024 [Full ADC Range] * 10/43 [Resistor Divider]
    const float kVoltageConvert = REFERENCE_VOLTAGE / 238.14;
    float voltage = kVoltageConvert * (float)analogRead(A3);
    if(voltage < 1.0) voltage = -1.0;

    delay(1);
    sbi(DDRC, 3);
    return voltage;
}

// Returns the theoretical (modeled) voltage you would expect after using a
// given fraction of the total charge of the battery.
// @usage - Fraction of the battery's charge used [0..1].
/*float getVoltageFromUsage(float usage) {
    // This formula is based on the AW IMR discharge curve.
    float voltage = 4.2 - 0.32 * log(8 * usage + 1) - exp(30 * (usage - 1));
    return voltage;
}*/

float getUsageFromVoltage(float voltage) {
    float v0 = 1;
    float v1 = v0 * v1;
    float v2 = v1 * v1;
    float v3 = v2 * v1;
    if(voltage < 2.5) {
        return -1;
    }
    if(voltage < 3.42566) {
        return 0.220054 * v3 - 1.87041 * v2 + 5.33235 * v1 - 5.08348;
    }
    if(voltage < 3.55914) {
        return 46.2142 * v3 - 476.7 * v2 + 1639.37 * v1 - 1879.54;
    }
    if(voltage < 4.2) {
        return 1.85736 * v3 - 23.3898 * v2 + 98.6768 * v1 - 138.452;
    }
    return 1.0;
}

/*
// Returns the percent charge of the battery [0..100] or -1 if charging.
// Uses a Li-Ion IMR discharge curve to approximate energy percentage
// (as opposed to just using the direct voltage level).
int getBatteryPercent() {
    const float kPrecision = 0.005;
    float pLower = 0.0, pUpper = 1.0;
    float voltage = getBatteryVoltage();
    if(voltage < 2.5) return -1;
    while(pUpper - pLower > kPrecision) {
        float pMiddle = (pLower + pUpper) / 2;
        // getVoltageFromUsage is monotonically decreasing so if it's too large,
        // we should use the upper range.
        if(getVoltageFromUsage(pMiddle) > voltage) {
            pLower = pMiddle;
        } else {
            pUpper = pMiddle;
        }
    }
    return (int)(pLower * 100);
}*/

int getBatteryPercent() {
    float voltage = getBatteryVoltage();
    float usage = getUsageFromVoltage(voltage);
    if(usage < 0) return -1;
    return 100 * usage;
}

// Returns true if currently charging and false otherwise.
// This can also be used to determine whether the device is connected to USB.
bool isCharging() {
    return getBatteryVoltage() < 0;
}

/*** Temperature Utilities ***/

// Returns the raw ADC output for a temperature sample.
int chipTempRaw(void) {
    ADCSRA |= _BV(ADSC);
    while((ADCSRA & _BV(ADSC)));
    return (ADCL | (ADCH << 8));
}

// Returns the current temperature in *C.
// Very high: 50*C
// High: 45*C
float getTemperature() {
    int kTempSamples = 100;
    float avg = 0.0;
    ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
    delay(10);
    chipTempRaw();

    for(int i = 1; i < kTempSamples; i++) {
        avg += chipTempRaw();
    }
    avg /= kTempSamples;

    // Interestingly, the value of average is very close to the actual
    // temperature in kelvin. Too bad it's not exact.
    avg = 1.01 * avg - 272;
    return avg;
}

/*** System Utilities ***/

// Checks the voltage and temperature to see if everything's ok.
// The return value gives the current status:
// Quaternary output AB where A gives battery status and B gives temperature.
// For A:
//      * 0: Battery OK!
//      * 1: Plugged in / no battery
//      * 2: Battery low
//      * 3: Battery critically low
// For B:
//      * 0: Temperature OK!
//      * 1: Temperature high
//      * 2: Temperature critically high
//      * 3: Temperature critically low
/*int systemCheck() {
    // TODO
    return 0;
}*/

