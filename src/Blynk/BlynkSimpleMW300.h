/**
 * @file       BlynkSimpleMW300.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2018 Volodymyr Shymanskyy
 * @date       Jun 2018
 * @brief      Marvell EZ-Connect MW300/302 Wi-Fi
 *
 */

#ifndef BlynkSimpleMW300
#define BlynkSimpleMW300

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "MW300"
#endif

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <utility/BlynkFifo.h>

#define LWIP_COMPAT_SOCKETS 0
#include <lwip/netdb.h>
#include <lwip/sockets.h>

class BlynkTransportMW300
{
public:
    BlynkTransportMW300()
        : mSockID (-1)
    {
    }

    void begin(char BLYNK_UNUSED *h, uint16_t BLYNK_UNUSED p) {}

    bool connect() {
        disconnect();

        int16_t status;

        const char domain[64] = "test.blynk.cc";
        unsigned port = 80;
        
        BLYNK_LOG2("Connecting to ", domain);

        hostent* host = lwip_gethostbyname(domain);

        if (NULL != host) {
          sockaddr_in dest_addr;
          dest_addr.sin_family = AF_INET;
          dest_addr.sin_port = htons(port);
          dest_addr.sin_addr.s_addr = *(long*) (host->h_addr);
          memset(&(dest_addr.sin_zero), '\0', 8);

          int sock = lwip_socket(AF_INET, SOCK_STREAM, 0);
          if (sock < 0) return false;

          if (lwip_connect(sock, (sockaddr*) &dest_addr, sizeof(sockaddr)) < 0) {
            lwip_close(sock);
            return false;
          }
          BLYNK_LOG1("Connected");
          mSockID = sock;
          
          int NONBLOCK = 1;
          lwip_ioctl(mSockID, FIONBIO, &NONBLOCK);
          
          int enable = 1;
          lwip_setsockopt(mSockID, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
        }


        return connected();
    }

    void disconnect() {
        if (connected()) {
            mBuffRX.clear();
            lwip_close(mSockID);
            mSockID = -1;
            BLYNK_LOG1("Disconnected");
        }
    }

    bool connected() {
        return mSockID >= 0;
    }

    size_t read(void* buf, size_t len) {
        if (available() < len) return 0;

        return mBuffRX.get((uint8_t*)buf, len);
    }

    size_t write(const void* buf, size_t len) {
        if (!connected()) return 0;

        int bytesTx = lwip_send(mSockID, buf, len, 0);
        if (bytesTx < 0) {
            disconnect();
            return 0;
        }
        return bytesTx;
    }

    size_t available() {
        if (!connected()) return 0;

        uint8_t buf[64];
        while (mBuffRX.free() >= sizeof(buf)) {
            int ret = lwip_recv(mSockID, buf, sizeof(buf), 0);
            if (ret > 0) {
                mBuffRX.put(buf, ret);
            } else if (ret < 0) {
                //BLYNK_LOG2("lwip_recv:", ret);
                break;
            } else if (ret == 0) {
                disconnect();
                break;
            }
        }

        return mBuffRX.size();
    }

private:

    int mSockID;
    BlynkFifo<uint8_t, BLYNK_MAX_READBYTES> mBuffRX;
};

class BlynkUserDefined
    : public BlynkProtocol<BlynkTransportMW300>
{
    typedef BlynkProtocol<BlynkTransportMW300> Base;
public:
    BlynkUserDefined(BlynkTransportMW300& transp)
        : Base(transp)
    {}

    void begin(const char* auth)
    {
        Base::begin(auth);
    }

private:
};

static BlynkTransportMW300 _blynkTransport;
BlynkUserDefined Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
