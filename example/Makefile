

all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o sst.o sst.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tick_tsk.o tick_tsk.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o queue.o queue.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o semaphore.o semaphore.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o uart.o uart.c
	avr-gcc -mmcu=atmega328p main.c -o main sst.o tick_tsk.o queue.o semaphore.o uart.o
	avr-objcopy -O ihex -R .eeprom main main.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex
