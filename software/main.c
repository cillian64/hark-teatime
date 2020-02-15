#include <avr/io.h>
#define F_CPU 1E6 				// 1MHz
#include <util/delay.h>

#define LED_RED PB0
#define LED_YEL PB1
#define LED_GRE PB2
#define TRIGGER PB3
#define BUZZER  PB4

#define ON(PIN) PORTB &= ~(1 << PIN)
#define OFF(PIN) PORTB |= (1 << PIN)

inline setup_pins(void) {
    DDRB |= _BV(LED_RED) | _BV(LED_YEL) | _BV(LED_GRE) | _BV(BUZZER);
    OFF(LED_RED);
    OFF(LED_GRE);
    OFF(LED_YEL);
    OFF(BUZZER);
}

int main(void) {
    char i;
    
    setup_pins();

    while (1) {
        if((PINB & _BV(TRIGGER)) == 0) {
            ON(LED_GRE);
            for(i=0; i<62; i++){
                _delay_ms(1000);
            }
            OFF(LED_GRE);
            ON(LED_YEL);
            for(i=0; i<62; i++){
                _delay_ms(1000);
            }
            OFF(LED_YEL);
            ON(LED_RED);
            for(i=0; i<62; i++){
                _delay_ms(1000);
            }
            OFF(LED_RED);
            ON(BUZZER);
            for(i=0; i<12; i++){
                if(i%2 == 0) {
                    ON(LED_RED);
                    ON(LED_YEL);
                    ON(LED_GRE);
                } else {
                    OFF(LED_RED);
                    OFF(LED_YEL);
                    OFF(LED_GRE);
                }
                _delay_ms(250);
            }
            OFF(BUZZER);
        }
    }
}		



