# blynk-library-ez-connect
Blynk example for Marvell® EZ-Connect™ MW302

![demo](https://github.com/vshymanskyy/blynk-library-ez-connect/raw/master/demo.png)

## Getting Started

1. Download and install [Marvell's EZ-Connect Lite SDK](https://github.com/marvell-iot/ez-connect-lite)
2. Download this example, put it in `blynk-library-ez-connect` subfolder of SDK root
2. Navigate to SDK root: `cd ez-connect-lite`
4. Build example: `make APP=blynk-library-ez-connect clean all -j9`
5. Flash it to the board: `sudo python sdk/tools/OpenOCD/flashprog.py --mcufw ./bin/mw302_rd/blynk.bin`
