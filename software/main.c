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
    char i;

    OFF(RCLK);
    for(i = 0; i < 32; i++){
        OFF(SCLK);
        if(i == sec || (32-block) <= i) {
            OFF(SER);
        } else {
            ON(SER);
        }
        ON(SCLK);
    }
    ON(RCLK);
    OFF(SCLK);
    OFF(RCLK);
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

void arg_delay_ms(int n) {
    while(n--) {
        _delay_ms(1);
    }
}

int main(void) {
    char total;
    char inner;
    char i;
    int step_delay[32] = {30, 31, 32, 33, 34, 35, 37, 38, 40, 41, 43, 45, 47, 50, 52, 55, 58, 62, 66, 71, 76, 83, 90, 100, 111, 125, 142, 166, 200, 250, 333, 500};
    char step_post[32] = {10, 8, 8, 10, 14, 20, 1, 12, 0, 16, 11, 10, 13, 0, 12, 10, 14, 8, 10, 6, 12, 4, 10, 0, 1, 0, 6, 4, 0, 0, 1, 0};
    
    setup_pins();

    while(1) {
        for(total = 0; total < 32; total++) {
            for(inner = 0; inner < 10; inner++) {
                arg_delay_ms(step_post[total]);   
                for(i = -1; i < (32-total); i++) {
                    display(i, total);
                    arg_delay_ms(step_delay[total]);
                }
            }
        }
        for(i = 0; i < 5; i++) {
            display(-1,32);
            buzz500ms();
            display(-1,0);
            _delay_ms(500);
        }
        sleep_forever();
    }
}		



