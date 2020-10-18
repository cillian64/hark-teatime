CPPFLAGS=-I.
MCU=attiny45
all: main.hex

main.elf: main.o 

%.o: %.c
	avr-gcc ${CPPFLAGS} -Os -mmcu=${MCU} -o $@ -c $^

%.elf: %.o
	avr-gcc -Os -mmcu=${MCU} -o $@ $^

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

%.lst: %.elf
	avr-objdump -h -S $^ > $@

clean:
	rm -f *.o *.elf *.hex *.lst


program: main.hex
	./avrdude.exe -p t45 -c usbtiny -e -U flash:w:$^

fuses:
	./avrdude.exe -p t45 -c usbtiny -e -U lfuse:w:0xA2:m
	./avrdude.exe -p t45 -c usbtiny -e -U hfuse:w:0xDF:m

