
#define BUF256

struct ringBuf {
    uint8_t *buffer;
    uint8_t writeIndex;
    uint8_t readIndex;
#ifndef BUF256
    unsigned char size;
#endif
};

#define bufDataExist(b) /*((unsigned char)*/(b.readIndex != b.writeIndex)//)

void bufWrite(struct ringBuf *b, uint8_t d);
void bufWriteIntIC1(struct ringBuf *b, uint8_t d);
uint8_t bufRead(struct ringBuf *b);
//unsigned char bufDataExist(struct ringBuf *b);
void bufClear(struct ringBuf *b);
#ifdef BUF256
void bufInit(struct ringBuf *b, uint8_t *buf);
#else
void bufInit(struct ringBuf *b, unsigned char *buf, unsigned char size);
#endif

extern uint8_t irRxBuffer1[];
extern struct ringBuf irRxBuffer;
