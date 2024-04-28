####### BEGINNING #######

#COMMANDS
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

#SETTINGS
MCU = atmega328p # nom du device
SERIAL = /dev/ttyUSB0 # port USB
UART_BAUDRATE = 115200
BAUDRATE =  115200 # unite de mesure du nombre de symbole transmissibles par secondes
PROGRAMMER = arduino # 
F_CPU = 16000000UL #frequence CPU


# Options de compilation
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
# -Os : optimisation

SRCS += main.c
SRCS += adc.c
SRCS += i2c_management.c
SRCS += uart_management.c
SRCS += timer_init.c
SRCS += captor.c

BIN = $(SRCS:.c=.bin)

ALLHEX = $(SRCS:.c=.hex)

# Règle par défaut
all: hex flash

# Règle pour compiler et générer le fichier hex
hex: $(ALLHEX)

%.bin: %.c
	$(CC) $(CFLAGS) $(SRCS) -o main.bin

%.hex: %.bin
	$(OBJCOPY) -R .eeprom -O ihex main.bin main.hex

# Règle pour flasher le microcontrôleur
flash:
	@killall screen 2>/dev/null || true
	$(AVRDUDE) -p $(MCU) -P $(SERIAL) -c $(PROGRAMMER) -b $(BAUDRATE) -U flash:w:main.hex

# Règle pour nettoyer les fichiers temporaires
clean:
	rm -f main.hex main.bin

PHONY : hex all clean flash bin