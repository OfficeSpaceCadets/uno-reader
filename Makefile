
all: build

clean:
	platformio run --target clean

build:
	platformio run

monitor:
	platformio serialports monitor -p /dev/cu.usbmodem1411

upload:
	platformio run --target upload

