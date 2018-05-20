
exec-y += blynk

blynk-objs-y := src/main.cpp src/runtime.cpp \
		src/Blynk/utility/BlynkDebug.cpp \
		src/Blynk/utility/BlynkHandlers.cpp \
		src/Blynk/utility/BlynkTimer.cpp \
		src/Blynk/utility/utility.cpp

blynk-cflags-y := -I$(d)/src/Blynk -I$(d)/src -DMW300

blynk-lflags-y := -lsupc++_nano

blynk-cflags-y+= -DMAX_SOCKETS_TCP=$(CONFIG_MAX_SOCKETS_TCP)
blynk-cflags-y+= -DMAX_LISTENING_SOCKETS_TCP=$(CONFIG_MAX_LISTENING_SOCKETS_TCP)
blynk-cflags-y+= -DMAX_SOCKETS_UDP=$(CONFIG_MAX_SOCKETS_UDP)
blynk-cflags-y+= -DTCP_SND_BUF_COUNT=$(CONFIG_TCP_SND_BUF_COUNT)
blynk-cflags-y+= -DTCPIP_STACK_TX_HEAP_SIZE=$(CONFIG_TCPIP_STACK_TX_HEAP_SIZE)
