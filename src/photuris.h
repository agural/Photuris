/***********************************************************
 * photuris.h
 *
 * For Photuris defines.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/09/03 - 2013/09/03
 **********************************************************/

// Ensure this library description is only included once.
#ifndef photuris_h
#define photuris_h

// Bit operation defines
#define	sbi(port, pbit)	(port) |= (1 << (pbit))
#define	cbi(port, pbit)	(port) &= ~(1 << (pbit))
#define gbi(port, pbit) ((port >> pbit) & 1)

// Processor defines
#ifndef F_CPU
#define	F_CPU 12000000UL
#endif // F_CPU

/*FUSES = {
    .low =	0xD6,
    .high =	0xDD,
    .extended = 0xF9,
};*/

// Photuris defines
#define REFERENCE_VOLTAGE 3.62

// Photuris PORTB pins
#define slide_0 0
#define ctlLEDE 1
#define ctlLEDA 2
#define usbmosi 3
#define usbmiso 4
#define usb_sck 5
#define xtal_s1 6
#define xtal_s2 7

// Photuris PORTC pins
#define slide_9 0
#define mainswO 1
#define mainswI 2
#define xml_pwr 3
#define pot_sda 4
#define pot_scl 5
#define reset_p 6

// Photuris PORTD pins
#define ir_recv 0
#define slide_1 1
#define slide_3 2
#define ctlLEDB 3
#define slide_6 4
#define ctlLEDC 5
#define ctlLEDD 6
#define slide_8 7

// Useful functions
void delay_us(uint16_t count) {
    while(count--) {
        _delay_us(1);
    }
}

void delay_ms(uint16_t count) {
    while(count--) {
        _delay_ms(1);
    }
}

// Bootloading
void (*jump_to_bootloader)(void) = (void (*)())0x1C00; __attribute__ ((unused))

void startBootloader(void) {
    cbi(TIMSK0, TOIE0);
    cli();
    wdt_disable();

    cbi(ADCSRA, ADIE);
    cbi(ADCSRA, ADEN);

    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    jump_to_bootloader();
}

#endif // photuris_h
