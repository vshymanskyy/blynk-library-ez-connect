extern "C" {
  #include <wm_os.h>
  #include <wmstdio.h>
  #include <wmtime.h>
  #include <wmsdk.h>
  #include <board.h>

  #include "runtime.h"
}

#define WIFI_SSID          "structure7"
#define WIFI_PASS          "lebowski8"

#define BLYNK_AUTH         "5f7a98878c8946c78574a8883b427f4c"

#include <SerialPort.h>

SerialPort serial;

#define BLYNK_PRINT serial
//#define BLYNK_DEBUG

#include <BlynkSimpleMW300.h>

volatile bool wifiConnected = false;

void wlan_event_normal_link_lost(void *data)
{
    wmprintf("wlan_event_normal_link_lost() has been invoked \r\n");
    wifiConnected = false;
}

void wlan_event_normal_connect_failed(void *data)
{
    wmprintf("wlan_event_normal_connect_failed() has been invoked \r\n");
    wifiConnected = false;
}

/* This function gets invoked when station interface connects to home AP.
 * Network dependent services can be started here.
 */
void wlan_event_normal_connected(void *data)
{
    wifiConnected = true;
}


extern "C"
int main()
{
    do_global_ctors();

    if (wmstdio_init(UART0_ID, 0) != WM_SUCCESS) {
        return -WM_FAIL;
    }

    Blynk.begin(BLYNK_AUTH);

    wmprintf("Build Time: " __DATE__ " " __TIME__ "\r\n");

    while(true) {
        if (!wifiConnected) {
          wmprintf("Connecting to %s...\n", WIFI_SSID);
          wm_wlan_connect(WIFI_SSID, WIFI_PASS);
          while (!wifiConnected) {
            os_thread_sleep(os_msec_to_ticks(1000));
            wmprintf(".");
          }
        }

        Blynk.run();
        os_thread_sleep(os_msec_to_ticks(1));
    }
    return 0;
}
