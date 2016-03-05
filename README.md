#uno-reader#

Arduino based RFID reader.

Starting point came from [this blog](http://devsketches.blogspot.com/2014/05/rfid-sensor-funduino-rfid-rc522.html).

###Prerequisites###

Install PlatformIO:

    $ brew install platformio

This will install the *platformio* command line tool.

###Build###

Run the build:

    $ platformio run
    
Install the build on a connected board:

    $ platformio run --target upload

###Output###

To view the output from the *Serial.println* statements:

Find out what port the Arduino device is listening on:

    $ platformio serialports list

Listen to the specific port:

    $ platformio serialports monitor -p /dev/cu.usbmodem1411

Terminating the listening is CTR+]

    