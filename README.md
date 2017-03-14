# POST /bank Hackathon Roadshow Medal

This repository contains hardware documentation (Eagle files and PDF) and firmware sources (C) for the medals given to winners at the POST /bank hackathon series 2016/2017 Grand Final.

The actual boards given out differ in two points:
- MCU ground connections (Pins 5 and 41) are missing on the board due to a PCB manufacturing error. They are manually routed using wire.
- Due to a worldwide supply shortage of TBD62083 drivers, the boards are populated with a TBD62003 chip (7 channels instead of 8). The remaining channel is populated with a 2N7000 NMOS on top of the TBD62003.

The board has pads for a resistive and a capacitive touch sensor, however, they are not used in the current firmware.

The firmware is based on the everykey SDK (see https://github.com/presseverykey/everykey-sdk for prerequisites, toolchain setup and more examples). Basically, an ARM GCC cross compiler and a firmware checksum tool is required. The MCU supports flashing via USB mass storage in ROM, so no additional flashing hardware is required. The firmware binary can be just copied over. To enable flashing mode, press the button while inserting the board to a USB port (add 0.5-1mm of cardboard or similar under the PCB for a stable connection). Some OSes will mount the drive directly, some require an additional reset. If required, a MCU reset can be triggered by connecting the corresponding pad of R5 to GND, e.g. using metal tweezers.
