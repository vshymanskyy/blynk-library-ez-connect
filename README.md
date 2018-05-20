# blynk-library-ez-connect
Blynk example for Marvell® EZ-Connect™ MW302

![demo](https://github.com/vshymanskyy/blynk-library-ez-connect/raw/master/demo.png)

## Getting Started

Here are the instructions for AWS IoT Starter Kit on Linux. Feel free to adjust them to your board and OS.

1. Download and install [Marvell's EZ-Connect Lite SDK](https://github.com/marvell-iot/ez-connect-lite)
2. Download this example, put it in `blynk-library-ez-connect` subfolder of SDK root
3. Register your Blynk account and create a Project, so you get a Blynk Auth Token
2. In `src/main.cpp`, adjust `WIFI_SSID`, `WIFI_PASS` and `BLYNK_AUTH`
2. Navigate to SDK root: `cd ez-connect-lite`
4. Build: `make APP=blynk-library-ez-connect clean all -j9`
5. Flash: `sudo python sdk/tools/OpenOCD/flashprog.py --mcufw ./bin/mw302_rd/blynk.bin`
6. Open serial console: `cu -l /dev/ttyUSB1 -s 115200`. (Hint: type `~.` when you want close it)
7. Done. Reset the board to start the firmware
