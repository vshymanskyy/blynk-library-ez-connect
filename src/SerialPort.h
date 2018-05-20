#ifndef SerialPort_h
#define SerialPort_h

enum PrintMode {
  DEC, HEX
};

extern char* dtostrf_internal(double number, signed char width, unsigned char prec, char *s);

class SerialPort {
public:
    void print(int arg, PrintMode p = DEC) {
        const char* fmt = (p == DEC) ? "%d" : "%x";
        wmprintf(fmt, arg);
    }

    void print(uint32_t arg) {
        wmprintf("%lu", arg);
    }

    void print(size_t arg) {
        wmprintf("%lu", arg);
    }

    void print(long arg) {
        wmprintf("%ld", arg);
    }

    void print(unsigned char arg) {
        wmprintf("%u", arg);
    }

    void print(char arg) {
        wmprintf("%c", arg);
    }

    void print(float arg) {
        wmprintf("%f", arg);
    }

    void print(const char* arg) {
        wmprintf("%s", arg);
    }

    template <typename T>
    void println(T arg) {
        print(arg);
        println();
    }

    void println() {
        wmprintf("\r\n");
    }

    template<class T>
    SerialPort& operator <<(T arg) {
        print(arg);
        return *this;
    }
};

#endif /* SerialPort_h */
