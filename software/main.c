#include <avr/io.h>
#define F_CPU 1E6 				// 1MHz
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define RCLK PB0
#define SCLK PB1
#define SER PB2
#define BUZZER  PB4

#define OFF(PIN) PORTB &= ~(1 << PIN)
#define ON(PIN) PORTB |= (1 << PIN)

inline void setup_pins(void) {
    DDRB |= _BV(RCLK) | _BV(SCLK) | _BV(SER) | _BV(BUZZER) | _BV(PB3);
    OFF(RCLK);
    OFF(SCLK);
    OFF(SER);
    OFF(PB3);
    OFF(BUZZER);
}

inline void display(char sec, char block) {
    char init_off;
    char mid_off;
    char i;

    if(sec < 2) {
        init_off = 0;
    } else {
        init_off = sec - 1;
    }

    if(sec > 0 && sec <= (32 - block)) {
        mid_off = 32 - block - init_off - 1;
    } else {
        mid_off = 32 - block;
    }

    OFF(RCLK);
    if(sec > 0 && sec <= (32 - block)){
        for(i = 0; i < init_off; i++){
            OFF(SCLK);
            ON(SER);
            ON(SCLK);
        }
        OFF(SCLK);
        OFF(SER);
        ON(SCLK);
    }
    for(i = 0; i < mid_off; i++){
        OFF(SCLK);
        ON(SER);
        ON(SCLK);
    }
    for(i = 0; i < block; i++){
        OFF(SCLK);
        OFF(SER);
        ON(SCLK);
    }
    ON(RCLK);
}

inline void sleep_forever() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    sleep_enable();
    sleep_bod_disable();
    sei();
    sleep_cpu();
}

static inline void buzz500ms() {
    char c1, c2;
    for(c1 = 0; c1 < 127; c1++) {
        for(c2 = 0; c2 < 8; c2++) {
            ON(BUZZER);
            _delay_us(250);
            OFF(BUZZER);
            _delay_us(250);
        }
    }
}

int main(void) {
    char total;
    char inner;
    char i;
    
    setup_pins();

    while(1) {
        for(total = 0; total < 32; total++) {
            for(inner = 0; inner < 10; inner++) {
                for(i = 1; i < 33; i++) {
                    display(i, total);
                    _delay_ms(31);
                }
                _delay_ms(8);   
            }
        }
        for(i = 0; i < 5; i++) {
            display(0,32);
            buzz500ms();
            display(0,0);
            _delay_ms(500);
        }
        sleep_forever();
    }
}		



